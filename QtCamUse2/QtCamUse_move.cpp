#include "QtCamUse_move.h"
#include "ui_QtCamUse_move.h"

#include <stdio.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

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

QtCamUse_move::QtCamUse_move(QWidget *parent)
	:ui(new Ui::QtCamUse_moveClass),
	m_scene(0), m_image_item(0),
	m_imageprocess(new QtImageProcess)
{
	ui->setupUi(this);
	m_scene = new QtCamUse_move_ChildScene();
	ui->gvMain->setScene(m_scene);

	this->setMouseTracking(true);
	ui->gvMain->setMouseTracking(true);
	connect(m_scene, SIGNAL(mouse_move_pos(int, int)), this, SLOT(slot_mouse_move_pos_show(int, int)), Qt::QueuedConnection);
	//m_timer = new QTimer(this);
	//connect(m_timer, SIGNAL(timeout()), this, SLOT(camera_statues()));
	//m_timer->start(1000);

	m_mouse_pos = new QLabel(this);
	m_mouse_pos->setAlignment(Qt::AlignHCenter);
	ui->statusBar->addWidget(m_mouse_pos);
	
	m_thread = new CaptureThread(this);		//图像传输线程的信号接收完成于上一窗口，使全程只有一条图像线程

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
	disconnect(m_scene, SIGNAL(mouse_move_pos(int, int)), this, SLOT(slot_mouse_move_pos_show(int, int)));
	if (m_image_item)
	{
		m_scene->removeItem(m_image_item);
		delete m_image_item;
		m_image_item = 0;
	}
	
	m_image_item = m_scene->addPixmap(QPixmap::fromImage(img));
	resizeView();
	
	//m_scene->setSceneRect(0, 0, img.width(), img.height());
	//m_scene->setSceneRect(0, 0, 800, 600);
	
	connect(m_scene, SIGNAL(mouse_move_pos(int, int)), this, SLOT(slot_mouse_move_pos_show(int, int)));
	g_disply_fps++;
}

void QtCamUse_move::showEvent(QShowEvent *)
{
	//ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

void QtCamUse_move::resizeView()
{
	ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);		//sykdebug

}

void QtCamUse_move::resizeEvent(QResizeEvent *event)
{
	//QtCamUse_move::resizeEvent(event);
	//ui->gvMain->horizontalScrollBarPolicy();
	//ui->gvMain->verticalScrollBarPolicy();
	//ui->gvMain->fitInView(0, 0, 800, 600, Qt::KeepAspectRatioByExpanding);
	//ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

void QtCamUse_move::closeEvent(QCloseEvent * e)
{

	//linux 需要打开
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
		//相机反初始化。释放资源。
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

	//CameraSnapToBuffer抓拍一张图像保存到buffer中
	if (CameraSnapToBuffer(g_hCamera, &tFrameHead, &pbyBuffer, 1000) == CAMERA_STATUS_SUCCESS)
	{
		int iHeight = g_tCapability.sResolutionRange.iHeightMax;
		int iWidth = g_tCapability.sResolutionRange.iWidthMax;
		pbImgBuffer = (unsigned char*)malloc(iHeight*iWidth * 3);
		/*
		将获得的相机原始输出图像数据进行处理，叠加饱和度、
		颜色增益和校正、降噪等处理效果，最后得到RGB888
		格式的图像数据。
		*/
		CameraImageProcess(g_hCamera, pbyBuffer, pbImgBuffer, &tFrameHead);

		//将图像缓冲区的数据保存成图片文件。
		if (path.isEmpty() == TRUE || CameraSaveImage(g_hCamera, filename, pbImgBuffer, &tFrameHead, FILE_BMP, 100) != CAMERA_STATUS_SUCCESS)
		{
			QMessageBox::information(NULL, tr("Path error"), tr("The path to save backimage is invalid"));
			free(pbImgBuffer);
			return;
		}

		m_imageprocess->getBackImageFromPath(filename);

		//释放由CameraGetImageBuffer获得的缓冲区。
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

	//CameraSnapToBuffer抓拍一张图像保存到buffer中
	if (CameraSnapToBuffer(g_hCamera, &tFrameHead, &pbyBuffer, 1000) == CAMERA_STATUS_SUCCESS)
	{
		int iHeight = g_tCapability.sResolutionRange.iHeightMax;
		int iWidth = g_tCapability.sResolutionRange.iWidthMax;
		pbImgBuffer = (unsigned char*)malloc(iHeight*iWidth * 3);
		/*
		将获得的相机原始输出图像数据进行处理，叠加饱和度、
		颜色增益和校正、降噪等处理效果，最后得到RGB888
		格式的图像数据。
		*/
		CameraImageProcess(g_hCamera, pbyBuffer, pbImgBuffer, &tFrameHead);

		//将图像缓冲区的数据保存成图片文件。
		if (path.isEmpty() == TRUE || CameraSaveImage(g_hCamera, filename, pbImgBuffer, &tFrameHead, FILE_BMP, 100) != CAMERA_STATUS_SUCCESS)
		{
			QMessageBox::information(NULL, tr("Path error"), tr("The path to save templateimage is invalid"));
			free(pbImgBuffer);
			return;
		}

		m_imageprocess->getTemplateImageFromPath(filename);

		//释放由CameraGetImageBuffer获得的缓冲区。
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
	int x = e->scenePos().x();
	int y = e->scenePos().y();
	emit mouse_move_pos(e->scenePos().x(), e->scenePos().y());
}