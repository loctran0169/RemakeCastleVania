#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Torch.h"
#include"Utils.h"
#include"Weapon.h"

#define BOOMERANG_BBOX_WIDTH						28.0f
#define BOOMERANG_HEIGHT							28.0f

#define BOOMERANG_SPEED								0.45f

#define BOOMERANG_PADDING_HIDE						10.0f

class CBoomerang : public CWeapon
{
public:
	CGame *game;
	bool isFirst = false;
	CBoomerang() :CWeapon() {
		game = CGame::GetInstance();
		CGameObject::type = gameType::BOOMERANG;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void setPosition(float _x, float _y, int _nx);
	~CBoomerang();
};

