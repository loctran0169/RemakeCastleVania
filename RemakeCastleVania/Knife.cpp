#include "Knife.h"

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);
	if (x < xCam || x > xCam + SCREEN_WIDTH)
		SetAttack(false);
	else if(isAttack){
		vx = DAGGER_SPEED * nx;
		CGameObject::Update(dt); // cập nhật thời gian, vận tốc
		x += dx;
	}
}

void CKnife::Render()
{
	animation_set->at(0)->Render(x, y, nx);
	//RenderBoundingBox();
}

void CKnife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + KNIFE_BBOX_WIDTH;
	top = y;
	bottom = y + KNIFE_BBOX_HEIGHT;
}

void CKnife::setPosition(float _x, float _y, int _nx)
{
	this->nx = _nx;
	if(nx>0)
		CGameObject::SetPosition(_x-SIMON_PADDING_ANI-10, _y + 10);
	else
		CGameObject::SetPosition(_x+SIMON_BBOX_WIDTH, _y + 10);
	timeAttact = GetTickCount();
}

CKnife::~CKnife()
{

}
