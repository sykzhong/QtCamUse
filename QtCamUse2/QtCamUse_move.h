#ifndef QTCAMUSE_MOVE_H
#define QTCAMUSE_MOVE_H

#include <QtGui>
#include <QMouseEvent>

#include <QtCamUse.h>
#include "CameraApi.h"
#include "QtImageProcess.h"
#include "QtCamUse_process.h"

#include <qgraphicsscene.h>
#include <QGraphicsSceneMouseEvent>

namespace Ui
{
	class QtCamUse_moveClass;
}

class QtCamUse_move_ChildScene :public QGraphicsScene
{
	Q_OBJECT
signals :
	void mouse_move_pos(int, int);
protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *);
};

class QtCamUse_move :public QMainWindow
{
	Q_OBJECT
public:
	//QtCamUse_move(QWidget *parent = 0);
	QtCamUse_move(QWidget *parent = 0);
	~QtCamUse_move();
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);
	void resizeEvent(QResizeEvent *);
	void resizeView();
	int status;

protected:
	QtImageProcess *m_imageprocess;			//进行图像处理的正体

private:
	Ui::QtCamUse_moveClass *ui;

	QtCamUse_move_ChildScene *m_scene;				//摄像头图像显示的scene
	QTimer *m_timer;						//更新摄像头状态的时间类

	CaptureThread* m_thread;				
	QMutex mutex;							//同步锁
	QGraphicsPixmapItem *m_image_item;

	QLabel *m_mouse_pos;

signals:
	void back_to_mainwindow();
	void get_template_image();
	void get_back_image();

private slots:
	void Image_process(QImage img);
	void on_pushButton_back_to_mainwindow_clicked();
	void on_pushButton_get_back_save_clicked();
	void on_pushButton_get_back_load_clicked();
	void on_pushButton_get_template_save_clicked();
	void on_pushButton_get_template_load_clicked();
	void on_pushButton_image_process_clicked();
	void slot_mouse_move_pos_show(int, int);
};

#endif