#include "Warrior.h"

void CWarrior::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	zone->Update(dt);
	if (zone->isCollitionSimon) {
		if (x > zone->simon->x)
			nx = -1;
		else
			nx = 1;

		if (x + WARRIOR_BBOX_WIDTH >= boundLeft)
			nx = -1;
		else if (x <= zone->x)
			nx = 1;
	}
	else {
		if (x + WARRIOR_BBOX_WIDTH >= boundLeft)
			nx = -1;
		else if (x <= zone->x)
			nx = 1;
	}
	vx = WARRIOR_SPEED_X * nx;
	CGameObject::Update(dt);
	x += dx;
}

void CWarrior::Render()
{
	animation_set->at(0)->Render(x, y, -nx);
	//RenderBoundingBox();
}

void CWarrior::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WARRIOR_BBOX_WIDTH;
	bottom = y + WARRIOR_BBOX_HEIGHT;
}

CWarrior::~CWarrior()
{
}
