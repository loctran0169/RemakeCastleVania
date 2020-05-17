#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	currentScence = id;
	map = CMap::GetInstance();
	game = CGame::GetInstance();
	dataNextScreen = DataNextScreen::GetInstance();
	dataScreen = DataScreen::GetInstance();
	key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::checkCollisonWeapon(vector<LPGAMEOBJECT>* coObjects)
{
	for (auto& weapon : player->weapons) {
		if (weapon.second->GetAttack()) {
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				if (weapon.second->GetLastTimeAttack() > coObjects->at(i)->timeBeAttacked) {
					if (weapon.second->isCollitionObjectWithObject(coObjects->at(i))) {
						CGameObject *gameObj = coObjects->at(i);
						switch (gameObj->getType())
						{
						case gameType::TORCH: {
							DebugOut(L"Va chạm torch\n");
							gameObj->isHitted = true;
							if (weapon.second->getType() == gameType::DAGGER) {
								player->weapons[gameType::DAGGER]->SetAttack(false);
								DebugOut(L"exits attack dagger \n");
							}
							break;
						}
						case gameType::BRICK: {
							// mấy cục đá đánh rớt item
							break;
						}
						default:
							break;
						}
						gameObj->timeBeAttacked = GetTickCount();
						
					}
				}
			}
		}
	}
}

void CPlayScene::checkCollisonWithItem()
{
	for (UINT i = 0; i < listItems.size(); i++) {
		if (!listItems[i]->isPicked) {
			if (player->isCollitionObjectWithObject(listItems[i])) {
				switch (listItems[i]->getType())
				{
				case gameType::ITEM_WHIP: {
					Whip* whip =dynamic_cast<Whip*>(player->weapons[gameType::WHIP]);
					if (player->isAttact) {			
						whip->setIDFreeze(whip->getAniID());
						whip->animation_set->at(whip->getIDFreeze())->setLopping(true);
						whip->isLopping = true;
						player->attactTime += SIMON_EATTING_TIME;
					}					
					whip->whipUpgrade();

					//trâng thái đừng khi ăn item
					player->isEatItem = true;
					player->timeEatItem = GetTickCount();
					player->animation_set->at(player->currentAni)->setLopping(true);					
					player->prevAni = player->currentAni;				
					player->isRenderLopping = true;
					break;
				}
				case gameType::ITEM_HEART: {
					player->heartWeapon++;
					DebugOut(L"Chạm item heart: %d tim\n",player->heartWeapon);
					// cộng tim cho simon(chưa làm)
					break;
				}
				case gameType::ITEM_KNIFE: {
					player->weapons[gameType::DAGGER] = new CKnife();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::DAGGER);
					player->weapons[gameType::DAGGER]->SetAnimationSet(ani_set);
					player->currentWeapon = gameType::DAGGER;
					DebugOut(L"Đã nhặt dao \n");
					break;
				}
				case gameType::ITEM_BOOMERANG: {
					player->weapons[gameType::BOOMERANG] = new CBoomerang();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::BOOMERANG);
					player->weapons[gameType::BOOMERANG]->SetAnimationSet(ani_set);
					player->currentWeapon = gameType::BOOMERANG;
					DebugOut(L"Đã nhặt boomerang \n");
					break;
				}
				case gameType::ITEM_AXE: {
					player->weapons[gameType::AXE] = new CAxe();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::AXE);
					player->weapons[gameType::AXE]->SetAnimationSet(ani_set);
					player->currentWeapon = gameType::AXE;
					DebugOut(L"Đã nhặt axe \n");
					break;
				}
				case gameType::ITEM_WATER_FIRE: {
					player->weapons[gameType::WATER_FIRE] = new CWaterFire();
					CAnimationSets * animation_sets = CAnimationSets::GetInstance();
					LPANIMATION_SET ani_set = animation_sets->Get(gameType::WATER_FIRE);
					player->weapons[gameType::WATER_FIRE]->SetAnimationSet(ani_set);
					player->currentWeapon = gameType::WATER_FIRE;
					DebugOut(L"Đã nhặt water fire \n");
					break;
				}
				default:
					break;
				}
				listItems[i]->isPicked = true;
			}
		}
	}
}

void CPlayScene::checkCollisonWithHideObj()
{
	bool isAllowJump = true;
	bool isOnUpStair = false;
	bool isOnDownStair = false;
	for (UINT i = 0; i < listHidenObjects.size(); i++) {
		if (player->isCollitionObjectWithObject(listHidenObjects[i])) {
			switch (listHidenObjects[i]->getType())
			{
			case gameType::PORTAL: {
				if (player->isAutoGoWithJump)break;
				CPortal *p = dynamic_cast<CPortal *>(listHidenObjects[i]);
				DebugOut(L"collision portal \n");
				if (!player->isAutoGoWithJump) {
					DebugOut(L"[INFO] Switching to scene %d \n", p->GetSceneId());
					CGame::GetInstance()->SwitchScene(p->GetSceneId(), p->isStair);
					return;
				}
				break;
			}
			case gameType::CHECK_AUTO_GO: {
				if (player->isAutoGoWithJump)break;
				CHidenObject *p = dynamic_cast<CHidenObject *>(listHidenObjects[i]);
				float l, t, r, b;
				p->GetBoundingBox(l, t, r, b);
				player->isAutoGo = true;
				if (player->isJump) {
					player->collXFirst = l;
					player->isAutoGoWithJump = true;
				}
				else
					//DebugOut(L"[INFO] vào trạng thái tự đi \n");
					player->setValueAutoGo(r - l, 0.0f, SIMON_STATE_IDLE, 1,false);//chưa xử lý trường lợp -1
				break;
			}
			case gameType::DISABLE_JUMP:
				isAllowJump = false;
				break;
			case gameType::GO_UP_STAIR: {
				CHidenObject *p = dynamic_cast<CHidenObject *>(listHidenObjects[i]);
				float l, t, r, b;
				p->GetBoundingBox(l, t, r, b);
				DebugOut(L"chạm stair \n");
				isOnUpStair = true;
				player->nxCheckStairUp = p->nx;
				player->xStairUp = l + ((p->nx < 0) ? SIMON_BBOX_WIDTH / 2.0f : 0);
				break;
			}
			case gameType::GO_DOWN_STAIR: {
				CHidenObject *p = dynamic_cast<CHidenObject *>(listHidenObjects[i]);
				float l, t, r, b;
				p->GetBoundingBox(l, t, r, b);

				isOnDownStair = true;
				player->nxCheckStairDown = p->nx;
				player->xStairDown = l + ((p->nx < 0) ? 2 : -2);
				break;
			}
			default:
				break;
			}
		}
	}

	player->isAllowJump = isAllowJump;
	player->isOnCheckStairUp = isOnUpStair;
	player->isOnCheckStairDown = isOnDownStair;
}

void CPlayScene::checkCollisonWithEnemy(vector<LPGAMEOBJECT>* coObjects)
{
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAPTXT 7

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_MAPTXT(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() <2) return; // skip invalid lines
	int texID = atoi(tokens[0].c_str());
	wstring pathFile = ToWSTR(tokens[1]);
	map->scene = texID;
	map->setTexture(CTextures::GetInstance()->Get(texID));
	map->readMapTxt(pathFile.c_str());
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}
	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	bool isHidenObject = false;

	switch (object_type)
	{
	case gameType::SIMON: {
		if (player != NULL)
		{
			DebugOut(L"[ERROR] Simon object was created before! ");
			return;
		}
		DebugOut(L"[ERROR] Đã tạo simon \n");
		obj = new Simon();
		player = (Simon*)obj;
		break;
	}
	case gameType::BRICK: {
		int numberObj = atoi(tokens[4].c_str());
		int isCross = atoi(tokens[5].c_str());
		if (numberObj > 1) {
			if (isCross == 0)
				obj = new CBrick(x, y, x + BRICK_BBOX_WIDTH * numberObj, y + BRICK_BBOX_HEIGHT);
			else
				obj = new CBrick(x, y, x + BRICK_BBOX_WIDTH, y + BRICK_BBOX_HEIGHT * numberObj);
		}
		else
			obj = new CBrick();
		break;
	}
	case gameType::TORCH: {
		int itemId = atoi(tokens[4].c_str());
		obj = new CTorch();
		obj->setItemID(itemId);
		break;
	}
	case gameType::PORTAL:{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		nextScence = scene_id;
		obj = new CPortal(x, y, r, b, scene_id);
		isHidenObject = true;

		int isOnStair = atoi(tokens[7].c_str());
		int px = atoi(tokens[8].c_str());
		int py = atoi(tokens[9].c_str());
		int pnx = atoi(tokens[10].c_str());
		int pny = atoi(tokens[11].c_str());
		if (isOnStair == 1) {
			nextIsStair = true;
			dynamic_cast<CPortal*>((CPortal*)obj)->isStair = true;
			dataNextScreen->setData(isOnStair, px, py, pnx, pny);
		}
		else
			dynamic_cast<CPortal*>((CPortal*)obj)->isStair = false;
		break;
	}
	case gameType::CHECK_AUTO_GO:{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		obj = new CHidenObject(x, y, r, b);
		isHidenObject = true;
		break;
	}
	case gameType::DISABLE_JUMP: {
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		obj = new CHidenObject(x, y, r, b);
		obj->setType(gameType::DISABLE_JUMP);
		isHidenObject = true;
		break;
	}
	case gameType::GO_UP_STAIR: {
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		float nx = atof(tokens[6].c_str());
		obj = new CHidenObject(x, y, r, b);
		obj->setType(gameType::GO_UP_STAIR);
		obj->nx = nx;
		isHidenObject = true;
		break;
	}
	case gameType::GO_DOWN_STAIR: {
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		float nx = atof(tokens[6].c_str());
		obj = new CHidenObject(x, y, r, b);
		obj->setType(gameType::GO_DOWN_STAIR);
		obj->nx = nx;
		isHidenObject = true;
		break;
	}
	case gameType::SKATEBOARD:{
		int bL = atoi(tokens[4].c_str());
		int bR = atoi(tokens[5].c_str());
		obj = new CSkateBoard(bL,bR);
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	if (object_type == gameType::SIMON) {
		int ani_set_whip_id = atoi(tokens[4].c_str());
		LPANIMATION_SET ani_set_whip = animation_sets->Get(ani_set_whip_id);
		dynamic_cast<Whip*>(((Simon*)obj)->weapons[gameType::WHIP])->SetAnimationSet(ani_set_whip);
	}
	if (object_type != gameType::BRICK) 
		obj->SetAnimationSet(ani_set);
	if (isHidenObject == true)
		listHidenObjects.push_back(obj);
	else
		objects.push_back(obj);
}

Item * CPlayScene::getNewItem(int id, float x, float y)
{
	Item *item;
	switch (id)
	{
	case gameType::ITEM_KNIFE:
		item = new Item(gameType::ITEM_KNIFE);
		item->SetPosition(x, y);
		break;
	case gameType::ITEM_HEART:
		item = new Item(gameType::ITEM_HEART);
		item->SetPosition(x, y);
		break;
	case gameType::ITEM_WHIP:
		item = new Item(gameType::ITEM_WHIP);
		item->SetPosition(x, y);
		break;
	case gameType::ITEM_MONEY_1:
		item = new Item(gameType::ITEM_MONEY_1);
		item->SetPosition(x, y);
		break;
	case gameType::ITEM_MONEY_2:
		item = new Item(gameType::ITEM_MONEY_2);
		item->SetPosition(x, y);
		break;
	case gameType::ITEM_MONEY_3:
		item = new Item(gameType::ITEM_MONEY_3);
		item->SetPosition(x, y);
		break;
	case gameType::ITEM_BOOMERANG:
		item = new Item(gameType::ITEM_BOOMERANG);
		item->SetPosition(x, y);
		break;
	case gameType::ITEM_WATER_FIRE:
		item = new Item(gameType::ITEM_WATER_FIRE);
		item->SetPosition(x, y);
		break;
	case gameType::ITEM_AXE:
		item = new Item(gameType::ITEM_AXE);
		item->SetPosition(x, y);
		break;
	default:
		item = new Item(gameType::ITEM_WHIP);
		item->SetPosition(x, y);
		break;
	}
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ANI_SET_ITEM);
	item->SetAnimationSet(ani_set);
	item->timeExit = GetTickCount();
	return item;
}

void CPlayScene::Load(bool isNextScreen_Stair)
{
	sceneFilePath = game->getScenes()[game->GetCurrentSceneId()]->getPath();
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[MAPTXT]") { section = SCENE_SECTION_MAPTXT; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_MAPTXT: _ParseSection_MAPTXT(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();
	if (isNextScreen_Stair) {
		DataScreen * p = DataScreen::GetInstance();
		if (p->isOnStair) {
			player->isStair = true;
			player->x = p->x;
			player->y = p->y;
			player->nx = p->nx;
			if (p->ny == 1) {
				player->SetState(SIMON_STATE_IDLE_STAIR);
				player->isGoDown = true;
				player->isGoStairByUp = true;
			}
			else {
				player->SetState(SIMON_STATE_IDLE_STAIR);
				player->isGoUp = true;
				player->isGoStairByUp = false;
			}
		}
	}
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	// Update camera to follow simon
	float cx, cy;
	player->GetPosition(cx, cy);
	if (cx > SCREEN_WIDTH / 2 && cx < map->boundingMapRight - SCREEN_WIDTH / 2)
		game->setCamX(cx - SCREEN_WIDTH / 2);
	else if (cx > map->boundingMapRight - SCREEN_WIDTH / 2)
		game->setCamX(map->boundingMapRight - SCREEN_WIDTH);
	else
		game->setCamX(0);

	//khi ăn item whip
	if (player->isEatItem) {
		if (GetTickCount() - player->timeEatItem < SIMON_EATTING_TIME) {
			return;
		}
		else {			Whip * whip = dynamic_cast<Whip*>(player->weapons[gameType::WHIP]);
			whip->animation_set->at(whip->getAniID())->setLopping(false);
			player->animation_set->at(player->prevAni)->setLopping(false);
			if (!player->isAttact || !player->isJump) {
				player->vx = 0.0f;			
			}
			player->isEatItem = false;
		}		
	}
	//process update sau hki ăn item (đóng băng thời gian)
	if (player->isRenderLopping) {
		if (player->isAttact) { //khi đang tấn công
			if (GetTickCount() - player->attactTime > SIMON_ATTACT_TIME) {
				player->isAttact = false;
				player->attactTime = -1;
				player->animation_set->at(player->prevAni)->resetFrame();
				player->isRenderLopping = false;
				for (auto&weapon : player->weapons) {
					if (weapon.second->GetAttack()) {
						switch (weapon.second->getType())
						{
						case gameType::WHIP: {
							Whip* whip = dynamic_cast<Whip*>(player->weapons[gameType::WHIP]);
							whip->SetAttack(false);
							whip->animation_set->at(whip->getAniID())->resetFrame();
							whip->isLopping = false;																					
							break;
						}
						case gameType::DAGGER:
							break;
						default:
							break;
						}
					}
				}											
				if (CGame::GetInstance()->IsKeyDown(DIK_DOWN) == false && player->isSit) {
					player->y -= (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
					player->isSit = false;
				}
			}
			else {  ////// xử lý lại
				/*Whip* whip = dynamic_cast<Whip*>(player->weapons[gameType::WHIP]);
				if (whip->animation_set->at(whip->getAniID())->getCurrentFrame() == 0) {
					whip->animation_set->at(whip->getAniID())->setLopping(false);
					whip->animation_set->at(whip->getAniID())->resetFrame();
					whip->SetAttack(false);
					whip->isLopping=false;
				}*/
			}
		}
		else {
			player->animation_set->at(player->prevAni)->resetFrame();
			player->isRenderLopping = false;
		}
	}
	else {
		if (player->isAttact) { //khi đang tấn công
			if (GetTickCount() - player->attactTime >= SIMON_ATTACT_TIME) {

				for (auto&weapon : player->weapons) {
					if (weapon.second->GetAttack()) {
						switch (weapon.second->getType())
						{
						case gameType::WHIP: {
							Whip* whip = dynamic_cast<Whip*>(player->weapons[gameType::WHIP]);
							whip->SetAttack(false);
							whip->animation_set->at(whip->getAniID())->resetFrame();//reset framw do xét frame<2 collision
							break;
						}
						case gameType::DAGGER:
							break;
						default:
							break;
						}
					}
				}	
				player->isAttact = false;
				player->attactTime = -1;
				if (CGame::GetInstance()->IsKeyDown(DIK_DOWN) == false && player->isSit) {
					player->y -= (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
					player->isSit = false;
				}
			}
		}
	}

	//update objects tĩnh
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 1; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	objects[0]->Update(dt, &coObjects);
	//update items
	for (size_t i = 0; i < listItems.size(); i++)
	{
		listItems[i]->Update(dt, &coObjects);
	}
	// update enemy mà chưa làm
	//*************************************************************************************************

	//simon chết thì ko có va chạm
	if (player->state != SIMON_STATE_DIE) {
		checkCollisonWeapon(&objects);// với cái objects ko phải enemy
		checkCollisonWithHideObj();
		checkCollisonWithItem();	
	}

	//xóa objects ko sài
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<CTorch *>(objects.at(i))) {
			auto *torch = dynamic_cast<CTorch*>(objects.at(i));
			if (torch->isFinish) {
				listItems.push_back(getNewItem(torch->itemID, torch->x, torch->y));
				objects.erase(objects.begin() + i);
				delete torch;
			}
		}
	}
	//update xóa item
	for (int i = 0; i < listItems.size(); i++) {
		if (listItems[i]->isPicked) {
			auto *item = dynamic_cast<Item*>(listItems.at(i));
			listItems.erase(listItems.begin() + i);
			delete item;
		}
	}
}

void CPlayScene::Render()
{
	map->drawMap();
	for (int i = 1; i < objects.size(); i++)//render objects
		objects[i]->Render();
	for (int i = 0; i < listItems.size(); i++)// render items
		listItems[i]->Render();
	for (int i = 0; i < listHidenObjects.size(); i++)// render hiden
		listHidenObjects[i]->Render();
	player->Render();
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	listItems.clear();
	listHidenObjects.clear();
	objects.clear();
	player = NULL;
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame *game = CGame::GetInstance();
	Simon *simon = ((CPlayScene*)scence)->player;
	if (simon->isAttact || simon->isEatItem || simon->isAutoGo)return;
	switch (KeyCode)
	{
	case DIK_S:
		if (!simon->isAllowJump||simon->isStair)return;
		if (simon->isJump == 0 && simon->isSit == false )
			if (simon->isAttact == false) {				
				if (game->IsKeyDown(DIK_RIGHT))
				{
					simon->isJumpRight = true;
					simon->isJumpLeft = false;
				}
				else if (game->IsKeyDown(DIK_LEFT)) {
					simon->isJumpRight = false;
					simon->isJumpLeft = true;
				}
				else {
					simon->isJumpRight = false;
					simon->isJumpLeft = false;
				}
				simon->SetState(SIMON_STATE_JUMP);
			}
		break;
	case DIK_A:
		if (!simon->isAttact && !simon->isEatItem)
			if(game->IsKeyDown(DIK_UP)&&simon->currentWeapon!=0)
				simon->attackWeapon(simon->currentWeapon);
			simon->attackWeapon(gameType::WHIP);
		break;
	case DIK_R: // reset
		for (auto&scence : game->getScenes()) {
			DebugOut(L"scene: %d \n",scence.second->getID());
		}
		CGame::GetInstance()->SwitchScene(game->GetCurrentSceneId(),false);
		break;
	case DIK_M:
		try {
			if (((CPlayScene*)scence)->nextScence == NULL) return;
			CGame::GetInstance()->SwitchScene(((CPlayScene*)scence)->nextScence, false);
		}catch(exception ex){}
		break;
	case DIK_ESCAPE:
		DestroyWindow(game->getHwnd());
		break;
	}
	
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	Simon *simon = ((CPlayScene*)scence)->player;
	if (simon->isAttact || simon->isEatItem ||simon->isAutoGo)return;
	if (KeyCode == DIK_DOWN) {
		if (simon->isSit) {
			if (!simon->isAttact) {
				simon->isSit = false;
				simon->y -= (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
			}
		}
	}
	else if (KeyCode == DIK_RIGHT || KeyCode == DIK_LEFT)
	{
		if (!simon->isJumpRight && !simon->isJumpLeft)
			simon->vx = 0;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	Simon *simon = ((CPlayScene*)scence)->player;
	if (simon->isAttact || simon->isEatItem || simon->isAutoGo)return;
	// disable control key when Mario die 
	if (simon->GetState() == SIMON_STATE_DIE) return;

	if (game->IsKeyDown(DIK_DOWN))
		if ((simon->isOnCheckStairDown || simon->isStair) && !simon->isJump)
			simon->goDownStair();
		else if (!simon->isAttact && !simon->isSit) {
			if (!simon->isJump) {
				if (!simon->isSit)
					simon->y += (SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
				simon->SetState(SIMON_STATE_SIT);
			}
		}

	if (game->IsKeyDown(DIK_UP) && !simon->isAttact && !simon->isJump) {
		simon->goUpStair();
	}

	if (game->IsKeyDown(DIK_RIGHT)) {
		if (!simon->isAttact && !simon->isJump && !simon->isStair)
			if (!simon->isSit && !simon->isEatItem)
				simon->SetState(SIMON_STATE_WALKING_RIGHT);
			else
				simon->nx = 1.0f;
	}

	if (game->IsKeyDown(DIK_LEFT)) {
		if (!simon->isAttact && !simon->isJump && !simon->isStair)
			if (!simon->isSit && !simon->isEatItem)
				simon->SetState(SIMON_STATE_WALKING_LEFT);
			else
				simon->nx = -1.0f;
	}
	/*else
		simon->SetState(SIMON_STATE_IDLE);*/
}