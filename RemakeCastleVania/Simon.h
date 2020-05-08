﻿#pragma once
#include "GameObject.h"
#include "Brick.h"
#include"define.h"
#include"Whip.h"
#include "Utils.h"
#include "Game.h"
#include"Torch.h"
#include"Portal.h"
#include"Map.h"
#include"PlayScence.h"

class Simon : public CGameObject
{
public:
	CGame *game;
	int level;
	int untouchable;
	int currentAni;
	int prevAni;
	int heartWeapon;
	
	//thời gian hành động
	DWORD untouchable_start;
	DWORD attactTime = 0;
	DWORD jumpTime = 0;
	DWORD timeFreeze = 0;
	
public:
	
	bool isSit = false;//trạng thái ngồi
	bool isJump = false; // trạng thái nhảy
	bool isAllowJump = true; //cho phép nhảy
	bool isAttact = false; // trạng thái đánh
	bool isEatItem = false; //trạng thái khi ăn whip item
	bool isJumpRight = false; // nhảy phải thì ko đổi hướng
	bool isJumpLeft = false;// nhảy trái thì ko đổi hướng
	bool isOnBase = false; //đang đúng dưới sàn
	bool isRenderLopping = false; //render ani còn lại khi khi đóng băng

	//cầu thang
	bool isOnCheckStairUp = false; //đang đúng bật cầu thang đi lên
	float nxCheckStairUp = 1; //chìu x đi lên
	float xStairUp = 0;
	bool isOnCheckStairDown = false; // đang đứng bật cầu thang đi xuống
	float nxCheckStairDown = 1; // chìu x đi xuống
	float midleStairDown = 0;
	bool isStair = false; //đang đứng cầu thang
	bool isGoUp = false; //đi lên cầu thang
	bool isGoDown = false; // đi xuống cầu thang
	float distanceYGone = 0;
	float ground_Y = 0.0f;

	float autoGoX_Default = 0;
	float autoGoX_Distance = 0;
	float autoGoY_Default = 0;
	float autoGoY_Distance = 0;
	int state_new = 0;
	int nx_new = 0;
	//autoGO
	bool isAutoGo=false;
	bool isAutoGoWithJump=false;
	float collXFirst = 0;

	DWORD timeEatItem = 0;
	gameType currentWeapon;
	unordered_map<int, CWeapon*>weapons;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void attackWeapon(gameType weaponType);
	void checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void setValueAutoGo(float disX, float disY, int new_state, int new_nx);
	void goUpStair();

	void setEatItem(bool b) { isEatItem = b; }
	bool getEatItem() { return isEatItem; }
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	Simon();
};