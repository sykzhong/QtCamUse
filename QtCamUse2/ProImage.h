#ifndef _PROIMAGE_H_
#define _PROIMAGE_H_
#include "HSVHist.h"
#include "ImageCon.h"
#include <set>
#include <fstream>
using namespace std;
using namespace cv;

enum QtMouseEvent
{
	QT_MOUSE_LBUTTONDOWN = 0,
	QT_MOUSE_MOVE = 1,
	QT_MOUSE_RBUTTONDOWN = 2
};

class ProImage:public HSVHist
{
	Q_OBJECT
public:
	ProImage();
	~ProImage();
	void preproImage();										//��ͼ�����Ԥ����

	void Init();											//������ز�����ʼ��
	void setImageWin(const string &_winname);				//�趨����������ʾ����
	void initWin();											//��ʼ�����ڣ���ʼ��ʾͼ�ν��棩

	void getContour();										//��ȡͼ��������ȥ������������
	
	//void showImage();										//�����û����������ʾ����
	void coverImage(Mat &dst, Mat &img);					//��dstʹ��img���и���
	void highlightImage(const int &_selectindex);			//���û�ѡ����������и�����ʾ
	void lowlightImage(const int &_selectindex);			//���û�����ѡ��������ָ�������ʾ
	void fitContour();										//�����û�������������������������

	void getData(ProImage Temp);							//���ڽ�ģ�����ݴ�����dst
	void printContour();

	void showState();										//���������������������״̬�Լ��ǶȻ�׼���

	void writeResult(string _imgname = "");					//��ʾ�û����������ս��

	static void onMouseHandle(int event, int x, int y, int flags, void* param);
	void proMouseEvent(int x, int y, int event);
	static int compArea(vector<Point> first, vector<Point> second);

	void reset();

	Mat transProResult();									//��Ϊ���⴫����ʾͼ���ͨ��
private:
	Mat conindex;						//��¼��������ֵ
	vector<Vec4i> hierachy;				//�����ȼ�

	string winname;						//�û�������������
	Mat m_showimage;					//�û���������ͼ��

	
	vector<Mat> r_orgcon;				//�ֿ�洢ԭ����
	vector<Mat> b_orgcon;				//�ֿ�洢ԭ������������ʾ��

	int selectindex;					//��¼��ѡ��ĵ�����������
	int recoverflag;					//�Ƿ�ԭ�ı�ǣ���ʾ�ã�

	Mat sykcheck;						//debug ��
protected:
	vector<ImageCon> vecImageCon;		//�洢����������Ϣ

	vector<vector<Point>> veccon;		//��¼ԭʼ����
	set<int> chosen;					//��¼��ѡ���������������
	vector<vector<Point>> vecpoly;		//��¼���ж������ϵ�����
	vector<RotatedRect> vececllipse;	//��¼������Բ��ϵ�����

	int angleindex;						//��¼��Ϊ�ǶȻ�׼������������Ĭ��Ϊ��������0��
public slots:
	void slot_receive_mouse_move_pos(int, int, int);
	
};
#endif