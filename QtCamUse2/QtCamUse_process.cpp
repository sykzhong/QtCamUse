#include "QtCamUse_process.h"
#include "ui_QtCamUse_process.h"

QtCamUse_process::QtCamUse_process(QWidget *parent, QtImageProcess *_m_imageprocess)
	:ui(new Ui::QtCamUse_processClass),
	m_scene(0), 
	m_image_item(0), 
	m_imageprocess(_m_imageprocess)
{
	ui->setupUi(this);
	m_scene = new QtCamUse_process_ChildScene();
	ui->gvMain->setScene(m_scene);

	this->setMouseTracking(true);
	ui->gvMain->setMouseTracking(true);

	qRegisterMetaType< cv::Mat >("cv::Mat");
	connect(m_imageprocess, SIGNAL(proResult(QImage)), this, SLOT(ImageShow(QImage)));

	connect(this->m_scene, SIGNAL(mouse_move_pos(int, int, int)), m_imageprocess, SLOT(slot_receive_mouse_event(int, int, int)));
}

QtCamUse_process::~QtCamUse_process()
{

}

void QtCamUse_process::ImageShow(QImage image)
{
	disconnect(this->m_scene, SIGNAL(mouse_move_pos(int, int, int)), m_imageprocess, SLOT(slot_receive_mouse_event(int, int, int)));
	//终止鼠标事件的响应，防止fitinview引起的鼠标事件循环响应死锁bug
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
	//重启鼠标事件响应
	connect(this->m_scene, SIGNAL(mouse_move_pos(int, int, int)), m_imageprocess, SLOT(slot_receive_mouse_event(int, int, int)));
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

void QtCamUse_process_ChildScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
	int x = e->scenePos().x();
	int y = e->scenePos().y();
	if (point.x() != x || point.y() != y)
	{
		point.setX(x);
		point.setY(y);
		emit mouse_move_pos(x, y, QT_MOUSE_MOVE);			//用于传输给ImageProcess类的slot
	}
	else
		return;
}