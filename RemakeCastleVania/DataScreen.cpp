#include"DataScreen.h"

void DataScreen::Update()
{
	player = *simon;
	if (GetTickCount() - lastTimeSub >= 1000) {
		maxTime--;
		lastTimeSub = GetTickCount();
	}
}
