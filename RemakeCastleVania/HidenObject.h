#pragma once
#include "GameObject.h"
#include"Utils.h"

class CHidenObject : public CGameObject
{
protected:
	int width;
	int height;
public:
	float x_cam;
	bool isDeleteEnemy = false;
	CHidenObject();
	CHidenObject(float l, float t, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int getWidht() { return width; }
	int getHeight() { return height; }
	~CHidenObject();
};