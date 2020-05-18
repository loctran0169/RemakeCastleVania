#include "Candle.h"




void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isHitted &&GetTickCount() - timeBeAttacked >= TIME_EFFECT)
		isFinish = true;
}

void CCandle::Render()
{
	if (!isHitted)
		animation_set->at(0)->Render(x, y);
	else
		if (!isFinish)
			animation_set->at(1)->Render(x, y);
	//RenderBoundingBox();
}

void CCandle::
GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + CANDLE_BBOX_WIDGHT;
	b = y + CANDLE_BBOX_HEIGHT;
}

CCandle::~CCandle()
{
}
