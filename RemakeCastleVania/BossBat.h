#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define BOSSBAT_1_BBOX_WIDTH			32
#define BOSSBAT_1_BBOX_HEIGHT			32

#define BOSSBAT_2_BBOX_WIDTH			100
#define BOSSBAT_2_BBOX_HEIGHT			48

#define BOSSBAT_3_BBOX_WIDTH			64
#define BOSSBAT_3_BBOX_HEIGHT			48

#define BOSSBAT_4_BBOX_WIDTH			22
#define BOSSBAT_4_BBOX_HEIGHT			30

class CBossBat : public CMonter // quái xương
{

public:
	CBossBat() :CMonter() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void beAttack();
	~CBossBat();
};
