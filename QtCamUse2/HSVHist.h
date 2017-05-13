#ifndef _HSVHIST_H_
#define _HSVHIST_H_
#include "GlobalHeader.h"
#include "capturethread.h"

class HSVHist:public QObject
{
	Q_OBJECT
public:
	HSVHist();
	~HSVHist();
	int getImage(string path);
	int getImage(Mat &image);

	void getHist(Mat &mask = Mat());
	void drawHist();
	void removeSeg(HSVHist &back);
	static Mat removeBack(HSVHist& dst, HSVHist& back);
	void showImage(string strpath = "");
	void Init();
	void Split(const Mat& src, Mat* mv, Mat &mask);			//�������split�������ֽ����õ�ͨ��mat����Ϊ1�����ڱ���ͼ��
private:
	Mat hsvplane[3];		//�洢HSV��ͨ��
	
	float svrange[2];
	float hrange[2];
	const float *ranges[3];	//hsv��ȡֵ��Χ
	double maxval;			//ԭʼ�����е����ֵ

	int bin_w;				//ֱ��ͼ������
	int hist_h, hist_w;		//ֱ��ͼ�����
	Mat hist_img;			//������ʾ������ֱ��ͼ

protected:
	string path;			//ԭͼ·��

	Mat srcimage;			//ԭͼ��,��ȡΪHSV��ʽ
	Mat m_image;
	Mat hsvhist;			//���ڴ洢ֱ��ͼ������
	int histsize[3];		//hsv��ֱ��ͼ�зֲ���

	CaptureThread *m_thread;		//����ͼ�����ݵ��߳�

private slots:
	//void slot_receive_image(QImage);
};


#endif

