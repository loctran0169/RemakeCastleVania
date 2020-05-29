#include "ZoneGhostWalk.h"

void CZoneGhostWalk::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CZoneGhostWalk::Render()
{
	//RenderBoundingBox();
}

void CZoneGhostWalk::GetBoundingBox(float & _left, float & _top, float & _right, float & _bottom)
{
	_left = x;
	_top = y;
	_right = right;
	_bottom = bottom;
}

void CZoneGhostWalk::createGhostWalk(vector<LPGAMEOBJECT>& listEnemy)
{
	float xCam, yCam;
	game->GetCamPos(xCam, yCam);

	int num = 0;
	for (int i = 0; i < listEnemy.size(); i++) {
		if (listEnemy.at(i)->getType() == gameType::GHOST_WALK) {
			auto * ghost = dynamic_cast<CGhostWalk*>(listEnemy[i]);
			if (ghost->timeBeAttacked != 0) 
				timeBeAttacks[ghost->id] = ghost->timeBeAttacked;
			num++;
		}
	}
	if (num >= 3)return; // chỉ xuất hiện tối đa 3 con trên 1 màn hình
	
	vector<CPoint> pointss = allowToCreate(xCam);
	for (int i = 0; i < 3; i++) {
		if (GetTickCount() - lastTimeCreate < GHOSTWALK_BETWEEN_CREATE_TIME) return; // min thời gian xuất kiên nối típ
		if (timeBeAttacks[i] != 0 && GetTickCount() - timeBeAttacks[i] < GHOSTWALK_MIN_APPEAR_TIME) return; // con nào bị chết sai 2 giây thì mới được tạo lại
		
		int position = rand() % pointss.size();
		int xAppear; // vị trí xuất hiện x
		if (pointss[position].nx == 1)
			xAppear = xCam + GHOSTWALK_PADDING_X;
		else
			xAppear = xCam + SCREEN_WIDTH - GHOSTWALK_BBOX_WIDTH - GHOSTWALK_PADDING_X;
		CGhostWalk * gh = new CGhostWalk(i, pointss[position].nx, xAppear, pointss[position].y);
		lastTimeCreate = GetTickCount();
		timeBeAttacks[i] = 0;
		listEnemy.push_back(gh);
		num++;
		if (num >= 3)break;
	}
}

void CZoneGhostWalk::addPointAppear(CPoint point, int pos)
{
	pointAppears[pos] = point;
	if (pos < 3) // tại vì chỉ có 3 con trên 1 màn hình
		timeBeAttacks[pos] = 0;
}

vector<CPoint> CZoneGhostWalk::allowToCreate(float xCam)
{
	vector<CPoint> allow;
	allow.clear();
	for (int i = 0; i < pointAppears.size(); i++) {
		if (pointAppears[i].nx == 1 && pointAppears[i].x > xCam && pointAppears[i].x < xCam + SCREEN_WIDTH)
			continue;
		else if (pointAppears[i].nx == -1 && pointAppears[i].x > xCam && pointAppears[i].x < xCam + SCREEN_WIDTH)
			continue;
		else
			allow.push_back(pointAppears[i]);
	}
	return allow;
}

CZoneGhostWalk::~CZoneGhostWalk()
{
}
