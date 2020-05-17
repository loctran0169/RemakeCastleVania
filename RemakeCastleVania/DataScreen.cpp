#include"DataScreen.h"

DataScreen * DataScreen::__instance = NULL;

DataScreen * DataScreen::GetInstance()
{
	if (__instance == NULL) __instance = new DataScreen();
	return __instance;
}
