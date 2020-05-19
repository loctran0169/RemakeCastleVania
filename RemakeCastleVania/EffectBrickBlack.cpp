#include "EffectBrickBlack.h"


CEffectBrickBlack::CEffectBrickBlack(int _x, int _y, int model)
{
	x = _x;
	y = _y;
	type = gameType::EFFECT_BRICKBLACK;
	game = CGame::GetInstance();
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(EFFECT_BRICKBLACK);
	SetAnimationSet(ani_set);
	switch (model)
	{
	case 1:
		nx = -1;
		vx = EFFECT_BRICKBLACK_1_SPEED_X;
		vy = EFFECT_BRICKBLACK_1_SPEED_Y;
		break;
	case 2:
		nx = 1;
		vx = EFFECT_BRICKBLACK_2_SPEED_X;
		vy = EFFECT_BRICKBLACK_1_SPEED_Y;
		break;
	case 3:
		nx = -1;
		vx = EFFECT_BRICKBLACK_3_SPEED_X;
		vy = EFFECT_BRICKBLACK_1_SPEED_Y;
		break;
	case 4:
		nx = 1;
		vx = EFFECT_BRICKBLACK_4_SPEED_X;
		vy = EFFECT_BRICKBLACK_1_SPEED_Y;
		break;
	}
}

void CEffectBrickBlack::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);
	if (y + EFFECT_BRICKBLACK_BBOX_WIDTH > SCREEN_HEIGHT)
		setFinish(true);
	else if (!isFinish) {
		CGameObject::Update(dt);
		vy += EFFECT_BRICKBLACK_GRAVITY * dt;
		x += dx;
		y += dy;
	}
	
}

void CEffectBrickBlack::Render()
{
	animation_set->at(0)->Render(x, y, nx);
	//RenderBoundingBox();
}

void CEffectBrickBlack::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

CEffectBrickBlack::~CEffectBrickBlack()
{
}
