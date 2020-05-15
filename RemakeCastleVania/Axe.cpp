#include "Axe.h"



void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);
	if (y + AXE_BBOX_HEIGHT > SCREEN_HEIGHT)
		SetAttack(false);
	else if (isAttack) {
		vy += AXE_SPEED_GRAVITY * dt;
		CGameObject::Update(dt); // cập nhật thời gian, vận tốc
		x += dx * nx;
		y += dy;
	}
}

void CAxe::Render()
{
	animation_set->at(0)->Render(x, y, nx);
	//RenderBoundingBox();
}

void CAxe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH;
	bottom = y + AXE_BBOX_HEIGHT;
}

void CAxe::setPosition(float _x, float _y, int _nx)
{
	this->nx = _nx;
	vx = AXE_SPEED_X;
	vy = -AXE_SPEED_Y;
	if (nx > 0)
		CGameObject::SetPosition(_x - SIMON_PADDING_ANI - SIMON_PADDING_WEAPON_ATTACK, _y + SIMON_PADDING_WEAPON_ATTACK);
	else
		CGameObject::SetPosition(_x + SIMON_BBOX_WIDTH, _y + SIMON_PADDING_WEAPON_ATTACK);
	timeAttact = GetTickCount();
}

CAxe::~CAxe()
{
}
