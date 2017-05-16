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
}

//Mat QtImageProcess::QImage2Mat(QImage &image)
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
	int index = 0;							//轮廓索引值，正值表示存在轮廓
	if (y < 0 || y >= src->srcimage.rows || x < 0 || x >= src->srcimage.cols)
		return;
	for (int i = 0; i <src->vecImageCon.size(); i++)
	{
		if (src->vecImageCon[i].value_image.at<uchar>(y, x) != 0)
		{
			index = src->vecImageCon[i].value_image.at<uchar>(y, x);
			break;
		}
	}
	switch (event)
	{
	case QT_MOUSE_LBUTTONDOWN:		//左键单击，则对所选轮廓的颜色、状态进行相应更改
		if (index > 0)
		{
			int &_flag = src->vecImageCon[index - 1].flag;
			_flag++;
			if (_flag >= sizeof(ImageCon::g_color) / sizeof(Scalar))
				_flag = 0;
			src->vecImageCon[index - 1].updateColor();
		}
		src->showState();
		break;
	case QT_MOUSE_MOVE:
		cout << src->sykcheck.at<Vec3b>(y, x) << endl;
		if (index > 0)
		{
			src->highlightImage(index - 1);
			src->selectindex = index;
		}
		else
		{
			if (src->selectindex != -1)
			{
				src->lowlightImage(src->selectindex - 1);
				src->selectindex = -1;
			}
		}
		break;
	case QT_MOUSE_RBUTTONDOWN:
		if (index > 0)
		{
			if (index - 1 != src->angleindex)
			{
				/***更新proimage的angleindex***/
				src->vecImageCon[src->angleindex].angleflag = 0;
				src->angleindex = index - 1;
				src->vecImageCon[src->angleindex].angleflag = 1;
				src->showState();
			}
			break;
		}
	}
}