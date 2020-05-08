#include "Map.h"
#include"Utils.h"

CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

void CMap::readMapTxt(LPCWSTR filePath) {

	ifstream inp(filePath, ios::in);
	inp >> rowsMap >> colsMap >> colsTileMap;
	boundingMapRight = colsMap * TILE_MAP_SIZE;
	for (int i = 0; i < rowsMap; i++)
		for (int j = 0; j < colsMap; j++) {
			inp >> tileMap[i][j];
		}
	inp.close();
}

void CMap::drawMap() {
	float xCam, yCam;
	CGame::GetInstance()->GetCamPos(xCam, yCam);
	int colStart = (int)xCam / TILE_MAP_SIZE;
	int colEnd = ((int)xCam + SCREEN_WIDTH) / TILE_MAP_SIZE < colsMap - 1 ? (xCam + SCREEN_WIDTH) / TILE_MAP_SIZE : colsMap - 1;

	for (int i = 0; i < rowsMap; i++)//nếu là game có chiều cao thay đổi
	{
		for (int j = colStart; j <= colEnd; j++)
		{
			int left = (tileMap[i][j] % colsTileMap) * TILE_MAP_SIZE;
			int top = (tileMap[i][j] / colsTileMap) * TILE_MAP_SIZE;
			int right = left + TILE_MAP_SIZE;
			int bottom = top + TILE_MAP_SIZE;
			CGame::GetInstance()->Draw(TILE_MAP_SIZE*j, TILE_MAP_SIZE*i + HEIGHTBOARD, texturesMap, left, top, right, bottom);
			if (right==boundingMapRight)
				DebugOut(L"[INFO] Bounding rightMap: %d \n", right);
		}
	}
}

CMap::CMap()
{
	boundingMapLeft = boundingMapRight = 0;
	scene = 1;
	colsMap = 1;
	rowsMap = 1;
	texturesMap = NULL;
}


CMap::~CMap()
{
}
