#include "ImageCon.h"

const Scalar ImageCon::g_color[4] = { WHITE, RED, BLUE, GREEN };

void ImageCon::inputCon(vector<Point> &_contour, const int &_value, const int &_flag, const int &_thicklinesize, const int &_thinlinesize)
{
	contour.resize(_contour.size());
	flag = _flag;
	color = g_color[flag];
	thicklinesize = _thicklinesize;
	value = _value;
	thinlinesize = _thinlinesize;
	copy(_contour.begin(), _contour.end(), contour.begin());
	angleflag = 0;
}

void ImageCon::cvtCon2Mat(const Mat &_template)
{
	value_image = Mat(_template.size(), CV_8UC1, Scalar::all(0));
	show_image = Mat(_template.size(), CV_8UC3, Scalar::all(0));
	drawContours(value_image, vector<vector<Point>>(1, contour), -1, Scalar(value), thicklinesize);		//������������ֵͼ������״̬��ϸ��
	drawContours(show_image, vector<vector<Point>>(1, contour), -1, color, thinlinesize);				//��������(�Ǹ���״̬��ϸ)
}

void ImageCon::fitContour()
{
	switch (flag)
	{
	case CON_POLY:
		approxPolyDP(contour, polycontour, 5, true);
		break;
	case CON_ELLIPSE:
		Mat pointsf;
		Mat(contour).convertTo(pointsf, CV_32F);
		ellipsebox = fitEllipse(pointsf);	
		break;
	}
	if (flag != CON_IGNORE)
		getCenterTh();
}

void ImageCon::updateColor()
{
	color = g_color[flag];
}

void ImageCon::getCenterTh()
{
	switch (flag)
	{
	case CON_POLY:
		CV_Assert(polycontour.size() >= 1);
		conmoment = moments(polycontour, false);
		concenter = Point2f(conmoment.m10 / conmoment.m00, conmoment.m01 / conmoment.m00);
		conth = 0.5*atan(2 * conmoment.nu11 / (conmoment.nu20 - conmoment.nu02));
		conth_degrees = conth / PI * 180;
		break;
	case CON_ELLIPSE:
		CV_Assert(ellipsebox.size.width != 0);
		/*ֱ��ʹ����Բ��Ͻ����Ϊ���ĺͽǶ�ֵ*/
		concenter = ellipsebox.center;
		conth = (ellipsebox.angle - 90) / 180 * PI;				//ellipsebox.angleΪ��Բ������y�Ḻ����ļнǣ�-90��ת��Ϊx��������ļн�
		conth_degrees = conth / PI * 180;
		break;
	case CON_NORMAL:
		CV_Assert(contour.size() >= 1);
		conmoment = moments(contour, false);
		concenter = Point2f(conmoment.m10 / conmoment.m00, conmoment.m01 / conmoment.m00);
		conth = 0.5*atan(2 * conmoment.nu11 / (conmoment.nu20 - conmoment.nu02));
		break;
	case CON_IGNORE:
		CV_Assert(0);
	}

}