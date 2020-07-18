#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Torch.h"
#include"Utils.h"
#include"Weapon.h"

#define WHITEBONE_BBOX_WIDTH						32
#define WHITEBONE_BBOX_HEIGHT						32

//max y,gravity = 0.035f 0.0004f, min y,gravity = 0.028f 0.0004f,
#define WHITEBONE_SPEED_X							0.08f
#define WHITEBONE_SPEED_Y_MAX						0.35f
#define WHITEBONE_SPEED_Y_MIN						0.28f

#define	WHITEBONE_SPEED_GRAVITY						0.00045f

class CWhiteBone :public CWeapon
{
	static float speedY;
public:
	CGame * game;
	CWhiteBone() :CWeapon() {
		CGameObject::type = gameType::BONE_WEAPON;
		game = CGame::GetInstance();

		CAnimationSets * animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(gameType::BONE_WEAPON);
		SetAnimationSet(ani_set);
		speedY = (speedY == WHITEBONE_SPEED_Y_MAX) ? WHITEBONE_SPEED_Y_MIN : WHITEBONE_SPEED_Y_MAX;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void setPosition(float _x, float _y, int _nx);
	~CWhiteBone();
};
