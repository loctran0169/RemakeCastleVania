#pragma once

//Screen
#define SCREEN_WIDTH								512
#define SCREEN_HEIGHT								480
#define HEIGHTBOARD									50

//map
#define TILE_MAP_SIZE								32

//Simon
#define SIMON_ATTACT_TIME							400
#define SIMON_EATTING_TIME							500
//Trạng thái di chuyển cùa simon
#define SIMON_STATE_IDLE							0
#define SIMON_STATE_WALKING_RIGHT					1
#define SIMON_STATE_WALKING_LEFT					2
#define SIMON_STATE_JUMP							3
#define SIMON_STATE_DIE								4
#define SIMON_STATE_SIT								5
#define SIMON_STATE_ATTACK							6
#define SIMON_STATE_ATTACK_WITH_SUB					7
#define SIMON_STATE_LEVEL_UP						8
#define SIMON_STATE_AUTO_WALK						9
#define SIMON_STATE_ATTACKED						10
#define SIMON_STATE_SIT_AFTER_FALL					11
#define SIMON_STATE_INVISIBLE						12
#define SIMON_STATE_UP_STAIR						13
#define SIMON_STATE_DOWN_STAIR						14
#define SIMON_STATE_IDLE_STAIR						15
#define SIMON_STATE_ATTACK_UP						16
#define SIMON_STATE_ATTACK_DOWN						17
#define SIMON_STATE_ON_SKATE						18

//animation của simon
#define SIMON_ANI_IDLE								0
#define SIMON_ANI_WALKING							1
#define SIMON_ANI_JUMPING							2
#define SIMON_ANI_SITTING							3
#define SIMON_ANI_STANDING_ATTACKING 				4
#define SIMON_ANI_SITTING_ATTACKING					5
#define SIMON_ANI_EATTING							6
#define SIMON_ANI_GO_UP 							7
#define SIMON_ANI_GO_DOWN							8
#define SIMON_ANI_HURT								9
#define SIMON_ANI_IDLE_UP							10
#define SIMON_ANI_IDLE_DOWN							11
#define SIMON_ANI_ATTACK_UP							12
#define SIMON_ANI_ATTACK_DOWN						13
#define SIMON_ANI_DIE								14

//Kích cờ simon
#define SIMON_BBOX_WIDTH							32
#define SIMON_BBOX_HEIGHT							63
#define SIMON_PADDING_ATTACT						16

#define SIMON_SIT_BBOX_WIDTH						32
#define SIMON_SIT_BBOX_HEIGHT						48
#define SIMON_PADDING_ANI							15
#define SIMON_PADDING_WEAPON_ATTACK					10
#define SIMON_PADDING_WEAPON_ATTACK_WATERFIRE_X		10
#define SIMON_PADDING_WEAPON_ATTACK_WATERFIRE_Y		15
//tốc độ
#define SIMON_WALKING_SPEED							0.12f 
#define SIMON_JUMP_SPEED_Y							0.34f
#define SIMON_JUMP_GRAVITY							0.0009f
#define SIMON_JUMP_DEFLECT_SPEED					0.02f
#define SIMON_GRAVITY								0.005f
#define SIMON_DIE_DEFLECT_SPEED						0.5f
#define SIMON_AUTO_GO_SPEED							0.4f
#define SIMON_STAIR_SPEED							0.08f
#define DAGGER_SPEED								0.3f
#define BOOMERANG_SPEED								0.45f
#define AXE_SPEED_X									0.2f
#define AXE_SPEED_Y									0.5f
#define	AXE_SPEED_GRAVITY							0.0012f
#define SKATEBOARD_SPEED_X							0.045f

//Thời gian simon
#define SIMON_UNTOUCHABLE_TIME						3000
#define SIMON_TIME_JUMPPING_SIT						300
//Whip
#define WHIP_BBOX_WIDGHT_LV1						42
#define WHIP_BBOX_WIDGHT_LV2						42
#define WHIP_BBOX_WIDGHT_LV3						72
#define WHIP_BBOX_HEIGHT							15
#define	WHIP_LEVEL_MAX								3
#define	WHIP_PADDING_ATTACK							16
#define	WHIP_PADDING_TOP							17
//Torch
#define TORCH_BBOX_WIDGHT							32
#define TORCH_BBOX_HEIGHT							64

//animation_set_id
#define	ANIMATION_SET_ID_SIMON						1
#define	ANIMATION_SET_ID_BRICK						2
#define	ANIMATION_SET_ID_TORCH						3
#define	ANIMATION_SET_ID_WHIP						4
#define	ANIMATION_SET_ID_ITEM						5
//items
#define ITEM_GRAVITY								0.002f
#define ITEM_TIME_EXIT								3000

#define ITEM_HEART_BBOX_WIDTH						24
#define ITEM_HEART_BBOX_HEIGHT						20

#define ITEM_WHIP_BBOX_WIDTH						32
#define ITEM_WHIP_BBOX_HEIGHT						32

#define ITEM_MONEY_BBOX_WIDTH						30
#define ITEM_MONEY_BBOX_HEIGHT						30

#define ITEM_AXE_BBOX_WIDTH							32
#define ITEM_AXE_BBOX_HEIGHT						32

#define ITEM_WATERFIRE_BBOX_WIDTH					32
#define ITEM_WATERFIRE_BBOX_HEIGHT					32

#define KNIFE_BBOX_WIDTH							32
#define KNIFE_BBOX_HEIGHT							18

#define WATERFIRE_WATER_BBOX_WIDTH					20
#define WATERFIRE_WATER_BBOX_HEIGHT					20

#define WATERFIRE_BBOX_WIDTH						32
#define WATERFIRE_BBOX_HEIGHT						25

#define AXE_BBOX_WIDTH								28
#define AXE_BBOX_HEIGHT								28

#define BOOMERANG_BBOX_WIDTH						28
#define BOOMERANG_HEIGHT							28

#define SKATEBOARD_BBOX_WIDTH						64
#define SKATEBOARD_BBOX_HEIGHT						16

//ani item_type
#define ANI_SET_ITEM								5
#define ANI_SET_ITEM_WHIP							0
#define ANI_SET_ITEM_WHIP							1
#define ANI_SET_ITEM_WHIP							2
#define ANI_SET_ITEM_WHIP							3

enum gameType
{
	//item
	ITEM_KNIFE = 0,
	ITEM_HEART = 1,
	ITEM_WHIP = 2,
	ITEM_MONEY_1 = 3,
	ITEM_MONEY_2 = 4,
	ITEM_MONEY_3 = 5,
	ITEM_BOOMERANG = 6,
	ITEM_WATER_FIRE = 7,
	ITEM_AXE = 8,

	//weapon
	WEAPON_SPECIAL = 10,
	WHIP = 11,
	DAGGER = 12,
	AXE = 13,
	BOOMERANG = 14,
	WATER_FIRE = 15,

	//objects
	SIMON = 50, // player
	BRICK = 51, //gạch
	TORCH = 52, //đuốc
	PORTAL = 53, //chuyển màn
	CHECK_AUTO_GO = 54, //auto đi bộ qua hết obj này
	DISABLE_JUMP = 55, // không cho jump
	GO_UP_STAIR = 56, //đi lên cầu thang
	GO_DOWN_STAIR = 57, // đi xuống cầu thang
	SKATEBOARD = 58
};

//effect
#define TIME_EFFECT					450
