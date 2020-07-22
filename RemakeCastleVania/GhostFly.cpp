#include "GhostFly.h"
#include<math.h>

void CGhostFly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	float camX, camY;
	game->GetCamPos(camX, camY);

	if (x < camX || x + GHOSTFLY_BBOX_WIDTH > camX + SCREEN_WIDTH)
		isHitted = true;
	

	if (isIdle && GetTickCount() - timeBeAttack >= GHOSTFLY_TIME_WAIT_ATTACK) {
		animation_set->at(0)->setLopping(false);
		isIdle = false;
	}
	if (!isHitted) {
		if (GetTickCount() - timeBackUpAddressSimon > 500) {

			line = new CLine(x, y, simon->x, simon->y + GHOSTFLY_PADDING_ATTACK);
			timeBackUpAddressSimon = GetTickCount();
		}
		if (isIdle)
			vx = 0;
		else
			vx = GHOSTFLY_SPEED;
		CGameObject::Update(dt);

		float *xy = line->toXY(abs(dx));

		x = xy[0];
		y = xy[1];
		nx = xy[2];
	}
}

void CGhostFly::Render()
{
	if (simon->isUsingWeapon(gameType::STOP_WATCH))
		animation_set->at(0)->setLopping(true);
	else
		animation_set->at(0)->setLopping(false);
	animation_set->at(0)->Render(x, y, -nx);
	//RenderBoundingBox(xRender,yRender);
}

void CGhostFly::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + GHOSTFLY_BBOX_WIDTH;
	bottom = y + GHOSTFLY_BBOX_HEIGHT;
}

void CGhostFly::SetPosition(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
	timeBackUpAddressSimon = GetTickCount();
	line = new CLine(x, y, simon->x, simon->y + GHOSTFLY_PADDING_ATTACK);
}

void CGhostFly::beAttack()
{
	if (health > 0 && !isIdle) health--;
	if (health <1 ) isHitted = true;

	timeBeAttack = GetTickCount();
	timeBackUpAddressSimon = GetTickCount();
	line = new CLine(x, y, simon->x, simon->y + GHOSTFLY_PADDING_ATTACK);

	animation_set->at(0)->setLopping(true);

	isIdle = true;
}

CGhostFly::~CGhostFly()
{
	
}
