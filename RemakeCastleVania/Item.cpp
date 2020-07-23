#include "Item.h"

void Item::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
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

void Item::setValueGravity(float _l, float _r,float _vx, float _vy)
{
	boundLeft = _l;
	boundRight = _r;
	vx = _vx;
	vy = _vy;
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (timeExit != 0 && GetTickCount() - timeExit > ITEM_TIME_EXIT) {
		isPicked = true;
	}

	if (type != gameType::ITEM_HEART_MINI) {
		CGameObject::Update(dt);
		vy += ITEM_GRAVITY * dt;
	}
	else {
		if (x + ITEM_HEART_MINI_BBOX_WIDTH / 2 >= boundRight)
			vx = -SMALLHEART_SPEED_X;
		else if (x + ITEM_HEART_MINI_BBOX_WIDTH / 2 <= boundLeft)
		{
			vx = SMALLHEART_SPEED_X;
		}
		CGameObject::Update(dt);
	}

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
		float min_tx, min_ty, nx = 0, ny;
		float rdx, rdy;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// block 
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0) {
			vx = 0;
			vy = 0;
			if (timeExit == 0)
				timeExit = GetTickCount();
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
void Item::Render() {
	if (!isPicked)
		animation_set->at(type)->Render(x, y);
	//RenderBoundingBox();
}
void Item::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	if (type == gameType::ITEM_HEART) {
		r = x + ITEM_HEART_BBOX_WIDTH;
		b = y + ITEM_HEART_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_KNIFE) {
		r = x + KNIFE_BBOX_WIDTH;
		b = y + KNIFE_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_MONEY_1) {
		r = x + ITEM_MONEY_BBOX_WIDTH;
		b = y + ITEM_MONEY_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_MONEY_2) {
		r = x + ITEM_MONEY_BBOX_WIDTH;
		b = y + ITEM_MONEY_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_MONEY_3) {
		r = x + ITEM_MONEY_BBOX_WIDTH;
		b = y + ITEM_MONEY_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_WHIP) {
		r = x + ITEM_WHIP_BBOX_WIDTH;
		b = y + ITEM_WHIP_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_AXE) {
		r = x + ITEM_AXE_BBOX_WIDTH;
		b = y + ITEM_AXE_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_BOOMERANG) {
		r = x + ITEM_BOOMERANG_BBOX_WIDTH;
		b = y + ITEM_BOOMERANG_HEIGHT;
	}
	else if (type == gameType::ITEM_WATER_FIRE) {
		r = x + ITEM_WATERFIRE_BBOX_WIDTH;
		b = y + ITEM_WATERFIRE_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_HEART_MINI) {
		r = x + ITEM_HEART_MINI_BBOX_WIDTH;
		b = y + ITEM_HEART_MINI_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_INVISIBLE) {
		r = x + ITEM_INVISIBLE_BBOX_WIDTH;
		b = y + ITEM_INVISIBLE_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_DOUBLE_SHOT) {
		r = x + ITEM_DOUBLESHOT_BBOX_WIDTH;
		b = y + ITEM_DOUBLESHOT_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_TRIPLE_SHOT) {
		r = x + ITEM_TRIPLESHOT_BBOX_WIDTH;
		b = y + ITEM_TRIPLESHOT_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_STOP_WATCH) {
		r = x + ITEM_STOPWATCH_BBOX_WIDTH;
		b = y + ITEM_STOPWATCH_BBOX_HEIGHT;
	}
}

Item::~Item()
{

}