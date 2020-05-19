#pragma once
#include "HidenObject.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

class CBrick : public CHidenObject
{
public:
	CBrick();
	CBrick(float l, float t, float r, float b) :CHidenObject(l, t, r, b) {
		type = gameType::BRICK;
	}
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};