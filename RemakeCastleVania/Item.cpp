#include "Item.h"


void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);

	vy += ITEM_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (y + WHIPITEM_BBOX_HEIGHT >= 9 * TILE_MAP_SIZE + HEIGHTBOARD) {
		if (vy > 0) {
			vy = 0;
			y = 8 * TILE_MAP_SIZE + HEIGHTBOARD;
		}
	}
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
		animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}
void Item::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	if (typeItem == ItemType::HEART) {
		r = x + HEART_BBOX_WIDTH;
		b = y + HEART_BBOX_HEIGHT;
	}
	else if (typeItem == ItemType::KNIFE) {
		r = x + KNIFE_BBOX_WIDTH;
		b = y + KNIFE_BBOX_HEIGHT;
	}
	else if (typeItem == ItemType::MONEY) {
		r = x + MONEY_BBOX_WIDTH;
		b = y + MONEY_BBOX_HEIGHT;
	}
	else if (typeItem == ItemType::WHIP) {
		r = x + WHIPITEM_BBOX_WIDTH;
		b = y + WHIPITEM_BBOX_HEIGHT;
	}
}
Item::~Item()
{

}