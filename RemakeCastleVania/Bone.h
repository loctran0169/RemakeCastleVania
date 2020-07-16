#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"
#include"Simon.h"

#define BONE_BBOX_WIDTH			32
#define BONE_BBOX_HEIGHT		64

#define BONE_MIN_LEFT_TO_SIMON	128
#define BONE_MIN_RIGHT_TO_SIMON	96

#define	BONE_STATE_IDLE			0
#define	BONE_STATE_WALK			1
#define	BONE_STATE_JUMP			2

#define BONE_JUMP_SPEED_X		0.12f
#define BONE_JUMP_SPEED_Y		0.2f

#define BONE_WALK_SPEED_X		0.13f
#define BONE_WALK_SPEED_Y		0.2f

#define BONE_GRAVITY_SPEED		0.0005f

#define BONE_TIME_WAIT_ATTACK	380
#define BONE_TIME_WAIT_IDLE		1000

class CBone : public CMonter // quái xương
{
	Simon * simon;
	CGame *game;
	
	int nxWalk = 0;
	bool isWalkAutoX = false; // tự động đi theo x
	float autoGoX_Distance = 0;

	bool isJump = false; //đang nhảy
	bool isOnCheckJump = false; // có đang đứng tại vị trí tự nhảy hay ko

	DWORD timeBeginState = 0;
	DWORD timeWaitState = 0;
public:
	CBone() :CMonter() {
		type = gameType::BONE;
		simon = Simon::GetInstance();
		game = CGame::GetInstance();
		SetState(BONE_STATE_WALK);
		timeBeginState = GetTickCount();

		deteleBeforeLoadFromGrid = false;

		CAnimationSets * animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(gameType::BONE);
		SetAnimationSet(ani_set);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);

	void checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void checkCollisonWithHidenObjects(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void beAttack();

	void SetPosition(float x, float y);
	void setAutoNx();
	float float_randomX(float min, float max);
	float randomPositionX();
	~CBone();
};
