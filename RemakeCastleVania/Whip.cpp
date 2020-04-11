#include "Whip.h"


void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOut(L"size: %d \n",(coObjects)->size());
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
	animation_set->at(level - 1)->Render(x,y);
	RenderBoundingBox();
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	switch (level)
	{
	case 1:
		right = x + WHIP_BBOX_WIDGHT;
		bottom = y + WHIP_BBOX_HEIGHT;
		break;
	case 2:
		right = x + WHIP_BBOX_WIDGHT + 20;
		bottom = y + WHIP_BBOX_HEIGHT;
		break;

	case 3:
		right = x + WHIP_BBOX_WIDGHT;
		bottom = y + WHIP_BBOX_HEIGHT;
		break;
	}
}

Whip::~Whip()
{
}
