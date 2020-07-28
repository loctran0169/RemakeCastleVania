#include "Scence.h"

CScene::CScene(int id, int _stageMap, int _parentMapId, int _soundId, int _maxTime, LPCWSTR filePath)
{
	this->id = id;
	this->stageMap = _stageMap;
	this->maxTime = _maxTime;
	this->parentMapId = _parentMapId;
	this->soundId = _soundId;
	this->sceneFilePath = filePath;
}