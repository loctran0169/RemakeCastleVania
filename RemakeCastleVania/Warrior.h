#pragma once
#include "Zone.h"
#include"Monter.h"


#define WARRIOR_BBOX_WIDTH			32
#define WARRIOR_BBOX_HEIGHT			64

#define WARRIOR_SPEED_X				0.055f
class CWarrior : public CMonter // chiến binh thép
{
private:
	int boundRight, boundLeft;
	CZone *zone;
public:
	CWarrior(int _zl, int _zt, int _zr, int _zb) :CMonter() {
		type = gameType::WARRIOR;
		zone =  new CZone(_zl, _zt, _zr, _zb);
		nx = -1;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void setZoneWalk(int _right, int _left) { boundLeft = _left; boundRight = _right; }
	~CWarrior();
};

