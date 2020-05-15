#include "WaterFire.h"



void CWaterFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CWaterFire::Render()
{
}

void CWaterFire::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CWaterFire::setPosition(float _x, float _y, int _nx)
{
	this->nx = _nx;
	if (nx > 0)
		CGameObject::SetPosition(_x - SIMON_PADDING_ANI - 10, _y + 10);
	else
		CGameObject::SetPosition(_x + SIMON_BBOX_WIDTH, _y + 10);
	timeAttact = GetTickCount();
}

CWaterFire::~CWaterFire()
{
}
