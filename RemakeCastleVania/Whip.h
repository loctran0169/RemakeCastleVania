#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Torch.h"
#include"Utils.h"

class Whip : public CGameObject
{
public:
	int level;	//level whip
	float xr, yr;	//vị trí render
	Whip() :CGameObject() {
		level = 3;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void setPosRender(float _xr, float _yr) { xr = _xr; yr = _yr; }
	~Whip();
};

