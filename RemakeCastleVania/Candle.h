#pragma once
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
class CCandle :public CGameObject
{
public:
	bool isFinish = false;

	CCandle() :CGameObject() {
		CGameObject::type = gameType::CANDLE;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	~CCandle();
};

