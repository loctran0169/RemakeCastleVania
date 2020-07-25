#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Simon.h"
#include"Utils.h"
#include"Weapon.h"
#include"Line.h"

#define ENEMY_FIRE_BBOX_WIDTH	14
#define ENEMY_FIRE_BBOX_HEIGHT	12

#define ENEMY_FIRE_SPEED_X		0.1f
class CEnemyFire :public CWeapon
{
	static float speedY;
public:
	CGame * game;
	Simon *simon;
	CLine *line;
	CEnemyFire() :CWeapon() {
		CGameObject::type = gameType::ENEMY_FIRE;
		game = CGame::GetInstance();
		simon = Simon::GetInstance();
		CAnimationSets * animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(gameType::ENEMY_FIRE);
		SetAnimationSet(ani_set);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void setPosition(float _x, float _y, int _nx);
	~CEnemyFire();
};

