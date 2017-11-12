#include "Tool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Tool w;
	w.SetTextToList(a.arguments());
	w.setWindowTitle(QString("NormalMap Generator"));
	w.setFixedSize(QSize(1280, 720));
	w.show();
	return a.exec();
}
