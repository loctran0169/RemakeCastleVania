#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"
#include"Simon.h"

#define MONKEY_BBOX_WIDTH		32
#define MONKEY_BBOX_HEIGHT		32

#define	MONKEY_STATE_IDLE		0
#define	MONKEY_STATE_WALK		1
#define	MONKEY_STATE_JUMP		2

#define MONKEY_JUMP_SPEED_X		0.2f
#define MONKEY_JUMP_SPEED_Y		0.5f

#define MONKEY_WALK_SPEED_X		1.0f
#define MONKEY_WALK_SPEED_Y		1.0f

#define MONKEY_GRAVITY_SPEED	0.0012f
class CMonkey : public CMonter // quái xương
{
	Simon * simon;
	CGame *game;
	DWORD timeChangeState;
	bool isIdle = true;
	bool isJump = false;
	int numOfSate = 0; // số lần thực hiện trạng thái
public:
	CMonkey() :CMonter() {
		type = gameType::MONKEY;
		simon = Simon::GetInstance();
		game->GetInstance();
		timeChangeState = GetTickCount();
		SetState(MONKEY_STATE_IDLE);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void SetState(int state);
	~CMonkey();
};
