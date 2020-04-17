#pragma once
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
	bool isAttact = false; // trạng thái đánh
	bool isEatItem = false; //trạng thái khi ăn whip item
	bool isJumpRight = false; // nhảy phải thì ko đổi hướng
	bool isJumpLeft = false;// nhảy trái thì ko đổi hướng
	bool isOnBase = false; //đang đúng dưới sàn
	bool isRenderLopping = false; //render ani còn lại khi khi đóng băng

	//autoGO
	bool isAutoGo=false;
	bool isAutoGoWithJump=false;
	float autoGoX1=0;
	float autoGoX2=0;
	float autoGoX3=0;

	DWORD timeEatItem = 0;
	gameType currentWeapon;
	unordered_map<int, CWeapon*>weapons;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void attackWeapon(gameType weaponType);

	void setEatItem(bool b) { isEatItem = b; }
	bool getEatItem() { return isEatItem; }
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	Simon();
};