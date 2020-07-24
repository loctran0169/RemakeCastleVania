#pragma once

#include "HidenObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CHidenObject
{
public:
	int scene_id;	// target scene to switch to

	bool isOnStair;
	int px;
	int py;
	int pnx;
	int pny;
public:
	bool isStair = false;
	CPortal(float l, float t, float r, float b, int scene_id) :CHidenObject(l, t, r, b) {
		this->scene_id = scene_id;
		type = gameType::PORTAL;
	}
	virtual void Render();
	int GetSceneId() { return scene_id; }
	void setData(int _isOnStair, int _x, int _y, int _nx, int _ny) {
		isOnStair = _isOnStair;
		px = _x;
		py = _y;
		pnx = _nx;
		pny = _ny;
	}

	~CPortal();
};