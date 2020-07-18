#include "Bone.h"

void CBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float camX, camY;
	game->GetCamPos(camX, camY);
	checkCollisonWithHidenObjects(dt, coObjects);

	if (y + BONE_BBOX_HEIGHT > camY + SCREEN_HEIGHT)
		isHitted = true;
	else if (GetTickCount() - timeWaitState <= 200)
		return;
	else if (isJump) {
		vy += BONE_GRAVITY_SPEED * dt;
		CGameObject::Update(dt);
		checkCollisonWithBricks(dt, coObjects);
	}
	else if (isAttack) {
		if (bonePerHit < 1)isAttack = false;
	}
	else if (isWalkAutoX) {
		
		CGameObject::Update(dt);
		if (abs(dx) <= abs(autoGoX_Distance) && autoGoX_Distance != 0)
		{
			if (abs(dx) <= abs(autoGoX_Distance))
			{
				x += dx * nxWalk;
				autoGoX_Distance -= abs(dx);;;
			}
		}
		else {
			x += autoGoX_Distance * nx;
			isWalkAutoX = false;
			SetState(BONE_STATE_IDLE);
			autoGoX_Distance = 0;
			if (GetTickCount() - lastTimeAttack >= BONE_TIME_WAIT_ATTACK && abs(x + BONE_BBOX_WIDTH / 2 - simon->x - SIMON_BBOX_WIDTH / 2) <= BRICK_BBOX_WIDTH * 3.5f) {
				attackBone();
				lastTimeAttack = GetTickCount();
			}
		}
		checkCollisonWithBricks(dt, coObjects);
	}
	else {
		SetState(BONE_STATE_WALK);
		autoGoX_Distance = abs(randomPositionX() - (x + BONE_BBOX_WIDTH / 2));
		autoGoX_Distance = (autoGoX_Distance > BRICK_BBOX_WIDTH * 1.5F) ? BRICK_BBOX_WIDTH * 1.5f : autoGoX_Distance;
		setAutoNx();
	}
}

void CBone::Render()
{
	animation_set->at((isJump) ? 1 : 0)->Render(x, y, -nx);
	//RenderBoundingBox();
}

void CBone::GetBoundingBox(float & _left, float & _top, float & _right, float & _bottom)
{
	_left = x;
	_top = y;
	_right = x + BONE_BBOX_WIDTH;
	_bottom = y + BONE_BBOX_HEIGHT;
}

void CBone::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BONE_STATE_IDLE:
		vx = vy = 0;
		autoGoX_Distance = 0;
		isJump = false;
		isWalkAutoX = false;
		break;
	case BONE_STATE_WALK:
		vx = BONE_WALK_SPEED_X;
		isJump = false;
		isWalkAutoX = true;
		break;
	case BONE_STATE_JUMP:
		vx = BONE_JUMP_SPEED_X * nxWalk;
		vy = -BONE_JUMP_SPEED_Y;
		isJump = true;
		isWalkAutoX = false;
		break;
	}
}

void CBone::checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

	bool isComparePosition = false;
	for (UINT i = 0; i < listActives.size(); i++) {
		if (isCollitionObjectWithObject(listActives[i])) {
			float l, t, r, b;
			listActives[i]->GetBoundingBox(l, t, r, b);
			if (abs(y + BONE_BBOX_HEIGHT - b) <= BRICK_BBOX_HEIGHT * 1.5f && (abs(x + BONE_BBOX_WIDTH/2 - l) <= BONE_SPACE_CLIMBTOTOP || abs(x + BONE_BBOX_WIDTH/2 - r) <= BONE_SPACE_CLIMBTOTOP)) {
				y = t - BONE_BBOX_HEIGHT - 1;
				isComparePosition = true;
			}
		}
	}

	// kiểm ra va chạm với Brick
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(&listActives, coEvents);
	if (coEvents.size() == 0)
	{
		if (state != BONE_STATE_WALK) {
			x += dx;
			y += dy;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		if (!isJump) {
			//x += min_tx * dx + nx * 0.4f;
			//if (nx != 0) vx = 0;
		}

		if (ny == -1) {
			y += min_ty * dy + ny * 0.4f;
			SetState(BONE_STATE_IDLE);
			timeWaitState = GetTickCount();
		}
		else {
			if (isJump)
				x += dx;
			y += dy;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBone::checkCollisonWithHidenObjects(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	isOnCheckJump = false;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listActives;
	listActives.clear();

	for (UINT i = 0; i < coObjects->size(); i++)//lọc ra danh sách cần xét va chạm disable jump
		if (coObjects->at(i)->getType() == gameType::BE_JUMP)
			if (isCollitionObjectWithObject(coObjects->at(i))) {
				if (!isJump) {
					auto *beJump = dynamic_cast<CMustBeJump*>(coObjects->at(i));
					nxWalk = beJump->getNX();
					SetState(BONE_STATE_JUMP);
					isOnCheckJump = true;
				}
			}
}

void CBone::beAttack()
{
	isHitted = true;
}

void CBone::attackBone()
{
	isAttack = true;
	int num = rand() % (4 - 1 + 1) + 1;
	bonePerHit = (num == 4) ? 2 : 1;
}

void CBone::attackWeapon(vector<LPGAMEOBJECT>& listWeapon)
{
	if (bonePerHit < 1)return;
	else {		
		if (GetTickCount() - lastTimeAttackPerHit >= 300) {
			CWhiteBone * bone = new CWhiteBone();
			bone->setPosition(x, y, nx);
			bone->SetAttack(true);
			listWeapon.push_back(bone);
			lastTimeAttackPerHit = GetTickCount();
			bonePerHit--;
		}
	}
}

void CBone::SetPosition(float _x, float _y)
{
	CGameObject::SetPosition(_x, _y);
	setAutoNx();
	randomPositionX();
}

void CBone::setAutoNx()
{
	if (x + BONE_BBOX_WIDTH / 2 < simon->x + SIMON_BBOX_WIDTH / 2)
		nx = 1;
	else nx = -1;
}

float CBone::float_randomX(float min, float max)
{
	float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
	return min + scale * (max - min);      /* [min, max] */
}

float CBone::randomPositionX()
{
	int minLeft, minRight;
	if (x + BONE_BBOX_WIDTH / 2 < simon->x + SIMON_BBOX_WIDTH / 2) {
		minLeft = simon->x - BONE_MIN_LEFT_TO_SIMON;
		minRight = simon->x - BONE_MIN_RIGHT_TO_SIMON;
	}
	else {
		minLeft = simon->x + SIMON_BBOX_WIDTH + BONE_MIN_RIGHT_TO_SIMON;
		minRight = simon->x + SIMON_BBOX_WIDTH + BONE_MIN_LEFT_TO_SIMON;
	}
	float ran;
	//float ran = float_randomX(minLeft, minRight);
	if (x < (minLeft + minRight) / 2)
		ran = minRight+5;
	else
		ran = minLeft-5;
	if (x < minLeft)
		nxWalk = 1;
	else
		nxWalk = -1;
	return ran;
}

CBone::~CBone()
{
}
