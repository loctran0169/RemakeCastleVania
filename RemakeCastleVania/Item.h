#pragma once
#include"GameObject.h"
#include"define.h"
#include"Sprites.h"
class Item : public CGameObject
{
public:
	int typeItem;
	bool isPicked = false;
	Item(int _type) : CGameObject() {
		typeItem = _type;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~Item();
};

