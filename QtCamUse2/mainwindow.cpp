#include "mainwindow.h"
#include "ui_QtCamUse.h"
#include "capturethread.h"
#include <stdio.h>
#include <QFile>
#include <QFileDialog>

int                     g_hCamera = -1;     //设备句柄
unsigned char           * g_pRawBuffer = NULL;     //raw数据
unsigned char           * g_pRgbBuffer = NULL;     //处理后数据缓存区
tSdkFrameHead           g_tFrameHead;       //图像帧头信息
tSdkCameraCapbility     g_tCapability;      //设备描述信息

int                     g_SaveParameter_num = 0;    //保存参数组
int                     g_SaveImage_type = 0;         //保存图像格式

Width_Height            g_W_H_INFO;         //显示画板到大小和图像大小
BYTE                    *g_readBuf = NULL;    //画板显示数据区
int                     g_read_fps = 0;       //统计读取帧率
int                     g_disply_fps = 0;     //统计显示帧率

/*
*  SDK等初始化操作
*
*
*/
int MainWindow::init_SDK()
{

	int                     iCameraCounts = 4;
	int                     iStatus = -1;
	tSdkCameraDevInfo       tCameraEnumList[4];

	//sdk初始化  0 English 1中文
	CameraSdkInit(1);

	//枚举设备，并建立设备列表
	CameraEnumerateDevice(tCameraEnumList, &iCameraCounts);

	//没有连接设备
	if (iCameraCounts == 0) {
		return -1;
	}

	//相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
	iStatus = CameraInit(&tCameraEnumList[0], -1, -1, &g_hCamera);

	//初始化失败
	if (iStatus != CAMERA_STATUS_SUCCESS) {
		return -1;
	}
	//获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数
	CameraGetCapability(g_hCamera, &g_tCapability);

	g_pRgbBuffer = (unsigned char*)malloc(g_tCapability.sResolutionRange.iHeightMax*g_tCapability.sResolutionRange.iWidthMax * 3);
	g_readBuf = (unsigned char*)malloc(g_tCapability.sResolutionRange.iHeightMax*g_tCapability.sResolutionRange.iWidthMax * 3);

	/*让SDK进入工作模式，开始接收来自相机发送的图像
	数据。如果当前相机是触发模式，则需要接收到
	触发帧以后才会更新图像。    */
	CameraPlay(g_hCamera);

	/*
	设置图像处理的输出格式，彩色黑白都支持RGB24位
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

	GUI_init_Resolution(g_hCamera, &g_tCapability);			//仅初始化了列表未直接选定分辨率
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
*  相机状态栏
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
*  图像显示刷新处理
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
*分辨率的设置
*
*
*/
int  MainWindow::GUI_init_Resolution(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	int                     i = 0;
	tSdkImageResolution     *pImageSizeDesc = pCameraInfo->pImageSizeDesc;// 预设分辨率选择
	int                     iImageSizeDesc = pCameraInfo->iImageSizeDesc; // 预设分辨率的个数，即pImageSizeDesc数组的大小
    //windows 编码
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
	tSdkImageResolution *pImageSizeDesc = pCameraInfo->pImageSizeDesc;		//预设分辨率
	tSdkImageResolution sResolution;	//获取当前设置的分辨率
	
	CameraGetImageResolution(hCamera, &sResolution);

	g_W_H_INFO.sensor_width = pImageSizeDesc[sResolution.iIndex].iWidth;
	g_W_H_INFO.sensor_height = pImageSizeDesc[sResolution.iIndex].iHeight;
	g_W_H_INFO.buffer_size = g_W_H_INFO.sensor_width * g_W_H_INFO.sensor_height;

	ui->res_combobox->setCurrentIndex(sResolution.iIndex);
	return 1;
}