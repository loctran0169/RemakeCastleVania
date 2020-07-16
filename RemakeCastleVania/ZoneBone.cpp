#include "ZoneBone.h"



void CZoneBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CZone::Update(dt);
	if (!isCollitionSimon)// xét có thể tạo
		isAllowToCreate = true;
}

void CZoneBone::Render()
{
	//RenderBoundingBox();
}

void CZoneBone::GetBoundingBox(float & _left, float & _top, float & _right, float & _bottom)
{
	_left = x;
	_top = y;
	_right = right;
	_bottom = bottom;
}

void CZoneBone::createBone(vector<LPGAMEOBJECT>& listEnemy)
{
	if (isAllowToCreate && allowToCreate()) {
		CBone * bone = new CBone();
		bone->SetPosition(point->x, point->y);
		listEnemy.push_back(bone);
		isAllowToCreate = false;
	}
}

bool CZoneBone::allowToCreate()
{
	if (point->x - BONE_PADDING_CREATE_X < game->cam_x || point->x + BONE_BBOX_WIDTH + BONE_PADDING_CREATE_X > game->cam_x + SCREEN_WIDTH)
		return false;
	return true;
}

void CZoneBone::setPointPosition(float _x, float _y)
{
	point->setPosition(_x, _y);
}

CZoneBone::~CZoneBone()
{
}
