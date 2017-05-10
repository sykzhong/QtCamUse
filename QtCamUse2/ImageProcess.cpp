#include "ImageProcess.h"

void ImageProcess::getImage()
{
	
}

void ImageProcess::processImage()
{
	HSVHist src, back;
	src.getImage(srcImage);
	back.getImage(backImage);

	HSVHist::removeBack(src, back);


}

void ImageProcess::slot_get_template_image(QImage image)
{
	srcImage = Mat();
	srcImage = QImage2Mat(image);
}

void ImageProcess::slot_get_back_image(QImage image)
{
	backImage = Mat();
	backImage = QImage2Mat(image);
}

Mat ImageProcess::QImage2Mat(QImage &image)
{
	Mat tmpmat;
	//qDebug() << image.format();
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		tmpmat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		tmpmat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(tmpmat, tmpmat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		tmpmat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return tmpmat;
}
