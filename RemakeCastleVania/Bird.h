#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define BRID_BBOX_WIDTH			32
#define BIRD_BBOX_HEIGHT		32

class CBird : public CMonter // trym đen
{

public:
	CBird() :CMonter() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CBird();
};
