#pragma once
#include <vector>
#include "GameObject.h"
#include"Map.h"
#include"define.h"

#define GRID_CELL_WIDTH 256
class CCell
{
public:
	vector<LPGAMEOBJECT> objects;
	CCell(){}
};

typedef CCell * LPCELL;

class CGrid
{
public:
	CMap *map;
	vector<LPCELL> cells;
public:
	static CGrid * __instance;
	static CGrid * GetInstance();
	void deleteObject(int cellId, LPGAMEOBJECT object);
	void addObjectToCell(int idCell, LPGAMEOBJECT object);
	void setNumberCells();
	void getObjectFromGrid(vector<LPGAMEOBJECT>& listObj, vector<LPGAMEOBJECT>& listEnemy,int x, int y);
	CGrid(){
		map = CMap::GetInstance();
		cells = vector<LPCELL>();
	}
	void clearObjects();
	~CGrid() {}
};

