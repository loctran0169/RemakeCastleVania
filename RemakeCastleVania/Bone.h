#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define BONE_BBOX_WIDTH			32
#define BONE_BBOX_HEIGHT		64

class CBone : public CMonter // quái xương
{

public:
	CBone() :CMonter() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void beAttack();
	~CBone();
};
