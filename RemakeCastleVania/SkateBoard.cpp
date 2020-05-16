#include "SkateBoard.h"




void CSkateBoard::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (x <= boundingLeft)
		nx = 1;
	else if (x + SKATEBOARD_BBOX_WIDTH >= boundingRight)
		nx = -1;
	CGameObject::Update(dt);
	x += dx * nx;
}

void CSkateBoard::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CSkateBoard::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + SKATEBOARD_BBOX_WIDTH;
	b = y + SKATEBOARD_BBOX_HEIGHT;
}

CSkateBoard::~CSkateBoard()
{
}
