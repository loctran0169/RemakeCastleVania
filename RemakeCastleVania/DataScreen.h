#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include"Simon.h"
#include"Monter.h"


class DataScreen
{
	Simon*simon;		
public:
	CMonter *boss;
	Simon player;
	DWORD maxTime = 400;
	DWORD lastTimeSub;
	int parentMapID;
	int mapID;
	int score = 0;
	int stage = 0;
	bool isOnStair;
	int x;
	int y;
	int nx;
	int ny;
public:
	DataScreen(int _mapID){
		simon = Simon::GetInstance();
		player = Simon();
		lastTimeSub = GetTickCount();
		isOnStair = 0;
		mapID = _mapID;
		x = 0;
		y = 0;
		nx = 0;
		ny = 0;
	}
	DataScreen(int _isOnStair, int _x, int _y, int _nx, int _ny) {
		isOnStair = _isOnStair;
		x = _x;
		y = _y;
		nx = _nx;
		ny = _ny;
	}
	void Update();
	void setData(int _isOnStair, int _x, int _y, int _nx, int _ny) {
		isOnStair = _isOnStair;
		x = _x;
		y = _y;
		nx = _nx;
		ny = _ny;
	}
	void addScore(int _score) { score += _score; }
	void setStage(int _stage) { stage = _stage; }
	void setMaxTime(DWORD _time) { maxTime = _time; }
	void setMapID(int _id) { mapID = _id; }
	void setParentMapID(int a) { parentMapID = a; }
	void copyOf(DataScreen * dataX) {
		isOnStair = dataX->isOnStair;
		x = dataX->x;
		y = dataX->y;
		nx = dataX->nx;
		ny = dataX->ny;
	}
	void setBoss(CMonter *_boss) { boss = _boss; }
	Simon init(Simon * simon) {
		return *simon;
	}
};

