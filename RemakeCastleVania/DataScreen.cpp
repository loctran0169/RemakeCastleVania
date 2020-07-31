#include"DataScreen.h"

#define MILI_TO_SECOND	1000
void DataScreen::Update()
{
	player = init(simon);
	if (GetTickCount() - lastTimeSub >= MILI_TO_SECOND && player.numLife>=0) {
		maxTime--;
		lastTimeSub = GetTickCount();
		if (maxTime <= 20)
			CSound::GetInstance()->play(gameType::TIMEOUT, NULL, 1);
	}
}

void DataScreen::reset()
{	
	maxTime = 0;
	lastTimeSub = GetTickCount();
	parentMapID = game->getFirstScreen();
	mapID = game->getFirstScreen();
	score = 0;
	stage = 0;
	isOnStair = false;
	//x;
	//y;
	//nx;
	//ny;
}

void DataScreen::setData(int _isOnStair, int _x, int _y, int _nx, int _ny)
{
	isOnStair = _isOnStair;
	x = _x;
	y = _y;
	nx = _nx;
	ny = _ny;
}

void DataScreen::copyOf(DataScreen * dataX)
{
	isOnStair = dataX->isOnStair;
	x = dataX->x;
	y = dataX->y;
	nx = dataX->nx;
	ny = dataX->ny;
}
