#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Utils.h"
class CMonter : public CGameObject
{
	bool isDead = false;
public:
	CMonter() :CGameObject() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CMonter();
};

