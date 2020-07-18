#include "ZoneMonkey.h"



void CZoneMonkey::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CZone::Update(dt);
	if (!isCollitionSimon)// xét có thể tạo
		isAllowToCreate = true;
}

void CZoneMonkey::Render()
{
	//RenderBoundingBox();
} 

void CZoneMonkey::GetBoundingBox(float & _left, float & _top, float & _right, float & _bottom)
{
	_left = x;
	_top = y;
	_right = right;
	_bottom = bottom;
}

void CZoneMonkey::createMonkey(vector<LPGAMEOBJECT>& listEnemy)
{
	if (isAllowToCreate && allowToCreate()) {
		CMonkey * monkey = new CMonkey();
		monkey->SetPosition(point->x, point->y);
		listEnemy.push_back(monkey);		
		isAllowToCreate = false;
	}
}

bool CZoneMonkey::allowToCreate()
{
	if (point->x - MONKEY_PADDING_CREATE_X < game->cam_x || point->x + MONKEY_BBOX_WIDTH + MONKEY_PADDING_CREATE_X > game->cam_x + SCREEN_WIDTH)
		return false;
	return true;
}

void CZoneMonkey::setPointPosition(float _x, float _y)
{
	point->setPosition(_x, _y);
}

CZoneMonkey::~CZoneMonkey()
{
}
