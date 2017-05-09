#include "QtCamUse_move.h"
#include "ui_QtCamUse_move.h"

#include <stdio.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

extern int                  g_hCamera;          //�豸���
extern unsigned char        * g_pRawBuffer;     //raw����
extern unsigned char        * g_pRgbBuffer;     //���������ݻ�����
extern tSdkFrameHead        g_tFrameHead;       //ͼ��֡ͷ��Ϣ
extern tSdkCameraCapbility  g_tCapability;      //�豸������Ϣ


extern int                     g_SaveParameter_num;    //���������
extern int                     g_SaveImage_type;         //����ͼ���ʽ

extern Width_Height            g_W_H_INFO;         //��ʾ���嵽��С��ͼ���С
extern BYTE                    *g_readBuf;    //������ʾ������
extern int                     g_read_fps;       //ͳ�ƶ�ȡ֡��
extern int                     g_disply_fps;     //ͳ����ʾ֡��

QtCamUse_move::QtCamUse_move(QWidget *parent)
	:ui(new Ui::QtCamUse_moveClass),
	m_scene(0), m_image_item(0)
{
	ui->setupUi(this);
	m_scene = new QGraphicsScene(this);
	ui->gvMain->setScene(m_scene);

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(camera_statues()));
	m_timer->start(1000);

	m_thread = new CaptureThread(this);		//ͼ�����̵߳��źŽ����������һ���ڣ�ʹȫ��ֻ��һ��ͼ���߳�

	connect(m_thread, SIGNAL(captured(QImage)),
		this, SLOT(Image_process(QImage)), Qt::BlockingQueuedConnection);

	m_thread->start();
	m_thread->stream();
	status = 1;
}

QtCamUse_move::~QtCamUse_move()
{
	delete ui;
}

void QtCamUse_move::Image_process(QImage img)
{

	//if (m_thread->quit)
	//{
	//	return;
	//}


	if (m_image_item)
	{
		m_scene->removeItem(m_image_item);
		delete m_image_item;
		m_image_item = 0;
	}

	m_image_item = m_scene->addPixmap(QPixmap::fromImage(img));

	m_scene->setSceneRect(0, 0, 800, 600);
	//m_scene->setSceneRect(0, 0, 800, 600);

	g_disply_fps++;
}

void QtCamUse_move::showEvent(QShowEvent *)
{
	ui->gvMain->fitInView(m_scene->sceneRect());
}

void QtCamUse_move::closeEvent(QCloseEvent * e)
{

	//linux ��Ҫ��
	//CameraSetTriggerMode(g_hCamera, 0);

	m_thread->stop();
	while (!m_thread->wait(500))
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

void QtCamUse_move::on_pushButton_back_to_mainwindow_clicked()
{
	emit(back_to_mainwindow());
}