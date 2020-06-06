#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"
#include"Simon.h"
#include"Brick.h"
#include"BrickBlack.h"
#include"HidenObject.h"


#define MONKEY_BBOX_WIDTH		32
#define MONKEY_BBOX_HEIGHT		32

#define	MONKEY_STATE_IDLE		0
#define	MONKEY_STATE_WALK		1
#define	MONKEY_STATE_JUMP		2

#define MONKEY_JUMP_SPEED_X		0.14f
#define MONKEY_JUMP_SPEED_Y		0.45f

#define MONKEY_WALK_SPEED_X		0.4f
#define MONKEY_WALK_SPEED_Y		0.12f

#define MONKEY_GRAVITY_SPEED	0.0012f

#define MONKEY_TIME_WAIT_ATTACK	380
class CMonkey : public CMonter // quái xương
{
	Simon * simon;
	CGame *game;
	DWORD timeChangeState; // thời gian chuyển trạng thái
	DWORD timeBeAttack;
	bool isIdle = true;
	bool isJump = false;
	bool isDisableJump = false;
	int numOfSate = 0; // số lần thực hiện trạng thái
	DWORD timeBeginState = 0;
public:
	CMonkey() :CMonter() {
		type = gameType::MONKEY;
		simon = Simon::GetInstance();
		game = CGame::GetInstance();
		timeChangeState = GetTickCount();
		SetState(MONKEY_STATE_IDLE);
		deteleBeforeLoadFromGrid = false;

		CAnimationSets * animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(gameType::MONKEY);
		SetAnimationSet(ani_set);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void checkCollisonWithHidenObjects(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void SetState(int state);
	void beAttack();
	~CMonkey();
};
