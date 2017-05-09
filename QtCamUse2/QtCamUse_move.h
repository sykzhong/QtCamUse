#ifndef QTCAMUSE_MOVE_H
#define QTCAMUSE_MOVE_H

#include <QtGui>

#include <QtCamUse.h>
#include "CameraApi.h"

namespace Ui
{
	class QtCamUse_moveClass;
}

class QtCamUse_move :public QMainWindow
{
	Q_OBJECT
public:
	//QtCamUse_move(QWidget *parent = 0);
	QtCamUse_move(QWidget *parent = 0);
	~QtCamUse_move();
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);
	int status;

protected:

private:
	Ui::QtCamUse_moveClass *ui;

	QGraphicsScene *m_scene;				//摄像头图像显示的scene
	QTimer *m_timer;						//更新摄像头状态的时间类

	CaptureThread* m_thread;				
	QMutex mutex;							//同步锁
	QGraphicsPixmapItem *m_image_item;

signals:
	void back_to_mainwindow();

private slots:
	void Image_process(QImage img);
	void on_pushButton_back_to_mainwindow_clicked();
};

#endif