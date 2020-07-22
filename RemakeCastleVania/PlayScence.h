#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include"HidenObject.h"
#include "Brick.h"
#include"BrickBlack.h"
#include"Item.h"
#include "Simon.h"
#include "Map.h"
#include"Whip.h"
#include"Knife.h"
#include"StopWatch.h"
#include"Boomerang.h"
#include"Axe.h"
#include"WaterFire.h"
#include"SkateBoard.h"
#include"DataNextScreen.h"
#include"DataScreen.h"
#include"Grid.h"
#include"Candle.h"
#include"EffectBrickBlack.h"
#include"Warrior.h"
#include"BlackBat.h"
#include"ZoneGhostFly.h"
#include"ZoneGhostWalk.h"
#include"BossBat.h"
#include"ZoneMonkey.h"
#include"ZoneBird.h"
#include"ZoneBone.h"

class Simon;
class CPlayScene : public CScene
{
protected:			

	static Simon* player; // A play scene has to have player, right? 
	CGame *game;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> listEffect;
	vector<LPGAMEOBJECT> listEnemy;// load từ grid ra
	vector<LPGAMEOBJECT> listEnemyWeapon;// danh sách vũ khí xuất hiện quái vật
	vector<Item*> listItems;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_MAPTXT(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
public:
	CMap *map;
	CGrid *grid;
	int currentScence;
	DataNextScreen *dataNextScreen;
	DataScreen *dataScreen;
	int nextScence;
	bool nextIsStair;
	bool isDisableCamera = false;
	Simon* getPlayer() { return player; }
	CPlayScene(int id = 0, LPCWSTR filePath = NULL);

	//collision
	void checkCollisonWeapon(vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> *coEnemys);
	void checkCollisonWithItem();
	void checkCollisonSimonWithEnemy(); // kiểm tra va chạm simon với quái
	void checkCollisonWithHideObj();
	void checkCollisonWithEnemy(vector<LPGAMEOBJECT> *coObjects);

	Item * getNewItem(int id, float x, float y);
	virtual void Load(bool isNextScreen = false);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

