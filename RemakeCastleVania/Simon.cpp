#include "Simon.h"
#include"Textures.h"

Simon::Simon() : CGameObject()
{
	game = CGame::GetInstance();
	untouchable = 0;
	prevAni = 0;
	heartWeapon = 0;
	SetState(SIMON_STATE_IDLE);
	weapons[gameType::WHIP] = new Whip();
}


void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	// vị trí khi chảy
	if (isJump) {// xét đang nhãy thì ko đổi hướng
		if (isJumpRight)
			vx = SIMON_WALKING_SPEED * 1.0f;
		else if (isJumpLeft)
			vx = -SIMON_WALKING_SPEED * 1.0f;
		vy += SIMON_JUMP_GRAVITY * dt;
	} 
	else {
		vy += SIMON_GRAVITY * dt;
	}
	//simon ko bị rớt ra khỏi camera
	if (x < CMap::GetInstance()->boundingMapLeft)
		x = CMap::GetInstance()->boundingMapLeft;
	if (x + SIMON_BBOX_WIDTH > CMap::GetInstance()->boundingMapRight)
		x = CMap::GetInstance()->boundingMapRight - SIMON_BBOX_WIDTH;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listBricks;
	listBricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)//lọc ra danh sách brick
		if (coObjects->at(i)->getType() == gameType::BRICK)
			listBricks.push_back(coObjects->at(i));

	// kiểm ra va chạm với Brick
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(&listBricks, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		isOnBase = false;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;

		if (ny < 0) {
			y += min_ty * dy + ny * 0.4f;
			vy = 0;
			if (isJump) {
				isJump = isJumpLeft = isJumpRight = false;
				vx = 0;
			}
		}
		else
			y += dy;
		if (ny != 0) isOnBase = true;
		else isOnBase = false;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (isEatItem) {
		if (GetTickCount() - timeEatItem > SIMON_EATTING_TIME) {
			timeEatItem = 0;
			isEatItem = false;
			timeFreeze = 0;
		}
		else {
			vx = 0;
		}
		//if (prevAni= SIMON_ANI_EATTING)
		//	attactTime += SIMON_EATTING_TIME;
	}
	if (isAttact && GetTickCount() - attactTime >= SIMON_ATTACT_TIME) {
		isAttact = false;
		attactTime = -1;
		weapons[gameType::WHIP]->SetAttack(false);
		if (CGame::GetInstance()->IsKeyDown(DIK_DOWN) == false && isSit) {
			y -= (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
			isSit = false;
		}
	}

	for (auto&weapon : weapons) {
		if (weapon.second->GetAttack()) {
			if (weapon.second->getType() == gameType::WHIP)
				weapons[gameType::WHIP]->setPosition(x, y, nx);
			weapon.second->Update(dt, coObjects);
		}
	}
}

void Simon::Render()
{
	int ani;
	if (nextScreen) ani = SIMON_ANI_WALKING;
	else if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (isEatItem)
	{
		if (prevAni != SIMON_ANI_EATTING)
			animation_set->at(prevAni)->resetFrame();
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
	animation_set->at(ani)->Render(x - SIMON_PADDING_ANI, y, nx, alpha);

	for (auto&weapon : weapons) {
		if (weapon.second->GetAttack())
			weapon.second->Render();
	}
	prevAni = ani;
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
	if (isSit || (!isAttact&&jumpTime > 0 && isJump&&!isEatItem)) {
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
}

void Simon::attackWeapon(gameType weaponType)
{
	switch (weaponType)
	{
	case gameType::WHIP:
		if (isAttact)return;// roi đánh đánh thì ko đánh nữa
		break;
	case gameType::DAGGER:
		heartWeapon--;
		break;
	default:
		break;
	}

	if (!weapons[weaponType]->GetAttack()) { // kho có xuất hiện trên màn hình thì cho đánh
		isAttact = true;
		attactTime = GetTickCount();
		if (!isJump) vx = 0;
		weapons[weaponType]->resetFrame();
		weapons[weaponType]->SetAttack(true);
		weapons[weaponType]->setPosition(x, y, nx);
	}
}



