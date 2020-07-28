#include "BossBat.h"


void CBossBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isWaiting) {
		if (timeBeginState == 0) {
			zone->Update(dt);
			if (zone->isCollitionSimon) {
				timeBeginState = GetTickCount();
			}
		}	
		else if (GetTickCount() - timeBeginState > BOSSBAT_TIME_WAITING_ACTIVE) {
			isWaiting = false;
			line = new CLine(x, y, randomX(), dyRepairToAttack);
			SetState(BOSSBAT_STATE_AUTOGO_ATTACK);
		}
	}
	else {
		CGameObject::Update(dt);
		if (GetTickCount() - timeBeginState > BOSSBAT_TIME_DIE && isDie)isHitted = true;
		if (isDie)return;
		if (GetTickCount() - timeBeginState < BOSSBAT_TIME_WAITING_AUTOGO && state == BOSSBAT_STATE_AUTOGO_REPAIR)return;
		if (GetTickCount() - timeBeginState < BOSSBAT_TIME_WAITING_AUTOGO && state == BOSSBAT_STATE_AUTOGO_ATTACK)return;
		if (GetTickCount() - timeBeginState < BOSSBAT_TIME_WAITING_FLY && state == BOSSBAT_STATE_FLY)return;

		if (isResetPositionParabol) {
			parabol = new CParabol(x, y, simon->x - SIMON_BBOX_WIDTH, simon->y + BOSSBAT_PADDING_ATTACK);
			vx = (abs(x - parabol->getX2()) > BRICK_BBOX_WIDTH * 2) ? BOSSBAT_SPEED_X : abs(x - parabol->getX2())*BOSSBAT_SPEED_X / BRICK_BBOX_WIDTH * 2;
			isResetPositionParabol = false;
		}
		if(isAutoGo){
			if (isAttack)return;
			float *xy = line->toXY(abs(dx), ((state == BOSSBAT_STATE_AUTOGO_ATTACK) ? dyRepairToAttack : dyRepair));
			x = xy[0];
			y = xy[1];
			nx = xy[2];
			if (xy[3] == 1) {
				SetState(BOSSBAT_STATE_IDLE);
				timeBeginState = GetTickCount();
			}
		}
		else {
			if (isGoUp) {
				line = new CLine(x, y, randomX(), dyRepairToAttack);
				SetState(BOSSBAT_STATE_AUTOGO_ATTACK);
				timeBeginState = GetTickCount();
				checkAttack();
				return;
			}
			else if (isGoDown) {
				SetState(BOSSBAT_STATE_FLY);
				timeBeginState = GetTickCount();
				isResetPositionParabol = true;
				return;
			}
			else {
				float * xy = parabol->toXYWithDx(abs(dx), dyRepair);
				x = xy[0];
				y = xy[1];
				nx = xy[2];
				if (xy[3] == 1) {
					line = new CLine(x, y, randomX(), dyRepairToAttack);
					SetState(BOSSBAT_STATE_AUTOGO_ATTACK);
					timeBeginState = GetTickCount();
					checkAttack();
					return;
				}
				if (x <= game->cam_x || x + BOSSBAT_BBOX_WIDTH >= game->cam_x + SCREEN_WIDTH) {
					line = new CLine(x, y, randomX(), dyRepair);
					SetState(BOSSBAT_STATE_AUTOGO_REPAIR);
				}
			}
		}
	}
}

void CBossBat::Render()
{
	if (simon->isUsingWeapon(gameType::STOP_WATCH))
		animation_set->at(getAniId())->setLopping(true);
	else
		animation_set->at(getAniId())->setLopping(false);

	animation_set->at(getAniId())->Render(x + ((isWaiting) ? BRICK_BBOX_WIDTH : ((isDie) ? (BOSSBAT_BBOX_WIDTH - BOSSBAT_EFFECT_DIE) / 2 : 0)), y);

	//zone->RenderBoundingBox();
	//RenderBoundingBox();
}

void CBossBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BOSSBAT_BBOX_WIDTH;
	bottom = y + BOSSBAT_BBOX_HEIGHT;
}

int CBossBat::getAniId()
{
	return ((isWaiting) ? BOSSBAT_ANI_IDLE : ((isDie) ? BOSSBAT_ANI_DIE : BOSSBAT_ANI_FLY));
}

float CBossBat::randomX()
{
	float ran = float_randomX((int)game->cam_x + BOSSBAT_PADDING_X_LEFT, (int)game->cam_x + SCREEN_WIDTH - BOSSBAT_PADDING_X_RIGHT);
	return ran;
}

float CBossBat::float_randomX(float min, float max)
{
	float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
	return min + scale * (max - min);      /* [min, max] */
}

void CBossBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSSBAT_STATE_IDLE:
		isAutoGo = false;
		vx = vy = 0;
		break;
	case BOSSBAT_STATE_AUTOGO_REPAIR:
		isAutoGo = true;
		isGoUp = true;
		isGoDown = false;
		vx = BOSSBAT_SPEED_AUTOGO_X;
		break;
	case BOSSBAT_STATE_AUTOGO_ATTACK:
		isAutoGo = true;
		isGoUp = false;
		isGoDown = true;
		vx = BOSSBAT_SPEED_AUTOGO_X;
		break;
	case BOSSBAT_STATE_FLY:
		isAutoGo = false;
		isGoUp = false;
		isGoDown = false;
		vx = BOSSBAT_SPEED_X;
		break;
	}
}

void CBossBat::checkAttack()
{
	if (abs(x + BOSSBAT_BBOX_WIDTH / 2 - simon->x - SIMON_BBOX_WIDTH / 2) >= BRICK_BBOX_WIDTH * 8)
		isAttack = true;
}

void CBossBat::attackWeapon(vector<LPGAMEOBJECT>& listWeapon)
{
	if (!isAttack)return;
	CEnemyFire * fire = new CEnemyFire();
	fire->setPosition(x + (BOSSBAT_BBOX_WIDTH - ENEMY_FIRE_BBOX_WIDTH) / 2, y + BOSSBAT_BBOX_WIDTH / 3);
	fire->SetAttack(true);
	listWeapon.push_back(fire);
	isAttack = false;
}

void CBossBat::beAttack()
{
	health -= 2;
	if (health < 1) {
		isDie = true;
		health = 0;
		CSound::GetInstance()->stop();
		CSound::GetInstance()->play(gameType::SOUND_STAGE_CLEAR, true, 0);
		timeBeginState = GetTickCount();
	}
}

CBossBat::~CBossBat()
{
}
