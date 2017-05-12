#include "ImageProcess.h"
#include "QtCamUse.h"
extern int                  g_hCamera;          //�豸���
extern unsigned char        * g_pRawBuffer;     //raw����
extern unsigned char        * g_pRgbBuffer;     //��������ݻ�����
extern tSdkFrameHead        g_tFrameHead;       //ͼ��֡ͷ��Ϣ
extern tSdkCameraCapbility  g_tCapability;      //�豸������Ϣ

extern int                     g_SaveParameter_num;    //���������
extern int                     g_SaveImage_type;         //����ͼ���ʽ

extern Width_Height            g_W_H_INFO;         //��ʾ���嵽��С��ͼ���С
extern BYTE                    *g_readBuf;    //������ʾ������
extern int                     g_read_fps;       //ͳ�ƶ�ȡ֡��
extern int                     g_disply_fps;     //ͳ����ʾ֡��

void ImageProcess::getBackImage(BYTE *pbImgBuffer, int width, int height)
{
	//�ڴ����������⣬������
	BYTE* pmat;
	memcpy(pmat, pbImgBuffer, height*width * 3);
	backImage = Mat(Size(width, height), CV_8UC3, pmat, Mat::AUTO_STEP);
	return;
}

void ImageProcess::getBackImage(char* filename)
{
	backImage = imread(filename);
	return;
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
