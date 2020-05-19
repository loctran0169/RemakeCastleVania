#pragma once
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"

//Torch
#define CANDLE_BBOX_WIDGHT							16
#define CANDLE_BBOX_HEIGHT							32

class CCandle :public CGameObject
{
public:
	CCandle() :CGameObject() {
		CGameObject::type = gameType::CANDLE;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	~CCandle();
};

