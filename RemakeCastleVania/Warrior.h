#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define WARRIOR_BBOX_WIDTH			32
#define WARRIOR_BBOX_HEIGHT			64

class CWarrior : public CMonter // chiến binh thép
{

public:
	CWarrior() :CMonter() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CWarrior();
};

