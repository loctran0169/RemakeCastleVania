#include "Zone.h"

void CZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	if (this->isCollitionObjectWithObject(simon)) {
		isCollitionSimon = true;
		float l, t, r, b;
		simon->GetBoundingBox(l,t,r,b);
		if ((l + r) / 2 > (x + right) / 2)
			isRight = true;
		else
			isRight = false;
	}
	else
		isCollitionSimon = false;
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
