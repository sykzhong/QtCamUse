#include <QtWidgets/QApplication>
#include "QtCamUse.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("GB2312");//���1
	QTextCodec::setCodecForLocale(codec);
	MainWindow w;
	//û�з����豸
	if (!w.status) {
		return 1;
	}

	w.show();
	return a.exec();
}
