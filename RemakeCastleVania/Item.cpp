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

void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	if (	GetTickCount() - timeExit > ITEM_TIME_EXIT) {
		isPicked = true;
	}
	CGameObject::Update(dt);

	vy += ITEM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx, rdy;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// block 
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0) vy = 0;
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
		r = x + HEART_BBOX_WIDTH;
		b = y + HEART_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_KNIFE) {
		r = x + KNIFE_BBOX_WIDTH;
		b = y + KNIFE_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_MONEY) {
		r = x + MONEY_BBOX_WIDTH;
		b = y + MONEY_BBOX_HEIGHT;
	}
	else if (type == gameType::ITEM_WHIP) {
		r = x + WHIPITEM_BBOX_WIDTH;
		b = y + WHIPITEM_BBOX_HEIGHT;
	}
}

Item::~Item()
{

}