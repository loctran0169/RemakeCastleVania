#pragma once
#include<math.h>
#include<algorithm>
#include"GameObject.h"
#include"Expression.h"

class CParabol
{
private: 
	float a, b, c;
	float x1, x2, y1, y2;
	float x1Temp, y1Temp;
public:
	CParabol(float _x1, float _y1, float _x2, float _y2);
	void createParabol(float _x1, float _y1, float _x2, float _y2);
	float toY(float _x);
	float toX(float _Y);

	float getX1() { return x1; }
	float getX2() { return x2; }

	float distance(float _x1, float _y1, float _x2, float _y2);

	float * toXY(float _dxy, float dyAttack);
	float * toXYPauseWhenOnI(float _dxy);
	~CParabol();
};

