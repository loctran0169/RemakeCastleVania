#include "Brick.h"

CBrick::CBrick()
{
	type = gameType::BRICK;
	width = BRICK_BBOX_WIDTH;
	height = BRICK_BBOX_HEIGHT;
}

void CBrick::Render()
{
	//animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}