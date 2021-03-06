﻿#pragma once

//Screen
#define SCREEN_WIDTH								512
#define SCREEN_HEIGHT								480
#define HEIGHTBOARD									95

//map
#define TILE_MAP_SIZE								32

//Simon
#define SIMON_ATTACT_TIME							400
#define SIMON_EATTING_TIME							500
#define MAX_HP										16
//Trạng thái di chuyển cùa simon
#define SIMON_STATE_IDLE							0 //trạng thái đứng
#define SIMON_STATE_WALKING_RIGHT					1 // trạng thái đi trái
#define SIMON_STATE_WALKING_LEFT					2 // di phải
#define SIMON_STATE_JUMP							3 //nhảy
#define SIMON_STATE_DIE								4 //chết
#define SIMON_STATE_SIT								5 //ngồi
#define SIMON_STATE_ATTACK							6 // đánh
#define SIMON_STATE_ATTACK_WITH_SUB					7 
#define SIMON_STATE_LEVEL_UP						8 // lên cấp
#define SIMON_STATE_AUTO_WALK						9 // tự đi
#define SIMON_STATE_ATTACKED						10 // đánh
#define SIMON_STATE_SIT_AFTER_FALL					11 // ngồi sau khi rơi
#define SIMON_STATE_INVISIBLE						12 // ẩn hình
#define SIMON_STATE_UP_STAIR						13 //lên cầu thang
#define SIMON_STATE_DOWN_STAIR						14 // xuống cầu thang
#define SIMON_STATE_IDLE_STAIR						15 // đứng trên cầu thang
#define SIMON_STATE_ATTACK_UP						16 // đánh hki đi lên
#define SIMON_STATE_ATTACK_DOWN						17 // đánh hki đi xuống
#define SIMON_STATE_ON_SKATE						18 // trên ván trược
#define SIMON_STATE_HURT							19 // bị đánh

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
#define SIMON_GRAVITY_HURTING						0.001f
#define SIMON_DIE_DEFLECT_SPEED						0.34f
#define SIMON_AUTO_GO_SPEED							0.4f
#define SIMON_STAIR_SPEED							0.08f
#define DAGGER_SPEED								0.3f
#define AXE_SPEED_X									0.2f
#define AXE_SPEED_Y									0.5f
#define	AXE_SPEED_GRAVITY							0.0012f
#define SKATEBOARD_SPEED_X							0.045f
#define SIMON_VJUMP_HURTING							0.2f

//Thời gian simon
#define SIMON_UNTOUCHABLE_TIME						2000
#define SIMON_UNTOUCHABLE_TIME_ITEM					8000
#define SIMON_TIME_JUMPPING_SIT						300
//Whip
#define WHIP_BBOX_WIDGHT_LV1						42
#define WHIP_BBOX_WIDGHT_LV2						42
#define WHIP_BBOX_WIDGHT_LV3						72
#define WHIP_BBOX_HEIGHT							20
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

#define ITEM_HEART_MINI_BBOX_WIDTH					16
#define ITEM_HEART_MINI_BBOX_HEIGHT					24

#define ITEM_INVISIBLE_BBOX_WIDTH						32
#define ITEM_INVISIBLE_BBOX_HEIGHT						32

#define ITEM_DOUBLESHOT_BBOX_WIDTH					26
#define ITEM_DOUBLESHOT_BBOX_HEIGHT					28

#define ITEM_TRIPLESHOT_BBOX_WIDTH					26
#define ITEM_TRIPLESHOT_BBOX_HEIGHT					28

#define ITEM_WHIP_BBOX_WIDTH						32
#define ITEM_WHIP_BBOX_HEIGHT						32

#define ITEM_BOOMERANG_BBOX_WIDTH					28.0f
#define ITEM_BOOMERANG_HEIGHT						28.0f

#define ITEM_MONEY_BBOX_WIDTH						30
#define ITEM_MONEY_BBOX_HEIGHT						30

#define ITEM_AXE_BBOX_WIDTH							32
#define ITEM_AXE_BBOX_HEIGHT						32

#define ITEM_WATERFIRE_BBOX_WIDTH					32
#define ITEM_WATERFIRE_BBOX_HEIGHT					32

#define ITEM_STOPWATCH_BBOX_WIDTH					32
#define ITEM_STOPWATCH_BBOX_HEIGHT					32

#define ITEM_CROSS_BBOX_WIDTH						32
#define ITEM_CROSS_BBOX_HEIGHT						32

#define ITEM_CROWN_BBOX_WIDTH						32
#define ITEM_CROWN_BBOX_HEIGHT						32

#define ITEM_FULL_HP_BBOX_WIDTH						24
#define ITEM_FULL_HP_BBOX_HEIGHT					28

#define KNIFE_BBOX_WIDTH							32
#define KNIFE_BBOX_HEIGHT							18

#define WATERFIRE_WATER_BBOX_WIDTH					20
#define WATERFIRE_WATER_BBOX_HEIGHT					20

#define WATERFIRE_BBOX_WIDTH						32
#define WATERFIRE_BBOX_HEIGHT						25

#define AXE_BBOX_WIDTH								28
#define AXE_BBOX_HEIGHT								28

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
	TIMEOUT = -2,//HẾT THỜI GIAN
	HIT = -1, // đánh
	//item0 ->
	ITEM_KNIFE = 0,
	ITEM_HEART = 1,
	ITEM_WHIP = 2,
	ITEM_MONEY_1 = 3,////////////
	ITEM_MONEY_2 = 4,/////////////
	ITEM_MONEY_3 = 5,/////////////
	ITEM_BOOMERANG = 6,
	ITEM_WATER_FIRE = 7,
	ITEM_AXE = 8,
	ITEM_HEART_MINI = 9,
	ITEM_INVISIBLE = 10,
	ITEM_DOUBLE_SHOT = 11, // item 2 gạch
	ITEM_TRIPLE_SHOT = 12, // item 3 gạch
	ITEM_STOP_WATCH = 13,
	ITEM_CROSS = 14,
	ITEM_CROWN = 15, // vương việng
	ITEM_FULL_HP = 16, //use to full HP
	//weapon 39->
	WHIP = 40,
	DAGGER = 41,
	AXE = 42,
	BOOMERANG = 43,
	WATER_FIRE = 44,
	BONE_WEAPON = 45,
	STOP_WATCH = 46,
	DOUBLE_SHOT = 47,
	TRIPLE_SHOT = 48,
	ENEMY_FIRE	= 49,

	//objects 50->
	SIMON = 50, // player
	BRICK = 51, //gạch
	TORCH = 52, //đuốc
	PORTAL = 53, //chuyển màn
	CHECK_AUTO_GO = 54, //auto đi bộ qua hết obj này
	DISABLE_JUMP = 55, // không cho jump
	GO_UP_STAIR = 56, //đi lên cầu thang
	GO_DOWN_STAIR = 57, // đi xuống cầu thang
	SKATEBOARD = 58, // thanh trược
	CANDLE = 59, //cây nến
	BRICKBLACK_1 = 60, //BRICK nổ 1
	BRICKBLACK_2 = 61, // Brick nổ 2
	ZONE_GHOST_FLY = 62, // khu vực tạo ghost fly
	ZONE_GHOST_WALK = 63, // khu vực xuất hiện ma đi bộ v:
	DISABLE_CAMERA = 64	, //vào sẻ set cứng camera lại
	ZONE_MONKEY = 65, //khu vực xuất hiện khỉ con
	ZONE_BIRD = 66, // khu vuc75 tao5 trym
	ZONE_BONE = 67, // khu khu vực xuất hiện bộ xương
	BE_JUMP = 68, //chạm object thì phải chuyển sang trạng thái nhẩy
	CHANGE_NX = 69, // THAY ĐỔI nx khi chạm

	//monster 100->
	WARRIOR = 100, // chiến binh thép
	BAT = 101,	//đơi xéo -> thẳng
	MONKEY = 102, // khỉ
	BONE = 103, // quái xương
	GHOST_FLY = 104, //ma bay
	GHOST_WALK = 105, //ma đi bộ
	BIRD = 106, // quạ đen
	BOSS_BAT = 107, //BOSS bat

	//effect 200->
	EFFECT_BRICKBLACK = 200, //mảnh vỡ
	EFFECT_MONEY = 201,

	GAME_OVER = 300,
	SIMON_DIE = 301,
	SOUND_STAGE_1 = 302,
	SOUND_STAGE_2 = 303,
	SOUND_STAGE_3 = 304,
	SOUND_STAGE_4 = 305,
	SOUND_STAGE_CLEAR = 306 //win game
};

//effect
#define TIME_EFFECT					450
