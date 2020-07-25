#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include"DataScreen.h"

class DataScreenManager
{
public:
	int mapID;
	static DataScreenManager * _instance;
	DataScreen *defaultScreen;
	DataScreen *currentScreenDefault;
	DataScreen *currentScreen;
public:
	DataScreenManager(int _map = 1) {
		defaultScreen = new DataScreen(_map);
		currentScreen = new DataScreen(_map);
		currentScreenDefault = new DataScreen(_map);
		_instance = this;
	}
	static DataScreenManager * GetInstance();
	void Update() {
		currentScreen->Update();
	}
	void nextScreen() {
		DataScreen temp = *currentScreen;
		*defaultScreen = temp;
	}
	void resetScreen() {
		DataScreen temp = *defaultScreen;
		*currentScreen = temp;
	}
	void saveStartScreen() {
		DataScreen temp = *currentScreen;
		*currentScreenDefault = temp;
	}
	void loadStartScreen() {
		DataScreen temp = *currentScreenDefault;
		*currentScreen = temp;
	}
};

