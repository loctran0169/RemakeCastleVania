#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include"DataNextScreen.h"

class DataScreen
{
public:
	static DataScreen * __instance;
	int isOnStair;
	int x;
	int y;
	int nx;
	int ny;
public:
	static DataScreen * GetInstance();

	void setData(int _isOnStair, int _x, int _y, int _nx, int _ny) {
		isOnStair = _isOnStair;
		x = _x;
		y = _y;
		nx = _nx;
		ny = _ny;
	}
	DataScreen() {
		isOnStair = 0;
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
	void copyOf(DataNextScreen * dataX) {
		isOnStair = dataX->isOnStair;
		x = dataX->x;
		y = dataX->y;
		nx = dataX->nx;
		ny = dataX->ny;
	}
};

