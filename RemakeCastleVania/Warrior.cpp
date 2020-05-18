#include "Warrior.h"

void CWarrior::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CWarrior::Render()
{
	animation_set->at(0)->Render(x, y, nx);
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
