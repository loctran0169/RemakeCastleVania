#include "Simon.h"
#include"Textures.h"

Simon::Simon() : CGameObject()
{
	untouchable = 0;
	SetState(SIMON_STATE_IDLE);
	whip = new Whip();
}

void Simon::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (!dynamic_cast<CTorch *>(coObjects->at(i)))
		{
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

			if (e->t > 0 && e->t <= 1.0f)
				coEvents.push_back(e);
			else
				delete e;
		}
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
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
		whip->Update(dt, coObjects);
		if (CGame::GetInstance()->IsKeyDown(DIK_DOWN) == false && isSit) {
			y -= (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
			isSit = false;
		}
	}
	if (isAttact == true)
	{
		if (nx > 0)
		{
			//roi bên phải
			whip->SetPosition(x+SIMON_BBOX_WIDTH, y + WHIP_PADDING_TOP);
			whip->setPosRender(x, y);
		}
		else
		{
			//roi bên trái
			float wl, wr, wt, wb;
			whip->GetBoundingBox(wl, wt, wr, wb);
			whip->SetPosition(x - (wr - wl) - SIMON_PADDING_ANI, y + WHIP_PADDING_TOP);
			whip->setPosRender(x + SIMON_BBOX_WIDTH * 2-7, y);
		}
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
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

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
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				DebugOut(L"[INFO] Switching to scene %d", p->GetSceneId());
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
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
	if (isAttact) {
		whip->nx = nx;
		whip->Render();
	}
	//RenderBoundingBox();
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		jumpTime = GetTickCount();
		isJump = true;
		break;
	case SIMON_STATE_ATTACK:
		if (!isJump) vx = 0;
		isAttact = true;
		attactTime = GetTickCount();
		break;
	case SIMON_STATE_SIT:
		vx = 0;
		isSit = true;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
	if (isSit || !isAttact&&jumpTime > 0 && isJump) {
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
}



