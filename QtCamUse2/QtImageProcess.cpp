#include "QtImageProcess.h"
#include "QtCamUse.h"
extern int                  g_hCamera;          //设备句柄
extern unsigned char        * g_pRawBuffer;     //raw数据
extern unsigned char        * g_pRgbBuffer;     //处理后数据缓存区
extern tSdkFrameHead        g_tFrameHead;       //图像帧头信息
extern tSdkCameraCapbility  g_tCapability;      //设备描述信息

extern int                     g_SaveParameter_num;    //保存参数组
extern int                     g_SaveImage_type;         //保存图像格式

extern Width_Height            g_W_H_INFO;         //显示画板到大小和图像大小
extern BYTE                    *g_readBuf;    //画板显示数据区
extern int                     g_read_fps;       //统计读取帧率
extern int                     g_disply_fps;     //统计显示帧率

QtImageProcess::QtImageProcess() :
	src(new ProImage), back(new ProImage)
{
	
}

QtImageProcess::~QtImageProcess()
{
	delete src;
	delete back;
}

void QtImageProcess::getBackImageFromPath(char* filename)
{
	m_backImage = imread(filename);
	return;
}

void QtImageProcess::getTemplateImageFromPath(char* filename)
{
	m_templateImage = imread(filename);
	return;
}

void QtImageProcess::processImage()
{
	src->getImage(m_templateImage);
	back->getImage(m_backImage);
	m_showImage = HSVHist::removeBack(*src, *back);
	emit proResult(Mat2QImage(m_showImage));
	src->getContour();
	src->setImageWin("");
	src->initWin();
}

//Mat ImageProcess::QImage2Mat(QImage &image)
//{
//	Mat tmpmat;
//	//qDebug() << image.format();
//	switch (image.format())
//	{
//	case QImage::Format_ARGB32:
//	case QImage::Format_RGB32:
//	case QImage::Format_ARGB32_Premultiplied:
//		tmpmat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
//		break;
//	case QImage::Format_RGB888:
//		tmpmat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
//		cv::cvtColor(tmpmat, tmpmat, CV_BGR2RGB);
//		break;
//	case QImage::Format_Indexed8:
//		tmpmat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
//		break;
//	}
//	return tmpmat;
//}

bool QtImageProcess::isReady()
{
	if (m_backImage.empty() != true && m_templateImage.empty() != true)
		return true;
	else
		return false;
}

void QtImageProcess::slot_receive_mouse_event(int x, int y, int event)
{
	src->proMouseEvent(x, y, event);
	emit proResult(Mat2QImage(src->transProResult()));
}