#pragma once
#include "Textures.h"
#include"Sprites.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include"Game.h"
#include"Utils.h"
#include"define.h"


class CMap
{
	int colsMap, rowsMap;
	int tileMap[300][300];
	static CMap* __instance;
	LPDIRECT3DTEXTURE9 texturesMap;
public:
	static CMap* GetInstance();
	int scene;
	int boundingMapLeft;
	int boundingMapRight;
	void readMapTxt(LPCWSTR filePath);
	void setTexture(LPDIRECT3DTEXTURE9 i) { texturesMap = i; }
	CMap();
	void drawMap();
	~CMap();
};

