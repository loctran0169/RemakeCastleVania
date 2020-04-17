#pragma once
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
class CTorch :public CGameObject
{
public:
	bool isFinish = false;
	
	CTorch() :CGameObject() {
		CGameObject::type = gameType::TORCH;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	
	~CTorch();
};

