#include"DataScreen.h"

#define MILI_TO_SECOND	1000
void DataScreen::Update()
{
	player = init(simon);
	if (GetTickCount() - lastTimeSub >= MILI_TO_SECOND) {
		maxTime--;
		lastTimeSub = GetTickCount();
		if (maxTime <= 20)
			CSound::GetInstance()->play(gameType::TIMEOUT, NULL, 1);
	}
}
