﻿#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"
#include"Simon.h"
#include"Zone.h"
#include"Line.h"
#include"Parabol.h"
#include"Expression.h"
#include"EnemyFire.h"
#include"Sound.h"

#define BOSSBAT_BBOX_WIDTH				100
#define BOSSBAT_BBOX_HEIGHT				48
#define BOSSBAT_EFFECT_DIE				48

#define BOSSBAT_ANI_IDLE				0
#define BOSSBAT_ANI_FLY					1
#define BOSSBAT_ANI_DIE					2

#define BOSSBAT_SPEED_X					0.16f
#define BOSSBAT_SPEED_AUTOGO_X			0.14f

#define BOSSBAT_PADDING_ATTACK			15.0f
#define BOSSBAT_PADDING_X_LEFT			64
#define BOSSBAT_PADDING_X_RIGHT			128

#define BOSSBAT_STATE_IDLE				0
#define BOSSBAT_STATE_AUTOGO_REPAIR		1
#define BOSSBAT_STATE_AUTOGO_ATTACK		2
#define BOSSBAT_STATE_FLY				3

#define BOSSBAT_PADDING_ATTACK			15

#define BOSSBAT_TIME_WAITING_ACTIVE		500
#define BOSSBAT_TIME_WAITING_AUTOGO		600
#define BOSSBAT_TIME_WAITING_FLY		1500
#define BOSSBAT_TIME_DIE				3000


class CBossBat : public CMonter // quái xương
{
public:
	Simon * simon;
	CGame * game;
	CZone * zone;
	CLine *line;
	CParabol *parabol;

	int dyRepair = 0; // từ đây sẽ di chuyển xuống dyRepairToAttack
	int dyRepairToAttack = 0; // đợi tý r bay vào simon

	bool isAttack = false;
	bool isDie = false;
	bool isAutoGo = false; // tự động đi theo đừng thằng
	bool isGoUp = false; // bay xuống
	bool isGoDown = false; // bay lên
	bool isResetPositionParabol = false;
	float autoGoX_Distance = 0.0f, autoGoY_Distance = 0.0f;

	DWORD timeBeginState = 0;
public:
	bool isWaiting = true; // đợi con simon đến bụp nó
	CBossBat(int _l, int _t, int _r, int _b, int _dyRepair, int _dyRepairToAttack) :CMonter() {
		type = gameType::BOSS_BAT;
		health = MAX_HP;
		simon = Simon::GetInstance();
		game = CGame::GetInstance();
		zone = new CZone(_l, _t, _r, _b);
		dyRepair = _dyRepair;
		dyRepairToAttack = _dyRepairToAttack;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int getAniId();
	float randomX();
	float float_randomX(float min, float max);
	void SetState(int state);
	void checkAttack();
	void attackWeapon(vector<LPGAMEOBJECT>& listWeapon); // hàm khai triển vũ khí
	void beAttack();
	~CBossBat();
};
