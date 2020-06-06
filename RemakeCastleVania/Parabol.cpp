#include "Parabol.h"



CParabol::CParabol(float _x1, float _y1, float _x2, float _y2)
{
	x1 = _x1;
	x2 = _x2;
	y1 = _y1;
	y2 = _y2;
	if (abs(x1 - x2) <= 32) {
		if(x1>=x2)
			x2 += 32;
		else
			x2 -= 32;
	}

	createParabol(x2, y2, x1, y1);
	x1Temp = x1;
	y1Temp = y1;
}

void CParabol::createParabol(float _x1, float _y1, float _x2, float _y2)
{
	if (y1 < y2) {
		a = (_y2 - _y1) / pow((_x1 - _x2), 2);
		b = -2 * a*_x1;
		c = _y1 - a * pow(_x1, 2) - b * _x1;
	}
	else {
		a = (_y1 - _y2) / pow((_x1 - _x2), 2);
		b = -2 * a*_x2;
		c = _y1 - a * pow(_x1, 2) - b * _x1;
	}
}

float CParabol::toY(float _x)
{
	return a * pow(_x, 2) + b * _x + c;
}

float CParabol::toX(float _Y)
{
	return 0.0f;
}

float CParabol::distance(float _x1, float _y1, float _x2, float _y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

float * CParabol::toXY(float _dxy, float dyAttack)
{
	float *hs = new float[4];

	hs[0] = x1Temp + _dxy * ((x1 < x2) ? 1 : -1);
	x1Temp = hs[0];
	hs[1] = toY(hs[0]);
	y1Temp = hs[1];
	hs[2] = (x1 > x2) ? -1 : 1;
	hs[3] = 0; //a[3] là check xem dừng lại hay ko
	if (y1Temp <= dyAttack) // chạm tới trục y có gị trị này thì dừng lại
		hs[3] = 1;
	return hs;
}

float * CParabol::toXYPauseWhenOnI(float _dxy)
{
	float *hs = new float[4];

	hs[0] = x1Temp + _dxy * ((x1 < x2) ? 1 : -1);
	x1Temp = hs[0];
	hs[1] = toY(hs[0]);
	y1Temp = hs[1];
	hs[2] = (x1 > x2) ? -1 : 1;
	hs[3] = 0; //a[3] là check xem dừng lại hay ko
	if (abs(y1Temp - y2) < 1)
		hs[3] = 1;
	return hs;
}

CParabol::~CParabol()
{
}
