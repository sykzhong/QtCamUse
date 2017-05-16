#ifndef _QTIMAGEPROCESS_H_
#define _QTIMAGEPROCESS_H_
#include "GlobalHeader.h"
#include "capturethread.h"
#include "HSVHist.h"
#include "ProImage.h"
class QtImageProcess:public QObject, public HSVHist
{
	Q_OBJECT
public:
	QtImageProcess();
	~QtImageProcess();
	void getBackImageFromPath(char* filename);
	void getTemplateImageFromPath(char* filename);
	void getTemplateImage();
	void processImage();
	//Mat QImage2Mat(QImage &image);
	bool isReady();

private:
	Mat m_templateImage;
	Mat m_backImage;
	Mat m_showImage;

	ProImage *src;
	ProImage *back;

signals:
	void proResult(QImage);

public slots:
	void slot_receive_mouse_event(int, int, int);
};

#endif