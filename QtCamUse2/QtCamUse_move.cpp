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
	m_scene(0), m_image_item(0)
{
	ui->setupUi(this);
	m_scene = new QGraphicsScene(this);
	ui->gvMain->setScene(m_scene);

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(camera_statues()));
	m_timer->start(1000);

	m_thread = new CaptureThread(this);		//图像传输线程的信号接收完成于上一窗口，使全程只有一条图像线程

	connect(m_thread, SIGNAL(captured(QImage)),
		this, SLOT(Image_process(QImage)), Qt::BlockingQueuedConnection);

	ui->lineEdit_get_back_path->setReadOnly(TRUE);

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

void QtCamUse_move::on_pushButton_get_template_clicked()
{

}

void QtCamUse_move::on_pushButton_get_back_save_clicked()
{

	QString path;
	char * filename;

	QDateTime time = QDateTime::currentDateTime();
	QString strtime = time.toString("yyyyMMdd_hhmmss");
	QString strfilename = QString("BackImage") + strtime + QString(".bmp");

	path = QFileDialog::getSaveFileName(this, "Save BackImage", strfilename);

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
			QMessageBox::information(NULL, tr("Path error"), tr("The path is invalid"));
			free(pbImgBuffer);
			return;
		}

		m_imageprocess.getBackImage(filename);

		//释放由CameraGetImageBuffer获得的缓冲区。
		CameraReleaseImageBuffer(g_hCamera, pbImgBuffer);
		free(pbImgBuffer);
	}
}