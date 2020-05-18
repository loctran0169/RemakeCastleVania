#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define MONKEY_BBOX_WIDTH		32
#define MONKEY_BBOX_HEIGHT		32

class CMonkey : public CMonter // quái xương
{

public:
	CMonkey() :CMonter() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CMonkey();
};
