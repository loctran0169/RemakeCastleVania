#include"DataScreenManager.h"

DataScreenManager * DataScreenManager::_instance = NULL;

DataScreenManager * DataScreenManager::GetInstance()
{
	if (_instance == NULL) _instance = new DataScreenManager();
	return _instance;
}
