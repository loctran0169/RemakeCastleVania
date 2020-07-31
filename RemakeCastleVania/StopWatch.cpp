#include "StopWatch.h"




void CStopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount() - timeAttact >= STOPWATCH_TIME) {
		SetAttack(false);
		CSound::GetInstance()->stop(STOP_WATCH);
	}
}

void CStopWatch::Render()
{

}

void CStopWatch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}

void CStopWatch::setPosition(float _x, float _y, int _nx)
{
	timeAttact = GetTickCount();
}

CStopWatch::~CStopWatch()
{
}
