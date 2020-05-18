#include "Grid.h"

CGrid * CGrid::__instance = NULL;

CGrid * CGrid::GetInstance()
{
	if (__instance == NULL) __instance = new CGrid();
	return __instance;
}

void CGrid::deleteObject(int cellId, LPGAMEOBJECT object)
{
	for (int i = 0; i < cells[cellId]->objects.size(); i++) {
		if (cells[cellId]->objects[i]== object) {
			cells[cellId]->objects.erase(cells[cellId]->objects.begin()+i);
		}
	}
}

void CGrid::addObjectToCell(int idCell, LPGAMEOBJECT object)
{
	cells[idCell]->objects.push_back(object);
}

void CGrid::setNumberCells()
{
	for (int i = 0; i < map->boundingMapRight/GRID_CELL_WIDTH; i++) {
		CCell * cell = new CCell();
		cells.push_back(cell);
	}
}

void CGrid::getObjectFromGrid(vector<LPGAMEOBJECT>& list,int x, int y)
{
	list.clear();
	int colStart = (int)x / GRID_CELL_WIDTH;
	int colEnd = ceil((x + SCREEN_WIDTH) / GRID_CELL_WIDTH);
	if (colEnd >= map->boundingMapRight / GRID_CELL_WIDTH)
		colEnd = map->boundingMapRight / GRID_CELL_WIDTH-1;
	for (int i = colStart; i <= colEnd; i++) {
		list.insert(list.end(),cells[i]->objects.begin(),cells[i]->objects.end());
	}
}

void CGrid::clearObjects()
{
	for (int i = 0; i < cells.size(); i++)
		cells.at(i)->objects.clear();
	cells.clear();
}
