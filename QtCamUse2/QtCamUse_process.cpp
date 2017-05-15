#include "QtCamUse_process.h"
#include "ui_QtCamUse_process.h"

QtCamUse_process::QtCamUse_process(QWidget *parent, ImageProcess *_m_imageprocess)
	:ui(new Ui::QtCamUse_processClass),
	m_scene(0), m_image_item(0), m_imageprocess(_m_imageprocess)
{
	ui->setupUi(this);
	m_scene = new QGraphicsScene(this);
	ui->gvMain->setScene(m_scene);

	qRegisterMetaType< cv::Mat >("cv::Mat");
	connect(m_imageprocess, SIGNAL(proResult(QImage)), this, SLOT(ImageShow(QImage)));
}

QtCamUse_process::~QtCamUse_process()
{

}



void QtCamUse_process::ImageShow(QImage image)
{
	if (m_image_item)
	{
		m_scene->removeItem(m_image_item);
		delete m_image_item;
		m_image_item = 0;
	}

	m_image_item = m_scene->addPixmap(QPixmap::fromImage(image));

	//m_scene->setSceneRect(0, 0, 800, 600);
	//m_scene->setSceneRect(0, 0, 800, 600);
	resizeView();
}

void QtCamUse_process::showEvent(QShowEvent *)
{
	//ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
	//ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

void QtCamUse_process::resizeView()
{
	ui->gvMain->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}