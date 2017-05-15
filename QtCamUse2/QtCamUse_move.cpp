#include "QtCamUse_move.h"
#include "ui_QtCamUse_move.h"

#include <stdio.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

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

QtCamUse_move::QtCamUse_move(QWidget *parent)
	:ui(new Ui::QtCamUse_moveClass),
	m_scene(0), m_image_item(0),
	m_imageprocess(new ImageProcess)
{
	ui->setupUi(this);
	m_scene = new QtCamUse_move_ChildScene();
	ui->gvMain->setScene(m_scene);
	this->setMouseTracking(true);
	ui->gvMain->setMouseTracking(true);
	connect(m_scene, SIGNAL(mouse_move_pos(int, int)), this, SLOT(slot_mouse_move_pos_show(int, int)));
	//m_timer = new QTimer(this);
	//connect(m_timer, SIGNAL(timeout()), this, SLOT(camera_statues()));
	//m_timer->start(1000);

	m_mouse_pos = new QLabel(this);
	m_mouse_pos->setAlignment(Qt::AlignHCenter);
	ui->statusBar->addWidget(m_mouse_pos);
	
	m_thread = new CaptureThread(this);		//ͼ�����̵߳��źŽ����������һ���ڣ�ʹȫ��ֻ��һ��ͼ���߳�

	connect(m_thread, SIGNAL(captured(QImage)),
		this, SLOT(Image_process(QImage)), Qt::BlockingQueuedConnection);

	ui->lineEdit_get_back_path->setReadOnly(TRUE);
	ui->lineEdit_get_template_path->setReadOnly(TRUE);

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

	//m_scene->setSceneRect(0, 0, img.width(), img.height());
	//m_scene->setSceneRect(0, 0, 800, 600);
	resizeView();
	g_disply_fps++;
}

void QtCamUse_move::showEvent(QShowEvent *)
{
	//ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
	//ui->gvMain->fitInView(m_scene->sceneRect());
}

void QtCamUse_move::resizeView()
{
	ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
	//ui->gvMain->fitInView(0, 0, 400, 400, Qt::KeepAspectRatioByExpanding);

}

void QtCamUse_move::resizeEvent(QResizeEvent *event)
{
	//QtCamUse_move::resizeEvent(event);
	//ui->gvMain->horizontalScrollBarPolicy();
	//ui->gvMain->verticalScrollBarPolicy();
	//ui->gvMain->fitInView(0, 0, 800, 600, Qt::KeepAspectRatioByExpanding);
	//ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
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

void QtCamUse_move::on_pushButton_get_back_save_clicked()
{
	QString path;
	char * filename;

	QDateTime time = QDateTime::currentDateTime();
	QString strtime = time.toString("yyyyMMdd_hhmmss");
	QString strfilename = QString("BI") + strtime + QString(".bmp");

	path = QFileDialog::getSaveFileName(this, "Save BackImage", strfilename, tr("BMP Image (*.bmp *.BMP)"));

	ui->lineEdit_get_back_path->setText(path);
	QByteArray tmp = path.toLatin1();
	filename = tmp.data();

	tSdkFrameHead	tFrameHead;
	BYTE			*pbyBuffer;
	BYTE			*pbImgBuffer;

	//CameraSnapToBufferץ��һ��ͼ�񱣴浽buffer��
	if (CameraSnapToBuffer(g_hCamera, &tFrameHead, &pbyBuffer, 1000) == CAMERA_STATUS_SUCCESS)
	{
		int iHeight = g_tCapability.sResolutionRange.iHeightMax;
		int iWidth = g_tCapability.sResolutionRange.iWidthMax;
		pbImgBuffer = (unsigned char*)malloc(iHeight*iWidth * 3);
		/*
		����õ����ԭʼ���ͼ�����ݽ��д������ӱ��Ͷȡ�
		��ɫ�����У��������ȴ���Ч�������õ�RGB888
		��ʽ��ͼ�����ݡ�
		*/
		CameraImageProcess(g_hCamera, pbyBuffer, pbImgBuffer, &tFrameHead);

		//��ͼ�񻺳��������ݱ����ͼƬ�ļ���
		if (path.isEmpty() == TRUE || CameraSaveImage(g_hCamera, filename, pbImgBuffer, &tFrameHead, FILE_BMP, 100) != CAMERA_STATUS_SUCCESS)
		{
			QMessageBox::information(NULL, tr("Path error"), tr("The path to save backimage is invalid"));
			free(pbImgBuffer);
			return;
		}

		m_imageprocess->getBackImageFromPath(filename);

		//�ͷ���CameraGetImageBuffer��õĻ�������
		CameraReleaseImageBuffer(g_hCamera, pbImgBuffer);
		free(pbImgBuffer);
	}
}

void QtCamUse_move::on_pushButton_get_back_load_clicked()
{
	QString path;
	char * filename;

	path = QFileDialog::getOpenFileName(this, "Load BackImage", NULL, tr("BMP Image (*.bmp *.BMP)"));
	ui->lineEdit_get_back_path->setText(path);
	QByteArray tmp = path.toLatin1();
	filename = tmp.data();
	m_imageprocess->getBackImageFromPath(filename);
}

void QtCamUse_move::on_pushButton_get_template_save_clicked()
{
	QString path;
	char * filename;

	QDateTime time = QDateTime::currentDateTime();
	QString strtime = time.toString("yyyyMMdd_hhmmss");
	QString strfilename = QString("TI") + strtime + QString(".bmp");

	path = QFileDialog::getSaveFileName(this, "Save TemplateImage", strfilename);

	ui->lineEdit_get_template_path->setText(path);
	QByteArray tmp = path.toLatin1();
	filename = tmp.data();

	tSdkFrameHead	tFrameHead;
	BYTE			*pbyBuffer;
	BYTE			*pbImgBuffer;

	//CameraSnapToBufferץ��һ��ͼ�񱣴浽buffer��
	if (CameraSnapToBuffer(g_hCamera, &tFrameHead, &pbyBuffer, 1000) == CAMERA_STATUS_SUCCESS)
	{
		int iHeight = g_tCapability.sResolutionRange.iHeightMax;
		int iWidth = g_tCapability.sResolutionRange.iWidthMax;
		pbImgBuffer = (unsigned char*)malloc(iHeight*iWidth * 3);
		/*
		����õ����ԭʼ���ͼ�����ݽ��д������ӱ��Ͷȡ�
		��ɫ�����У��������ȴ���Ч�������õ�RGB888
		��ʽ��ͼ�����ݡ�
		*/
		CameraImageProcess(g_hCamera, pbyBuffer, pbImgBuffer, &tFrameHead);

		//��ͼ�񻺳��������ݱ����ͼƬ�ļ���
		if (path.isEmpty() == TRUE || CameraSaveImage(g_hCamera, filename, pbImgBuffer, &tFrameHead, FILE_BMP, 100) != CAMERA_STATUS_SUCCESS)
		{
			QMessageBox::information(NULL, tr("Path error"), tr("The path to save templateimage is invalid"));
			free(pbImgBuffer);
			return;
		}

		m_imageprocess->getTemplateImageFromPath(filename);

		//�ͷ���CameraGetImageBuffer��õĻ�������
		CameraReleaseImageBuffer(g_hCamera, pbImgBuffer);
		free(pbImgBuffer);
	}
}

void QtCamUse_move::on_pushButton_get_template_load_clicked()
{
	QString path;
	char * filename;

	path = QFileDialog::getOpenFileName(this, "Load TemplateImage", NULL, tr("BMP Image (*.bmp *.BMP)"));
	ui->lineEdit_get_template_path->setText(path);
	QByteArray tmp = path.toLatin1();
	filename = tmp.data();
	m_imageprocess->getTemplateImageFromPath(filename);
}

void QtCamUse_move::on_pushButton_image_process_clicked()
{
	if (m_imageprocess->isReady() != true)
	{
		QMessageBox::information(NULL, tr("Warning"), tr("Lack backimage or templateimage"));
		return;
	}
	this->hide();
	QtCamUse_process *processwin = new QtCamUse_process(this, m_imageprocess);
	processwin->show();
	m_imageprocess->processImage();
}

void QtCamUse_move::slot_mouse_move_pos_show(int _x, int _y)
{
	m_mouse_pos->setText(QString("The mouse pos: x: %1  y:%2").arg(QString::number(_x, 'f', 2)).arg(QString::number(_y, 'f', 2)));
}

void QtCamUse_move_ChildScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
	emit mouse_move_pos(e->scenePos().x(), e->scenePos().y());
}