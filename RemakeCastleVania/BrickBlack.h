#pragma once
#include "GameObject.h"
#include "Utils.h"

#define BRICKBLACK_1_BBOX_WIDTH  32
#define BRICKBLACK_1_BBOX_HEIGHT 32

#define BRICKBLACK_2_BBOX_WIDTH  32
#define BRICKBLACK_2_BBOX_HEIGHT 64

class CBrickBlack : public CGameObject
{
	DWORD lastTimeBeAttack = 0;
	int countCollision = 0;
	bool isDelete = false;
public:
	CBrickBlack(gameType _type,bool _isDelete) :CGameObject() {
		type = _type;
		isDelete = _isDelete;
	}
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void beAttack();
};