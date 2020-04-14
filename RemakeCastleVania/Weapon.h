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
	DWORD timeAttact;
public:
	bool isAllowToUse = false;
	CWeapon() :CGameObject() {
		isAttack = false;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void CollisionWithListObjects(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void setPosition(float _x, float _y, int nx);
	virtual void setPositionRender(float _x, float _y);
	virtual bool allowCollision();
	virtual void resetFrame() = 0;
	bool GetAttack() { return isAttack; }
	void SetAttack(bool _isAttack) { isAttack = _isAttack; };

	DWORD GetLastTimeAttack() { return timeAttact; };
	~CWeapon();
};
