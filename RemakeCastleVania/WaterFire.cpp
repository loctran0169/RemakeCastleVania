#include "WaterFire.h"


void CWaterFire::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick *>(coObjects->at(i)))
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

void CWaterFire::checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		DebugOut(L"water chạm gạch \n");
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		y -= (WATERFIRE_BBOX_HEIGHT - WATERFIRE_WATER_BBOX_HEIGHT);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		vx = vy = 0;
		isWater = false;
		timeStartFire = GetTickCount();
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CWaterFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);
	if (y + ((isWater) ? WATERFIRE_WATER_BBOX_HEIGHT : WATERFIRE_BBOX_HEIGHT) > SCREEN_HEIGHT)
		SetAttack(false);
	else if (isAttack) {
		if (!isWater&&GetTickCount() - timeStartFire > WATERFIRE_ATTACK_TIME)// hết thời gian cháy
			SetAttack(false);
		else if (isWater) {
			vy += WATERFIRE_SPEED_GRAVITY * dt;
			CGameObject::Update(dt, coObjects); // cập nhật thời gian, vận tốc
			x += dx;
			y += dy;

			checkCollisonWithBricks(dt, coObjects);// xét va chạm gạch thì nổ lửa
		}
	}
}

void CWaterFire::Render()
{
	animation_set->at((isWater) ? WATERFIRE_ANI_WATER : WATERFIRE_ANI_FIRE)->Render(x, y, nx);
	//RenderBoundingBox();
}

void CWaterFire::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (isWater) {
		right = x + WATERFIRE_WATER_BBOX_WIDTH;
		bottom = y + WATERFIRE_WATER_BBOX_HEIGHT;
	}
	else {
		right = x + WATERFIRE_BBOX_WIDTH;
		bottom = y + WATERFIRE_BBOX_HEIGHT;
	}
}

void CWaterFire::setPosition(float _x, float _y, int _nx)
{
	this->nx = _nx;
	isWater = true;
	vx = WATERFIRE_SPEED_X * this->nx;
	vy = -WATERFIRE_SPEED_Y;
	if (nx > 0)
		CGameObject::SetPosition(_x - SIMON_PADDING_ANI - SIMON_PADDING_WEAPON_ATTACK+ SIMON_PADDING_WEAPON_ATTACK_WATERFIRE_X, _y + SIMON_PADDING_WEAPON_ATTACK+ SIMON_PADDING_WEAPON_ATTACK_WATERFIRE_Y);
	else
		CGameObject::SetPosition(_x + SIMON_BBOX_WIDTH - SIMON_PADDING_WEAPON_ATTACK_WATERFIRE_X-10, _y + SIMON_PADDING_WEAPON_ATTACK+ SIMON_PADDING_WEAPON_ATTACK_WATERFIRE_Y);
	timeAttact = GetTickCount();
}

CWaterFire::~CWaterFire()
{
}
