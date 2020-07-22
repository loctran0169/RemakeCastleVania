#pragma once
#include "Zone.h"
#include"Monter.h"
#include"Simon.h"

#define WARRIOR_BBOX_WIDTH			32
#define WARRIOR_BBOX_HEIGHT			64

#define WARRIOR_SPEED_X				0.055f

#define WARRIOR_TIME_WAIT_ATTACK	380
class CWarrior : public CMonter // chiến binh thép
{
private:
	CZone *zone;
	Simon *simon;
	bool isIdle = false; //đang đứng im hay ko
	DWORD timeBeAttack = 0; // thời gian cuối bị đánh
	int boundRight, boundLeft; // vùng di chuyển
public:
	CWarrior(int _zl, int _zt, int _zr, int _zb) :CMonter() {
		type = gameType::WARRIOR;
		health = 3; // máu
		zone =  new CZone(_zl, _zt, _zr, _zb);
		simon = Simon::GetInstance();
		nx = -1;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void setZoneWalk(int _right, int _left) { boundLeft = _left; boundRight = _right; }
	void beAttack();
	~CWarrior();
};

