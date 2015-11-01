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
,0xe};

#define MAP_TANK_BLANK_WIDTH 2
#define MAP_TANK_BLANK_HEIGHT 2
const char map_tank_blank[] PROGMEM ={
2,2
,0xe,0xe,0xe,0xe};

#define MAP_TANK1_UP_0_WIDTH 2
#define MAP_TANK1_UP_0_HEIGHT 2
const char map_tank1_up_0[] PROGMEM ={
2,2
,0x0,0x1,0xf,0x10};

#define MAP_TANK1_UP_1_WIDTH 2
#define MAP_TANK1_UP_1_HEIGHT 2
const char map_tank1_up_1[] PROGMEM ={
2,2
,0x2,0x3,0x11,0x12};

#define MAP_TANK1_RIGHT_0_WIDTH 2
#define MAP_TANK1_RIGHT_0_HEIGHT 2
const char map_tank1_right_0[] PROGMEM ={
2,2
,0x4,0x5,0x13,0x14};

#define MAP_TANK1_RIGHT_1_WIDTH 2
#define MAP_TANK1_RIGHT_1_HEIGHT 2
const char map_tank1_right_1[] PROGMEM ={
2,2
,0x6,0x7,0x15,0x16};

#define MAP_TANK2_UP_0_WIDTH 2
#define MAP_TANK2_UP_0_HEIGHT 2
const char map_tank2_up_0[] PROGMEM ={
2,2
,0x1b,0x1c,0x28,0x29};

#define MAP_TANK2_UP_1_WIDTH 2
#define MAP_TANK2_UP_1_HEIGHT 2
const char map_tank2_up_1[] PROGMEM ={
2,2
,0x1d,0x1e,0x2a,0x2b};

#define MAP_TANK2_RIGHT_0_WIDTH 2
#define MAP_TANK2_RIGHT_0_HEIGHT 2
const char map_tank2_right_0[] PROGMEM ={
2,2
,0x1f,0x20,0x2c,0x2d};

#define MAP_TANK2_RIGHT_1_WIDTH 2
#define MAP_TANK2_RIGHT_1_HEIGHT 2
const char map_tank2_right_1[] PROGMEM ={
2,2
,0x21,0x22,0x2e,0x2f};

#define MAP_EXPLOSION_0_WIDTH 2
#define MAP_EXPLOSION_0_HEIGHT 2
const char map_explosion_0[] PROGMEM ={
2,2
,0x8,0x9,0x17,0x18};

#define MAP_EXPLOSION_1_WIDTH 2
#define MAP_EXPLOSION_1_HEIGHT 2
const char map_explosion_1[] PROGMEM ={
2,2
,0xa,0xb,0x19,0x1a};

#define MAP_EXPLOSION_2_WIDTH 2
#define MAP_EXPLOSION_2_HEIGHT 2
const char map_explosion_2[] PROGMEM ={
2,2
,0xc,0xd,0xd,0xc};

#define MAP_BALL_WIDTH 1
#define MAP_BALL_HEIGHT 1
const char map_ball[] PROGMEM ={
1,1
,0x23};

#define MAP_ROCKET_UP_0_WIDTH 1
#define MAP_ROCKET_UP_0_HEIGHT 1
const char map_rocket_up_0[] PROGMEM ={
1,1
,0x24};

#define MAP_ROCKET_UP_1_WIDTH 1
#define MAP_ROCKET_UP_1_HEIGHT 1
const char map_rocket_up_1[] PROGMEM ={
1,1
,0x25};

#define MAP_ROCKET_RIGHT_0_WIDTH 1
#define MAP_ROCKET_RIGHT_0_HEIGHT 1
const char map_rocket_right_0[] PROGMEM ={
1,1
,0x26};

#define MAP_ROCKET_RIGHT_1_WIDTH 1
#define MAP_ROCKET_RIGHT_1_HEIGHT 1
const char map_rocket_right_1[] PROGMEM ={
1,1
,0x27};

#define MAP_RIGHT_ARROW_WIDTH 1
#define MAP_RIGHT_ARROW_HEIGHT 1
const char map_right_arrow[] PROGMEM ={
1,1
,0x30};

#define MAP_LEFT_ARROW_WIDTH 1
#define MAP_LEFT_ARROW_HEIGHT 1
const char map_left_arrow[] PROGMEM ={
1,1
,0x31};

#define MAP_DOWN_ARROW_WIDTH 1
#define MAP_DOWN_ARROW_HEIGHT 1
const char map_down_arrow[] PROGMEM ={
1,1
,0x32};

#define MAP_UP_ARROW_WIDTH 1
#define MAP_UP_ARROW_HEIGHT 1
const char map_up_arrow[] PROGMEM ={
1,1
,0x33};

#define SPRITES_DATA_SIZE 52
const char sprites_data[] PROGMEM={
 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x29, 0x29		 //tile:0
, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x29, 0x29, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b		 //tile:1
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0x20, 0x20, 0x2b, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x29, 0x29		 //tile:2
, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0x2b, 0x20, 0x20, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x29, 0x29, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12		 //tile:3
, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x29, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x2b		 //tile:4
, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x29, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x2b, 0x29, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b		 //tile:5
, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x29, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x2b		 //tile:6
, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0xfe, 0xfe, 0xfe, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0xfe, 0xfe, 0xfe, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x29, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x2b, 0x29, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b		 //tile:7
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f		 //tile:8
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe		 //tile:9
, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f		 //tile:10
, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe		 //tile:11
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:12
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:13
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:14
, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x29, 0x2b, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x29, 0x29, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:15
, 0x2b, 0x29, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x29, 0x29, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b		 //tile:16
, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x29, 0x2b, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x29, 0x29, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:17
, 0x2b, 0x29, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x29, 0x29, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0x20, 0x20, 0x20, 0x20, 0x20, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x12, 0x12, 0x12, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x2b, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x12, 0x12, 0x12		 //tile:18
, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x29, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12		 //tile:19
, 0x29, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x29, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x2b, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0xfe, 0xfe, 0xfe		 //tile:20
, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x2b, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x29, 0x29, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0x2b		 //tile:21
, 0x29, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x29, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0x2b, 0x20, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x20, 0x20, 0x20, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0xfe, 0xfe, 0xfe, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0xfe, 0xfe, 0xfe, 0x12, 0x2b, 0x12, 0x2b, 0x12, 0xfe, 0xfe, 0xfe		 //tile:22
, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:23
, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:24
, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x1f, 0x1f, 0xff, 0xff, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:25
, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0xfe, 0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x1f, 0x1f, 0xfe, 0xfe, 0x3f, 0x3f, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0xff, 0xff, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f		 //tile:26
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xf0, 0xf0		 //tile:27
, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xf0, 0xf0, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5		 //tile:28
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xe1, 0xe1, 0xf5, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xf0, 0xf0		 //tile:29
, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xf5, 0xe1, 0xe1, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf0, 0xf0, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90		 //tile:30
, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf0, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf5		 //tile:31
, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xf0, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xf5, 0xf0, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5		 //tile:32
, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf0, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf5		 //tile:33
, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xfe, 0xfe, 0xfe, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xfe, 0xfe, 0xfe, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xf0, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xf5, 0xf0, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5		 //tile:34
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:35
, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:36
, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:37
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0x3f, 0x3f, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0x3f, 0x3f, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0x3f, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:38
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0x3f, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0x3f, 0xad, 0xad, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xad, 0xad, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xad, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:39
, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xf0, 0xf5, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xf0, 0xf0, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:40
, 0xf5, 0xf0, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xf0, 0xf0, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5		 //tile:41
, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xf0, 0xf5, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xf0, 0xf0, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:42
, 0xf5, 0xf0, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xf0, 0xf0, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0x90, 0x90, 0x90, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0xf5, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x90, 0x90, 0x90		 //tile:43
, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf0, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90		 //tile:44
, 0xf0, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf0, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0xfe, 0xfe, 0xfe		 //tile:45
, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf5, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xf0, 0xf0, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xf5		 //tile:46
, 0xf0, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf0, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xf5, 0xe1, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe1, 0xe1, 0xe1, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xfe, 0xfe, 0xfe, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xfe, 0xfe, 0xfe, 0x90, 0xf5, 0x90, 0xf5, 0x90, 0xfe, 0xfe, 0xfe		 //tile:47
, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0x37, 0x37, 0xff, 0xff, 0xfe, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xff, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xfe, 0xff, 0x37, 0x37, 0x37, 0x37, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe		 //tile:48
, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x37, 0x37, 0xff, 0xfe, 0xff, 0xff, 0x37, 0x37, 0x37, 0x37, 0xff, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xff, 0xfe, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xff, 0xfe, 0xfe, 0xfe, 0x37, 0x37, 0x37, 0x37, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x37, 0x37, 0xff		 //tile:49
, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xfe, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0x37, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0x37, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0xfe, 0xfe, 0xfe		 //tile:50
, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0x37, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0x37, 0xfe, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0xfe, 0xfe, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0xfe, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xff, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff		 //tile:51
};