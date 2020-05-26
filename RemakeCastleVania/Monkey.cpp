#include "Monkey.h"

void CMonkey::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float camX, camY;
	game->GetCamPos(camX, camY);
	if (x < camX || x + MONKEY_BBOX_WIDTH > camX + SCREEN_WIDTH)
		isHitted = true;

	if (isIdle && GetTickCount() - timeBeAttack >= WARRIOR_TIME_WAIT_ATTACK) {
		animation_set->at(0)->setLopping(false);
	}

	if (isIdle && GetTickCount() - timeChangeState > 2000)
		isIdle = false;
	//else if
	CGameObject::Update(dt);
	checkCollisonWithBricks(dt,coObjects);
}

void CMonkey::Render()
{
	
}

void CMonkey::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CMonkey::checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

	// kiểm ra va chạm với Brick
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(&listBricks, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;

		//if (nx != 0) nx = 0;
		if (ny < 0) {
			y += min_ty * dy + ny * 0.4f;
			vy = 0;
			if (isJump) {
				vx = 0;
			}

			float l, t, r, b;
			GetBoundingBox(l, t, r, b);
		}
		else {
			y += dy;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMonkey::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MONKEY_STATE_IDLE:
		vx = 0;
		vy = 0;
		isJump = false;
		break;
	case MONKEY_STATE_WALK:
		vx = MONKEY_WALK_SPEED_X;
		vy = MONKEY_WALK_SPEED_Y;
		isJump = false;
		break;
	case MONKEY_STATE_JUMP:
		vx = MONKEY_JUMP_SPEED_X;
		vy = MONKEY_JUMP_SPEED_Y;
		isJump = true;
		break;
	}
}

void CMonkey::beAttack()
{
}

CMonkey::~CMonkey()
{
}
