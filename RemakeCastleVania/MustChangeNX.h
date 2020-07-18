#pragma once
#include"HidenObject.h"

class CMustChangeNX : public CHidenObject
{

public:
	CMustChangeNX(float l, float t, float r, float b, int _nx) :CHidenObject(l, t, r, b) {
		type = gameType::CHANGE_NX;
		nx = _nx;
	}
	virtual void Render();
	int getNX() { return nx; }
	~CMustChangeNX();
};

