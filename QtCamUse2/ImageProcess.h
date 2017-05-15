#ifndef _IMAGEPROCESS_H_
#define _IMAGEPROCESS_H_
#include "GlobalHeader.h"
#include "capturethread.h"
#include "HSVHist.h"
#include "ProImage.h"
class ImageProcess:public QObject, public HSVHist
{
	Q_OBJECT
public:
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

signals:
	void proResult(QImage);

private slots:

};

#endif