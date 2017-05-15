#include "ProImage.h"
ProImage::ProImage()
{
	
}

ProImage::~ProImage()
{

}

void ProImage::Init()
{
	//veccon.clear();
	//chosen.clear();
	vecImageCon.clear();
	//reset();
}

void ProImage::reset()
{
	selectindex = -1;
	recoverflag = 0;
}

void ProImage::preproImage()
{
	/****������Ȧ�������ȸ�ʴȥ���޳����ɾ�����������ʹ�����ͽ�������������������Ч����***/
	int morph_elem = 2;		//Element:\n 0: Rect - 1: Cross - 2: Ellipse
	int morph_size = 3;
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	erode(m_image, m_image, element, Point(-1, -1), 1);
	dilate(m_image, m_image, element, Point(-1, -1), 2);
	
	medianBlur(m_image, m_image, 3);
	//GaussianBlur(m_image, m_image, Size(3, 3), 0, 0);
	//imwrite("houghtest.jpg", m_image);

	
	//morphologyEx(m_image, m_image, MORPH_OPEN, element);
	//imshow("Proimage", m_image);
}

void ProImage::getContour()
{
	//dubug��
	sykcheck = srcimage.clone();
	cvtColor(sykcheck, sykcheck, CV_BGR2HSV);

	this->preproImage();			//Ԥ����
	Mat conimage;
	cvtColor(m_image, conimage, CV_BGR2GRAY);
	conindex = Mat(m_image.rows, m_image.cols, CV_8UC1, Scalar::all(0));
	findContours(conimage, veccon, hierachy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<int> index;

	for (int i = 0; i < veccon.size(); i++)		//ȥ��ϸС����
		if (contourArea(veccon[i]) < m_image.cols*m_image.rows / 50)
		{
			veccon.erase(veccon.begin() + i);
			i--;
		}
	sort(veccon.begin(), veccon.end(), ProImage::compArea);
	
	////////ʹ��ImageCon�洢������Ϣ/////////
	vecImageCon.resize(veccon.size());
	for (int i = 0; i < vecImageCon.size(); i++)
	{
		//inputCon(vector<Point> &_contour, const int &_value, const int &_flag, const int &_thicklinesize, const int &_thinlinesize)
		vecImageCon[i].inputCon(veccon[i], i + 1, 1, 8, 2);			
		vecImageCon[i].cvtCon2Mat(srcimage);
	}

	angleindex = 0;
	vecImageCon[angleindex].angleflag = 1;			//Ĭ�Ͻ�������������Ϊ�����Ƕ�ѡ��Ļ�׼����
	////////////////////////////////////////

}

void ProImage::setImageWin(const string &_winname)
{
	if (_winname.empty())
		return;
	winname = _winname;
	
	chosen.clear();
	reset();
	//////��ʼ������ͼ�񣬽������������////////
	//m_showimage = srcimage.clone();
	//for (int i = 0; i < veccon.size(); i++)
	//	coverImage(m_showimage, r_orgcon[i]);
	//reset();
	namedWindow(winname, WINDOW_AUTOSIZE);
	///////////////////////////////////////
}

void ProImage::initWin()
{
	m_showimage = srcimage.clone();
	for (int i = 0; i < vecImageCon.size(); i++)
		coverImage(m_showimage, vecImageCon[i].show_image);
	reset();
	//m_showimage = vecImageCon[0].show_image.clone();
	//imshow(winname, m_showimage);
	//showState();
}

void ProImage::coverImage(Mat &dst, Mat &img)			//ԭͼ��dst�ϸ���img
{
	CV_Assert(dst.size() == img.size() && dst.channels() == img.channels());
	int nChannels = img.channels();
	int nRows = img.rows;
	int nCols = img.cols;
	if (img.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	uchar* p;
	uchar* q;
	for(int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
		{
			p = img.ptr<uchar>(i);
			q = dst.ptr<uchar>(i);
			int k = 0;
			for (k = 0; k < nChannels; k++)
				if (p[j*nChannels+k] != 0)
					break;
			if (k < 3)
				for (k = 0; k < nChannels; k++)
					q[j*nChannels + k] = p[j*nChannels + k];					
		}
}

void ProImage::highlightImage(const int &_selectindex)
{
	ImageCon &src = vecImageCon[_selectindex];
	drawContours(m_showimage, vector<vector<Point>>(1, src.contour), -1, src.color, src.thicklinesize);
	//imshow(winname, m_showimage);
}

void ProImage::lowlightImage(const int &_selectindex)
{
	Mat &img1 = vecImageCon[_selectindex].show_image;
	Mat &img2 = srcimage;
	Mat &mask = vecImageCon[_selectindex].value_image;		//������
	Mat &dst = m_showimage;
	CV_Assert(dst.size() == img1.size() && dst.channels() == 3 && 
		mask.channels() == 1 && img1.channels() == 3 && img2.channels() == 3);
	int pChannels = mask.channels();		//mask��ͨ��������ͨ��
	int qChannels = dst.channels();			//img1, img2��dst��ͨ��������ͨ��
	int nRows = img1.rows;
	int nCols = img1.cols;
	if (img1.isContinuous() && img2.isContinuous() && dst.isContinuous() && mask.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	uchar* p_img1;			//img1��ָ��
	uchar* p_img2;
	uchar* p_dst;
	uchar* p_mask;
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
		{
			p_img1 = img1.ptr<uchar>(i);
			p_img2 = img2.ptr<uchar>(i);
			p_dst = dst.ptr<uchar>(i);
			p_mask = mask.ptr<uchar>(i);
			if (p_mask[j*pChannels] != 0)
			{
				int k;
				for (k = 0; k < qChannels; k++)
				{
					if (p_img1[j*qChannels + k] != 0)
						break;
				}
				if (k >= qChannels)				//˵���õ㲻��show image�ϣ��ָ�Ϊsrcimage
				{
					for (k = 0; k < qChannels; k++)
						p_dst[j*qChannels + k] = p_img2[j*qChannels + k];
				}
				else							//��show image�ķ�Χ�ڣ��ָ�Ϊcolor
				{
					for (k = 0; k < qChannels; k++)
						p_dst[j*qChannels + k] = vecImageCon[_selectindex].color[k];
				}
			}
		}
	imshow(winname, dst);
}

void ProImage::fitContour()
{
	for (int i = 0; i < vecImageCon.size(); i++)
	{
		if (vecImageCon[i].flag == CON_IGNORE)
		{
			vecImageCon.erase(vecImageCon.begin() + i);
			i--;
			continue;
		}
		vecImageCon[i].fitContour();
	}
}

void ProImage::writeResult(string _imgname)		//��¼�����Ĵ�����
{

	Mat result = srcimage.clone();
	for (int i = 0; i < vecImageCon.size(); i++)
	{
		ImageCon &src = vecImageCon[i];
		switch (src.flag)
		{
		case CON_IGNORE:
			break;
		case CON_NORMAL:
			drawContours(result, vector<vector<Point>>(1, src.contour), -1, src.color, src.thinlinesize);
			break;
		case CON_POLY:
			drawContours(result, vector<vector<Point>>(1, src.polycontour), -1, src.color, src.thinlinesize);
			break;
		case CON_ELLIPSE:
			ellipse(result, src.ellipsebox, src.color, 2, CV_AA);
			break;
		}
	}
	if (_imgname == "")
		_imgname = "result.jpg";
	//imshow(_imgname, result);
	imwrite(_imgname, result);
}

int ProImage::compArea(vector<Point> first, vector<Point> second)
{
	return contourArea(first) > contourArea(second);
}

void ProImage::onMouseHandle(int event, int x, int y, int flags, void* param)
{
	ProImage& proimage = *(ProImage*)param;
	int index = 0;							//��������ֵ����ֵ��ʾ��������
	if (y < 0 || y >= proimage.srcimage.rows || x < 0 || x >= proimage.srcimage.cols)
		return;
	for (int i = 0; i < proimage.vecImageCon.size(); i++)
	{
		if (proimage.vecImageCon[i].value_image.at<uchar>(y, x) != 0)
		{
			index = proimage.vecImageCon[i].value_image.at<uchar>(y, x);
			break;
		}
	}
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:		//��������������ѡ��������ɫ��״̬������Ӧ����
		if (index > 0)
		{
			int &_flag = proimage.vecImageCon[index - 1].flag;
			_flag++;
			if (_flag >= sizeof(ImageCon::g_color) / sizeof(Scalar))
				_flag = 0;
			proimage.vecImageCon[index - 1].updateColor();
		}
		proimage.showState();
		break;
	case CV_EVENT_MOUSEMOVE:
		cout << proimage.sykcheck.at<Vec3b>(y, x) << endl;
		if (index > 0)
		{
			proimage.highlightImage(index - 1);
			proimage.selectindex = index;
		}
		else
		{
			if (proimage.selectindex != -1)
			{
				proimage.lowlightImage(proimage.selectindex - 1);
				proimage.selectindex = -1;
			}
		}
		break;
	case CV_EVENT_RBUTTONDOWN:
		if (index > 0)
		{
			if (index - 1 != proimage.angleindex)
			{
				/***����proimage��angleindex***/
				proimage.vecImageCon[proimage.angleindex].angleflag = 0;
				proimage.angleindex = index - 1;
				proimage.vecImageCon[proimage.angleindex].angleflag = 1;
				proimage.showState();
			}
			break;
		}
	}
}

void ProImage::slot_receive_mouse_move_pos(int x, int y, int event)
{
	int index = 0;							//��������ֵ����ֵ��ʾ��������
	if (y < 0 || y >= this->srcimage.rows || x < 0 || x >= this->srcimage.cols)
		return;
	for (int i = 0; i <this->vecImageCon.size(); i++)
	{
		if (this->vecImageCon[i].value_image.at<uchar>(y, x) != 0)
		{
			index = this->vecImageCon[i].value_image.at<uchar>(y, x);
			break;
		}
	}
	switch (event)
	{
	case QT_MOUSE_LBUTTONDOWN:		//��������������ѡ��������ɫ��״̬������Ӧ����
		if (index > 0)
		{
			int &_flag = this->vecImageCon[index - 1].flag;
			_flag++;
			if (_flag >= sizeof(ImageCon::g_color) / sizeof(Scalar))
				_flag = 0;
			this->vecImageCon[index - 1].updateColor();
		}
		this->showState();
		break;
	case QT_MOUSE_MOVE:
		cout << this->sykcheck.at<Vec3b>(y, x) << endl;
		if (index > 0)
		{
			this->highlightImage(index - 1);
			this->selectindex = index;
		}
		else
		{
			if (this->selectindex != -1)
			{
				this->lowlightImage(this->selectindex - 1);
				this->selectindex = -1;
			}
		}
		break;
	case QT_MOUSE_RBUTTONDOWN:
		if (index > 0)
		{
			if (index - 1 != this->angleindex)
			{
				/***����proimage��angleindex***/
				this->vecImageCon[this->angleindex].angleflag = 0;
				this->angleindex = index - 1;
				this->vecImageCon[this->angleindex].angleflag = 1;
				this->showState();
			}
			break;
		}
	}

}

void ProImage::getData(ProImage Temp)		//ProImage��֮�䴫�ݱ�ѡ������index
{
	CV_Assert(Temp.vecImageCon.size() == this->vecImageCon.size());
	for (int i = 0; i < this->vecImageCon.size(); i++)
	{
		this->vecImageCon[i].flag = Temp.vecImageCon[i].flag;
		this->vecImageCon[i].updateColor();
	}
}

void ProImage::printContour()			//��ȡʵ����ͼ�Ĵ���
{
	ofstream fresult;
	fresult.open("contour.txt", ios::in | ios::ate);
	if (fresult.is_open())
	{
		for (int i = 0; i < veccon.size(); i++)
		{
			if (i == veccon.size() - 1)
			{
				fresult << i << endl;
				for (size_t j = 0; j < veccon[i].size(); j++)
				{
					fresult << veccon[i][j].x << " " << veccon[i][j].y << endl;
				}
			}
		}
	}
}

void ProImage::showState()
{
	//CvFont font;
	//double hscale = 1.0;
	//double vscale = 1.0;
	//int linewidth = 2;
	//cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, hscale, vscale, 0, linewidth);
	//Scalar textColor = RED;
	system("CLS");
	for (int i = 0; i < vecImageCon.size(); i++)
	{
		printf("vecImageCon[%d] state:\n", i);
		switch (vecImageCon[i].flag)
		{
		case CON_NORMAL:
			printf("Fitting state: CON_NORMAL\n");
			break;
		case CON_ELLIPSE:
			printf("Fitting state: CON_ELLIPSE\n");
			break;
		case CON_POLY:
			printf("Fitting state: CON_POLY\n");
			break;
		case CON_IGNORE:
			printf("Fitting state: CON_IGNORE\n");
			break;
		}
		printf("*****************************\n");
	}
	printf("Standard angle index is: %d\n", angleindex);
	//printf("*****************************\n");
}

