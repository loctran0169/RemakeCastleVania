#pragma once
#include"Monter.h"
#include"Zone.h"
#include"Line.h"
#include"Simon.h"

#define GHOSTFLY_BBOX_WIDTH			32
#define GHOSTFLY_BBOX_HEIGHT		32

#define GHOSTFLY_SPEED				0.12f


#define ZONE_CREATE_GHOSTFLY_WIDTH	32
#define ZONE_CREATE_GHOSTFLY_HEIGHT	96

#define GHOSTFLY_TIME_WAIT_ATTACK   350

#define GHOSTFLY_PADDING_SREEN		15
#define GHOSTFLY_PADDING_ATTACK		15


class CGhostFly : public CMonter // quái xương
{
private:
	CGame *game;
	CLine *line; //phương trình đường thẳng để di chuyển con quái bay này
	Simon *simon;

	int health = 3; // máu
	bool isIdle = false; //đang đứng im hay ko
	DWORD timeBeAttack = 0; // thời gian cuối bị đánh
	DWORD timeBackUpAddressSimon = 0;
public:
	CGhostFly() :CMonter() {
		game = CGame::GetInstance();
		type = gameType::GHOST_FLY;
		simon = Simon::GetInstance();
		deteleFromGrid = false;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetPosition(float _x, float _y);
	void beAttack();
	~CGhostFly();
};
