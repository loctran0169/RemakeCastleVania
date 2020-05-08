#pragma once
#include"GameObject.h"
#include"define.h"
#include"Sprites.h"
#include"Brick.h"
#include <algorithm>

class Item : public CGameObject
{
public:
	bool isPicked = false;
	DWORD timeExit;
	Item(gameType _type) : CGameObject() {
		CGameObject::type = _type;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	~Item();
};

