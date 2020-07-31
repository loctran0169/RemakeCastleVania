#include "Simon.h"

Simon* Simon::__instance = NULL;

Simon* Simon::GetInstance()
{
	if (__instance == NULL) __instance = new Simon();
	return __instance;
}

Simon::Simon() : CGameObject()
{
	game = CGame::GetInstance();
	untouchable = 0;
	prevAni = -1;
	SetState(SIMON_STATE_IDLE);
	weapons[gameType::WHIP] = new Whip();
}


void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	// reset untouchable timer if untouchable time has passed
	if (y + SIMON_BBOX_HEIGHT > game->cam_y + SCREEN_HEIGHT)dieStart();
	if (GetTickCount() - untouchable_start > timeTouchable)
	{
		untouchable_start = 0;
		untouchable = 0;
		if (isUsePotion) {
			isUsePotion = false;
			CSound::GetInstance()->play(gameType::ITEM_INVISIBLE, NULL, 1);
		}
	}
	else {
		if (isUsePotion && GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME_ITEM * 4 / 5) {
			isUsePotion = false;
			CSound::GetInstance()->play(gameType::ITEM_INVISIBLE, NULL, 1);
		}
	}
	if (isUseToFullHP) {
		if (GetTickCount() - timeEatItem > TIME_REVERT_HP_STEP) {
			plusHealth(2);
			timeEatItem = GetTickCount();
		}
		if (getHealth() == MAX_HP)
			isUseToFullHP = false;
	}
	else if (isAutoGo&&!isJump) {
		if ((abs(dx) <= abs(autoGoX_Distance)&& autoGoX_Distance !=0)|| (abs(dy) <= abs(autoGoY_Distance) && autoGoY_Distance != 0))
		{
			if (abs(dx) <= abs(autoGoX_Distance))
			{
				x += dx;
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
			x += autoGoX_Distance*nx;
			y += autoGoY_Distance*((isGoUp)?-1:1); //sai so

			int prev_state = state;
			nx = nx_new;
			SetState(state_new);
			autoGoX_Distance = 0;
			autoGoY_Distance = 0;

			
			if (nextAutoGo) {
				if (SIMON_STATE_UP_STAIR)
					setValueAutoGo(16.0f, 16.0f, SIMON_STATE_IDLE_STAIR, nx, false);
				else if(SIMON_STATE_DOWN_STAIR)
					setValueAutoGo(16.0f, 16.0f, SIMON_STATE_IDLE_STAIR, nx, false);
				nextAutoGo = false;
			}
			else if (isStair) {
				if (isOnCheckStairUp&&isOnCheckStairDown) {
					if (prev_state != SIMON_STATE_WALKING_RIGHT || prev_state != SIMON_STATE_WALKING_LEFT)
						SetState(SIMON_STATE_IDLE);
				}
				else if ((isGoDown && isOnCheckStairUp) || (isGoUp && isOnCheckStairDown)) {
					if (xStairUp != 0 && abs(x - xStairUp) >= BRICK_BBOX_WIDTH * 1.5f)
						SetState(SIMON_STATE_IDLE);
					else if (xStairDown != 0 && abs(x - xStairDown) >= BRICK_BBOX_WIDTH * 1.5f)
						SetState(SIMON_STATE_IDLE);
					else if (isOnCheckStairDown && !isGoStairByUp)
						SetState(SIMON_STATE_IDLE);
					else if (isOnCheckStairUp&&isGoStairByUp)
						SetState(SIMON_STATE_IDLE);
				}
			}
		}
	}
	else if (isStair) {

	}
	else {
		// Calculate dx, dy 
		if (isJump) {// xét đang nhãy thì ko đổi hướng
			if (isJumpRight)
				vx = SIMON_WALKING_SPEED;
			else if (isJumpLeft)
				vx = -SIMON_WALKING_SPEED;
			else
				vx = 0;
			vy += SIMON_JUMP_GRAVITY * dt;
		}
		else if(isHurt)
			vy += SIMON_GRAVITY_HURTING * dt;
		else {
			vy += SIMON_GRAVITY * dt;
		}
		//simon ko bị rớt ra khỏi camera
		if (x < game->cam_x)
			x = game->cam_x;
		if (x + SIMON_BBOX_WIDTH > game->cam_x + SCREEN_WIDTH)
			x = game->cam_x + SCREEN_WIDTH - SIMON_BBOX_WIDTH;

		if (!checkCollisonWithSkateBoard(dt, coObjects)) {
			if (!checkCollisonWithBricks(dt, coObjects))
			{
				x += dx;
				y += dy;
			}
		}
		else 
			x += dx;	
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
	if (isDie)
		ani = SIMON_ANI_DIE;
	else if (isStair) {
		if (isGoUp && vx != 0)
			ani = SIMON_ANI_GO_UP;
		else if (isGoDown && vx != 0)
			ani = SIMON_ANI_GO_DOWN;
		else if (isAttact&&isGoUp)
			ani = SIMON_ANI_ATTACK_UP;
		else if (isAttact&&isGoDown)
			ani = SIMON_ANI_ATTACK_DOWN;
		else {
			if (isGoUp) ani = SIMON_ANI_IDLE_UP;
			else ani = SIMON_ANI_IDLE_DOWN;
		}
	}
	else if (isHurt)
		ani = SIMON_ANI_HURT;
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
			if (!isSit)
				ani = SIMON_ANI_IDLE;
			else
				ani = SIMON_ANI_SITTING;
		}
		else {
			if (state == SIMON_STATE_ON_SKATE && !game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_LEFT))
				ani = SIMON_ANI_IDLE;
			else
				ani = SIMON_ANI_WALKING;
		}
	}
	int alpha = 255;
	if (untouchable) alpha = 128;
	currentAni = ani;
	if (isEatItem) {
		animation_set->at(prevAni + 15)->RenderIdFrame(animation_set->at(prevAni)->getCurrentFrame(), x - SIMON_PADDING_ANI, y, nx, D3DCOLOR_ARGB(128, rand() % 256, rand() % 256, rand() % 256));
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

bool Simon::isUsingWeapon(gameType _type)
{
	if (this->weapons.find(_type) != this->weapons.end()) // tìm đang sài nó ko
	{
		if (this->weapons[_type]->GetAttack() == true)
			return true;
	}
	return false;
}

void Simon::resetDoubleTripleShot()
{
	isUseDoubleShot = false;
	isUseTripleShot = false;
}

void Simon::startPlusFullHP()
{
	isUseToFullHP = true;
	SetState(SIMON_STATE_IDLE);
	timeEatItem = GetTickCount();
}

void Simon::dieStart()
{
	if (isDie)return;
	isDie = true;
	timeDieStart = GetTickCount();
	isHurt = false;
	untouchable_start = 0;
	untouchable = 0;
	CSound::GetInstance()->play(gameType::SIMON_DIE, NULL, 1);
	SetState(SIMON_STATE_DIE);
}

void Simon::resetState()
{
	isSit = false;
	isJump = false;
	isAttact = false;
	isEatItem = false;
	isRenderLopping = false;
	isUseToFullHP = false;
	isHurt = false;
	isUseTransparent = false;
	isStair = false;
	isGoUp = false;
	isGoDown = false;
	isGoStairByUp = false;
	isUseDoubleShot = false;
	isUseTripleShot = false;
	isUsePotion = false;
	isAutoGo = false;
	nextAutoGo = false;
	isDie = false;
	autoGoX_Distance = 0;
	autoGoY_Distance = 0;
	weapons.clear();
	currentWeapon = gameType::WHIP;
	lastItemCollect = gameType::ITEM_WHIP;
	weapons[gameType::WHIP] = new Whip();
	heartWeapon = 5;
	health = MAX_HP;
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	lastTimeChangeState = GetTickCount();
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
		vx = nx * SIMON_STAIR_SPEED;
		vy = SIMON_STAIR_SPEED;
		isStair = true;
		isGoDown = true;
		isGoUp = false;
		break;
	case SIMON_STATE_UP_STAIR:
		if (isGoDown) nx = -nx;
		vx = nx * SIMON_STAIR_SPEED;
		vy = -SIMON_STAIR_SPEED;
		isStair = true;
		isGoDown = false;
		isGoUp = true;
		break;
	case SIMON_STATE_IDLE_STAIR:
		vx = vy = 0;
		isStair = true;
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
		vx = vy = 0;
		xStairUp = xStairDown = 0;
		isJump = false;
		isStair = false;
		isGoDown = false;
		isGoUp = false;
		break;
	case SIMON_STATE_DIE:
		vx = 0;
		vy = -SIMON_DIE_DEFLECT_SPEED;
		isStair = false;
		isAutoGo = false;
		isJump = false;
		jumpTime = 0;
		isAttact = false;
		isHurt = false;
		dieStart();
		break;
	case SIMON_STATE_ON_SKATE:
		break;
	case SIMON_STATE_HURT:
		isHurt = true;
		isJump = false;
		isJumpRight = false;
		isJumpLeft = false;
		vx = SIMON_WALKING_SPEED * nxHurt;
		vy = -SIMON_VJUMP_HURTING;
		break;
	}
	stateSpeed = vx;
}

void Simon::SetHurt(int _nx)
{
	if (isHurt)return;
	if (isAttact) {
		animation_set->at(currentAni)->resetFrame();
		if (weapons[gameType::WHIP]) {
			auto *whip = dynamic_cast<Whip*>(weapons[gameType::WHIP]);
			whip->SetAttack(false);
			whip->animation_set->at(whip->getAniID())->resetFrame();			
		}
	}
	jumpTime = 0;

	if (!isStair && !isAutoGo) {
		nxHurt = _nx;
		nx = -_nx;
		SetState(SIMON_STATE_HURT);
	}
		
	StartUntouchable(SIMON_UNTOUCHABLE_TIME);
	isAutoGo = false;
	SubHealth(2);
}

void Simon::SubHealth(int num)
{
	health -= num; 
	if (health <= 0)
	{
		health = 0;
		dieStart();
	}
}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
	if (isSit || (!isAttact&&jumpTime > 0 && isJump && !isEatItem)) {
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
}

void Simon::attackWeapon(gameType weaponType)
{
	int heartMustSub = 0;
	switch (weaponType)
	{
	case gameType::WHIP:
		if (isAttact)return;// roi đánh đánh thì ko đánh nữa
		break;
	case gameType::AXE:
		if (heartWeapon < 1)return;
		heartMustSub++;
		break;
	case gameType::BOOMERANG:
		if (heartWeapon < 1)return;
		heartMustSub++;
		break;
	case gameType::DAGGER:
		if (heartWeapon < 1)return;
		heartMustSub++;
		break;
	case gameType::STOP_WATCH:
		if (heartWeapon < 5)return;
		heartMustSub += 5;
		break;
	case gameType::WATER_FIRE:
		if (heartWeapon < 1)return;
		heartMustSub++;
		break;
	default:
		break;
	}

	if (!weapons[weaponType]->GetAttack()) { // kho có xuất hiện trên màn hình thì cho đánh
		isAttact = true;
		attactTime = GetTickCount();
		if (!isJump) vx = 0;
		weapons[weaponType]->setPosition(x, y, nx);
		weapons[weaponType]->SetAttack(true);
		heartWeapon -= heartMustSub;
		if (weaponType != BOOMERANG && weaponType != STOP_WATCH)
			CSound::GetInstance()->play(weaponType, NULL, 1);
		else
			CSound::GetInstance()->play(weaponType, true, 0);
	}
	else {
		if (isUseDoubleShot && weaponType != gameType::WHIP && weaponType != gameType::STOP_WATCH) {
			bool isCreate = false;
			if (weapons.find(gameType::DOUBLE_SHOT) == weapons.end())
				isCreate = true;
			else {
				if (weapons[gameType::DOUBLE_SHOT]->GetAttack())return;
				else {
					if (weapons[gameType::DOUBLE_SHOT]->getType() != weaponType)
						isCreate = true;
				}
			}
			if (isCreate) {
				switch (weaponType)
				{
				case gameType::DAGGER: {
					weapons[gameType::DOUBLE_SHOT] = new CKnife();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::DAGGER);
					weapons[gameType::DOUBLE_SHOT]->SetAnimationSet(ani_set);
					break;
				}
				case gameType::BOOMERANG: {
					weapons[gameType::DOUBLE_SHOT] = new CBoomerang();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::BOOMERANG);
					weapons[gameType::DOUBLE_SHOT]->SetAnimationSet(ani_set);
					break;
				}
				case gameType::AXE: {
					weapons[gameType::DOUBLE_SHOT] = new CAxe();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::AXE);
					weapons[gameType::DOUBLE_SHOT]->SetAnimationSet(ani_set);
					break;
				}
				case gameType::WATER_FIRE: {
					weapons[gameType::DOUBLE_SHOT] = new CWaterFire();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::WATER_FIRE);
					weapons[gameType::DOUBLE_SHOT]->SetAnimationSet(ani_set);
					break;
				}
				default:
					break;
				}
			}
			
			isAttact = true;
			attactTime = GetTickCount();
			if (!isJump) vx = 0;
			weapons[DOUBLE_SHOT]->setPosition(x, y, nx);
			weapons[DOUBLE_SHOT]->SetAttack(true);
			heartWeapon -= heartMustSub;
			if (weaponType != BOOMERANG)
				CSound::GetInstance()->play(weaponType, NULL, 1);
			else
				CSound::GetInstance()->play(weaponType, true, 0);
		}
		else if (isUseTripleShot && weaponType != gameType::WHIP && weaponType != gameType::STOP_WATCH) {
			bool isCreateDouble = false;
			bool isCreateTriple = false;
			if (weapons.find(gameType::DOUBLE_SHOT) == weapons.end())
				isCreateDouble = true;
			else if (weapons.find(gameType::TRIPLE_SHOT) == weapons.end())
				isCreateTriple = true;
			else {
				if (weapons[gameType::DOUBLE_SHOT]->GetAttack() && weapons[gameType::TRIPLE_SHOT]->GetAttack())
					return;
				else {
					if (weapons[gameType::DOUBLE_SHOT]->getType() != weaponType)
						isCreateDouble = true;
					else if (weapons[gameType::TRIPLE_SHOT]->getType() != weaponType)
						isCreateTriple = true;
				}
			}
			if (isCreateDouble||isCreateTriple) {
				gameType createType = (isCreateDouble) ? gameType::DOUBLE_SHOT : gameType::TRIPLE_SHOT;
				switch (weaponType)
				{
				case gameType::DAGGER: {
					weapons[createType] = new CKnife();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::DAGGER);
					weapons[createType]->SetAnimationSet(ani_set);
					break;
				}
				case gameType::BOOMERANG: {
					weapons[createType] = new CBoomerang();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::BOOMERANG);
					weapons[createType]->SetAnimationSet(ani_set);
					break;
				}
				case gameType::AXE: {
					weapons[createType] = new CAxe();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::AXE);
					weapons[createType]->SetAnimationSet(ani_set);
					break;
				}
				case gameType::WATER_FIRE: {
					weapons[createType] = new CWaterFire();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::WATER_FIRE);
					weapons[createType]->SetAnimationSet(ani_set);
					break;
				}
				default:
					break;
				}
			}

			isAttact = true;
			attactTime = GetTickCount();
			if (!isJump) vx = 0;
			gameType createType = (!weapons[gameType::DOUBLE_SHOT]->GetAttack()) ? gameType::DOUBLE_SHOT : gameType::TRIPLE_SHOT;
			weapons[createType]->setPosition(x, y, nx);
			weapons[createType]->SetAttack(true);
			heartWeapon -= heartMustSub;
			if (weaponType != BOOMERANG)
				CSound::GetInstance()->play(weaponType, NULL, 1);
			else
				CSound::GetInstance()->play(weaponType, true, 0);
		}
	}
}

bool Simon::checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listBricks;
	listBricks.clear();

	for (UINT i = 0; i < coObjects->size(); i++)//lọc ra danh sách brick
		if (coObjects->at(i)->getType() == gameType::BRICK||
			(coObjects->at(i)->getType() == gameType::BRICKBLACK_1 && !coObjects->at(i)->isHitted)||
			(coObjects->at(i)->getType() == gameType::BRICKBLACK_2 && !coObjects->at(i)->isHitted))
			listBricks.push_back(coObjects->at(i));

	CalcPotentialCollisions(&listBricks, coEvents);
	if (coEvents.size() == 0)
	{
		return false;
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
					SetState(SIMON_STATE_WALKING_LEFT);
					this->nx = (collXFirst > this->x) ? 1 : -1;
					setValueAutoGo(abs(collXFirst -10.0f - this->x), 0.0f,SIMON_STATE_WALKING_RIGHT, 1, true);
				}
			}
			if (isHurt) {
				isHurt = false;
				SetState(SIMON_STATE_IDLE);
			}
		}
		else {
			y += dy;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	return true;
}

bool Simon::checkCollisonWithSkateBoard(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listSkates;
	listSkates.clear();

	for (UINT i = 0; i < coObjects->size(); i++)//lọc ra danh sách ván trược
		if (coObjects->at(i)->getType() == gameType::SKATEBOARD)
			listSkates.push_back(coObjects->at(i));

	CalcPotentialCollisions(&listSkates, coEvents);
	if (coEvents.size() == 0)
	{
		return false;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++) {
			LPCOLLISIONEVENT e = coEventsResult[i];
			CSkateBoard * skate = dynamic_cast<CSkateBoard*>(e->obj);

			if (ny < 0) {
				y += min_ty * dy + ny * 0.4f;
				SetState(SIMON_STATE_IDLE);
				if (isJump) {
					isJump = isJumpLeft = isJumpRight = false;
					vx = 0;
				}
				
				if (stateSpeed == 0) {
					SetState(SIMON_STATE_ON_SKATE);
					vx = SKATEBOARD_SPEED_X * skate->nx;
				}
			}
		}		
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	return true;
}

void Simon::setValueAutoGo(float disX, float disY, int new_state, int new_nx,bool auto_afterAutoGo)
{
	isAutoGo = true;

	autoGoX_Distance = disX;
	autoGoY_Distance = disY;
	state_new = new_state;
	nx_new = new_nx;
	nextAutoGo = auto_afterAutoGo;
}

void Simon::goUpStair()
{
	if(isStair){
		SetState(SIMON_STATE_UP_STAIR);
		setValueAutoGo(16.0f, 16.0f, SIMON_STATE_IDLE_STAIR, nx,false);
		return;
	}
	else {
		if (isOnCheckStairUp) {
			int temp_nx = (xStairUp > this->x) ? 1 : -1;
			if (temp_nx > 0)
				SetState(SIMON_STATE_WALKING_RIGHT);
			else
				SetState(SIMON_STATE_WALKING_LEFT);
			setValueAutoGo(abs(xStairUp - this->x), 0.0f, SIMON_STATE_UP_STAIR, nxCheckStairUp,true);
			isGoStairByUp = true;
		}
	}
}

void Simon::goDownStair()
{
	if (isStair) {
		SetState(SIMON_STATE_DOWN_STAIR);
		setValueAutoGo(16.0f, 16.0f, SIMON_STATE_IDLE_STAIR, nx,false);
		return;
	}
	else {
		if (isOnCheckStairDown) {
			int temp_nx = (xStairDown > this->x) ? 1 : -1;
			if (temp_nx > 0)
				SetState(SIMON_STATE_WALKING_RIGHT);
			else
				SetState(SIMON_STATE_WALKING_LEFT);
			setValueAutoGo(abs(xStairDown - this->x), 0.0f, SIMON_STATE_DOWN_STAIR, nxCheckStairDown,true);
			isGoStairByUp = false;
		}
	}
}



