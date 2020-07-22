#include "GhostWalk.h"




void CGhostWalk::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	float xCam, yCam;
	game->GetCamPos(xCam, yCam);

	if (x < xCam || x + GHOSTWALK_BBOX_WIDTH > xCam + SCREEN_WIDTH) {
		isHitted = true;
		timeBeAttacked = GetTickCount() - GHOSTWALK_BETWEEN_DIE_TIME;
	}
	vx = GHOSTWALK_SPEED_X * nx;
	CGameObject::Update(dt);
	vy += GHOSTWALK_SPEED_GRAVITY * dt;

	checkCollisonWithBricks(dt, coObjects);
}

void CGhostWalk::Render()
{
	if (simon->isUsingWeapon(gameType::STOP_WATCH))
		animation_set->at(0)->setLopping(true);
	else
		animation_set->at(0)->setLopping(false);
	animation_set->at(0)->Render(x, y, -nx);
	//RenderBoundingBox();
}

void CGhostWalk::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + GHOSTWALK_BBOX_WIDTH;
	bottom = y + GHOSTWALK_BBOX_HEIGHT;
}

void CGhostWalk::checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listBricks;
	listBricks.clear();

	for (UINT i = 0; i < coObjects->size(); i++)//lọc ra danh sách brick
		if (coObjects->at(i)->getType() == gameType::BRICK ||
			(coObjects->at(i)->getType() == gameType::BRICKBLACK_1 && !coObjects->at(i)->isHitted) ||
			(coObjects->at(i)->getType() == gameType::BRICKBLACK_2 && !coObjects->at(i)->isHitted))
			listBricks.push_back(coObjects->at(i));

	CalcPotentialCollisions(&listBricks, coEvents);
	if (coEvents.size() == 0)
	{
		//x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx, rdy;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// block 
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0) {
			vy = 0;
			x += dx;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGhostWalk::beAttack()
{
	health--;
	if (health < 1)isHitted = true;
	timeBeAttacked = GetTickCount();
}

CGhostWalk::~CGhostWalk()
{
}
