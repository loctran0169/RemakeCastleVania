#pragma once
#include <unordered_map>
#include <d3dx9.h>

class DataNextScreen
{
public:
	static DataNextScreen * __instance;
	int isOnStair;
	int x;
	int y;
	int nx;
	int ny;
public:
	static DataNextScreen * GetInstance();

	void setData(int _isOnStair, int _x, int _y, int _nx, int _ny) {
		isOnStair = _isOnStair;
		x = _x;
		y = _y;
		nx = _nx;
		ny = _ny;
	}
	DataNextScreen(){
		isOnStair = 0;
		x = 0;
		y = 0;
		nx = 0;
		ny = 0;
	}
	DataNextScreen(int _isOnStair, int _x, int _y, int _nx, int _ny) {
		isOnStair = _isOnStair;
		x = _x;
		y = _y;
		nx = _nx;
		ny = _ny;
	}
};

