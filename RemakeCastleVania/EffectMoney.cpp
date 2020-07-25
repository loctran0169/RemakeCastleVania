#include "EffectMoney.h"


void CEffectMoney::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (GetTickCount() - timeStart > MAX_TIME_ALIVE)
		setFinish(true);
}

void CEffectMoney::Render()
{
	animation_set->at((type == gameType::ITEM_MONEY_1) ? 0 : ((type == gameType::ITEM_MONEY_2) ? 1 : ((type == gameType::ITEM_MONEY_3) ? 2 : 3)))->Render(x, y);

}

void CEffectMoney::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

CEffectMoney::~CEffectMoney()
{
}
