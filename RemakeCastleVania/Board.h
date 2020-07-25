#pragma once
#include"GameObject.h"
#include"define.h"
#include"Utils.h"
#include"Simon.h"
#include"DataScreenManager.h"

#define GAME_FONT L"textures\\fonts\\prstart.ttf"

#define PADDING_FONT		15
#define PADDING_HP			8

#define SPRITE_BIG_BOARD	10
#define SPRITE_HP_BOSS		11
#define SPRITE_HP_SIMON		12
#define SPRITE_HP_EMPTY		13

class CBoard :public CGameObject
{
private:
	static CBoard* _instance;
	CGame *game;
	DataScreenManager *data;
	Simon* simon;
	CSprites *sprites;
	CTextures *textures;
public:
	static CBoard* GetInstance();
	CBoard();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void DrawNumber(int max, float x, float y, int number);
	void DrawHP	(float x, float y, bool isSimon, int hp);
	~CBoard();
};

