#include "QtCamUse.h"
#include "ui_QtCamUse.h"
#include "capturethread.h"
#include <stdio.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>


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
	CameraSetFrameSpeed(g_hCamera, 2);			//������Ĳɼ�֡����Ϊ����
	
	
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

void MainWindow::slot_res_combobox_activated(int index)
{

	tSdkImageResolution   *pImageSizeDesc = g_tCapability.pImageSizeDesc;// Ԥ��ֱ���ѡ��

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
	//����Ԥ���ķֱ��ʡ�
	CameraSetImageResolution(g_hCamera, &(pImageSizeDesc[index]));
	m_thread->stream();
	//ui->gvMain->scale(1/1.5,1/1.5);
}

int MainWindow::GUI_init_Trigger(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	/*
	δΪ�Զ��ع�ģʽ���ÿ�Ƶ���ȹ���
	*/
	int pbySnapMode;
	int StrobeMode = 0;
	int uPolarity = 0;
	//�������Ĵ���ģʽ
	CameraGetTriggerMode(hCamera, &pbySnapMode);
	//��������Ĵ���ģʽ��0��������ɼ�ģʽ��1��ʾ�������ģʽ��2��ʾӲ������ģʽ
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

		CameraGetStrobeMode(hCamera, &StrobeMode);		//��õ�ǰSTROBE�ź����õ�ģʽ
		CameraGetStrobePolarity(hCamera, &uPolarity);	//��������ǰSTROBE�źŵ���Ч���ԡ�Ĭ��Ϊ�ߵ�ƽ��Ч

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

	//���ͼ��ľ���״̬��
	CameraGetMirror(hCamera, MIRROR_DIRECTION_HORIZONTAL, &m_bHflip);
	CameraGetMirror(hCamera, MIRROR_DIRECTION_VERTICAL, &m_bVflip);

	//����ѡ������
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
		//�������Ĵ���ģʽ��
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
		//��������Ĵ���ģʽ��
		CameraSetTriggerMode(g_hCamera, 1);

		//��������Ĵ���ģʽ��0��ʾ�����ɼ�ģʽ��1��ʾ�������ģʽ��2��ʾӲ������ģʽ��

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
		//�������Ĵ���ģʽ��
		CameraSetTriggerMode(g_hCamera, 2);

		//��������Ĵ���ģʽ��0��ʾ�����ɼ�ģʽ��1��ʾ�������ģʽ��2��ʾӲ������ģʽ��
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
	//ִ��һ��������ִ�к󣬻ᴥ����CameraSetTriggerCountָ����֡����
	CameraSoftTrigger(g_hCamera);
}

int MainWindow::GUI_init_exposure(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	BOOL            AEstate = FALSE;
	//int             pbyAeTarget;			//����Ŀ��ֵ
	//BOOL            FlickEnable = FALSE;	//��Ƶ��ʹ��״̬
	//int             piFrequencySel;			//��Ƶ��Ƶ��ֵ
	double          pfExposureTime;		
	int             pusAnalogGain;
	double	        m_fExpLineTime = 0;//��ǰ�����ع�ʱ�䣬��λΪus
	tSdkExpose      *  SdkExpose = &pCameraInfo->sExposeDesc;

	//��������ǰ���ع�ģʽ��
	CameraGetAeState(hCamera, &AEstate);

	////����Զ��ع������Ŀ��ֵ��
	//CameraGetAeTarget(hCamera, &pbyAeTarget);

	////����Զ��ع�ʱ��Ƶ�����ܵ�ʹ��״̬��
	//CameraGetAntiFlick(hCamera, &FlickEnable);

	//����Զ��ع�ʱ����Ƶ����Ƶ��ѡ��
	//CameraGetLightFrequency(hCamera, &piFrequencySel);

	//���������ع�ʱ�䡣
	CameraGetExposureTime(hCamera, &pfExposureTime);

	//���ͼ���źŵ�ģ������ֵ��
	CameraGetAnalogGain(hCamera, &pusAnalogGain);

	/*
	���һ�е��ع�ʱ�䡣����CMOS�����������ع�
	�ĵ�λ�ǰ�����������ģ���ˣ��ع�ʱ�䲢������΢��
	���������ɵ������ǻᰴ��������ȡ�ᡣ���������
	���þ��Ƿ���CMOS����ع�һ�ж�Ӧ��ʱ�䡣
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
		//��������ع��ģʽ���Զ������ֶ�����
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
	double	    m_fExpLineTime = 0;//��ǰ�����ع�ʱ�䣬��λΪus
	ui->exposure_mode_manual->setChecked(false);
	if (checked)
	{
		//���������ع�ʱ�䡣
		CameraGetExposureTime(g_hCamera, &pfExposureTime);

		//���ͼ���źŵ�ģ������ֵ��
		CameraGetAnalogGain(g_hCamera, &pusAnalogGain);

		/*
		���һ�е��ع�ʱ�䡣����CMOS�����������ع�
		�ĵ�λ�ǰ�����������ģ���ˣ��ع�ʱ�䲢������΢��
		���������ɵ������ǻᰴ��������ȡ�ᡣ���������
		���þ��Ƿ���CMOS����ع�һ�ж�Ӧ��ʱ�䡣
		*/
		CameraGetExposureLineTime(g_hCamera, &m_fExpLineTime);

		ui->horizontalSlider_gain->setValue(pusAnalogGain);
		ui->horizontalSlider_exposure_time->setValue(pfExposureTime / m_fExpLineTime);

		ui->exposure_manual->setEnabled(true);
		CameraSetAeState(g_hCamera, false);
	}
}
//�ֶ��ع� ����
void MainWindow::slot_horizontalSlider_gain_valueChanged(int value)
{
	/*
	���������ͼ��ģ������ֵ����ֵ����CameraGetCapability���
	��������Խṹ����sExposeDesc.fAnalogGainStep����
	�õ�ʵ�ʵ�ͼ���źŷŴ�����
	*/
	CameraSetAnalogGain(g_hCamera, value);
}

void MainWindow::slot_horizontalSlider_exposure_time_valueChanged(int value)
{
	double          m_fExpLineTime = 0;//��ǰ�����ع�ʱ�䣬��λΪus
	char            buffer[16];
	/*
	���һ�е��ع�ʱ�䡣����CMOS�����������ع�
	�ĵ�λ�ǰ�����������ģ���ˣ��ع�ʱ�䲢������΢��M
	���������ɵ������ǻᰴ��������ȡ�ᡣ���������
	���þ��Ƿ���CMOS����ع�һ�ж�Ӧ��ʱ�䡣
	*/
	CameraGetExposureLineTime(g_hCamera, &m_fExpLineTime);
	/*
	�����ع�ʱ�䡣��λΪ΢�롣����CMOS�����������ع�
	�ĵ�λ�ǰ�����������ģ���ˣ��ع�ʱ�䲢������΢��
	���������ɵ������ǻᰴ��������ȡ�ᡣ�ڵ���
	�������趨�ع�ʱ��󣬽����ٵ���CameraGetExposureTime
	�����ʵ���趨��ֵ��
	*/
	CameraSetExposureTime(g_hCamera, value*m_fExpLineTime);
	if (!exposure_time_lineedit_status) {
		//����1000�ǻ���ɺ���
		sprintf(buffer, "%0.3f", ((value*m_fExpLineTime) / 1000));
		ui->lineEdit_exposure_time->setText(QString(buffer));
	}
}

void MainWindow::closeEvent(QCloseEvent * e)
{

	//linux ��Ҫ��
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
		//�������ʼ�����ͷ���Դ��
		CameraUnInit(g_hCamera);
		g_hCamera = -1;
	}
	QMainWindow::closeEvent(e);
}

void MainWindow::on_pushButton_AWB_once_clicked()
{
	CameraSetOnceWB(g_hCamera);
}

//ˮƽ����
void MainWindow::on_checkBox_isp_h_clicked(bool checked)
{
	if (checked) 
		//����ͼ������������������Ϊˮƽ�ʹ�ֱ��������ˮƽ
		CameraSetMirror(g_hCamera, MIRROR_DIRECTION_HORIZONTAL, true);
	else 
		//����ͼ������������������Ϊˮƽ�ʹ�ֱ��������ˮƽ
		CameraSetMirror(g_hCamera, MIRROR_DIRECTION_HORIZONTAL, false);

}

//��ֱ����
void MainWindow::on_checkBox_isp_v_clicked(bool checked)
{
	if (checked)
		//����ͼ������������������Ϊˮƽ�ʹ�ֱ�������򡣴�ֱ
		CameraSetMirror(g_hCamera, MIRROR_DIRECTION_VERTICAL, true);
	else
		//����ͼ������������������Ϊˮƽ�ʹ�ֱ�������򡣴�ֱ
		CameraSetMirror(g_hCamera, MIRROR_DIRECTION_VERTICAL, false);
}

void MainWindow::on_radioButton_para_A_clicked(bool checked)
{
	ui->radioButton_para_A->setChecked(true);

	if (checked) {

		/*
		�浱ǰ���������ָ���Ĳ������С�����ṩ��A,B,C,D
		A,B,C,D����ռ������в����ı��档
		*/
		CameraSaveParameter(g_hCamera, g_SaveParameter_num);
		g_SaveParameter_num = 0;

		//����ָ����Ĳ���������С�
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
		�浱ǰ���������ָ���Ĳ������С�����ṩ��A,B,C,D
		A,B,C,D����ռ������в����ı��档
		*/
		CameraSaveParameter(g_hCamera, g_SaveParameter_num);
		g_SaveParameter_num = 1;

		//����ָ����Ĳ���������С�
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
		�浱ǰ���������ָ���Ĳ������С�����ṩ��A,B,C,D
		A,B,C,D����ռ������в����ı��档
		*/
		CameraSaveParameter(g_hCamera, g_SaveParameter_num);
		g_SaveParameter_num = 2;

		//����ָ����Ĳ���������С�
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
		�浱ǰ���������ָ���Ĳ������С�����ṩ��A,B,C,D
		A,B,C,D����ռ������в����ı��档
		*/
		CameraSaveParameter(g_hCamera, g_SaveParameter_num);
		g_SaveParameter_num = 3;

		//����ָ����Ĳ���������С�
		CameraLoadParameter(g_hCamera, g_SaveParameter_num);
		m_thread->pause();
		GUI_init_parameter(g_hCamera, &g_tCapability);
		m_thread->stream();
	}
}

int MainWindow::GUI_init_WB(int hCamera, tSdkCameraCapbility * pCameraInfo)
{
	int RPos, GPos, BPos;

	//����ѡ����
	//��õ�ǰԤ���ķֱ��ʡ�
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

		//��QStringת��Ϊchar*
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

//Ĭ�ϲ���
void MainWindow::on_pushButton_para_default_clicked()
{
	//����ָ����Ĳ���������С�
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
		connect(m_QtCamUse_move_window, SIGNAL(back_to_mainwindow()), this, SLOT(slot_recover()));		//����ԭ���ڸ�ԭ��
		b_child_window = TRUE;
	}
	m_QtCamUse_move_window->show();
	//connect(m_thread, SIGNAL(captured(QImage)), m_QtCamUse_move_window,						//����m_thread��QtCamUse_move_window��ͼ����ղ�
	//	SLOT(m_QtCamUse_move_window->QtCamUse_move::Image_process(QImage)), Qt::QueuedConnection);
	
	disconnect(m_thread, SIGNAL(captured(QImage)), this, SLOT(Image_process(QImage)));		//�Ͽ�m_thread��Image_process֮�����ϵ
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

	if (init_SDK() == -1)		//�����³�ʼ�����
	{
		status = 0;
		return;
	}
	connect(m_thread, SIGNAL(captured(QImage)), this, SLOT(Image_process(QImage)), Qt::BlockingQueuedConnection);
	m_thread->start();
	m_thread->stream();
	this->show();
}