#pragma once
#include"GameObject.h"
#include"define.h"
#include"Sprites.h"
#include"Brick.h"
#include <algorithm>

#define SMALLHEART_SPEED_X 0.04f
#define SMALLHEART_SPEED_Y 0.075f

#define	MAXTIME_FULLHP		10000
class Item : public CGameObject
{
private:
	float boundRight, boundLeft;
	int maxTimeExit = ITEM_TIME_EXIT;
public:
	bool isPicked = false;
	DWORD timeExit = 0;
	Item(gameType _type) : CGameObject() {
		CGameObject::type = _type;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void setValueGravity(float _l, float _r, float _vx, float _vy);
	void setMaxTimeExit(int _maxTimeExit = ITEM_TIME_EXIT) { maxTimeExit = _maxTimeExit; }
	~Item();
};

