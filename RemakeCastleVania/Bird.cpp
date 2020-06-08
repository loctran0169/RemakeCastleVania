#include "Bird.h"


void CBird::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float camX, camY;
	game->GetCamPos(camX, camY);
	if (x < camX || x + BRICK_BBOX_WIDTH > camX + SCREEN_WIDTH)
		isHitted = true;

	if (isIdle && GetTickCount() - timeBeAttack >= BIRD_TIME_WAIT_ATTACK) {
		animation_set->at(0)->setLopping(false);
	}

	if (isIdle && GetTickCount() - timeChangeState > 1000) {
		isIdle = false;
		setFlyParabol();
	}
	else if (!isIdle) {
		isFlying = true;
		CGameObject::Update(dt);
		if (timeBeginState != 0 && GetTickCount() - timeBeginState < 1000) { isFlying = false; return; }
		if (isAutoGo) {
			x += dx * nx;
		}
		else {
			float * xy = parabol->toXYPauseWhenOnI(abs(dx));
			x = xy[0];
			y = xy[1];
			nx = xy[2];
			if (xy[3] == 1) {
				if (y > simon->y && y < simon->y + SIMON_BBOX_HEIGHT) {
					setAutoNx();
					SetState(BIRD_STATE_FLY_DY);
				}
				else {
					setFlyParabol();
					SetState(BIRD_STATE_FLY_PARABOL);
				}
				timeBeginState = GetTickCount();
				return;
			}
		}
	}
}

void CBird::Render()
{
	animation_set->at((!isFlying) ? 0 : 1)->Render(x, y, -nx);
	//RenderBoundingBox();
}

void CBird::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BIRD_BBOX_WIDTH;
	bottom = y + BIRD_BBOX_HEIGHT;
}

void CBird::setFlyParabol()
{
	line = new CLine(x, y, simon->x + SIMON_BBOX_WIDTH / 2, simon->y + BIRD_PADDING_ATTACK);
	float yFlying = y + ((y < simon->y + BIRD_PADDING_ATTACK) ? 1 : -1)*abs(y - (simon->y + BIRD_PADDING_ATTACK)) * 2 / 3;
	(yFlying <= 32) ? yFlying = 32 : yFlying = yFlying;
	parabol = new CParabol(x , y, line->toX(yFlying), yFlying);
	SetState(BIRD_STATE_FLY_PARABOL);
}

void CBird::setAutoNx()
{
	if (x < simon->x + SIMON_BBOX_WIDTH / 2)
		nx = 1;
	else nx = -1;
}

void CBird::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BIRD_STATE_IDLE:
		vx = vy = 0;
		isAutoGo = false;
		break;
	case BIRD_STATE_FLY_DY:
		vx = BIRD_SPEED_DY;
		vy = 0;
		isAutoGo = true;
		break;
	case BIRD_STATE_FLY_PARABOL:
		vx = BIRD_SPEED_X;
		vy = BIRD_SPEED_Y;
		isAutoGo = false;
		break;
	default:
		break;
	}
}

void CBird::beAttack()
{
	isHitted = true;
}

CBird::~CBird()
{
}
