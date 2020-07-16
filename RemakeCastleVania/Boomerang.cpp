#include "Boomerang.h"


CBoomerang::~CBoomerang()
{
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);
	if (x < xCam || x + BOOMERANG_BBOX_WIDTH > xCam + SCREEN_WIDTH) {
		if (!isFirst) {
			isFirst = true;
			if (x < xCam) {
				x = xCam + BOOMERANG_PADDING_HIDE;
				nx = 1;
			}
			else {
				x = xCam + SCREEN_WIDTH - BOOMERANG_BBOX_WIDTH - BOOMERANG_PADDING_HIDE;
				nx = -1;
			}
		}
		else
			SetAttack(false);
	}
	else if (isAttack) {
		vx = BOOMERANG_SPEED * nx;
		CGameObject::Update(dt); // cập nhật thời gian, vận tốc
		x += dx;
	}
}

void CBoomerang::Render()
{
	animation_set->at(0)->Render(x, y, nx);
	//RenderBoundingBox();
}

void CBoomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x+BOOMERANG_BBOX_WIDTH;
	bottom = y + BOOMERANG_HEIGHT;
}

void CBoomerang::setPosition(float _x, float _y, int _nx)
{
	isFirst = false;
	this->nx = _nx;
	if (nx > 0)
		CGameObject::SetPosition(_x - SIMON_PADDING_ANI - SIMON_PADDING_WEAPON_ATTACK, _y + SIMON_PADDING_WEAPON_ATTACK);
	else
		CGameObject::SetPosition(_x + SIMON_BBOX_WIDTH, _y + SIMON_PADDING_WEAPON_ATTACK);
	timeAttact = GetTickCount();
}
