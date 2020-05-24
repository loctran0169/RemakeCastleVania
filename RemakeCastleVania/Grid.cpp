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
			DebugOut(L"Đã xóa obj id = %d \n",object->getType());
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

void CGrid::getObjectFromGrid(vector<LPGAMEOBJECT>& listObj, vector<LPGAMEOBJECT>& listEnemy,int x, int y)
{
	listObj.clear();
	for (int i = 0; i < listEnemy.size(); i++) {
		if (listEnemy[i]->deteleBeforeLoadFromGrid)
			listEnemy.erase(listEnemy.begin() + i);
	}
	int colStart = (int)x / GRID_CELL_WIDTH;
	int colEnd = ceil((x + SCREEN_WIDTH) / GRID_CELL_WIDTH);
	if (colEnd >= map->boundingMapRight / GRID_CELL_WIDTH)
		colEnd = map->boundingMapRight / GRID_CELL_WIDTH-1;
	for (int i = colStart; i <= colEnd; i++) {
		CCell * cell = cells[i];
		for (int j = 0; j < cell->objects.size(); j++) {
			gameType type = cell->objects[j]->getType();
			if (type == gameType::WARRIOR || type == gameType::BAT ||
				type == gameType::MONKEY || type == gameType::BONE ||
				type == gameType::GHOST_WALK || type == gameType::BIRD || type == gameType::BOSS_BAT) {
				if (std::find(listEnemy.begin(), listEnemy.end(), cell->objects[j]) == listEnemy.end())
					listEnemy.push_back(cell->objects[j]);
			}
			else
				listObj.push_back(cell->objects[j]);
		}
	}
}

void CGrid::clearObjects()
{
	for (int i = 0; i < cells.size(); i++)
		cells.at(i)->objects.clear();
	cells.clear();
}
