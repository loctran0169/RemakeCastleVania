#pragma once
#include "GameObject.h"

class CHidenObject : public CGameObject
{
protected:
	int width;
	int height;
public:
	CHidenObject(float l, float t, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CHidenObject();
};