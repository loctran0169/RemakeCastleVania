#include "BrickBlack.h"

void CBrickBlack::Render()
{
	if (type==gameType::BRICKBLACK_1)
	{
		if (countCollision < 2)
			animation_set->at(countCollision)->Render(x, y);
	}
	else if (type==gameType::BRICKBLACK_2) {
		if (countCollision < 3)
			animation_set->at(countCollision)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CBrickBlack::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	if (type == gameType::BRICKBLACK_1) {
		r = x + BRICKBLACK_1_BBOX_WIDTH;
		b = y + BRICKBLACK_1_BBOX_HEIGHT;
	}
	else if(type == gameType::BRICKBLACK_2){
		r = x + BRICKBLACK_2_BBOX_WIDTH;
		b = y + BRICKBLACK_2_BBOX_HEIGHT;
	}
}

void CBrickBlack::beAttack()
{
	if (GetTickCount() - lastTimeBeAttack < SIMON_ATTACT_TIME)return;

	if (type == gameType::BRICKBLACK_1 && countCollision < 1)
		countCollision++;
	else if (type == gameType::BRICKBLACK_2 && countCollision < 2)
		countCollision++;
	if (type == gameType::BRICKBLACK_1 && countCollision > 0 || type == gameType::BRICKBLACK_2&& countCollision > 1) {
		isHitted = true;
		if(isDelete)
			isFinish = true;
	}
	lastTimeBeAttack = GetTickCount();
}
