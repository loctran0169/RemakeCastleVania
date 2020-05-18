#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Torch.h"
#include"Utils.h"
#include"Weapon.h"
#include"Brick.h"
#include <algorithm>

#define WATERFIRE_ATTACK_TIME	1500

#define WATERFIRE_SPEED_X		0.26f
#define WATERFIRE_SPEED_Y		0.3f
#define WATERFIRE_SPEED_GRAVITY	0.0015f

#define WATERFIRE_ANI_WATER		0
#define WATERFIRE_ANI_FIRE		1

class CWaterFire : public CWeapon
{
	DWORD timeStartFire;
public:
	CGame * game;
	bool isWater = true;
	CWaterFire() :CWeapon() {
		CGameObject::type = gameType::WATER_FIRE;
		game = CGame::GetInstance();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void setPosition(float _x, float _y, int _nx);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	
	~CWaterFire();
};

