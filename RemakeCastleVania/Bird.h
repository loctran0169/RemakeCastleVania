#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"
#include"Simon.h"
#include"Line.h"
#include"Parabol.h"
#include"Parabol.h"
#include"Line.h"

#define BIRD_BBOX_WIDTH			32
#define BIRD_BBOX_HEIGHT		32

#define BRID_STATE_IDLE			0
#define BRID_STATE_FLY			1

#define BIRD_TIME_WAIT_ATTACK	400

#define	BIRD_STATE_IDLE			0
#define	BIRD_STATE_FLY_DY		1
#define	BIRD_STATE_FLY_PARABOL	2

#define BIRD_SPEED_X			0.08f
#define BIRD_SPEED_Y			0.12f
#define BIRD_SPEED_DY			0.18f

#define	BIRD_PADDING_ATTACK	15
class CBird : public CMonter // trym đen
{
	Simon*simon;
	CGame *game;
	CParabol * parabol;
	CLine * line;

	bool isIdle = true;
	bool isAutoGo = true;
	bool isFlying = false;

	DWORD timeBeAttack = 0;
	DWORD timeChangeState = 0;
	DWORD timeBeginState = 0;
public:
	CBird() :CMonter() {
		type = gameType::BIRD;
		simon = Simon::GetInstance();
		game = CGame::GetInstance();
		deteleBeforeLoadFromGrid = false;
		SetState(BIRD_STATE_IDLE);

		timeChangeState = GetTickCount();
		CAnimationSets * animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(gameType::BIRD);
		SetAnimationSet(ani_set);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void setFlyParabol();
	void setAutoNx();
	void SetState(int state);
	void beAttack();
	~CBird();
};
