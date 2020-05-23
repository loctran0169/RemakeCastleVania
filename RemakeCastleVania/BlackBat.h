#pragma once
#include "Zone.h"
#include"Monter.h"
#include"Game.h"

#define BLACKBAT_BBOX_WIDTH			32
#define BLACKBAT_BBOX_HEIGHT		32

#define BLACKBAT_DISTANCE_X			64.0f
#define BLACKBAT_DISTANCE_Y			64.0f

#define BLACKBAT_SPEED_X			0.2f // thẳng
#define BLACKBAT_SPEED_Y			0.2f

#define BLACKBAT_SPEED_X_OVA		0.13f // chéo
#define BLACKBAT_SPEED_Y_OVA		0.13f

#define BLACKBAT_ANI_IDLE			0
#define BLACKBAT_ANI_FLY			1

class CBlackBat : public CMonter // đơi đen
{
private:
	CZone *zone; 
	CGame *game;
	float autoGoX_Distance=0.0f, autoGoY_Distance=0.0f;
	bool isAutoGo = false;
public:
	CBlackBat(int _zl, int _zt, int _zr, int _zb) :CMonter() {
		type = gameType::BAT;
		zone = new CZone(_zl, _zt, _zr, _zb);
		game = CGame::GetInstance();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void startFly(int _nx);
	~CBlackBat();
};
