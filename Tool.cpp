#include "Tool.h"
#include "qfiledialog.h"
#include "qtextcodec.h"
#include "qdrag.h"
#include "qevent.h"
#include "qmimedata.h"

//TODO : テクスチャサイズに合わせてスケーリングする
//TODO : プレビュー機能を強化(拡縮移動等)
//TODO : もう少しコードをきれいにする

Tool::Tool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// バッファリングをしないようにする
	setAttribute(Qt::WA_PaintOnScreen, true);
	// ハンドラの再利用を禁止する
	setAttribute(Qt::WA_NativeWindow, true);
	//ドラッグアンドドロップを受け付ける
	setAcceptDrops(true);
	//DirectXの初期化
	Lobelia::Bootup();
	auto& glWidget = ui.openGLWidget;
	//スワップチェイン作成
	Lobelia::Math::Vector2 scale(glWidget->size().width(), glWidget->size().height());
	swapChain = std::make_unique<Lobelia::Graphics::SwapChain>(reinterpret_cast<HWND>(glWidget->winId()), scale, DXGI_SAMPLE_DESC{ 1,0 });
	view = std::make_unique<Lobelia::Graphics::View>(Lobelia::Math::Vector2(0, 0), scale);
	view->SetEyePos(Lobelia::Math::Vector3(0, 30, 0));
	view->SetEyeTarget(Lobelia::Math::Vector3(0, 0, 30));
	view->SetEyeUpDirection(Lobelia::Math::Vector3(0, 1, 0));
	installEventFilter(this);
	//描画更新を走らせるために60FPS分のタイマーイベントを走らせている
	startTimer(16);
	//ウィジェットのアクションをつなげる
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(FileOpen()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(FileSave()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ComputeNormalMap()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(SettingReset()));
	//ショートカット登録
	ui.actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	ui.actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	ui.pushButton_2->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
	//初期値代入
	amplitude = f_cast(ui.doubleSpinBox->value());
	//ファイルが開かれていないのでnullptr
	isOpen = false; normal = nullptr; diffuse = nullptr;
	//とりあえず非活性化
	DeactivateApplicationWidget();
	SwitchDiffuse();
}
Tool::~Tool() {
	//DirectX終了
	Lobelia::Shutdown();
};
void Tool::SetTextToList(QStringList list) {
	foreach(QString str, list) {
		std::string path = str.toStdString();
		if (Lobelia::Graphics::TextureFileAccessor::JudgeExtension(path.c_str()) == Lobelia::Graphics::TextureFileAccessor::Extension::NO_SUPPORT)continue;
		LoadFile(str);
		break;
	}
}

void Tool::ActivateApplicationWidget() {
	ui.doubleSpinBox->setEnabled(true);
	ui.pushButton->setEnabled(true);
	ui.red->setEnabled(true);
	ui.green->setEnabled(true);
	ui.blue->setEnabled(true);
	ui.alpha->setEnabled(true);
	ui.luminance->setEnabled(true);
	ui.default_radio->setEnabled(true);
	ui.mirror_u->setEnabled(true);
	ui.mirror_v->setEnabled(true);
	ui.invert_vector->setEnabled(true);
	ui.compute_occlusion->setEnabled(true);
	ui.progressBar->setEnabled(true);
	ui.actionSave->setEnabled(true);
	ui.pushButton_2->setEnabled(true);
	ui.diffuse_change->setEnabled(true);
	ui.diffuse_change_2->setEnabled(true);
}
void Tool::DeactivateApplicationWidget() {
	ui.doubleSpinBox->setDisabled(true);
	ui.pushButton->setDisabled(true);
	ui.red->setDisabled(true);
	ui.green->setDisabled(true);
	ui.blue->setDisabled(true);
	ui.alpha->setDisabled(true);
	ui.luminance->setDisabled(true);
	ui.default_radio->setDisabled(true);
	ui.mirror_u->setDisabled(true);
	ui.mirror_v->setDisabled(true);
	ui.invert_vector->setDisabled(true);
	ui.compute_occlusion->setDisabled(true);
	ui.progressBar->setDisabled(true);
	ui.actionSave->setDisabled(true);
	ui.default_radio->setDisabled(true);
	ui.pushButton_2->setDisabled(true);
	ui.diffuse_change->setDisabled(true);
	ui.diffuse_change_2->setDisabled(true);
}
//引数でパスを受け取るようにする
void Tool::LoadFile(QString& path) {
	ui.progressBar->setValue(0);
	renderer = std::make_unique<Lobelia::Graphics::Sprite>(path.toLocal8Bit().toStdString().c_str());
	ui.progressBar->setValue(60);
	diffuse = renderer->GetMaterial()->GetTexture();
	ui.progressBar->setValue(90);
	isOpen = true;
	ui.progressBar->setValue(100);
	normal.reset();
	SwitchDiffuse();
}
void Tool::PictureScalingRender() {
	Lobelia::Graphics::Transform2D transform = {};
	auto& glWidget = ui.openGLWidget;
	//描画領域サイズ
	Lobelia::Math::Vector2 renderRectScale(glWidget->size().width(), glWidget->size().height());
	if (!diffuse)return;
	//画像サイズ
	Lobelia::Math::Vector2 imageScale = diffuse->GetSize();
	//拡縮比
	Lobelia::Math::Vector2 ratio(renderRectScale.x / imageScale.x, renderRectScale.y / imageScale.y);
	//x,yどちらのほうがフレームの限界に近いか調べる
	if (ratio.x < ratio.y) {
		//xのほうが近い場合
		transform.scale = imageScale*ratio.x;
		//画像をちょうど真ん中に配置
		float bias = renderRectScale.y - transform.scale.y;
		transform.position.y = bias / 2;
	}
	else {
		//yのほうが近い場合
		transform.scale = imageScale*ratio.y;
		//画像をちょうど真ん中に配置
		float bias = renderRectScale.x - transform.scale.x;
		transform.position.x = bias / 2;
	}
	transform.rotation = 0.0f;
	renderer->Render(transform, Lobelia::Math::Vector2(), renderer->GetMaterial()->GetTexture()->GetSize(), 0xFFFFFFFF);
}
void Tool::RendererChangeDiffuse() {
	SwitchDiffuse();
	if (!diffuse)return;
	renderer->GetMaterial()->ChangeTexture(diffuse);
}
void Tool::RendererChangeNormal() {
	SwitchNormal();
	if (!normal)return;
	renderer->GetMaterial()->ChangeTexture(normal.get());
}
void Tool::SwitchDiffuse() {
	ui.diffuse_change->setChecked(true);
	isDiffuse = true;
}

void Tool::SwitchNormal() {
	ui.diffuse_change_2->setChecked(true);
	isDiffuse = false;
}
void Tool::Update() {
	static bool enable = false;
	//アクティブになった瞬間
	if (!enable&&isOpen) ActivateApplicationWidget();
	//ファイルが開かれたらアクティブ
	if (isOpen) enable = true;
	//描画の切り替え
	if (renderer&&ui.diffuse_change->isChecked() != isDiffuse) {
		if (isDiffuse) {
			RendererChangeNormal();
			isDiffuse = false;
		}
		else {
			RendererChangeDiffuse();
			isDiffuse = true;
		}
	}
	if (normal)ui.diffuse_change_2->setDisabled(false);
	else ui.diffuse_change_2->setDisabled(true);
}
void Tool::Render() {
	view->Activate();
	swapChain->Clear(0xFF000000);
	if (renderer) PictureScalingRender();
	swapChain->Present();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//override
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Tool::eventFilter(QObject* obj, QEvent* event) {
	Update();
	Render();
	if (event->type() == QEvent::ShortcutOverride)	return true;
	return false;
}
void Tool::dragEnterEvent(QDragEnterEvent* event) {
	QString path = event->mimeData()->text();
	if (Lobelia::Graphics::TextureFileAccessor::JudgeExtension(path.toStdString().c_str()) == Lobelia::Graphics::TextureFileAccessor::Extension::NO_SUPPORT)return;
	event->acceptProposedAction();
}
void Tool::dropEvent(QDropEvent *event) {
	QString path = event->mimeData()->urls().first().toLocalFile();
	if (Lobelia::Graphics::TextureFileAccessor::JudgeExtension(path.toStdString().c_str()) == Lobelia::Graphics::TextureFileAccessor::Extension::NO_SUPPORT)return;
	ui.progressBar->setValue(0);
	LoadFile(path);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//slots
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tool::ComputeNormalMap() {
	if (!isOpen)return;
	DeactivateApplicationWidget();
	ui.progressBar->setValue(0);
	amplitude = f_cast(ui.doubleSpinBox->value());
	ui.progressBar->setValue(10);

	DWORD flags = DirectX::CNMAP_DEFAULT;
	if (ui.default_radio->isChecked())flags |= DirectX::CNMAP_DEFAULT;
	else if (ui.red->isChecked())flags |= DirectX::CNMAP_CHANNEL_RED;
	else if (ui.green->isChecked())flags |= DirectX::CNMAP_CHANNEL_GREEN;
	else if (ui.blue->isChecked())flags |= DirectX::CNMAP_CHANNEL_BLUE;
	else if (ui.alpha->isChecked())flags |= DirectX::CNMAP_CHANNEL_ALPHA;
	else if (ui.luminance->isChecked())flags |= DirectX::CNMAP_CHANNEL_LUMINANCE;
	if (ui.mirror_u->isChecked())flags |= DirectX::CNMAP_MIRROR_U;
	if (ui.mirror_v->isChecked())flags |= DirectX::CNMAP_MIRROR_V;
	if (ui.invert_vector->isChecked())flags |= DirectX::CNMAP_INVERT_SIGN;
	if (ui.compute_occlusion->isChecked())flags |= DirectX::CNMAP_COMPUTE_OCCLUSION;
	ui.progressBar->setValue(30);

	if (!normal)normal = std::make_unique<Lobelia::Graphics::Texture>(diffuse->GetSize(), DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE, DXGI_SAMPLE_DESC{ 1,0 });

	Lobelia::Graphics::TextureFileAccessor::CreateNormalMap(diffuse, normal.get(), amplitude, flags);
	ui.progressBar->setValue(90);
	renderer->GetMaterial()->ChangeTexture(normal.get());
	ui.progressBar->setValue(100);
	ActivateApplicationWidget();
	SwitchNormal();
}
void Tool::FileOpen() {
	ui.progressBar->setValue(0);
	QString path = QFileDialog::getOpenFileName(this, "Open File", "", tr("WIC Format (*.png;*.jpg;*.bmp);;TGA Format (*.tga);;All Files (*)"));
	if (path.isEmpty())return;
	ui.progressBar->setValue(10);
	LoadFile(path);
}
void Tool::FileSave() {
	if (!isOpen && normal)return;
	ui.progressBar->setValue(0);
	QString path = QFileDialog::getSaveFileName(this, "Save File", "", tr("WIC Format (*.png;*.jpg;*.bmp);;TGA Format (*.tga);;All Files (*)"));
	if (path.isEmpty())return;
	ui.progressBar->setValue(30);
	Lobelia::Graphics::TextureFileAccessor::Save(path.toLocal8Bit().data(), normal.get());
	ui.progressBar->setValue(100);
}
void Tool::SettingReset() {
	ui.progressBar->setValue(0);
	ui.default_radio->setChecked(true);
	ui.mirror_u->setChecked(false);
	ui.mirror_v->setChecked(false);
	ui.invert_vector->setChecked(false);
	ui.compute_occlusion->setChecked(false);
	ui.progressBar->setValue(100);
	amplitude = -15.0f;
}
