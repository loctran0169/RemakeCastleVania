#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Torch.h"
#include"Utils.h"
#include"Weapon.h"
class CKnife : public CWeapon
{
public:
	CGame *game;
	CKnife() :CWeapon() {
		game = CGame::GetInstance();
		CGameObject::type = gameType::DAGGER;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void setPosition(float _x, float _y, int _nx);
	~CKnife();
};
