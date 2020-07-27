#pragma once
#include "GameObject.h"
#include "Brick.h"
#include"SkateBoard.h"
#include"define.h"
#include"Whip.h"
#include "Utils.h"
#include "Game.h"
#include"Torch.h"
#include"Portal.h"
#include"Map.h"
#include"Knife.h"
#include"Boomerang.h"
#include"Axe.h"
#include"WaterFire.h"
#include"Sound.h"

#define TIME_REVERT_HP_STEP		400
#define TIME_REVERT				1900
class Simon : public CGameObject
{
private:
	static Simon* __instance;
public:
	CGame *game;
	int untouchable;
	int currentAni;
	int prevAni;
	int numLife = 1;//max 3
	int health = 2;//MAX_HP;
	int heartWeapon = 5;
	int timeTouchable = SIMON_UNTOUCHABLE_TIME;
	float stateSpeed = 0.0f;
	//thời gian hành động
	bool isDie = false;
	DWORD timeDieStart = 0;

	DWORD lastTimeChangeState = 0;
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
	bool isRenderLopping = false; //render ani còn lại khi khi đóng băng
	bool isUseToFullHP = false; //trạng thái bơm hp từ từ
	bool isHurt = false; //Trạng thái bị đánh
	int nxHurt = 1;

	bool isUseTransparent = false; // sử dụng bình màu vàng ko va chạm

	//cầu thang
	bool isOnCheckStairUp = false; //đang đúng bật cầu thang đi lên
	float nxCheckStairUp = 1; //chìu x đi lên
	float xStairUp = 0;
	bool isOnCheckStairDown = false; // đang đứng bật cầu thang đi xuống
	float nxCheckStairDown = 1; // chìu x đi xuống
	float xStairDown = 0;
	bool isStair = false; //đang đứng cầu thang
	bool isGoUp = false; //đi lên cầu thang
	bool isGoDown = false; // đi xuống cầu thang
	bool isGoStairByUp = false; // trạng thái đi lên bằng cầu thang dưới

	bool isUseDoubleShot = false; // dùng double shot
	bool isUseTripleShot = false; // dùng triple shot
	bool isUsePotion = false; // dùng bình nẩ thân
	//bool isOnGround = false;

	//autoGO
	bool isAutoGo = false; //tự động đi
	bool nextAutoGo = false; //tự động đi sau tự động đi
	bool isAutoGoWithJump = false;
	float collXFirst = 0;
	float autoGoX_Distance = 0;
	float autoGoY_Distance = 0;
	int state_new = 0;
	int nx_new = 0;

	DWORD timeEatItem = 0;
	gameType currentWeapon = gameType::WHIP;
	gameType lastItemCollect = gameType::ITEM_WHIP;
	unordered_map<int, CWeapon*>weapons;
	Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
	void StartUntouchable(int _timeTouch) { untouchable = 1; untouchable_start = GetTickCount(); timeTouchable = _timeTouch; }

	void attackWeapon(gameType weaponType);
	bool checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	bool checkCollisonWithSkateBoard(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void setValueAutoGo(float disX, float disY, int new_state, int new_nx, bool auto_afterAutoGo);
	void goUpStair();
	void goDownStair();

	static Simon* GetInstance();

	void setEatItem(bool b) { isEatItem = b; }
	bool getEatItem() { return isEatItem; }

	void plusHeart(int num) { heartWeapon += num; }
	void SetHurt(int _nx);

	int getHealth() { return health; }
	void plusHealth(int num) { health += num; }
	void SubHealth(int num);
	bool getDie() { return isDie; }

	bool isUsingWeapon(gameType _type);
	int getHealthWeapon() { return heartWeapon; }
	void resetDoubleTripleShot();

	void startPlusFullHP();

	int getLife() { return numLife; }
	void dieStart();
	void resetState();
};