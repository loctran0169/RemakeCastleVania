#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define GHOSTFLY_BBOX_WIDTH			32
#define GHOSTFLY_BBOX_HEIGHT		32

class CGhostFly : public CMonter // quái xương
{

public:
	CGhostFly() :CMonter() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CGhostFly();
};
