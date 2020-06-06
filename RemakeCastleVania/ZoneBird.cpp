#include "ZoneBird.h"




void CZoneBird::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CZone::Update(dt);
	if (!isCollitionSimon)// xét có th? t?o
		isAllowToCreate = true;
}

void CZoneBird::Render()
{
	//RenderBoundingBox();
}

void CZoneBird::GetBoundingBox(float & _left, float & _top, float & _right, float & _bottom)
{
	_left = x;
	_top = y;
	_right = right;
	_bottom = bottom;
}

void CZoneBird::createBird(vector<LPGAMEOBJECT>& listEnemy)
{
	if (isAllowToCreate && allowToCreate()) {
		CBird * bird = new CBird();
		bird->SetPosition(point->x, point->y);
		listEnemy.push_back(bird);
		isAllowToCreate = false;
	}
}

bool CZoneBird::allowToCreate()
{
	if (point->x - MONKEY_PADDING_CREATE_X < game->cam_x || point->x + BIRD_BBOX_WIDTH + MONKEY_PADDING_CREATE_X > game->cam_x + SCREEN_WIDTH)
		return false;
	return true;
}

void CZoneBird::setPointPosition(float _x, float _y)
{
	point->setPosition(_x, _y);
}

CZoneBird::~CZoneBird()
{
}
