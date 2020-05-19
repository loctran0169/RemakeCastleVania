#pragma once
#include"GameObject.h"
#include"define.h"
#include"Utils.h"
#include"Game.h"

#define EFFECT_BRICKBLACK_1_SPEED_X		-0.15f
#define EFFECT_BRICKBLACK_1_SPEED_Y		-0.25f

#define EFFECT_BRICKBLACK_2_SPEED_X		 0.15f
#define EFFECT_BRICKBLACK_2_SPEED_Y		-0.2f

#define EFFECT_BRICKBLACK_3_SPEED_X		-0.07
#define EFFECT_BRICKBLACK_3_SPEED_Y		-0.22

#define EFFECT_BRICKBLACK_4_SPEED_X		 0.1
#define EFFECT_BRICKBLACK_4_SPEED_Y		-0.3

#define EFFECT_BRICKBLACK_GRAVITY		0.0015f

#define EFFECT_BRICKBLACK_BBOX_WIDTH	23
class CEffectBrickBlack : public CGameObject
{
	CGame * game;
public:
	CEffectBrickBlack(int _x, int _y, int model);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void setFinish(bool _isFinish) { isFinish = _isFinish; }
	~CEffectBrickBlack();
};

