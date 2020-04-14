#pragma once
#include"Game.h"
#include"GameObject.h"
#include"Sprites.h"
#include"define.h"
#include"Torch.h"
#include"Utils.h"

class CWeapon : public CGameObject
{
protected:
	bool isAttack;
	int aniFreeze;
	DWORD timeAttact;
public:
	bool isAllowToUse = false;
	bool isLopping;//trạng phái render khi đóng băng
	CWeapon() :CGameObject() {
		isAttack = false;
		aniFreeze = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void CollisionWithListObjects(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void setPosition(float _x, float _y, int nx);
	virtual void setPositionRender(float _x, float _y);
	virtual bool allowCollision();
	virtual void resetFrame() = 0;
	int getIDFreeze() { return aniFreeze; }
	void setIDFreeze(int a) { aniFreeze = a; }

	bool GetAttack() { return isAttack; }
	void SetAttack(bool _isAttack) { isAttack = _isAttack; };

	DWORD GetLastTimeAttack() { return timeAttact; };
	~CWeapon();
};
