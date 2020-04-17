#pragma once

#include "HidenObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CHidenObject
{
	int scene_id;	// target scene to switch to 
public:
	CPortal(float l, float t, float r, float b, int scene_id) :CHidenObject(l, t, r, b) {
		this->scene_id = scene_id;
		type = gameType::PORTAL;
	}
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneId() { return scene_id; }
	~CPortal();
};