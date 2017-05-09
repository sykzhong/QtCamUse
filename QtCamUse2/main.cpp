#include <QtWidgets/QApplication>
#include "QtCamUse.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("GB2312");//情况1
	QTextCodec::setCodecForLocale(codec);
	MainWindow w;
	//没有发现设备
	if (!w.status) {
		return 1;
	}

	w.show();
	return a.exec();
}
