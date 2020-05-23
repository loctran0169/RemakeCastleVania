#pragma once
#include<math.h>

class CLine
{
private:
	float a, b;
	float x1, x2, y1, y2;
	float x1Temp, y1Temp;
public:
	CLine(float _x1, float _y1, float _x2, float _y2);
	void createLine(float _x1, float _y1, float _x2, float _y2);
	float toY(float _x);
	float toX(float _Y);

	float distance(float _x1, float _y1, float _x2, float _y2);

	float * toXY(float _dxy);

	~CLine() { a = b = NULL; }
};

