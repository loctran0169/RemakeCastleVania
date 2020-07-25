#include "Scence.h"

CScene::CScene(int id, int _stageMap,int _maxTime, LPCWSTR filePath)
{
	this->id = id;
	this->stageMap = _stageMap;
	this->maxTime = _maxTime;
	this->sceneFilePath = filePath;
}