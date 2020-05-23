#include "Warrior.h"

void CWarrior::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	zone->Update(dt);
	if (isIdle && GetTickCount() - timeBeAttack >= WARRIOR_TIME_WAIT_ATTACK) {
		animation_set->at(0)->setLopping(false);
		isIdle = false;
	}
	if (zone->isCollitionSimon) {
		if (x > zone->simon->x)
			nx = -1;
		else
			nx = 1;
	}

	if (x + WARRIOR_BBOX_WIDTH >= boundLeft)
		nx = -1;
	else if (x <= zone->x)
		nx = 1;

	if (isIdle)
		vx = 0.0f;
	else
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

void CWarrior::beAttack()
{
	if (health > 0 && !isIdle) health--;
	if (health == 0) isHitted = true;
	timeBeAttack = GetTickCount();
	animation_set->at(0)->setLopping(true);
	isIdle = true;
}

CWarrior::~CWarrior()
{
}
