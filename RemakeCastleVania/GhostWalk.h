#pragma once
#include"Monter.h"
#include"define.h"
#include"Utils.h"

#define GHOSTWALK_BBOX_WIDTH		32
#define GHOSTWALK_BBOX_HEIGHT		64

#define GHOSTWALK_SPEED_X			0.18f
#define GHOSTWALK_SPEED_GRAVITY			0.06f

#define GHOSTWALK_BETWEEN_DIE_TIME	1500
#define GHOSTWALK_PADDING_X			10
class CGhostWalk : public CMonter // quái xương
{
public:
	int id;
	CGame *game;
public:
	CGhostWalk(int _id, int _nx, int _x, int _y) :CMonter() {
		type = gameType::GHOST_WALK;
		health = 1;
		id = _id;
		nx = _nx;
		x = _x;
		y = _y;
		game = CGame::GetInstance();
		deteleBeforeLoadFromGrid = false;

		CAnimationSets * animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(gameType::GHOST_WALK);
		SetAnimationSet(ani_set);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void checkCollisonWithBricks(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void beAttack();
	~CGhostWalk();
};
