#include "Line.h"
#include"Utils.h"

CLine::CLine(float _x1, float _y1, float _x2, float _y2)
{
	x1 = x1Def = _x1;
	x2 = x2Def = _x2;
	y1 = y1Def = _y1;
	y2 = y2Def = _y2;
	createLine(x1, y1, x2, y2);

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
	DebugOut(L"a b %f %f \n", a, b);
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
	return a;
}


float * CLine::toXY(float _dxy, float _dOY, bool isSwap)
{
	float *a = new float[4];
	a[0] = x1Temp + (_dxy / distance(x1, y1, x2, y2))*(x2 - x1Temp);
	x1Temp = a[0];
	a[1] = y1Temp + (_dxy / distance(x1, y1, x2, y2))*(y2 - y1Temp);
	y1Temp = a[1];
	a[2] = (x1 > x2) ? -1 : 1;
	a[3] = 0; //a[3] là check xem dừng lại hay ko
	if (y1 < y2Def && y1Temp >= _dOY && isReverse == false) {
		a[3] = 1;
	}
	else if (y1 > y2Def && y1Temp <= _dOY && isReverse == false) {
		a[3] = 1;
	}
	if (isSwap) {
		if ((y1 < y2Def && y1Temp >= y2Def)||(y1 > y2Def && y1Temp <= y2Def)) {
			x1Def = x1Def + abs(x1Def - x2Def) * 2 * ((x1Def < x2Def) ? 1 : -1);
			swap(x1Def, x2Def);
			swap(y1Def, y2Def);
			createLine(x1Def, y1Def, x2Def, y2Def);
			x1 = x1Def;
			y1 = y1Def;
			x2 = toX(_dOY);
			y2 = _dOY;
			y1Temp = toY(x1Temp);
			isReverse = false;
		}
	}
	return a;
}
