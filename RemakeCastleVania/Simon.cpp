#include "Simon.h"
#include"Textures.h"


void Simon::CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents) {
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		/*if (!dynamic_cast<BigFire *>(coObjects->at(i)))
		{
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

			if (e->t > 0 && e->t <= 1.0f)
				coEvents.push_back(e);
			else
				delete e;
		}*/
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (nextScreen) {
		x = x + nx * 0.5;
		return;
	}

	if (isAttact&&GetTickCount() - attactTime >= SIMON_ATTACT_TIME) {
		isAttact = false;
		//x += SIMON_PADDING_ATTACT/2;
		//whip->Update(dt, coObjects);
	}
	if (timeWait != 0) {
		if (GetTickCount() - timeWait >= 400) {
			timeWait = 0;
		}
		else {
			vx = 0;
			return;
		}
	}
	// Simple fall down
	vy += SIMON_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	/*if (y + SIMON_BBOX_HEIGHT >= 8 * TILE_MAP_SIZE+HEIGHTBOARD) {
		if (vy > 0) {
			vy = 0;
			y = 7 * TILE_MAP_SIZE+HEIGHTBOARD-1;
			if (isJump) {
				SetState(SIMON_STATE_IDLE);
				isJump = false;
			}

		}
	}*/
	if (isAttact == true)
	{
		if (nx > 0)
		{
			// Whip position equal to simon position
			//whip->SetPosition(x, y + (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT));
		}
		else
		{
			// Whip position equal to simon position + simon width - whip width
			float wl, wr, wt, wb;
			//whip->GetBoundingBox(wl, wt, wr, wb);
			//whip->SetPosition(x + SIMON_BBOX_WIDTH - (wr - wl), y + (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT));
		}
	}

	//khi simon đi qua vách trái
	if (x < 0)
		x = 0;
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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny,rdx,rdy);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			/*if (dynamic_cast<Item *>(e->obj)) {
				Item *item = dynamic_cast<Item*>(e->obj);
				item->isPicked = !item->isPicked;
				timeWait = GetTickCount();
				vx = 0;
				if (item->typeItem == ItemType::WHIP)
					whip->level = 2;
			}
			else if (dynamic_cast<CBrick *>(e->obj)) {
				if (e->ny < 0) {
					if (isJump) {
						isJump = false;
						y -= (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
					}
					vy = 0;
				}
				else if (e->ny > 0) {
					y += dy;
				}
			}
			else if (dynamic_cast<HidenObject *>(e->obj)) {
				nextScreen = true;
			}*/
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	int ani;
	if (nextScreen) ani = ANI_WALKING_RIGHT;
	else if (state == SIMON_STATE_DIE)
		ani = ANI_DIE;
	else if (timeWait != 0)
	{
		if (nx > 0)
			ani = ANI_EAT_ITEM_RIGHT;
		else
			ani = ANI_EAT_ITEM_LEFT;
	}
	else if (isAttact) {
		if (nx > 0) {
			if (isSit)
				ani = ANI_SIT_HIT_RIGHT;
			else
				ani = ANI_HIT_RIGHT;
		}
		else
		{
			if (isSit)
				ani = ANI_SIT_HIT_LEFT;
			else
				ani = ANI_HIT_LEFT;
		}
	}
	else if (isJump) {
		if (nx > 0)
			ani = ANI_JUMP_RIGHT;
		else
			ani = ANI_JUMP_LEFT;
	}
	else {

		if (vx == 0) {
			if (!isSit) {
				if (nx > 0)
					ani = ANI_IDLE_RIGHT;
				else
					ani = ANI_IDLE_LEFT;
			}
			else {
				if (nx > 0)
					ani = ANI_SIT_RIGHT;
				else
					ani = ANI_SIT_LEFT;
			}
		}
		else if (vx > 0)
			ani = ANI_WALKING_RIGHT;
		else
			ani = ANI_WALKING_LEFT;
	}
	int alpha = 255;
	if (untouchable) alpha = 128;
	/*animations[ani]->Render(x, y, alpha);

	if (isAttact) {
		if (whip->level == 1) {
			if (!isSit) {
				if (nx > 0)
					whip->animations[0]->Render(x, y);
				else
					whip->animations[1]->Render(x, y);
			}
			else {
				if (nx > 0)
					whip->animations[0]->Render(x, y + (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT));
				else
					whip->animations[1]->Render(x, y + (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT));
			}
		}
		else
			whip->animations[2]->Render(x, y);*/

		//whip->RenderBoundingBox();
	//}
	//RenderBoundingBox();
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
		if (isJump)return;
		vy = -SIMON_JUMP_SPEED_Y;
		isJump = true;
		isSit = false;
		break;
	case SIMON_STATE_ATTACK:
		if (isAttact) return;
		if (!isJump) vx = 0;
		isAttact = true;
		//x -= SIMON_PADDING_ATTACT/2;
		//if (!isJump) vx = 0;
		attactTime = GetTickCount();
		break;
	case SIMON_STATE_SIT:
		if (isJump)return;
		if (!isSit)y += (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
		isSit = true;
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		if (isSit) {
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
	if (isSit || isJump) {
		left = x;
		top = y;
		right = x + SIMON_SIT_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
	else {

		left = x;
		top = y;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
	}
	if (isAttact) {
		left = x - SIMON_PADDING_ATTACT;
		right = x + SIMON_SIT_BBOX_WIDTH + SIMON_PADDING_ATTACT;
	}
}

