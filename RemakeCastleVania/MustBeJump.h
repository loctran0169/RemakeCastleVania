#pragma once
#include"HidenObject.h"

class CMustBeJump : public CHidenObject
{
	
public:
	CMustBeJump(float l, float t, float r, float b, int _nx) :CHidenObject(l, t, r, b) {
		type = gameType::BE_JUMP;
		nx = _nx;
	}
	int getNX() { return nx; }
	~CMustBeJump();
};

