#include "WhiteBone.h"

float CWhiteBone::speedY = WHITEBONE_SPEED_Y_MIN;

void CWhiteBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float xCam, yCam;
	if (y + WHITEBONE_BBOX_HEIGHT > SCREEN_HEIGHT)
		SetAttack(false);
	else if (isAttack) {
		vy += WHITEBONE_SPEED_GRAVITY * dt;
		CGameObject::Update(dt); // cập nhật thời gian, vận tốc
		x += dx * nx;
		y += dy;
	}
}

void CWhiteBone::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CWhiteBone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHITEBONE_BBOX_WIDTH;
	bottom = y + WHITEBONE_BBOX_HEIGHT;
}

void CWhiteBone::setPosition(float _x, float _y, int _nx)
{
	this->nx = _nx;
	vx = WHITEBONE_SPEED_X;
	vy = - speedY;
	if (nx > 0)
		CGameObject::SetPosition(_x , _y + SIMON_PADDING_WEAPON_ATTACK);
	else
		CGameObject::SetPosition(_x, _y + SIMON_PADDING_WEAPON_ATTACK);
	timeAttact = GetTickCount();
}

CWhiteBone::~CWhiteBone()
{
}
