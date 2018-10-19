/*
 * Copyright 2015 Lawrence Brooks
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LB_TYPES_H
#define LB_TYPES_H

#include "utils.h"
#include "macros.h"

typedef struct sLevelState {
	u8 level_state;
	u8 level_map[30*25];
} Level;

typedef struct sSpriteShared {
	u8 direction;
	u16 speed;
	u8 recoiled;
	u16 x;
	u16 y;
} SpriteShared;

typedef struct sShot {
	SpriteShared shared;
	u8 shot_type;
	u8 hit_count;
	u8 rebounds;
	u8 active;
	u16 distance;
	Animation up_anim;
	Animation right_anim;

} Shot;

typedef struct sTurret {
	SpriteShared shared;
	u8 lives;
	Shot shot[MAX_SHOTS];
} Turret;

typedef struct sHandleSelectState {
	char handle_id;
	u8 handle[3];
	char char_index;
	u8 select_state;
} HandleSelectState;

typedef struct NetMessageStruct {
    u8 code;
	u8 object_pos_x;
	u8 object_pos_y;
	u8 score;
	u8 level_score;
	SpriteShared shared;
	JoyPadState joyPadState;
	u8 handle[3];
} NetMessage;

typedef struct sPlayer {
	char handle_id;
	u8 handle[3];
	u8 active_shots;
	u8 old_active_shots;
	u16 spawn_x;
	u16 spawn_y;
	u8 flags;
	u8 grace_frame;
	u16 max_speed;
	u8 has_rocket;
	u8 has_over_speed;
	u8 feeling_my_way;
	u8 tank_tactic;
	u8 shot_tactic;
	u16 goal_direction;
	u16 deadlock_count_x;
	u16 deadlock_count_y;
	char goal;
	char goal_reached;
	u16 old_held;
	u16 old_x;
	u16 old_y;
	Shot shot[MAX_SHOTS];
	Animation up_anim;
	Animation right_anim;
	Animation exp_anim;
	NetMessage netMessage;
} Player;

typedef struct sGameState {
	u8 current_screen;
	u8 current_level;
	u8 paused;
	u8 boss_fight_status;
	u8 boss_fight_player_hud;
	u8 boss_fight_player_lives;
	u8 toggle_counter;
	u8 toggle_blank;
	u8 demo_choice;
	u16 demo_counter;
	u16 scope_counter;
	u16 tank_rank_counter;
	Player* boss_fight_player;
	JoyPadState* boss_fight_joypad;
	char selection;
} Game;

typedef struct sTileAnimations {
	u8 next_available;
	TileAnimation anims[TILE_ANIMATIONS_LENGTH];
} TileAnimations;

#endif
