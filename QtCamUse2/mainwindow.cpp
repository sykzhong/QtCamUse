#include "mainwindow.h"
#include "ui_QtCamUse.h"
#include "capturethread.h"
#include <stdio.h>
#include <QFile>
#include <QFileDialog>

int                     g_hCamera = -1;     //�豸���
unsigned char           * g_pRawBuffer = NULL;     //raw����
unsigned char           * g_pRgbBuffer = NULL;     //��������ݻ�����
tSdkFrameHead           g_tFrameHead;       //ͼ��֡ͷ��Ϣ
tSdkCameraCapbility     g_tCapability;      //�豸������Ϣ

int                     g_SaveParameter_num = 0;    //���������
int                     g_SaveImage_type = 0;         //����ͼ���ʽ

Width_Height            g_W_H_INFO;         //��ʾ���嵽��С��ͼ���С
BYTE                    *g_readBuf = NULL;    //������ʾ������
int                     g_read_fps = 0;       //ͳ�ƶ�ȡ֡��
int                     g_disply_fps = 0;     //ͳ����ʾ֡��

/*
*  SDK�ȳ�ʼ������
*
*
*/
int MainWindow::init_SDK()
{

	int                     iCameraCounts = 4;
	int                     iStatus = -1;
	tSdkCameraDevInfo       tCameraEnumList[4];

	//sdk��ʼ��  0 English 1����
	CameraSdkInit(1);

	//ö���豸���������豸�б�
	CameraEnumerateDevice(tCameraEnumList, &iCameraCounts);

	//û�������豸
	if (iCameraCounts == 0) {
		return -1;
	}

	//�����ʼ������ʼ���ɹ��󣬲��ܵ����κ����������صĲ����ӿ�
	iStatus = CameraInit(&tCameraEnumList[0], -1, -1, &g_hCamera);

	//��ʼ��ʧ��
	if (iStatus != CAMERA_STATUS_SUCCESS) {
		return -1;
	}
	//�����������������ṹ�塣�ýṹ���а�������������õĸ��ֲ����ķ�Χ��Ϣ����������غ����Ĳ���
	CameraGetCapability(g_hCamera, &g_tCapability);

	g_pRgbBuffer = (unsigned char*)malloc(g_tCapability.sResolutionRange.iHeightMax*g_tCapability.sResolutionRange.iWidthMax * 3);
	g_readBuf = (unsigned char*)malloc(g_tCapability.sResolutionRange.iHeightMax*g_tCapability.sResolutionRange.iWidthMax * 3);

	/*��SDK���빤��ģʽ����ʼ��������������͵�ͼ��
	���ݡ������ǰ����Ǵ���ģʽ������Ҫ���յ�
	����֡�Ժ�Ż����ͼ��    */
	CameraPlay(g_hCamera);

	/*
	����ͼ����������ʽ����ɫ�ڰ׶�֧��RGB24λ
	*/
	if (g_tCapability.sIspCapacity.bMonoSensor) {
		CameraSetIspOutFormat(g_hCamera, CAMERA_MEDIA_TYPE_MONO8);
	}
	else {
		CameraSetIspOutFormat(g_hCamera, CAMERA_MEDIA_TYPE_RGB8);
	}
	return 0;
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QtCamUseClass), m_scene(0), m_image_item(0)
{
	if (init_SDK() == -1) {
		status = 0;
		return;
	}
	ui->setupUi(this);
	m_scene = new QGraphicsScene(this);
	ui->gvMain->setScene(m_scene);

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(camera_statues()));
	m_timer->start(1000);

	m_thread = new CaptureThread(this);
	//start task thread
	connect(m_thread, SIGNAL(captured(QImage)),
		this, SLOT(Image_process(QImage)), Qt::BlockingQueuedConnection);

	m_camera_statuesFps = new QLabel(this);
	m_camera_statuesFps->setAlignment(Qt::AlignHCenter);
	ui->statusBar->addWidget(m_camera_statuesFps);

	GUI_init_Resolution(g_hCamera, &g_tCapability);			//����ʼ�����б�δֱ��ѡ���ֱ���
	GUI_init_parameter(g_hCamera, &g_tCapability);


	m_thread->start();
	m_thread->stream();
	status = 1;
}

MainWindow::~MainWindow()
{
	delete ui;
}

/*
*  ���״̬��
*
*
*/

void MainWindow::camera_statues()
{
	m_camera_statuesFps->setText(QString("Capture fps: %1  Display fps :%2").arg(QString::number(g_read_fps, 'f', 2)).arg(QString::number(g_disply_fps, 'f', 2)));
	g_read_fps = 0;
	g_disply_fps = 0;
}

/*
*  ͼ����ʾˢ�´���
*
*
*/

void MainWindow::Image_process(QImage img)
{

	if (m_thread->quit)
	{
		return;
	}


	if (m_image_item)
	{
		m_scene->removeItem(m_image_item);
		delete m_image_item;
		m_image_item = 0;
	}

	m_image_item = m_scene->addPixmap(QPixmap::fromImage(img));

	m_scene->setSceneRect(0, 0, img.width(), img.height());
	//m_scene->setSceneRect(0, 0, 800, 600);


	g_disply_fps++;

}

/*
*�ֱ��ʵ�����
*
*
*/
int  MainWindow::GUI_init_Resolution(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	int                     i = 0;
	tSdkImageResolution     *pImageSizeDesc = pCameraInfo->pImageSizeDesc;// Ԥ��ֱ���ѡ��
	int                     iImageSizeDesc = pCameraInfo->iImageSizeDesc; // Ԥ��ֱ��ʵĸ�������pImageSizeDesc����Ĵ�С
    //windows ����
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	for (i = 0;i<iImageSizeDesc;i++) {
		ui->res_combobox->addItem(QString("%1").arg(pImageSizeDesc[i].acDescription));
	}
	return 1;
}

int MainWindow::GUI_init_parameter(int hCamera, tSdkCameraCapbility *pCamerInfo)
{
	GUI_set_Resolution(hCamera, pCamerInfo);
	return 0;
}

int MainWindow::GUI_set_Resolution(int hCamera, tSdkCameraCapbility *pCameraInfo)
{
	tSdkImageResolution *pImageSizeDesc = pCameraInfo->pImageSizeDesc;		//Ԥ��ֱ���
	tSdkImageResolution sResolution;	//��ȡ��ǰ���õķֱ���
	
	CameraGetImageResolution(hCamera, &sResolution);

	g_W_H_INFO.sensor_width = pImageSizeDesc[sResolution.iIndex].iWidth;
	g_W_H_INFO.sensor_height = pImageSizeDesc[sResolution.iIndex].iHeight;
	g_W_H_INFO.buffer_size = g_W_H_INFO.sensor_width * g_W_H_INFO.sensor_height;

	ui->res_combobox->setCurrentIndex(sResolution.iIndex);
	return 1;
}