#pragma once
#include"Game.h"
class CBoard
{
	static CBoard* _instance;
public:
	static CBoard* GetInstance();
	CBoard();
	void Render();
	~CBoard();
};

