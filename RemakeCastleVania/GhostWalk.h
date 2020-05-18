#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define GHOSTWALK_BBOX_WIDTH		32
#define GHOSTWALK_BBOX_HEIGHT		32

class CGhostWalk : public CMonter // quái xương
{

public:
	CGhostWalk() :CMonter() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CGhostWalk();
};
