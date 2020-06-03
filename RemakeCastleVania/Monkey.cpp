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

	if (isIdle && GetTickCount() - timeChangeState > 1000) {
		isIdle = false;
		numOfSate = 0;
		SetState(MONKEY_STATE_JUMP);
	}
	else if(!isIdle) {
		if (timeBeginState != 0 && GetTickCount() - timeBeginState < 300) return;
		if (vx == 0 && numOfSate < 2) {
			if (isDisableJump) {
				numOfSate = 0;
				SetState(MONKEY_STATE_WALK);
			}
			else
				SetState(state);
		}
		else if (vx == 0 && numOfSate > 1) {
			numOfSate = 0;
			if (simon->isHurt)
				SetState(state);
			else {
				if (state == MONKEY_STATE_JUMP)
					SetState(MONKEY_STATE_WALK);
				else
					SetState(MONKEY_STATE_JUMP);

				if (x + MONKEY_BBOX_WIDTH / 2 > simon->x + SIMON_BBOX_WIDTH / 2)
					nx = -1;
				else
					nx = 1;
			}
		}

		if (isJump) {// xét đang nhãy thì ko đổi hướng
			if (state == MONKEY_STATE_JUMP)
				vx = (nx > 0) ? abs(MONKEY_JUMP_SPEED_X) : -abs(MONKEY_JUMP_SPEED_X);
			else
				vx = (nx > 0) ? abs(MONKEY_WALK_SPEED_X) : -abs(MONKEY_WALK_SPEED_X);
			vy += MONKEY_GRAVITY_SPEED * dt;
		}
		else {
			vy += SIMON_GRAVITY * dt;
		}
	}

	CGameObject::Update(dt);
	checkCollisonWithHidenObjects(dt, coObjects);
	checkCollisonWithBricks(dt,coObjects);
	DebugOut(L"isDisableJump %d \n",isDisableJump);
}

void CMonkey::Render()
{
	animation_set->at((isJump) ? 1 : 0)->Render(x, y, -nx);
}

void CMonkey::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + MONKEY_BBOX_WIDTH;
	bottom = y + MONKEY_BBOX_HEIGHT;
}

void CMonkey::checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listActives;
	listActives.clear();

	for (UINT i = 0; i < coObjects->size(); i++)//lọc ra danh sách cần xét va chạm
		if (coObjects->at(i)->getType() == gameType::BRICK ||
			(coObjects->at(i)->getType() == gameType::BRICKBLACK_1 && !coObjects->at(i)->isHitted) ||
			(coObjects->at(i)->getType() == gameType::BRICKBLACK_2 && !coObjects->at(i)->isHitted))
			listActives.push_back(coObjects->at(i));

	// kiểm ra va chạm với Brick
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(&listActives, coEvents);
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

		//x += min_tx * dx + nx * 0.4f;

		//if (nx != 0) nx = 0;
		if (ny == -1) {
			y += min_ty * dy + ny * 0.4f;
			vy = 0;
			if (isJump) {
				vx = 0;
				isJump = false;
				timeBeginState = GetTickCount();
			}
		}
		else {
			x += dx;
			y += dy;
		}
		if (nx != 0 && ny == 0) {
			float l, t, r, b;
			GetBoundingBox(l, t, r, b);
			y = t - MONKEY_BBOX_HEIGHT - 1;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMonkey::checkCollisonWithHidenObjects(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	isDisableJump = false;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listActives;
	listActives.clear();

	for (UINT i = 0; i < coObjects->size(); i++)//lọc ra danh sách cần xét va chạm disable jump
		if (coObjects->at(i)->getType() == gameType::DISABLE_JUMP)
			if (isCollitionObjectWithObject(coObjects->at(i)))
				isDisableJump = true;
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
		vy = -MONKEY_WALK_SPEED_Y;
		isJump = true;
		break;
	case MONKEY_STATE_JUMP:
		vx = MONKEY_JUMP_SPEED_X;
		vy = -MONKEY_JUMP_SPEED_Y;
		isJump = true;
		break;
	}
	numOfSate++;
}

void CMonkey::beAttack()
{
	isHitted = true;
}

CMonkey::~CMonkey()
{
}
