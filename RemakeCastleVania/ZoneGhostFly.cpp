#include "ZoneGhostFly.h"



void CZoneGhostFly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	zone->Update(dt);
	zoneCreate->Update(dt);

	if (!zone->isCollitionSimon) // xét có thể tạo
		isAllowToCreate = true;
}

void CZoneGhostFly::Render()
{
	//zone->RenderBoundingBox();
	//zoneCreate->RenderBoundingBox();
}

void CZoneGhostFly::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = zoneCreate->x;
	top = zoneCreate->y;
	right = left + ZONE_CREATE_GHOSTFLY_WIDTH;
	bottom = top + ZONE_CREATE_GHOSTFLY_HEIGHT;
}

LPGAMEOBJECT CZoneGhostFly::createGhostFly()
{
	float camX, camY;
	game->GetCamPos(camX, camY);
	float _x, _y;
	if (px == -1)
		_x = camX + GHOSTFLY_PADDING_SREEN;
	else if (px == 1)
		_x = camX + SCREEN_WIDTH - GHOSTFLY_BBOX_WIDTH - GHOSTFLY_PADDING_SREEN;
	else
		_x = px;
	_y = yDefault;
	CGhostFly * ghost = new CGhostFly();
	ghost->SetPosition(_x, _y);
	isAllowToCreate = false;
	return ghost;
}

CZoneGhostFly::~CZoneGhostFly()
{
}
