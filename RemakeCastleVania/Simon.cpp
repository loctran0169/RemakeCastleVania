#include "Simon.h"
#include"Textures.h"

Simon::Simon() : CGameObject()
{
	untouchable = 0;
	SetState(SIMON_STATE_IDLE);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (isJump) {
		/*dx = vx * dt;
		dy = vy * dt;*/
		vy += SIMON_JUMP_GRAVITY * dt;
	} 
	else {
		vy += SIMON_GRAVITY * dt;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	//buộc simon ở trong camera
	if (x < CMap::GetInstance()->boundingMapLeft)
		x = CMap::GetInstance()->boundingMapLeft;
	if (x + SIMON_BBOX_WIDTH > CMap::GetInstance()->boundingMapRight)
		x = CMap::GetInstance()->boundingMapRight - SIMON_BBOX_WIDTH;
	//thời gian attack
	if (isAttact&&GetTickCount() - attactTime >= SIMON_ATTACT_TIME) {
		isAttact = false;
		//x += SIMON_PADDING_ATTACT/2;
		//whip->Update(dt, coObjects);
	}
	// No collision occured, proceed normally
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
		// how to push back SIMON if collides with a moving objects, what if SIMON is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->ny < 0) {
					if (isJump) {
						isJump = false;
					}
					vy = 0;
				}
				else if (e->ny > 0) {
					y += dy;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	int ani;
	if (nextScreen) ani = SIMON_ANI_WALKING;
	else if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (timeWait != 0)
	{
		ani = SIMON_ANI_EATTING;
	}
	else if (isAttact) {
			if (isSit)
				ani = SIMON_ANI_SITTING_ATTACKING;
			else
				ani = SIMON_ANI_STANDING_ATTACKING;
	}
	else if (isJump) {
		ani = SIMON_ANI_JUMPING;
		if (GetTickCount() - jumpTime > SIMON_TIME_JUMPPING_SIT) {
			ani = SIMON_STATE_IDLE;
			jumpTime = 0;
		}
	}
	else {

		if (vx == 0) {
			if (!isSit) {
				ani = SIMON_ANI_IDLE;
			}
			else {
				ani = SIMON_ANI_SITTING;
			}
		}
		else
			ani = SIMON_ANI_WALKING;
	}
	int alpha = 255;
	if (untouchable) alpha = 128;
	if (nx > 0)
		animation_set->at(ani)->Render(x-SIMON_PADDING_ANI, y, alpha);
	else
		animation_set->at(ani)->Render(x- SIMON_PADDING_ANI, y,-1, alpha);
	RenderBoundingBox();
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		if (isAttact && !isJump)
			vx = 0;
		else
			vx = SIMON_WALKING_SPEED;
		nx = 1;
		isSit = false;
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (isAttact && !isJump)
			vx = 0;
		else
			vx = -SIMON_WALKING_SPEED;
		nx = -1;
		isSit = false;
		break;
	case SIMON_STATE_JUMP:
		if (isJump||isSit)return;
		vy = -SIMON_JUMP_SPEED_Y;
		jumpTime = GetTickCount();
		isJump = true;
		isSit = false;
		break;
	case SIMON_STATE_ATTACK:
		if (isAttact) return;
		if (!isJump) vx = 0;
		isAttact = true;
		attactTime = GetTickCount();
		break;
	case SIMON_STATE_SIT:
		if (isJump||isSit)return;
		if (!isSit) {
			if (isAttact)
				return;
			else {
				y += (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
				isSit = true;
				vx = 0;
				vy = 0;
			}
		}
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		if (isSit&&!isAttact) {
			isSit = false;
			y -= (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
		}
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		isSit = false;
		break;
	}
}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
	if (isSit || !isAttact&&jumpTime > 0 && isJump)
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
}



