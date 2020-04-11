#pragma once
#include "GameObject.h"
#include "Brick.h"
#include"define.h"
#include"Whip.h"
#include <algorithm>
#include "Utils.h"
#include "Game.h"
#include"Torch.h"
#include"Portal.h"
#include"Map.h"
#include"PlayScence.h"

class Simon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	//trạng thái đứng ca
	bool isStair = false;
	//thời gian hành động
	DWORD attactTime = 0;
	DWORD jumpTime = 0;
	
public:
	Whip *whip;
	bool nextScreen;
	DWORD timeWait = 0;
	bool isSit = false;
	bool isJump = false;
	bool isAttact = false;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	Simon();
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
};