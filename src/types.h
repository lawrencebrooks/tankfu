/*
 * Author: Lawrence Brooks
 */

#ifndef LB_TYPES_H
#define LB_TYPES_H

#include "utils.h"
#include "macros.h"

typedef struct __attribute__ ((packed)) sGameState {
	u8 current_screen;
	u8 current_level;
	u8 level_count;
	u8 paused;
	char selection;
} Game;

typedef struct __attribute__ ((packed)) sLevelState {
	u8 level_state;
	u8 level_map[30*25];
	u8 render_buffer[12];
	u8 buffer_size;
	u8 render_index;
	u8 render_all;
} Level;

typedef struct __attribute__ ((packed)) sShot {
	u8 shot_type;
	float x;
	float y;
	u8 rebounds;
	u8 active;
	u8 direction;
	float speed;
	Animation up_anim;
	Animation right_anim;

} Shot;

typedef struct __attribute__ ((packed)) sPlayer {
	char handle_id;
	u8 handle[3];
	u8 score;
	u8 level_score;
	u8 active_shots;
	float x;
	float y;
	u8 spawn_x;
	u8 spawn_y;
	u8 direction;
	u8 player_state;
	u8 banter_frame;
	u8 banter_index;
	u8 grace_frame;
	float speed;
	u8 max_speed;
	Shot shot[MAX_SHOTS];
	Animation up_anim;
	Animation right_anim;
	Animation exp_anim;
} Player;

typedef struct __attribute__ ((packed)) sHandleSelectState {
	char handle_id;
	u8 handle[3];
	char char_index;
	u8 select_state;
} HandleSelectState;

#endif
