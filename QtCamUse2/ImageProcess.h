#ifndef _IMAGEPROCESS_H_
#define _IMAGEPROCESS_H_
#include "GlobalHeader.h"
#include "capturethread.h"
#include "HSVHist.h"
class ImageProcess:QObject
{
	Q_OBJECT
public:
	void getImage();
	void getBackImage(BYTE *pbImgBuffer, int width, int height);
	void getBackImage(char* filename);
	void getTemplateImage();
	void processImage();
	Mat QImage2Mat(QImage &image);

private:
	Mat srcImage;
	Mat backImage;

private slots:
	void slot_get_template_image(QImage);
	void slot_get_back_image(QImage);
};

#endif