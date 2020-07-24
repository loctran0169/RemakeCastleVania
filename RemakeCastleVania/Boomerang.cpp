#include "Boomerang.h"


CBoomerang::~CBoomerang()
{
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);
	if (!isFirst && (x < xCam || x + BOOMERANG_BBOX_WIDTH > xCam + SCREEN_WIDTH || abs(x - defaultX) >= BOOMERANG_BBOX_WIDTH * 11))
	{
		isFirst = true;
		if (x + BOOMERANG_BBOX_WIDTH / 2 < xCam + SCREEN_WIDTH / 2) {
			nx = 1;
			x += BOOMERANG_PADDING_HIDE;
		}
		else {
			nx = -1;
			x -= BOOMERANG_PADDING_HIDE;
		}
	}
	else if (isFirst && (x < xCam || x + BOOMERANG_BBOX_WIDTH > xCam + SCREEN_WIDTH))
			SetAttack(false);
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
	defaultX = (nx > 0) ? _x - SIMON_PADDING_ANI - SIMON_PADDING_WEAPON_ATTACK : _x + SIMON_BBOX_WIDTH;
	CGameObject::SetPosition(defaultX, _y + SIMON_PADDING_WEAPON_ATTACK);
	timeAttact = GetTickCount();
}
