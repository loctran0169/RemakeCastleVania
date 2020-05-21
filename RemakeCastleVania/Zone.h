#pragma once
#include"GameObject.h"
#include"define.h"
#include"Utils.h"
#include "Simon.h"

class CZone : public CGameObject // vùng hoạt động
{
public:
	float right, bottom;
	bool isCollitionSimon = false;
	bool isRight = false;
public:
	Simon * simon;
	CZone(int l, int t, int r, int b) :CGameObject() {
		simon = Simon::GetInstance();
		x = l;
		y = t;
		right = r;
		bottom = b;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CZone();
};

