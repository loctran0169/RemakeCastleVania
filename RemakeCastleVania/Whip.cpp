#include "Whip.h"


void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float wl, wr, wt, wb;
	GetBoundingBox(wl, wt, wr, wb);
	RECT rectWhip, rectObject;
	rectWhip.left = (int)wl;
	rectWhip.top = (int)wt;
	rectWhip.right = (int)wr;
	rectWhip.bottom = (int)wb;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CTorch *>(coObjects->at(i)))
		{
			CTorch *torch = dynamic_cast<CTorch *>(coObjects->at(i));
			float zl, zr, zt, zb;
			torch->GetBoundingBox(zl, zt, zr, zb);
			rectObject.left = (int)zl;
			rectObject.top = (int)zt;
			rectObject.right = (int)zr;
			rectObject.bottom = (int)zb;
			if (CGame::GetInstance()->isCollision(rectWhip, rectObject))
			{
				torch->isTouch = true;
				torch->timeHitted = GetTickCount();
			}
		}
	}
}

void Whip::Render()
{
	animation_set->at(level - 1 + ((nx > 0) ? 0 : WHIP_LEVEL_MAX))->Render(xr, yr, nx);
	RenderBoundingBox();
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	if (nx > 0)
		left = x + SIMON_PADDING_ANI;
	top = y;
	switch (level)
	{
	case 1:
		right = left + WHIP_BBOX_WIDGHT_LV1;
		bottom = y + WHIP_BBOX_HEIGHT;
		break;
	case 2:
		right = left + WHIP_BBOX_WIDGHT_LV2;
		bottom = y + WHIP_BBOX_HEIGHT;
		break;

	case 3:
		right = left + WHIP_BBOX_WIDGHT_LV3;
		bottom = y + WHIP_BBOX_HEIGHT;
		break;
	}
}

Whip::~Whip()
{
}
