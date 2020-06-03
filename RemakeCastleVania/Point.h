#pragma once
#include<math.h>
class CPoint
{
public:
	float x=0, y=0, nx=0;
public:
	CPoint(){}
	CPoint(float _x, float _y) {
		x = _x;
		y = _y;
	}
	CPoint(float _x, float _y, float _nx) {
		x = _x;
		y = _y;
		nx = _nx;
	}
	void setPosition(float _x, float _y , float _nx = 1) {
		x = _x;
		y = _y;
		nx = _nx;
	}
};