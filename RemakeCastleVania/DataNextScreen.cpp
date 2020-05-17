#include"DataNextScreen.h"

DataNextScreen * DataNextScreen::__instance = NULL;

DataNextScreen * DataNextScreen::GetInstance()
{
	if (__instance == NULL) __instance = new DataNextScreen();
	return __instance;
}
