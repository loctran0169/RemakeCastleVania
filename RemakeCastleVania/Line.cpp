﻿#include "Line.h"
#include"Utils.h"

CLine::CLine(float _x1, float _y1, float _x2, float _y2)
{
	x1 = _x1;
	x2 = _x2;
	y1 = _y1;
	y2 = _y2;
	createLine(x1, y1, x2, y2);
	DebugOut(L"%f %f %f %f \n", x1, y1, x2, y2);

	if (x2 > x1) {
		x2 += 50.0f;
		y2 = toY(x2);
	}
	else {
		x2 -= 50.0f;
		y2 = toY(x2);
	}

	x1Temp = x1;
	y1Temp = y1;
}

void CLine::createLine(float _x1, float _y1, float _x2, float _y2)
{
	a = (_y1 - _y2) / (_x1 - _x2);
	b = (_y2*_x1 - _x2 * _y1) / (_x1 - _x2);
}

float CLine::toY(float _x)
{
	float tempY = (a*_x + b);
	return tempY;
}

float CLine::toX(float _Y)
{
	float tempX = (_Y - b) / a;
	return tempX;
}

float CLine::distance(float _x1, float _y1, float _x2, float _y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

float * CLine::toXY(float _dxy)
{
	float *a = new float[3];
	a[0] = x1Temp + (_dxy / distance(x1, y1, x2, y2))*(x2 - x1Temp);
	x1Temp = a[0];
	a[1] = y1Temp + (_dxy / distance(x1, y1, x2, y2))*(y2 - y1Temp);
	y1Temp = a[1];
	a[2] = (x1 > x2) ? -1 : 1;

	////cập nhật lại khi đi qua con tọa độ cần đi
	//if (x1Temp >= x2 && x2 >= x1) {
	//	x2 += 100.0f;
	//	y2 = toY(x2);
	//}
	//else if (x1 >= x2 && x2 >= x1Temp) {
	//	x2 -= 100.0f;
	//	y2 = toY(x2);
	//}
	return a;
}
