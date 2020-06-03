#pragma once
#include"Zone.h"
#include"Simon.h"
#include"GhostWalk.h"
#include"Point.h"

#define ZONE_CREATE_GHOSTFLY_WIDTH	32
#define ZONE_CREATE_GHOSTFLY_HEIGHT	96

#define GHOSTWALK_MIN_APPEAR_TIME	2500
#define GHOSTWALK_BETWEEN_CREATE_TIME	300

class CZoneGhostWalk : public CZone
{
private:
	CGame *game;
	Simon * simon;
	unordered_map<int, DWORD> timeBeAttacks; // danh sách thời gian con nào bị đánh
	unordered_map<int, CPoint> pointAppears; // các vị trí xuất hiện của ghost

	DWORD lastTimeCreate = 0; // thời gian tạo gần nhất
public:
	CZoneGhostWalk(int _l, int _t, int _r, int _b) :CZone(_l,_t,_r,_b) {
		type = gameType::ZONE_GHOST_WALK;
		simon = Simon::GetInstance();
		game = CGame::GetInstance();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void createGhostWalk(vector<LPGAMEOBJECT>& listEnemy);
	void addPointAppear(CPoint point, int pos);
	vector<CPoint> allowToCreate(float xCam);
	~CZoneGhostWalk();
};

