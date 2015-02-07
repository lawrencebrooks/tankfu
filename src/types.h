/*
 * Author: Lawrence Brooks
 */

#ifndef LB_TYPES_H
#define LB_TYPES_H

#include "utils.h"

typedef struct sGameState {
	unsigned char current_screen;
	unsigned char current_level;
	unsigned char level_count;
	unsigned char paused;
	char selection;
} Game;

typedef struct sLevelState {
	unsigned char level_state;
	unsigned char level_map[30*25];
	unsigned char render_buffer[12];
	unsigned char buffer_size;
	unsigned char render_index;
	unsigned char render_all;
} Level;

typedef struct sShot {
	unsigned char shot_type;
	unsigned char x;
	unsigned char y;
	unsigned char rebounds;
	unsigned char active;
	Animation up_anim;
	Animation right_anim;

} Shot;

typedef struct sPlayer {
	char handle_id;
	unsigned char handle[3];
	unsigned char score;
	unsigned char level_score;
	unsigned char active_shots;
	float x;
	float y;
	unsigned char spawn_x;
	unsigned char spawn_y;
	unsigned char direction;
	unsigned char player_state;
	unsigned char banter_frame;
	unsigned char banter_index;
	unsigned char grace_frame;
	float speed;
	unsigned char max_speed;
	Shot shot[2];
	Animation up_anim;
	Animation right_anim;
	Animation exp_anim;
} Player;

typedef struct sHandleSelectState {
	char handle_id;
	unsigned char handle[3];
	char char_index;
	unsigned char select_state;
} HandleSelectState;

#endif
