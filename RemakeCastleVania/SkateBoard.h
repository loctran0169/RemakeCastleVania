#pragma once
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"

class CSkateBoard : public CGameObject
{
	int boundingLeft;
	int boundingRight;
public:
	CSkateBoard(int l, int r) :CGameObject() {
		CGameObject::type = gameType::SKATEBOARD;
		boundingLeft = l;
		boundingRight = r;
		this->nx = 1;
		vx = SKATEBOARD_SPEED_X;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CSkateBoard();
};

