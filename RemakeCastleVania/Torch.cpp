#include "Torch.h"

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	if (isHitted && GetTickCount() - timeBeAttacked >= TIME_EFFECT)
		isFinish = true;
}
void CTorch::Render() {
	if (!isHitted)
		animation_set->at(0)->Render(x, y);
	else
		if (!isFinish)
			animation_set->at(1)->Render(x, y);
}
void CTorch::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	r = x + TORCH_BBOX_WIDGHT;
	b = y + TORCH_BBOX_HEIGHT;
}
CTorch::~CTorch()
{

}
