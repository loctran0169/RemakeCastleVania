#include "BlackBat.h"



void CBlackBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);
	if (isAutoGo && (x + BLACKBAT_BBOX_WIDTH < xCam || x > xCam + SCREEN_WIDTH))
		isHitted = true;
	if (!isHitted) {
		zone->Update(dt);
		if (!isAutoGo && zone->isCollitionSimon)
			startFly((zone->isRight) ? 1 : -1);
		if (isAutoGo) {
			if ((abs(dx) <= abs(autoGoX_Distance) && autoGoX_Distance != 0) || (abs(dy) <= abs(autoGoY_Distance) && autoGoY_Distance != 0))
			{
				if (abs(dx) <= abs(autoGoX_Distance))
				{
					x += dx;
					if (autoGoX_Distance != -100)
						autoGoX_Distance -= abs(dx);
				}
				if (abs(dy) <= abs(autoGoY_Distance))
				{
					y += dy;
					if (autoGoY_Distance != -100)
						autoGoY_Distance -= abs(dy);
				}
			}
			else {
				x += autoGoX_Distance * nx;
				y += autoGoY_Distance * -1;

				vx = BLACKBAT_SPEED_X * nx;
				vy = 0;

				autoGoX_Distance = -100;
				autoGoY_Distance = 0;
			}
		}
	}
}

void CBlackBat::Render()
{
	if(vx == 0)
		animation_set->at(BLACKBAT_ANI_IDLE)->Render(x, y, nx);
	else
		animation_set->at(BLACKBAT_ANI_FLY)->Render(x, y,-nx);
	//RenderBoundingBox();
}

void CBlackBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BLACKBAT_BBOX_WIDTH;
	bottom = y + BLACKBAT_BBOX_HEIGHT;
}

void CBlackBat::beAttack()
{
	health--;
	if (health < 1)
		isHitted = true;
}

void CBlackBat::startFly(int _nx)
{
	isAutoGo = true;
	this->nx = _nx;

	autoGoX_Distance = BLACKBAT_DISTANCE_X;
	autoGoY_Distance = BLACKBAT_DISTANCE_Y;

	vx = BLACKBAT_SPEED_X_OVA * nx;
	vy = BLACKBAT_SPEED_Y_OVA;
}

CBlackBat::~CBlackBat()
{

}
