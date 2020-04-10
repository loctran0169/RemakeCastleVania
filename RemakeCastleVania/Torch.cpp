#include "Torch.h"

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	if (isTouch &&GetTickCount() - timeHitted >= TIME_EFFECT)
		isFinish = true;
}
void CTorch::Render() {
	if (!isTouch)
		animation_set->at(1)->Render(x, y);
	else
		animation_set->at(1)->Render(x, y);
}
void CTorch::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	r = x + FIRE_BBOX_WIDGHT;
	b = y + FIRE_BBOX_HEIGHT;
}
CTorch::~CTorch()
{

}
