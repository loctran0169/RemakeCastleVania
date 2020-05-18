#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define BLACKBAT_BBOX_WIDTH			32
#define BLACKBAT_BBOX_HEIGHT		32

class CBlackBat : public CMonter // đơi đen
{

public:
	CBlackBat() :CMonter() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CBlackBat();
};
