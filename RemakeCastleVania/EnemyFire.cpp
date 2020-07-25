#include "EnemyFire.h"



void CEnemyFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);
	if (x<xCam || x + ENEMY_FIRE_BBOX_WIDTH>xCam + SCREEN_WIDTH ||
		y<yCam || y + ENEMY_FIRE_BBOX_HEIGHT>yCam + SCREEN_HEIGHT)
	{
		isAttack = false;
	}
	if (isAttack) {
		vx = ENEMY_FIRE_SPEED_X;
		CGameObject::Update(dt);
		x += dx * nx;
		y = line->toY(x);
	}
}

void CEnemyFire::Render()
{
	animation_set->at(0)->Render(x, y, nx);
	//RenderBoundingBox();
}

void CEnemyFire::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + ENEMY_FIRE_BBOX_WIDTH;
	bottom = y + ENEMY_FIRE_BBOX_HEIGHT;
}

void CEnemyFire::setPosition(float _x, float _y)
{
	CGameObject::SetPosition(_x, _y);
	if (x + ENEMY_FIRE_BBOX_WIDTH / 2 < simon->x + SIMON_BBOX_WIDTH / 2)
		nx = 1;
	else
		nx = -1;
	line = new CLine(x, y, simon->x + SIMON_BBOX_WIDTH / 2, simon->y + SIMON_BBOX_HEIGHT / 2);
	timeAttact = GetTickCount();
}

CEnemyFire::~CEnemyFire()
{
}
