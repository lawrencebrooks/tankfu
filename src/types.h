/*
 * Author: Lawrence Brooks
 */

#ifndef LB_TYPES_H
#define LB_TYPES_H

#include "utils.h"
#include "macros.h"

typedef struct sGameState {
	u8 current_screen;
	u8 current_level;
	u8 paused;
	char selection;
} Game;

typedef struct sLevelState {
	u8 level_state;
	u8 level_map[30*25];
} Level;

typedef struct sSpriteShared {
	u8 direction;
	u8 speed;
	float x;
	float y;
} SpriteShared;

typedef struct sShot {
	SpriteShared shared;
	u8 shot_type;
	u8 hit_count;
	u8 rebounds;
	u8 active;
	Animation up_anim;
	Animation right_anim;

} Shot;

typedef struct sPlayer {
	SpriteShared shared;
	char handle_id;
	u8 handle[3];
	u8 score;
	u8 level_score;
	u8 active_shots;
	u8 spawn_x;
	u8 spawn_y;
	u8 flags;
	u8 banter_frame;
	u8 banter_index;
	u8 grace_frame;
	u8 max_speed;
	u8 has_rocket;
	u8 has_over_speed;
	Shot shot[MAX_SHOTS];
	Animation up_anim;
	Animation right_anim;
	Animation exp_anim;
} Player;

typedef struct sHandleSelectState {
	char handle_id;
	u8 handle[3];
	char char_index;
	u8 select_state;
} HandleSelectState;

typedef struct sTileAnimations {
	u8 next_available;
	TileAnimation anims[TILE_ANIMATIONS_LENGTH];
} TileAnimations;

#endif
