#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"
#include "Map.h"

class Simon;
class CPlayScene : public CScene
{
protected:
	static CPlayScene* __instance;
	Simon *player;					// A play scene has to have player, right? 
	CGame *game;
	static vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_MAPTXT(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
public:
	CMap *map;
	int currentScence;
	static CPlayScene* GetInstance();
	Simon* getPlayer() { return player; }
	CPlayScene(int id = 0, LPCWSTR filePath = NULL);
	vector<LPGAMEOBJECT> getListObject() { return this->objects; }
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

