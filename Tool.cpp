#include "Tool.h"
#include "qfiledialog.h"
#include "qtextcodec.h"
#include "qdrag.h"
#include "qevent.h"
#include "qmimedata.h"

//TODO : �e�N�X�`���T�C�Y�ɍ��킹�ăX�P�[�����O����
//TODO : �v���r���[�@�\������(�g�k�ړ���)
//TODO : ���������R�[�h�����ꂢ�ɂ���

Tool::Tool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// �o�b�t�@�����O�����Ȃ��悤�ɂ���
	setAttribute(Qt::WA_PaintOnScreen, true);
	// �n���h���̍ė��p���֎~����
	setAttribute(Qt::WA_NativeWindow, true);
	//�h���b�O�A���h�h���b�v���󂯕t����
	setAcceptDrops(true);
	//DirectX�̏�����
	Lobelia::Bootup();
	auto& glWidget = ui.openGLWidget;
	//�X���b�v�`�F�C���쐬
	Lobelia::Math::Vector2 scale(glWidget->size().width(), glWidget->size().height());
	swapChain = std::make_unique<Lobelia::Graphics::SwapChain>(reinterpret_cast<HWND>(glWidget->winId()), scale, DXGI_SAMPLE_DESC{ 1,0 });
	view = std::make_unique<Lobelia::Graphics::View>(Lobelia::Math::Vector2(0, 0), scale);
	view->SetEyePos(Lobelia::Math::Vector3(0, 30, 0));
	view->SetEyeTarget(Lobelia::Math::Vector3(0, 0, 30));
	view->SetEyeUpDirection(Lobelia::Math::Vector3(0, 1, 0));
	installEventFilter(this);
	//�`��X�V�𑖂点�邽�߂�60FPS���̃^�C�}�[�C�x���g�𑖂点�Ă���
	startTimer(16);
	//�E�B�W�F�b�g�̃A�N�V�������Ȃ���
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(FileOpen()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(FileSave()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ComputeNormalMap()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(SettingReset()));
	//�V���[�g�J�b�g�o�^
	ui.actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	ui.actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	ui.pushButton_2->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
	//�����l���
	amplitude = f_cast(ui.doubleSpinBox->value());
	//�t�@�C�����J����Ă��Ȃ��̂�nullptr
	isOpen = false; normal = nullptr; diffuse = nullptr;
	//�Ƃ肠�����񊈐���
	DeactivateApplicationWidget();
	SwitchDiffuse();
}
Tool::~Tool() {
	//DirectX�I��
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
//�����Ńp�X���󂯎��悤�ɂ���
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
	//�`��̈�T�C�Y
	Lobelia::Math::Vector2 renderRectScale(glWidget->size().width(), glWidget->size().height());
	if (!diffuse)return;
	//�摜�T�C�Y
	Lobelia::Math::Vector2 imageScale = diffuse->GetSize();
	//�g�k��
	Lobelia::Math::Vector2 ratio(renderRectScale.x / imageScale.x, renderRectScale.y / imageScale.y);
	//x,y�ǂ���̂ق����t���[���̌��E�ɋ߂������ׂ�
	if (ratio.x < ratio.y) {
		//x�̂ق����߂��ꍇ
		transform.scale = imageScale*ratio.x;
		//�摜�����傤�ǐ^�񒆂ɔz�u
		float bias = renderRectScale.y - transform.scale.y;
		transform.position.y = bias / 2;
	}
	else {
		//y�̂ق����߂��ꍇ
		transform.scale = imageScale*ratio.y;
		//�摜�����傤�ǐ^�񒆂ɔz�u
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
	//�A�N�e�B�u�ɂȂ����u��
	if (!enable&&isOpen) ActivateApplicationWidget();
	//�t�@�C�����J���ꂽ��A�N�e�B�u
	if (isOpen) enable = true;
	//�`��̐؂�ւ�
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
