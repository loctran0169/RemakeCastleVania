#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
class Whip : public CGameObject
{
public:
	int level = 1;
	Whip() :CGameObject() {

	}
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	//virtual void Render();
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Whip();
};

