#pragma once
#include"Zone.h"
#include"Simon.h"
#include"Bone.h"
#include"Point.h"

#define BONE_PADDING_CREATE_X	16

class CZoneBone : public CZone // khu vực xuất hiện bộ xương
{
private:
	CGame *game;
	CPoint * point;
	bool isAllowToCreate = true;
public:
	CZoneBone(int _l, int _t, int _r, int _b) :CZone(_l, _t, _r, _b) {
		type = gameType::ZONE_BONE;
		game = CGame::GetInstance();
		point = new CPoint();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void createBone(vector<LPGAMEOBJECT>& listEnemy);
	bool allowToCreate();
	void setPointPosition(float _x, float _y); // vị trí xuất hiện bone
	~CZoneBone();
};

