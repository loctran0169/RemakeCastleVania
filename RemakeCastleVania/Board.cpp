#include "Board.h"


CBoard* CBoard::_instance = NULL;

CBoard* CBoard::GetInstance()
{
	if (_instance == NULL) _instance = new CBoard();
	return _instance;
}

CBoard::CBoard()
{
	game = CGame::GetInstance();
	data = DataScreenManager::GetInstance();
	sprites = CSprites::GetInstance();
	textures = CTextures::GetInstance();
}

void CBoard::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{

}

void CBoard::Render()
{
	float xCam, yCam;
	game->GetCamPos(xCam,yCam);
	simon = Simon::GetInstance();
	CSprites::GetInstance()->Get(SPRITE_BIG_BOARD)->Draw(xCam, yCam);
	DrawNumber(6, xCam + 105, yCam + 30, data->currentScreen->score);//in điểm
	DrawNumber(4, xCam + 295, yCam + 30, data->currentScreen->maxTime);// in thời gian
	DrawNumber(2, xCam + 465, yCam + 30, data->currentScreen->stage); // in stage

	DrawNumber(2, xCam + 370, yCam + 48, data->currentScreen->player.getHealthWeapon()); // in tim 
	DrawNumber(2, xCam + 370, yCam + 63, (data->currentScreen->player.getLife() >= 0) ? data->currentScreen->player.getLife() : 0); // in số mạng
	DrawHP(xCam + 113, yCam + 49, true, (data->currentScreen->player.health)); //máu simon
	DrawHP(xCam + 113, yCam + 65, false, (data->currentScreen->boss == NULL) ? MAX_HP : data->currentScreen->boss->health); // máu boss

	if (data->currentScreen->player.lastItemCollect != gameType::ITEM_WHIP) // in vũ khí đang sử dụng
		animation_set->at(data->currentScreen->player.lastItemCollect)->Render(xCam + 270, yCam + 55);
	if (data->currentScreen->player.isUseDoubleShot || data->currentScreen->player.isUseTripleShot)// in double shot
		animation_set->at((data->currentScreen->player.isUseDoubleShot) ? gameType::ITEM_DOUBLE_SHOT : gameType::ITEM_TRIPLE_SHOT)->Render(xCam + 420, yCam + 50);
}

void CBoard::GetBoundingBox(float & l, float & t, float & r, float & b)
{

}

void CBoard::DrawNumber(int max, float x, float y, int number)
{
	string str = to_string(number);
	for (int i = 0; i < max - str.size(); i++)
	{
		CSprites::GetInstance()->Get(0)->Draw(x, y);
		x += PADDING_FONT;
	}
	for (int i = 0; i < str.size(); i++)
	{
		CSprites::GetInstance()->Get(str[i] - '0')->Draw(x, y);
		x += PADDING_FONT;
	}
}

void CBoard::DrawHP(float x, float y, bool isSimon, int hp)
{
	for (int i = 0; i < hp; i++)
	{
		CSprites::GetInstance()->Get((isSimon)?SPRITE_HP_SIMON: SPRITE_HP_BOSS)->Draw(x, y);
		x += PADDING_HP;
	}
	for (int i = 0; i < 16 - hp; i++)
	{
		CSprites::GetInstance()->Get(SPRITE_HP_EMPTY)->Draw(x, y);
		x += PADDING_HP;
	}
}

CBoard::~CBoard()
{
}
