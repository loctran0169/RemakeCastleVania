#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Torch.h"
#include"Utils.h"
#include"Weapon.h"
#define MIN_TO_HIT_ONE_ENEMY	300
class Whip : public CWeapon
{
public:
	int level;	//level whip
	Whip() :CWeapon() {
		level = 1;
		CGameObject::type = gameType::WHIP;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int getAniID();
	void whipUpgrade();
	~Whip();
};

