#include "Weapon.h"


void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CWeapon::Render()
{

}

void CWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}

void CWeapon::CollisionWithListObjects(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAttack)return;

}

void CWeapon::setPosition(float _x, float _y, int _nx)
{
	CGameObject::SetPosition(_x, _y);
	this->nx = _nx;
	timeAttact = GetTickCount();
}

void CWeapon::setPositionRender(float _x, float _y)
{
}

CWeapon::~CWeapon()
{
}
