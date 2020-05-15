#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include"HidenObject.h"
#include "Brick.h"
#include"Item.h"
#include "Simon.h"
#include "Map.h"
#include"Whip.h"
#include"Knife.h"
#include"Boomerang.h"
#include"Axe.h"
#include"WaterFire.h"

class Simon;
class CPlayScene : public CScene
{
protected:
	Simon *player;					// A play scene has to have player, right? 
	CGame *game;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> listHidenObjects;
	vector<Item*> listItems;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_MAPTXT(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
public:
	CMap *map;
	int currentScence;
	int nextScence;
	Simon* getPlayer() { return player; }
	CPlayScene(int id = 0, LPCWSTR filePath = NULL);

	//collision
	void checkCollisonWeapon(vector<LPGAMEOBJECT> *coObjects);
	void checkCollisonWithItem();
	void checkCollisonWithHideObj();
	void checkCollisonWithEnemy(vector<LPGAMEOBJECT> *coObjects);

	Item * getNewItem(int id, float x, float y);
	virtual void Load();
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

