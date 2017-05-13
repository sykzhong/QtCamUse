#ifndef QTCAMUSE_MOVE_H
#define QTCAMUSE_MOVE_H

#include <QtGui>

#include <QtCamUse.h>
#include "CameraApi.h"
#include "ImageProcess.h"
#include "QtCamUse_process.h"

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
	ImageProcess *m_imageprocess;			//����ͼ���������

private:
	Ui::QtCamUse_moveClass *ui;

	QGraphicsScene *m_scene;				//����ͷͼ����ʾ��scene
	QTimer *m_timer;						//��������ͷ״̬��ʱ����

	CaptureThread* m_thread;				
	QMutex mutex;							//ͬ����
	QGraphicsPixmapItem *m_image_item;


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
};

#endif