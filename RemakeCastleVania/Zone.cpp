#include "Zone.h"


void CZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	isCollitionSimon = false;
	if (isCollitionObjectWithObject(simon)) {
		isCollitionSimon = true;
		float l, t, r, b;
		simon->GetBoundingBox(l,t,r,b);
		if ((l + r) / 2 > (x + right) / 2)
			isRight = false;
		else
			isRight = true;
	}
}

void CZone::Render()
{
}

void CZone::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = right;
	b = bottom;
}

CZone::~CZone()
{
}
