#pragma once
#include<math.h>
class CPoint
{
public:
	int x=0, y=0, nx=0;
public:
	CPoint(){}
	CPoint(int _x, int _y) {
		x = _x;
		y = _y;
	}
	CPoint(int _x, int _y, int _nx) {
		x = _x;
		y = _y;
		nx = _nx;
	}
};