#include "Simon.h"
#include"Textures.h"

Simon::Simon() : CGameObject()
{
	game = CGame::GetInstance();
	untouchable = 0;
	prevAni = -1;
	heartWeapon = 0;
	SetState(SIMON_STATE_IDLE);
	weapons[gameType::WHIP] = new Whip();
}


void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (isAutoGo&&!isJump) {
		//if (!isStair) {
		//	if (isAutoGoWithJump) {
		//		if (autoGoX3 != 0 && x > autoGoX1) {
		//			x += SIMON_AUTO_GO_SPEED * nx;
		//			nx = -1.0f;
		//		}
		//		else {
		//			isAutoGoWithJump = false;
		//			autoGoX3 = 0;
		//			nx = 1.0f;
		//		}
		//	}
		//	else {
		//		x += SIMON_AUTO_GO_SPEED * nx;
		//		if (x > autoGoX2) {
		//			isAutoGo = false;
		//			vx = 0;
		//		}
		//	}
		//}
		//else {
		//	//if(x < )
		//}

		if ((abs(dx) <= abs(autoGoX_Distance)&& autoGoX_Distance !=0)|| (abs(dy) <= abs(autoGoY_Distance) && autoGoY_Distance != 0))
		{
			if (abs(dx) <= abs(autoGoX_Distance))
			{
				x += dx*nx;
				autoGoX_Distance -= abs(dx);
			}
			if (abs(dy) <= abs(autoGoY_Distance))
			{
				y += dy;
				autoGoY_Distance -= abs(dy);
			}
		}
		else {
			isAutoGo = false;
			isAutoGoWithJump = false;

			nx = nx_new;
			SetState(state_new);
			autoGoX_Distance = 0;
			autoGoY_Distance = 0;

		}
	}
	else if (isStair) {

	}
	else {
		// Calculate dx, dy 
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

		checkCollisonWithBricks(dt,coObjects);

	}
	// vị trí khi chảy
	//DebugOut(L"midle %d \n",midleStairUp);
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
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (isAutoGo&&!isJump)
		ani = SIMON_ANI_WALKING;
	else if (isStair) {
		/*if(isGoUp)
			ani = SIMON_ANI_GO_UP;
		else if(SIMON_STATE_IDLE_STAIR)*/
			ani = SIMON_ANI_IDLE_UP;
	}
	else if (isAttact) {
		if (!isEatItem) {
			if (isSit)
				ani = SIMON_ANI_SITTING_ATTACKING;
			else
				ani = SIMON_ANI_STANDING_ATTACKING;
		}
		else {
			ani = SIMON_ANI_EATTING;
		}
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

	currentAni = ani;
	if (isEatItem) {
		animation_set->at(prevAni + 13)->RenderIdFrame(animation_set->at(prevAni)->getCurrentFrame(), x - SIMON_PADDING_ANI, y, nx, D3DCOLOR_ARGB(128, rand() % 256, rand() % 256, rand() % 256));
	}
	else {

		if (isRenderLopping&&isAttact)
			animation_set->at(prevAni)->Render(x - SIMON_PADDING_ANI, y, nx, alpha);
		else
			animation_set->at(ani)->Render(x - SIMON_PADDING_ANI, y, nx, alpha);
	}
	for (auto&weapon : weapons) {
		if (weapon.second->GetAttack())
			weapon.second->Render();
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
	case SIMON_STATE_DOWN_STAIR:
		if (isGoUp) nx = -nx;
		vx = nx * SIMON_AUTO_GO_SPEED;
		vy = SIMON_AUTO_GO_SPEED;
		isStair = true;
		isGoDown = true;
		isGoUp = false;
		break;
	case SIMON_STATE_UP_STAIR:
		if (isGoDown) nx = -nx;
		vx = nxCheckStairUp * SIMON_AUTO_GO_SPEED;
		vy = -SIMON_AUTO_GO_SPEED;
		isStair = true;
		isGoDown = false;
		isGoUp = true;
		break;
	case SIMON_STATE_IDLE_STAIR:
		vx = vy = 0;
		isStair = true;
		isGoDown = false;
		isGoUp = false;
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
	for (auto&weapon : weapons) {
		if (weapon.second->GetAttack() && weapon.second->getType() == weaponType)
			return;
	}

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
		weapons[weaponType]->setPosition(x, y, nx);
		//weapons[weaponType]->resetFrame();
		weapons[weaponType]->SetAttack(true);
	}
}

void Simon::checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
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

		//if (nx != 0) nx = 0;
		if (ny < 0) {
			y += min_ty * dy + ny * 0.4f;
			vy = 0;
			if (isJump) {
				isJump = isJumpLeft = isJumpRight = false;
				vx = 0;
				if (isAutoGoWithJump) {
					SetState(SIMON_STATE_WALKING_RIGHT);
					this->nx = (collXFirst > this->x) ? 1 : -1;
					setValueAutoGo(abs(collXFirst -10.0f - this->x), 0.0f, SIMON_STATE_WALKING_RIGHT, 1);
				}
			}
			isOnBase = true;
			float l, t, r, b;
			GetBoundingBox(l, t, r, b);
			ground_Y = b;
		}
		else {
			y += dy;
			isOnBase = false;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//DebugOut(L"ground: %d \n", ground_Y);
}

void Simon::setValueAutoGo(float disX, float disY, int new_state, int new_nx)
{
	isAutoGo = true;

	autoGoX_Distance = disX;
	autoGoY_Distance = disY;
	state_new = new_state;
	nx_new = new_nx;
}

void Simon::goUpStair()
{
	if(isStair){
		/*SetState(SIMON_STATE_UP_STAIR);

		isAutoGo = true;*/
		return;
	}
	else {
		if (isOnCheckStairUp) {
			DebugOut(L"%f %f \n",x,xStairUp);
			SetState(SIMON_STATE_WALKING_RIGHT);
			this->nx = (xStairUp > this->x) ? 1 : -1;
			setValueAutoGo(abs(xStairUp - this->x), 0.0f, SIMON_STATE_IDLE_STAIR, nxCheckStairUp);
		}
	}
}



