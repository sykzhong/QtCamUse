#include "GlobalHeader.h"

QImage Mat2QImage(Mat &src)
{
	const uchar *pSrc = (const uchar*)src.data;
	// Create QImage with same dimensions as input Mat  
	QImage image(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888);
	return image.rgbSwapped();
}

Mat QImage2Mat(QImage &src)
{
	cv::Mat mat;
	switch (src.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(src.height(), src.width(), CV_8UC4, (void*)src.constBits(), src.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(src.height(), src.width(), CV_8UC3, (void*)src.constBits(), src.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(src.height(), src.width(), CV_8UC1, (void*)src.constBits(), src.bytesPerLine());
		break;
	}
	return mat;
}