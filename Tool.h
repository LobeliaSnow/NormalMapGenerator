#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tool.h"
#include "Lobelia/Lobelia.hpp"

class Tool : public QMainWindow {
	Q_OBJECT
private:
	Ui::ToolClass ui;
	std::unique_ptr<Lobelia::Graphics::SwapChain> swapChain;
	std::unique_ptr<Lobelia::Graphics::View> view;
	std::unique_ptr<Lobelia::Graphics::Sprite> renderer;
	Lobelia::Graphics::Texture* diffuse;
	std::unique_ptr<Lobelia::Graphics::Texture> normal;
	float amplitude;
	bool isOpen;
	bool isDiffuse;
public:
	Tool(QWidget *parent = Q_NULLPTR);
	~Tool();
public:
	void SetTextToList(QStringList list);
private:
	void ActivateApplicationWidget();
	void DeactivateApplicationWidget();
	void LoadFile(QString& path);
	void PictureScalingRender();
	void RendererChangeDiffuse();
	void RendererChangeNormal();
	void SwitchDiffuse();
	void SwitchNormal();
private:
	void Update();
	void Render();
public:
	bool eventFilter(QObject* obj, QEvent* event)override;
	void dragEnterEvent(QDragEnterEvent* event)override;
	void dropEvent(QDropEvent *event)override;
private:
	public slots : void ComputeNormalMap();
	public slots:  void FileOpen();
	public slots:  void FileSave();
	public slots:  void SettingReset();

};
