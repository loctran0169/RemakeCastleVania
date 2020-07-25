#pragma once
#include "Textures.h"
#include"Sprites.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include"define.h"
#include"Utils.h"
#include <iostream>
#pragma comment(lib, "winmm.lib")

class CSound
{
	static CSound* __instance;
	int row;
	unordered_map<int, LPCWSTR >sounds;
public:
	static CSound* GetInstance();
	int scene;
	CSound();
	void readSoundTxt(LPCWSTR filePath = NULL);
	void playFromBegin(gameType type);
	void playMulti(gameType type);
	~CSound();
};

