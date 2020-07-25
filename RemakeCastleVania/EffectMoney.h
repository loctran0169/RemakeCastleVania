#pragma once
#include"GameObject.h"
#include"define.h"
#include"Utils.h"
#include"Game.h"

#define MAX_TIME_ALIVE	2000

class CEffectMoney : public CGameObject
{
	CGame * game;
	DWORD timeStart;
public:
	CEffectMoney(int _x, int _y, gameType model) {
		x = _x;
		y = _y;
		CGameObject::type = model;
		CAnimationSets * animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(EFFECT_MONEY);
		SetAnimationSet(ani_set);
		timeStart = GetTickCount();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void setFinish(bool _isFinish) { isFinish = _isFinish; }
	~CEffectMoney();
};
