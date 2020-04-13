#include "Whip.h"


void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAttack) {
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CTorch *>(coObjects->at(i)))
			{
				CTorch *torch = dynamic_cast<CTorch *>(coObjects->at(i));
				if (isCollitionObjectWithObject(coObjects->at(i)))
				{
					torch->isHitted = true;
					torch->timeHitted = GetTickCount();
				}
			}
		}
	}
}

void Whip::Render()
{
	if (isAttack)
		animation_set->at(level - 1 + ((nx > 0) ? 0 : WHIP_LEVEL_MAX))->Render(x,y, nx);
	//RenderBoundingBox();
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
