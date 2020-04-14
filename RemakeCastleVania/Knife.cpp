#include "Knife.h"

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CKnife::Render()
{
	//animation_set->at(0)->Render(x, y, nx);
}

void CKnife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + KNIFE_BBOX_WIDTH;
	top = y;
	bottom = y + KNIFE_BBOX_HEIGHT;
}

void CKnife::setPosition(float _x, float _y, int nx)
{
}

void CKnife::setPositionRender(float _x, float _y)
{
}

bool CKnife::allowCollision()
{
	return false;
}

void CKnife::resetFrame()
{
}

CKnife::~CKnife()
{

}
