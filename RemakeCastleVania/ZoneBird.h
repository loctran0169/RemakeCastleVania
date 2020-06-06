#pragma once
#include"Zone.h"
#include"Simon.h"
#include"Bird.h"
#include"Point.h"
#include"Monkey.h"
#define MONKEY_PADDING_CREATE_X	16

class CZoneBird : public CZone
{
private:
	CGame *game;
	CPoint * point;
	bool isAllowToCreate = true;
public:
	CZoneBird(int _l, int _t, int _r, int _b) :CZone(_l, _t, _r, _b) {
		type = gameType::ZONE_BIRD;
		game = CGame::GetInstance();
		point = new CPoint();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void createBird(vector<LPGAMEOBJECT>& listEnemy);
	bool allowToCreate();
	void setPointPosition(float _x, float _y); //vị trí xuất hiện
	~CZoneBird();
};

