/*
 * Transformation file: sprites.xml
 * Source image: ../art/sprites.png
 * Tile width: 8px
 * Tile height: 8px
 * Output format: (null)
 */
#define MAP_NONE_WIDTH 1
#define MAP_NONE_HEIGHT 1
const char map_none[] PROGMEM ={
1,1
,0x24};

#define MAP_TANK_BLANK_WIDTH 2
#define MAP_TANK_BLANK_HEIGHT 2
const char map_tank_blank[] PROGMEM ={
2,2
,0x24,0x24,0x24,0x24};

#define MAP_TANK1_UP_0_WIDTH 2
#define MAP_TANK1_UP_0_HEIGHT 2
const char map_tank1_up_0[] PROGMEM ={
2,2
,0x0,0x1,0xa,0xb};

#define MAP_TANK1_RIGHT_0_WIDTH 2
#define MAP_TANK1_RIGHT_0_HEIGHT 2
const char map_tank1_right_0[] PROGMEM ={
2,2
,0x2,0x3,0xc,0xd};

#define MAP_TANK2_UP_0_WIDTH 2
#define MAP_TANK2_UP_0_HEIGHT 2
const char map_tank2_up_0[] PROGMEM ={
2,2
,0x12,0x13,0x1c,0x1d};

#define MAP_TANK2_RIGHT_0_WIDTH 2
#define MAP_TANK2_RIGHT_0_HEIGHT 2
const char map_tank2_right_0[] PROGMEM ={
2,2
,0x14,0x15,0x1e,0x1f};

#define MAP_EXPLOSION_0_WIDTH 2
#define MAP_EXPLOSION_0_HEIGHT 2
const char map_explosion_0[] PROGMEM ={
2,2
,0x4,0x5,0xe,0xf};

#define MAP_EXPLOSION_1_WIDTH 2
#define MAP_EXPLOSION_1_HEIGHT 2
const char map_explosion_1[] PROGMEM ={
2,2
,0x6,0x7,0x10,0x11};

#define MAP_EXPLOSION_2_WIDTH 2
#define MAP_EXPLOSION_2_HEIGHT 2
const char map_explosion_2[] PROGMEM ={
2,2
,0x8,0x9,0x9,0x8};

#define MAP_BALL_WIDTH 1
#define MAP_BALL_HEIGHT 1
const char map_ball[] PROGMEM ={
1,1
,0x16};

#define MAP_ROCKET_UP_0_WIDTH 1
#define MAP_ROCKET_UP_0_HEIGHT 1
const char map_rocket_up_0[] PROGMEM ={
1,1
,0x17};

#define MAP_ROCKET_UP_1_WIDTH 1
#define MAP_ROCKET_UP_1_HEIGHT 1
const char map_rocket_up_1[] PROGMEM ={
1,1
,0x18};

#define MAP_ROCKET_RIGHT_0_WIDTH 1
#define MAP_ROCKET_RIGHT_0_HEIGHT 1
const char map_rocket_right_0[] PROGMEM ={
1,1
,0x19};

#define MAP_ROCKET_RIGHT_1_WIDTH 1
#define MAP_ROCKET_RIGHT_1_HEIGHT 1
const char map_rocket_right_1[] PROGMEM ={
1,1
,0x1a};

#define MAP_RIGHT_ARROW_WIDTH 1
#define MAP_RIGHT_ARROW_HEIGHT 1
const char map_right_arrow[] PROGMEM ={
1,1
,0x20};

#define MAP_DOWN_ARROW_WIDTH 1
#define MAP_DOWN_ARROW_HEIGHT 1
const char map_down_arrow[] PROGMEM ={
1,1
,0x21};

#define MAP_UP_ARROW_WIDTH 1
#define MAP_UP_ARROW_HEIGHT 1
const char map_up_arrow[] PROGMEM ={
1,1
,0x22};

#define MAP_SUB_SHOT_WIDTH 1
#define MAP_SUB_SHOT_HEIGHT 1
const char map_sub_shot[] PROGMEM ={
1,1
,0x1b};

#define MAP_SUB_TURRET_WIDTH 1
#define MAP_SUB_TURRET_HEIGHT 1
const char map_sub_turret[] PROGMEM ={
1,1
,0x23};

#define SPRITES_DATA_SIZE 37
const char sprites_data[] PROGMEM={
 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x29, 0x29		 //tile:0
, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x29, 0x29, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b		 //tile:1
, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x29, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x2b		 //tile:2
, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x29, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x2b, 0x29, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b		 //tile:3
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f		 //tile:4
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe		 //tile:5
, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f		 //tile:6
, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe		 //tile:7
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:8
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:9
, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x29, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x29, 0x29, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:10
, 0x2b, 0x29, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x29, 0x29, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b		 //tile:11
, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x29, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12		 //tile:12
, 0x29, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x29, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x2b, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe		 //tile:13
, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:14
, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:15
, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:16
, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0xfe, 0xfe, 0x3f, 0x3f, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f		 //tile:17
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xf0, 0xf0		 //tile:18
, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xf0, 0xf0, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5		 //tile:19
, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf0, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf5		 //tile:20
, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xf0, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xf5, 0xf0, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5		 //tile:21
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:22
, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:23
, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:24
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0x3f, 0x3f, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0x3f, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:25
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0x3f, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:26
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x9f, 0x9f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x9f, 0x9f, 0x9f, 0x9f, 0xfe, 0xfe, 0xfe, 0xfe, 0x9f, 0x9f, 0x9f, 0x9f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x9f, 0x9f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:27
, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xf0, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xf0, 0xf0, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:28
, 0xf5, 0xf0, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xf0, 0xf0, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5		 //tile:29
, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf0, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90		 //tile:30
, 0xf0, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf0, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe		 //tile:31
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0x7f, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0x7f, 0x7f, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0x7f, 0x7f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0x7f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0xfe, 0xfe, 0xfe		 //tile:32
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xfe, 0xfe, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0x7f, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:33
, 0xfe, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0x7f, 0x7f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0xfe, 0xfe, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:34
, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0xa6, 0xa6, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0xa6, 0xa6, 0x4a, 0x4a, 0x4a, 0xfe, 0x4a, 0x4a, 0xa6, 0xa6, 0x4a, 0x4a, 0xfe, 0xfe, 0xfe, 0x4a, 0xa6, 0xa6, 0x4a, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xa6, 0xa6, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xa6, 0xa6, 0xfe, 0xfe, 0xfe		 //tile:35
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:36
};
