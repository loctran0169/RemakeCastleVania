#pragma once
#include "GameObject.h"
#include "Brick.h"
#include"define.h"
#include"Whip.h"
#include <algorithm>
#include "Utils.h"
#include "Game.h"
#include"Torch.h"

class Simon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	//trạng thái đứng ca
	bool isStair = false;

	//hành cộng
	
	DWORD attactTime = 0;
	
public:
	bool nextScreen;
	DWORD timeWait = 0;
	bool isSit = false;
	bool isJump = false;
	bool isAttact = false;
	Simon() : CGameObject()
	{
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
};