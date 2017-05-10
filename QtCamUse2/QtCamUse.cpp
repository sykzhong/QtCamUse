#include "QtCamUse.h"
#include "ui_QtCamUse.h"
#include "capturethread.h"
#include <stdio.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>


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
	ui(new Ui::QtCamUseClass), 
	m_scene(0), 
	m_image_item(0), 
	m_QtCamUse_move_window(0),
	b_child_window(FALSE),
	b_pause(FALSE)
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

	ui->radioButton_para_A->setChecked(true);

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
	connect(ui->res_combobox, SIGNAL(QComboBox::activated(int)), this, SLOT(slot_res_combobox_activated(int)));
	return 1;
}

int MainWindow::GUI_init_parameter(int hCamera, tSdkCameraCapbility *pCameraInfo)
{
	GUI_set_Resolution(hCamera, pCameraInfo);
	GUI_init_Trigger(hCamera, pCameraInfo);
	GUI_init_exposure(hCamera, pCameraInfo);
	GUI_init_isp(hCamera, pCameraInfo);
	GUI_init_WB(hCamera, pCameraInfo);
	CameraSetFrameSpeed(g_hCamera, 2);			//将相机的采集帧率设为高速
	
	
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

void MainWindow::slot_res_combobox_activated(int index)
{

	tSdkImageResolution   *pImageSizeDesc = g_tCapability.pImageSizeDesc;// 预设分辨率选择

	g_W_H_INFO.sensor_width = pImageSizeDesc[index].iWidth;
	g_W_H_INFO.sensor_height = pImageSizeDesc[index].iHeight;
	g_W_H_INFO.buffer_size = g_W_H_INFO.sensor_width*g_W_H_INFO.sensor_height;


	if (pImageSizeDesc[index].iWidthZoomSw) {
		g_W_H_INFO.sensor_width = pImageSizeDesc[index].iWidthZoomSw;
		g_W_H_INFO.sensor_height = pImageSizeDesc[index].iHeightZoomSw;
	}

	if (g_W_H_INFO.sensor_width < g_W_H_INFO.display_width) {
		g_W_H_INFO.xOffsetFOV = (g_W_H_INFO.display_width - g_W_H_INFO.sensor_width) / 2;
	}
	else {
		g_W_H_INFO.xOffsetFOV = 0;
	}
	if (g_W_H_INFO.sensor_height < g_W_H_INFO.display_height) {
		g_W_H_INFO.yOffsetFOV = (g_W_H_INFO.display_height - g_W_H_INFO.sensor_height) / 2;
	}
	else {
		g_W_H_INFO.yOffsetFOV = 0;
	}
	m_thread->pause();
	//设置预览的分辨率。
	CameraSetImageResolution(g_hCamera, &(pImageSizeDesc[index]));
	m_thread->stream();
	//ui->gvMain->scale(1/1.5,1/1.5);
}

int MainWindow::GUI_init_Trigger(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	/*
	未为自动曝光模式设置抗频闪等功能
	*/
	int pbySnapMode;
	int StrobeMode = 0;
	int uPolarity = 0;
	//获得相机的触发模式
	CameraGetTriggerMode(hCamera, &pbySnapMode);
	//设置相机的触发模式。0代表持续采集模式，1表示软件触发模式，2表示硬件触发模式
	switch (pbySnapMode)
	{
	case 0:
		ui->radioButton_collect->setChecked(true);
		ui->software_trigger_once_button->setEnabled(false);
		break;
	case 1:
		ui->radioButton_software_trigger->setChecked(true);
		ui->software_trigger_once_button->setEnabled(true);
		break;
	case 2:
		ui->radioButton_hardware_trigger->setChecked(true);
		ui->software_trigger_once_button->setEnabled(false);

		CameraGetStrobeMode(hCamera, &StrobeMode);		//获得当前STROBE信号设置的模式
		CameraGetStrobePolarity(hCamera, &uPolarity);	//获得相机当前STROBE信号的有效极性。默认为高电平有效

		if (StrobeMode)
			CameraSetStrobePolarity(hCamera, 1);
		else
			CameraSetStrobePolarity(hCamera, 0);
		break;
	default:
		ui->radioButton_software_trigger->setChecked(true);
		ui->software_trigger_once_button->setEnabled(true);
		break;
	}
	QObject::connect(ui->radioButton_collect, SIGNAL(clicked(bool)), this, SLOT(slot_radioButton_collect_clicked(bool)));
	QObject::connect(ui->radioButton_software_trigger, SIGNAL(clicked(bool)), this, SLOT(slot_radioButton_software_trigger_clicked(bool)));
	QObject::connect(ui->radioButton_hardware_trigger, SIGNAL(clicked(bool)), this, SLOT(slot_radioButton_hardware_trigger_clicked(bool)));
	QObject::connect(ui->software_trigger_once_button, SIGNAL(clicked()), this, SLOT(slot_software_trigger_once_button_clicked()));
	return 1;
}

int MainWindow::GUI_init_isp(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	BOOL        m_bHflip = FALSE;
	BOOL        m_bVflip = FALSE;

	//获得图像的镜像状态。
	CameraGetMirror(hCamera, MIRROR_DIRECTION_HORIZONTAL, &m_bHflip);
	CameraGetMirror(hCamera, MIRROR_DIRECTION_VERTICAL, &m_bVflip);

	//设置选中内容
	if (m_bHflip) {
		ui->checkBox_isp_h->setChecked(true);
	}
	else {
		ui->checkBox_isp_h->setChecked(false);
	}
	if (m_bVflip) {
		ui->checkBox_isp_v->setChecked(true);
	}
	else {
		ui->checkBox_isp_v->setChecked(false);
	}

	return 1;
}

void MainWindow::slot_radioButton_collect_clicked(bool checked)
{
	ui->radioButton_collect->setChecked(true);
	if (checked)
	{
		//获得相机的触发模式。
		CameraSetTriggerMode(g_hCamera, 0);
		ui->radioButton_collect->setChecked(true);
		ui->software_trigger_once_button->setEnabled(false);
	}
}

void MainWindow::slot_radioButton_software_trigger_clicked(bool checked)
{
	ui->radioButton_software_trigger->setChecked(true);
	if (checked)
	{
		//设置相机的触发模式。
		CameraSetTriggerMode(g_hCamera, 1);

		//设置相机的触发模式。0表示连续采集模式；1表示软件触发模式；2表示硬件触发模式。

		ui->radioButton_software_trigger->setChecked(true);
		ui->software_trigger_once_button->setEnabled(true);
	}
}

void MainWindow::slot_radioButton_hardware_trigger_clicked(bool checked)
{
	int StrobeMode = 0;
	int  uPolarity = 0;

	ui->radioButton_hardware_trigger->setChecked(true);
	if (checked)
	{
		//获得相机的触发模式。
		CameraSetTriggerMode(g_hCamera, 2);

		//设置相机的触发模式。0表示连续采集模式；1表示软件触发模式；2表示硬件触发模式。
		ui->software_trigger_once_button->setEnabled(false);

		CameraGetStrobeMode(g_hCamera, &StrobeMode);
		CameraGetStrobePolarity(g_hCamera, &uPolarity);
		if (StrobeMode) 
		{
			CameraSetStrobePolarity(g_hCamera, 1);
			if (uPolarity) 
				CameraSetStrobePolarity(g_hCamera, 1);
			else
				CameraSetStrobePolarity(g_hCamera, 0);
		}
		else
			CameraSetStrobePolarity(g_hCamera, 0);
	}
}

void MainWindow::slot_software_trigger_once_button_clicked()
{
	//执行一次软触发。执行后，会触发由CameraSetTriggerCount指定的帧数。
	CameraSoftTrigger(g_hCamera);
}

int MainWindow::GUI_init_exposure(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	BOOL            AEstate = FALSE;
	//int             pbyAeTarget;			//亮度目标值
	//BOOL            FlickEnable = FALSE;	//抗频闪使能状态
	//int             piFrequencySel;			//抗频闪频率值
	double          pfExposureTime;		
	int             pusAnalogGain;
	double	        m_fExpLineTime = 0;//当前的行曝光时间，单位为us
	tSdkExpose      *  SdkExpose = &pCameraInfo->sExposeDesc;

	//获得相机当前的曝光模式。
	CameraGetAeState(hCamera, &AEstate);

	////获得自动曝光的亮度目标值。
	//CameraGetAeTarget(hCamera, &pbyAeTarget);

	////获得自动曝光时抗频闪功能的使能状态。
	//CameraGetAntiFlick(hCamera, &FlickEnable);

	//获得自动曝光时，消频闪的频率选择。
	//CameraGetLightFrequency(hCamera, &piFrequencySel);

	//获得相机的曝光时间。
	CameraGetExposureTime(hCamera, &pfExposureTime);

	//获得图像信号的模拟增益值。
	CameraGetAnalogGain(hCamera, &pusAnalogGain);

	/*
	获得一行的曝光时间。对于CMOS传感器，其曝光
	的单位是按照行来计算的，因此，曝光时间并不能在微秒
	级别连续可调。而是会按照整行来取舍。这个函数的
	作用就是返回CMOS相机曝光一行对应的时间。
	*/
	CameraGetExposureLineTime(hCamera, &m_fExpLineTime);

	connect(ui->horizontalSlider_gain, SIGNAL(valueChanged(int)), ui->spinBox_gain, SLOT(setValue(int)));
	connect(ui->spinBox_gain, SIGNAL(valueChanged(int)), ui->horizontalSlider_gain, SLOT(setValue(int)));

	ui->horizontalSlider_gain->setMinimum(SdkExpose->uiAnalogGainMin);
	ui->horizontalSlider_gain->setMaximum(SdkExpose->uiAnalogGainMax);
	ui->spinBox_gain->setMinimum(SdkExpose->uiExposeTimeMin);
	ui->spinBox_gain->setMaximum(SdkExpose->uiExposeTimeMax);

	exposure_time_lineedit_status = false;

	ui->horizontalSlider_exposure_time->setMinimum(SdkExpose->uiExposeTimeMin);
	ui->horizontalSlider_exposure_time->setMaximum(SdkExpose->uiExposeTimeMax);
	ui->horizontalSlider_exposure_time->setValue(pfExposureTime / m_fExpLineTime);

	if (!AEstate)
	{
		//设置相机曝光的模式。自动或者手动。关
		CameraSetAeState(hCamera, false);
		ui->exposure_manual->setEnabled(true);
		ui->exposure_mode_manual->setChecked(true);
	}
	else
	{
		CameraSetAeState(hCamera, true);
		ui->exposure_manual->setEnabled(false);
		ui->exposure_mode_auto->setChecked(true);
	}

	connect(ui->exposure_mode_auto, SIGNAL(clicked(bool)), this, SLOT(slot_exposure_mode_auto_clicked(bool)));
	connect(ui->exposure_mode_manual, SIGNAL(clicked(bool)), this, SLOT(slot_exposure_mode_manual_clicked(bool)));
	connect(ui->horizontalSlider_gain, SIGNAL(valueChanged(int)), this, SLOT(slot_horizontalSlider_gain_valueChanged(int)));
	connect(ui->horizontalSlider_exposure_time, SIGNAL(valueChanged(int)), this, SLOT(slot_horizontalSlider_exposure_time_valueChanged(int)));

	return 1;
}

void MainWindow::slot_exposure_mode_auto_clicked(bool checked)
{
	ui->exposure_mode_auto->setChecked(true);
	if (checked)
	{
		ui->exposure_manual->setEnabled(false);
		CameraSetAeState(g_hCamera, true);
	}
}

void MainWindow::slot_exposure_mode_manual_clicked(bool checked)
{
	double          pfExposureTime;
	int             pusAnalogGain;
	double	    m_fExpLineTime = 0;//当前的行曝光时间，单位为us
	ui->exposure_mode_manual->setChecked(false);
	if (checked)
	{
		//获得相机的曝光时间。
		CameraGetExposureTime(g_hCamera, &pfExposureTime);

		//获得图像信号的模拟增益值。
		CameraGetAnalogGain(g_hCamera, &pusAnalogGain);

		/*
		获得一行的曝光时间。对于CMOS传感器，其曝光
		的单位是按照行来计算的，因此，曝光时间并不能在微秒
		级别连续可调。而是会按照整行来取舍。这个函数的
		作用就是返回CMOS相机曝光一行对应的时间。
		*/
		CameraGetExposureLineTime(g_hCamera, &m_fExpLineTime);

		ui->horizontalSlider_gain->setValue(pusAnalogGain);
		ui->horizontalSlider_exposure_time->setValue(pfExposureTime / m_fExpLineTime);

		ui->exposure_manual->setEnabled(true);
		CameraSetAeState(g_hCamera, false);
	}
}
//手动曝光 增益
void MainWindow::slot_horizontalSlider_gain_valueChanged(int value)
{
	/*
	设置相机的图像模拟增益值。该值乘以CameraGetCapability获得
	的相机属性结构体中sExposeDesc.fAnalogGainStep，就
	得到实际的图像信号放大倍数。
	*/
	CameraSetAnalogGain(g_hCamera, value);
}

void MainWindow::slot_horizontalSlider_exposure_time_valueChanged(int value)
{
	double          m_fExpLineTime = 0;//当前的行曝光时间，单位为us
	char            buffer[16];
	/*
	获得一行的曝光时间。对于CMOS传感器，其曝光
	的单位是按照行来计算的，因此，曝光时间并不能在微秒M
	级别连续可调。而是会按照整行来取舍。这个函数的
	作用就是返回CMOS相机曝光一行对应的时间。
	*/
	CameraGetExposureLineTime(g_hCamera, &m_fExpLineTime);
	/*
	设置曝光时间。单位为微秒。对于CMOS传感器，其曝光
	的单位是按照行来计算的，因此，曝光时间并不能在微秒
	级别连续可调。而是会按照整行来取舍。在调用
	本函数设定曝光时间后，建议再调用CameraGetExposureTime
	来获得实际设定的值。
	*/
	CameraSetExposureTime(g_hCamera, value*m_fExpLineTime);
	if (!exposure_time_lineedit_status) {
		//除以1000是换算成毫秒
		sprintf(buffer, "%0.3f", ((value*m_fExpLineTime) / 1000));
		ui->lineEdit_exposure_time->setText(QString(buffer));
	}
}

void MainWindow::closeEvent(QCloseEvent * e)
{

	//linux 需要打开
	//CameraSetTriggerMode(g_hCamera, 0);

	m_thread->stop();
	while (!m_thread->wait(100))
	{
		QCoreApplication::processEvents();
	}

	if (g_readBuf != NULL) {
		free(g_readBuf);
		g_readBuf = NULL;
	}

	if (g_pRgbBuffer != NULL) {
		free(g_pRgbBuffer);
		g_pRgbBuffer = NULL;
	}

	if (g_hCamera>0) {
		//相机反初始化。释放资源。
		CameraUnInit(g_hCamera);
		g_hCamera = -1;
	}
	QMainWindow::closeEvent(e);
}

void MainWindow::on_pushButton_AWB_once_clicked()
{
	CameraSetOnceWB(g_hCamera);
}

//水平镜像
void MainWindow::on_checkBox_isp_h_clicked(bool checked)
{
	if (checked) 
		//设置图像镜像操作。镜像操作分为水平和垂直两个方向。水平
		CameraSetMirror(g_hCamera, MIRROR_DIRECTION_HORIZONTAL, true);
	else 
		//设置图像镜像操作。镜像操作分为水平和垂直两个方向。水平
		CameraSetMirror(g_hCamera, MIRROR_DIRECTION_HORIZONTAL, false);

}

//垂直镜像
void MainWindow::on_checkBox_isp_v_clicked(bool checked)
{
	if (checked)
		//设置图像镜像操作。镜像操作分为水平和垂直两个方向。垂直
		CameraSetMirror(g_hCamera, MIRROR_DIRECTION_VERTICAL, true);
	else
		//设置图像镜像操作。镜像操作分为水平和垂直两个方向。垂直
		CameraSetMirror(g_hCamera, MIRROR_DIRECTION_VERTICAL, false);
}

void MainWindow::on_radioButton_para_A_clicked(bool checked)
{
	ui->radioButton_para_A->setChecked(true);

	if (checked) {

		/*
		存当前相机参数到指定的参数组中。相机提供了A,B,C,D
		A,B,C,D四组空间来进行参数的保存。
		*/
		CameraSaveParameter(g_hCamera, g_SaveParameter_num);
		g_SaveParameter_num = 0;

		//加载指定组的参数到相机中。
		CameraLoadParameter(g_hCamera, g_SaveParameter_num);
		m_thread->pause();
		GUI_init_parameter(g_hCamera, &g_tCapability);
		m_thread->stream();

	}
}

void MainWindow::on_radioButton_para_B_clicked(bool checked)
{
	ui->radioButton_para_B->setChecked(true);

	if (checked) {

		/*
		存当前相机参数到指定的参数组中。相机提供了A,B,C,D
		A,B,C,D四组空间来进行参数的保存。
		*/
		CameraSaveParameter(g_hCamera, g_SaveParameter_num);
		g_SaveParameter_num = 1;

		//加载指定组的参数到相机中。
		CameraLoadParameter(g_hCamera, g_SaveParameter_num);
		m_thread->pause();
		GUI_init_parameter(g_hCamera, &g_tCapability);
		m_thread->stream();
	}
}

void MainWindow::on_radioButton_para_C_clicked(bool checked)
{
	ui->radioButton_para_C->setChecked(true);

	if (checked) {

		/*
		存当前相机参数到指定的参数组中。相机提供了A,B,C,D
		A,B,C,D四组空间来进行参数的保存。
		*/
		CameraSaveParameter(g_hCamera, g_SaveParameter_num);
		g_SaveParameter_num = 2;

		//加载指定组的参数到相机中。
		CameraLoadParameter(g_hCamera, g_SaveParameter_num);
		m_thread->pause();
		GUI_init_parameter(g_hCamera, &g_tCapability);
		m_thread->stream();
	}
}

void MainWindow::on_radioButton_para_D_clicked(bool checked)
{
	ui->radioButton_para_D->setChecked(true);

	if (checked) {

		/*
		存当前相机参数到指定的参数组中。相机提供了A,B,C,D
		A,B,C,D四组空间来进行参数的保存。
		*/
		CameraSaveParameter(g_hCamera, g_SaveParameter_num);
		g_SaveParameter_num = 3;

		//加载指定组的参数到相机中。
		CameraLoadParameter(g_hCamera, g_SaveParameter_num);
		m_thread->pause();
		GUI_init_parameter(g_hCamera, &g_tCapability);
		m_thread->stream();
	}
}

int MainWindow::GUI_init_WB(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	int RPos, GPos, BPos;

	//设置选中项
	//获得当前预览的分辨率。
	CameraGetGain(g_hCamera, &RPos, &GPos, &BPos);
	CameraSetGain(g_hCamera, RPos, GPos, BPos);
	return 1;
}

void MainWindow::on_pushButton_para_load_clicked()
{
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setNameFilters(QStringList("Config Files(*.config)"));
	fileDialog->setWindowTitle(tr("Select file"));
	if (fileDialog->exec() == QDialog::Accepted)
	{
		QString path = fileDialog->selectedFiles()[0];

		//由QString转换为char*
		char*  filename;
		QByteArray tmp = path.toLatin1();
		filename = tmp.data();

		int loadstatus = CameraReadParameterFromFile(g_hCamera, filename);

		if (loadstatus != CAMERA_STATUS_SUCCESS)
			QMessageBox::information(NULL, tr("Select file path"), tr("You didn't select any files."));
		else
		{
			m_thread->pause();
			GUI_init_parameter(g_hCamera, &g_tCapability);
			m_thread->stream();
		}
	}
	delete fileDialog;
}

void MainWindow::on_pushButton_para_save_clicked()
{
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(tr("Save file"));
	fileDialog->setNameFilters(QStringList("Config Files(*.config)"));
	if (fileDialog->exec() == QDialog::Accepted)
	{
		QString path = fileDialog->selectedFiles()[0];
		path += tr(".config");

		char*  filename;
		QByteArray tmp = path.toLatin1();
		filename = tmp.data();

		CameraSaveParameterToFile(g_hCamera, filename);

		m_thread->pause();
		GUI_init_parameter(g_hCamera, &g_tCapability);
		m_thread->stream();
	}
	delete fileDialog;
}

//默认参数
void MainWindow::on_pushButton_para_default_clicked()
{
	//加载指定组的参数到相机中。
	CameraLoadParameter(g_hCamera, PARAMETER_TEAM_DEFAULT);

	m_thread->pause();
	GUI_init_parameter(g_hCamera, &g_tCapability);
	m_thread->stream();
}

void MainWindow::on_pushButton_next_move_clicked()
{
	b_pause = TRUE;
	if (b_child_window == FALSE)
	{
		m_QtCamUse_move_window = new QtCamUse_move(this);
		connect(m_QtCamUse_move_window, SIGNAL(back_to_mainwindow()), this, SLOT(slot_recover()));		//开启原窗口复原槽
		b_child_window = TRUE;
	}
	m_QtCamUse_move_window->show();
	//connect(m_thread, SIGNAL(captured(QImage)), m_QtCamUse_move_window,						//连接m_thread与QtCamUse_move_window中图像接收槽
	//	SLOT(m_QtCamUse_move_window->QtCamUse_move::Image_process(QImage)), Qt::QueuedConnection);
	
	disconnect(m_thread, SIGNAL(captured(QImage)), this, SLOT(Image_process(QImage)));		//断开m_thread与Image_process之间的联系
	m_thread->pause();
	
	
	this->hide();
}

void MainWindow::slot_recover()
{
	if (b_pause == FALSE)
	{
		QMessageBox::information(NULL, tr("Wanrning"), tr("This mainwindow hasn't been closed"));
	}
	b_pause = FALSE;

	m_QtCamUse_move_window->close();
	delete m_QtCamUse_move_window;
	b_child_window = FALSE;

	if (init_SDK() == -1)		//需重新初始化相机
	{
		status = 0;
		return;
	}
	connect(m_thread, SIGNAL(captured(QImage)), this, SLOT(Image_process(QImage)), Qt::BlockingQueuedConnection);
	m_thread->start();
	m_thread->stream();
	this->show();
}