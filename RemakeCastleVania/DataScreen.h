#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include"Simon.h"

class DataScreen
{
	Simon*simon;
	Simon player;
public:
	int mapID;
	DWORD maxTime = 400;
	DWORD lastTimeSub;
	int score = 0;
	int stage;
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
	void copyOf(DataScreen * dataX) {
		isOnStair = dataX->isOnStair;
		x = dataX->x;
		y = dataX->y;
		nx = dataX->nx;
		ny = dataX->ny;
	}
};

