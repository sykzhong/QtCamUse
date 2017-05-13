#ifndef QTCAMUSE_PROCESS_H
#define QTCAMUSE_PROCESS_H

#include <QtGui>

#include <QtCamUse.h>
#include "CameraApi.h"
#include "ImageProcess.h"


namespace Ui
{
	class QtCamUse_processClass;
}

class QtCamUse_process :public QMainWindow
{
	Q_OBJECT
public:
	QtCamUse_process(QWidget *parent, ImageProcess *);
	~QtCamUse_process();
	//void showEvent(QShowEvent *);
	//void closeEvent(QCloseEvent *);

	QImage MattoQImage(Mat &);
protected:

private:
	Ui::QtCamUse_processClass *ui;
	QGraphicsScene *m_scene;				//����ͷͼ����ʾ��scene
	QTimer *m_timer;						//��������ͷ״̬��ʱ����
	QGraphicsPixmapItem *m_image_item;

	ImageProcess *m_imageprocess;			
private slots:
	void ImageShow(QImage image);
};

#endif