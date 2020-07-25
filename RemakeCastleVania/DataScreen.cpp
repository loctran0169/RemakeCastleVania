#include"DataScreen.h"

void DataScreen::Update()
{
	player = init(simon);
	if (GetTickCount() - lastTimeSub >= 1000) {
		maxTime--;
		lastTimeSub = GetTickCount();
	}
}
