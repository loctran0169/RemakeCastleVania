#pragma once
//id textures
#define ID_TEX_SIMON_RIGHT		 0
#define ID_TEX_SIMON_LEFT		 1
#define ID_TEX_ENEMY			 2
#define ID_TEX_BRICK			 3
#define ID_TEX_TILESET_MAP_1	 4
#define ID_TEX_WHIP				 5
#define ID_TEX_WHIP_2			 6
#define ID_TEX_BIGFIRE			 7
#define ID_TEX_WHIPVIP			 8
#define ID_TEX_EFFECT_DEAD		 9
#define ID_TEX_HEART			 10
#define ID_TEX_MONEY			 11
#define ID_TEX_KNIFE			 12

//Screen
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
#define HEIGHTBOARD 50
#define MAX_WIDTH_LV1 1536

//map
#define TILE_MAP_SIZE 32

//Simon
#define SIMON_ATTACT_TIME 450

//Trạng thái di chuyển cùa simon
#define SIMON_STATE_IDLE				0
#define SIMON_STATE_WALKING_RIGHT		1
#define SIMON_STATE_WALKING_LEFT		2
#define SIMON_STATE_JUMP				3
#define SIMON_STATE_DIE					4
#define SIMON_STATE_SIT					5
#define SIMON_STATE_ATTACK				6
#define SIMON_STATE_ATTACK_WITH_SUB		7
#define SIMON_STATE_LEVEL_UP			8
#define SIMON_STATE_AUTO_WALK			9
#define SIMON_STATE_ATTACKED			10
#define SIMON_STATE_SIT_AFTER_FALL		11
#define SIMON_STATE_INVISIBLE			12
#define SIMON_STATE_UP_STAIR			13
#define SIMON_STATE_DOWN_STAIR			14
#define SIMON_STATE_IDLE_STAIR			15
#define SIMON_STATE_WALK				16

//animation của simon
#define ANI_IDLE_RIGHT				0
#define ANI_IDLE_LEFT				1
#define ANI_WALKING_RIGHT			2
#define ANI_WALKING_LEFT			3
#define ANI_HIT_RIGHT				4
#define ANI_HIT_LEFT				5
#define ANI_JUMP_RIGHT				6
#define ANI_JUMP_LEFT				7
#define ANI_SIT_RIGHT				8
#define ANI_SIT_LEFT				9
#define ANI_SIT_HIT_RIGHT			10
#define ANI_SIT_HIT_LEFT			11
#define ANI_DIE						12
#define ANI_EAT_ITEM_RIGHT			13
#define ANI_EAT_ITEM_LEFT			14


//Kích cờ simon
#define SIMON_BBOX_WIDTH			32
#define SIMON_BBOX_HEIGHT			64
#define SIMON_PADDING_ATTACT		16

#define SIMON_SIT_BBOX_WIDTH		32
#define SIMON_SIT_BBOX_HEIGHT		48

//tốc độ simon
#define SIMON_WALKING_SPEED			0.1f 
#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_JUMP_DEFLECT_SPEED	0.02f
#define SIMON_GRAVITY				0.002f
#define SIMON_DIE_DEFLECT_SPEED		0.5f

//Thời gian chớp khi va chạm
#define SIMON_UNTOUCHABLE_TIME		3000

//Whip
#define WHIP_BBOX_WIDGHT			80
#define WHIP_BBOX_HEIGHT			15

//BigFire	
#define FIRE_BBOX_WIDGHT			 32
#define FIRE_BBOX_HEIGHT			 64

//items
#define ITEM_GRAVITY				0.002f
#define HEART_BBOX_WIDTH			16
#define HEART_BBOX_HEIGHT			16

#define WHIPITEM_BBOX_WIDTH			32
#define WHIPITEM_BBOX_HEIGHT		32

#define MONEY_BBOX_WIDTH			30
#define MONEY_BBOX_HEIGHT			30

#define KNIFE_BBOX_WIDTH			32
#define KNIFE_BBOX_HEIGHT			18

enum ItemType
{
	HEART = 1,
	WHIP = 2,
	MONEY = 3,
	KNIFE = 4
};

//effect
#define TIME_EFFECT					450