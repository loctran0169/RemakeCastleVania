#pragma once
#include"Zone.h"
#include"Simon.h"
#include"GhostFly.h"

#define ZONE_CREATE_GHOSTFLY_WIDTH	32
#define ZONE_CREATE_GHOSTFLY_HEIGHT	96

class CZoneGhostFly : public CGameObject
{
private:
	CGame *game;
	Simon * simon;
	CZone *zone; //khu vực ra khỏi thì reset lại xuất hiện (hi xa ra 7 ô)
	CZone *zoneCreate; // khu vực vào sẽ xuất hiện ma

	float px, yDefault; // phía và độ cáo xuất hiện
public:
	bool isAllowToCreate = true;
	CZoneGhostFly(int _l, int _t, int _r, int _b, int _xCreate, int _yCreate, int _px, int _y):CGameObject(){
		type = gameType::ZONE_GHOST_FLY;
		px = _px;
		yDefault = _y;
		simon = Simon::GetInstance();
		game = CGame::GetInstance();
		zoneCreate = new CZone(_xCreate, _yCreate, _xCreate + ZONE_CREATE_GHOSTFLY_WIDTH, _yCreate + ZONE_CREATE_GHOSTFLY_HEIGHT);
		zone = new CZone(_l, _t, _r, _b);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	LPGAMEOBJECT createGhostFly();
	~CZoneGhostFly();
};

