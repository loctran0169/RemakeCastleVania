#include "HidenObject.h"

CHidenObject::CHidenObject(float l, float t, float r, float b)
{
	x = l;
	y = t;
	width = r - l;
	height = b - t;
	type = gameType::CHECK_AUTO_GO;
}

void CHidenObject::Render()
{
	//RenderBoundingBox();
}

void CHidenObject::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

CHidenObject::~CHidenObject()
{
}
