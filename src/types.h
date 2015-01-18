/*
 * Author: Lawrence Brooks
 */

#ifndef LB_TYPES_H
#define LB_TYPES_H

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
} Level;

typedef struct sAnimation {
	unsigned char current_anim;
	unsigned char anim_count;
	unsigned char frames_per_anim;
	unsigned char frame_count;
	unsigned char* anims[3];
} Animation;

typedef struct sShot {
	unsigned char shot_type;
	unsigned char x;
	unsigned char y;
	unsigned char rebounds;
	unsigned char active;
	Animation animation;

} Shot;

typedef struct sPlayer {
	char handle_id;
	unsigned char handle[3];
	unsigned char score;
	unsigned char level_score;
	unsigned char active_shots;
	unsigned char x;
	unsigned char y;
	unsigned char spawn_x;
	unsigned char spawn_y;
	unsigned char direction;
	unsigned char player_state;
	unsigned char banter_frame;
	unsigned char banter_index;
	unsigned char grace_frame;
	unsigned char speed;
	Shot shot[2];
	Animation animation;
} Player;

typedef struct sHandleSelectState {
	char handle_id;
	unsigned char handle[3];
	char char_index;
	unsigned char select_state;
} HandleSelectState;

#endif
