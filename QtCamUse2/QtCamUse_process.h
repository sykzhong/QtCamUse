#ifndef QTCAMUSE_PROCESS_H
#define QTCAMUSE_PROCESS_H

#include <QtGui>

#include <QtCamUse.h>
#include "CameraApi.h"
#include "QtImageProcess.h"
#include <qgraphicsscene.h>
#include <QGraphicsSceneMouseEvent>

namespace Ui
{
	class QtCamUse_processClass;
}

class QtCamUse_process_ChildScene :public QGraphicsScene
{
Q_OBJECT
signals :
	void mouse_move_pos(int, int, int);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *);
};

class QtCamUse_process :public QMainWindow
{
	Q_OBJECT
public:
	QtCamUse_process(QWidget *parent, QtImageProcess *);
	~QtCamUse_process();
	void showEvent(QShowEvent *);
	void resizeView();
	//void closeEvent(QCloseEvent *);

	QImage MattoQImage(Mat &);
protected:

private:
	Ui::QtCamUse_processClass *ui;
	QtCamUse_process_ChildScene *m_scene;				//摄像头图像显示的scene
	QTimer *m_timer;						//更新摄像头状态的时间类
	QGraphicsPixmapItem *m_image_item;

	QtImageProcess *m_imageprocess;			
private slots:
	void ImageShow(QImage image);
};

#endif