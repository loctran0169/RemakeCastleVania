#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Utils.h"

class CMonter : public CGameObject
{	
public:
	int health;
	CMonter() :CGameObject() {
		
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void beAttack();
	int getHealth() { return health; }
	void setHealth(int num) { this->health = num; }
	~CMonter();
};

