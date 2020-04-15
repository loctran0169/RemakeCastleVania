#include "Whip.h"


void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"whip isAttack: %d %d \n", isAttack,GetTickCount());
}

void Whip::Render()
{
	if (isAttack)
		if(nx>0)
			animation_set->at(getAniID())->Render(x,y, nx);
		else
			animation_set->at(getAniID())->Render(x+SIMON_BBOX_WIDTH*2-7, y, nx);// -7 Do cắt sprites ko đều
	//RenderBoundingBox();
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	//if (animation_set->at(level - 1 + ((nx > 0) ? 0 : WHIP_LEVEL_MAX))->getCurrentFrame() < 2)//frame cuối mới xét ra chạm
	//	return;

	left = x - SIMON_PADDING_ATTACT * 0.75f;
	if (nx > 0)
		left = x + SIMON_BBOX_WIDTH + SIMON_PADDING_ATTACT * 0.75f;
	top = y + WHIP_PADDING_ATTACK;
	switch (level)
	{
	case 1:
		if (nx < 0)
			left -= WHIP_BBOX_WIDGHT_LV1;
		right = left + WHIP_BBOX_WIDGHT_LV1;
		bottom = top + WHIP_BBOX_HEIGHT;
		break;
	case 2:
		if (nx < 0)
			left -= WHIP_BBOX_WIDGHT_LV2;
		right = left + WHIP_BBOX_WIDGHT_LV2;
		bottom = top + WHIP_BBOX_HEIGHT;
		break;
	case 3:
		if (nx < 0)
			left -= WHIP_BBOX_WIDGHT_LV3;
		right = left + WHIP_BBOX_WIDGHT_LV3;
		bottom = top + WHIP_BBOX_HEIGHT;
		break;
	}
}

bool Whip::allowCollision()
{
	if (animation_set->at(level - 1 + ((nx > 0) ? 0 : WHIP_LEVEL_MAX))->getCurrentFrame() < 2)
		return false;
	return true;
}

void Whip::resetFrame()
{
	animation_set->at(level - 1 + ((nx > 0) ? 0 : WHIP_LEVEL_MAX))->resetFrame();
}

int Whip::getAniID()
{
	if (isLopping)
		return getIDFreeze();
	else
		return (level - 1 + ((nx > 0) ? 0 : WHIP_LEVEL_MAX));
}

void Whip::whipUpgrade()
{
	
	if (level == 1)
		level = 2;
	else if(level == 2)
		level = 3;	
}

Whip::~Whip()
{
}
