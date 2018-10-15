/*
 * Program: Tank Fu
 *
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
#include <uzebox.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "data/tiles.h"
#include "data/sprites.h"
#include "data/levels.h"
#include "data/patches.h"
#if JAMMA
#include "jamma.h"
#endif
#include "types.h"
#include "strings.h"
#include "utils.h"
#include "macros.h"
#include "networking.h"

/* Utilities */
void load_eeprom(struct EepromBlockStruct* block);
void fade_through();
void level_transition(u8 index);
void clear_sprites();
void save_eeprom(struct EepromBlockStruct* block);
void exit_game();
void print_level_score(Player* winner, Player* loser);
void send_net_message(u8 code, u8 object_pos_x, u8 object_pos_y);
void get_net_message();
void send_smart_net_message(Player* player, JoyPadState* p, u8 code);
u8 is_net_player(Player* player);
void record_player_posture(Player* player);
u8 player_posture_changed(Player* player);
void clearNetBuffers();

/* Initializers */
void init_player(Player* p, const char* map_tank_up_0, const char* map_tank_right_0);

/* Collision Detection */
void collision_detect_shot(Player* player, Shot* shot);

/* Screen loaders */
void load_splash();
void load_tank_rank();
void load_handle_select();
void load_host_net_game();
void load_join_net_game();
void load_level(int level_number);
void load_level_tiles(u8 blank);

/* other function declarations */
void kill_player(Player* player, u8 hud_x);

// Globals
Game game;
Player player1;
Player player2;
Level level;
TileAnimations tile_animations;
TileAnimation scope_animation;
TileAnimation sub_animation;
Turret turret1;
Turret turret2;
u8 wifi_status;
u16 global_frame_counter = 1;
u8 gameId[9] = "TFABCDEF";
u8 gameIdIndex = 2;
u8 frames = 0;

struct EepromBlockStruct handles;
struct EepromBlockStruct scores;

HandleSelectState p1s;
HandleSelectState p2s;

/* Initializers */
void init_scores(struct EepromBlockStruct* e)
{
    e->id = EEPROM_TANK_RANK_ID;
    memcpy_P(e->data, default_scores, 30);
}

void init_handles(struct EepromBlockStruct* e)
{
    e->id = EEPROM_HANDLES_ID;
    memcpy_P(e->data, default_handles, 30);
}

void init_tile_animations(TileAnimations* ta)
{
	ta->next_available = 0;
	for (u8 i = 0; i < TILE_ANIMATIONS_LENGTH; i++)
	{
		ta->anims[i].tile_index = 0;
		ta->anims[i].anim.current_anim = 0;
		ta->anims[i].anim.anim_count = 3;
		ta->anims[i].anim.frames_per_anim = FRAMES_PER_ANIM;
		ta->anims[i].anim.frame_count = 0;
		ta->anims[i].anim.looped = 0;
		ta->anims[i].anim.reversing = 0;
		ta->anims[i].anim.anims[0] = (char*)map_tile_exp_0;
		ta->anims[i].anim.anims[1] = (char*)map_tile_exp_1;
		ta->anims[i].anim.anims[2] = (char*)map_tile_exp_2;
	}
}

void init_scope_animation(TileAnimation* ta)
{
	ta->tile_index = 0;
	ta->anim.current_anim = 0;
	ta->anim.anim_count = 3;
	ta->anim.frames_per_anim = FRAMES_PER_SCOPE;
	ta->anim.frame_count = 0;
	ta->anim.looped = 0;
	ta->anim.reversing = 0;
	ta->anim.anims[0] = (char*)map_scope_0;
	ta->anim.anims[1] = (char*)map_scope_1;
	ta->anim.anims[2] = (char*)map_scope_2;
}

void init_sub_animation(TileAnimation* ta)
{
	ta->tile_index = 0;
	ta->anim.current_anim = 0;
	ta->anim.anim_count = 2;
	ta->anim.frames_per_anim = FRAMES_PER_SUB;
	ta->anim.frame_count = 0;
	ta->anim.looped = 0;
	ta->anim.reversing = 0;
	ta->anim.anims[0] = (char*)map_sub_emerging;
	ta->anim.anims[1] = (char*)map_sub;
}

void init_shot_state(Shot* s, u8 shot_type)
{
	s->shared.speed = SHOT_SPEED;
	s->shared.direction = D_UP;
	s->shared.recoiled = 0;
	s->active = 0;
	s->distance = 0;
	s->shot_type = shot_type;
	s->rebounds = SHOT_REBOUNDS;
	s->hit_count = (shot_type == BASIC_SHOT) ? BASIC_SHOT_HIT_COUNT : ROCKET_SHOT_HIT_COUNT;
	s->shared.x = OFF_SCREEN*100;
	s->shared.y = 0;
}

void set_shot_animations(Shot* s, u8 shot_type)
{
	s->up_anim.current_anim = 0;
	s->up_anim.anim_count = 2;
	s->up_anim.frames_per_anim = FRAMES_PER_ANIM;
	s->up_anim.frame_count = 0;
	s->up_anim.looped = 0;
	s->up_anim.reversing = 0;
	if (shot_type == BASIC_SHOT)
	{
		s->up_anim.anims[0] = (char*) map_ball;
		s->up_anim.anims[1] = (char*) map_ball;
		s->right_anim.anims[0] = (char*) map_ball;
		s->right_anim.anims[1] = (char*) map_ball;
	}
	else if (shot_type == ROCKET_SHOT)
	{
		s->up_anim.anims[0] = (char*) map_rocket_up_0;
		s->up_anim.anims[1] = (char*) map_rocket_up_1;
		s->right_anim.anims[0] = (char*) map_rocket_right_0;
		s->right_anim.anims[1] = (char*) map_rocket_right_1;
	}
	else
	{
		s->up_anim.anims[0] = (char*) map_sub_shot;
		s->up_anim.anims[1] = (char*) map_sub_shot;
		s->right_anim.anims[0] = (char*) map_sub_shot;
		s->right_anim.anims[1] = (char*) map_sub_shot;
	}
	s->up_anim.current_anim = 0;
	s->right_anim.anim_count = 2;
	s->right_anim.frames_per_anim = FRAMES_PER_ANIM;
	s->right_anim.frame_count = 0;
	s->right_anim.looped = 0;
	s->right_anim.reversing = 0;
}

void init_turret(Turret* t, u16 x, u16 y)
{
	t->lives = BOSS_TURRET_LIVES;
	t->shared.direction = D_LEFT;
	t->shared.recoiled = 0;
	t->shared.speed = BOSS_TURRET_SPEED;
	t->shared.x = x;
	t->shared.y = y;
	
	for (u8 i = 0; i < MAX_SHOTS; i++)
	{
		t->shot[i].shared.speed = BOSS_TURRET_SHOT_SPEED;
		t->shot[i].shared.direction = D_DOWN;
		t->shot[i].shared.recoiled = 0;
		t->shot[i].shared.x = OFF_SCREEN*100;
		t->shot[i].shared.y = 0;
		t->shot[i].active = 0;
		t->shot[i].distance = 10000;
		t->shot[i].shot_type = BOSS_TURRET_SHOT;
		t->shot[i].rebounds = SHOT_REBOUNDS;
		t->shot[i].hit_count = BOSS_TURRET_SHOT_HIT_COUNT;
		set_shot_animations(&t->shot[i], BOSS_TURRET_SHOT);
	}
}

void init_player(Player* p, const char* map_tank_up_0, const char* map_tank_right_0)
{
	p->grace_frame = FRAMES_PER_GRACE;
	p->netMessage.score = 0;
	p->netMessage.level_score = 0;
	p->netMessage.shared.direction = D_UP;
	p->netMessage.shared.speed = 0;
	p->netMessage.shared.recoiled = 0;
	p->max_speed = MAX_SPEED;
	p->has_over_speed = false;
	p->has_rocket = false;
	p->flags = 0;

	/* Tracks animation (Up) */
	p->up_anim.current_anim = 0;
	p->up_anim.anim_count = 1;
	p->up_anim.frames_per_anim = FRAMES_PER_ANIM;
	p->up_anim.frame_count = 0;
	p->up_anim.looped = 0;
	p->up_anim.reversing = 0;
	p->up_anim.anims[0] = (char*)map_tank_up_0;

	/* Tracks animation (Down) */
	p->right_anim.current_anim = 0;
	p->right_anim.anim_count = 1;
	p->right_anim.frames_per_anim = FRAMES_PER_ANIM;
	p->right_anim.frame_count = 0;
	p->right_anim.looped = 0;
	p->right_anim.reversing = 0;
	p->right_anim.anims[0] = (char*)map_tank_right_0;

	/* Explosion Animation */
	p->exp_anim.current_anim = 0;
	p->exp_anim.anim_count = 3;
	p->exp_anim.frames_per_anim = FRAMES_PER_ANIM;
	p->exp_anim.frame_count = 0;
	p->exp_anim.looped = 0;
	p->exp_anim.reversing = 0;
	p->exp_anim.anims[0] = (char*)map_explosion_0;
	p->exp_anim.anims[1] = (char*)map_explosion_1;
	p->exp_anim.anims[2] = (char*)map_explosion_2;

	/* Shot */
	p->active_shots = 0;
	p->old_active_shots = 0;
	for (u8 i = 0; i < MAX_SHOTS; i++)
	{
		init_shot_state(&p->shot[i], BASIC_SHOT);
		set_shot_animations(&p->shot[i], BASIC_SHOT);
	}
	
	/* pathfinding variables */
	p->feeling_my_way = 0;
	p->goal_direction = 0;
	p->goal = 0;
	p->goal_reached = 0;
	p->old_x = 0;
	p->old_y = 0;
	p->deadlock_count_x = 0;
	p->deadlock_count_y = 0;
}

void player_init_shot_state(Player* player)
{
	player->active_shots = 0;
	player->old_active_shots = 0;
	for (u8 i = 0; i < MAX_SHOTS; i++)
	{
		init_shot_state(&player->shot[i], BASIC_SHOT);
	}
}

void init_game_state()
{
	game.current_level = 0;
	game.selection = PVCPU;
	game.paused = 0;
	game.scope_counter = 0;
	game.boss_fight_status = 0;
	game.boss_fight_player = 0;
	game.boss_fight_joypad = 0;
	game.boss_fight_player_lives = BOSS_FIGHT_PLAYER_LIVES;
	game.boss_fight_player_hud = 0;
	game.toggle_counter = FRAMES_PER_BLANK;
	game.toggle_blank = 0;
	game.demo_counter = 0;
	game.demo_choice = 0;
	game.tank_rank_counter = 0;
	init_player(&player1, map_tank1_up_0, map_tank1_right_0);
	init_player(&player2, map_tank2_up_0, map_tank2_right_0);
}

/* Utilities */
void player_spawn(Player* player)
{
	player->grace_frame = 0;
	player->netMessage.shared.x = player->spawn_x;
	player->netMessage.shared.y = player->spawn_y;
	player->netMessage.shared.direction = D_UP;
	player->netMessage.shared.speed = 0;
	player->netMessage.shared.recoiled = 0;
	player->tank_tactic = LBRandom(0, 2);
	player->shot_tactic = LBRandom(0, 2);
	
}

void waitForVSync()
{
    ProcessSprites();
    WaitVsync(1);
    RestoreBackground();
#if JAMMA
    handle_coin_insert();
#endif
}

void load_eeprom(struct EepromBlockStruct* block)
/*
 * Load from EEPROM
 *  EEPROM Statuses
 *  0x00 = Success
 *  0x01 = EEPROM_ERROR_INVALID_BLOCK
 *  0x02 = EEPROM_ERROR_FULL
 *  0x03 = EEPROM_ERROR_BLOCK_NOT_FOUND
 *  0x04 = EEPROM_ERROR_NOT_FORMATTED
 */
{
	u8 status = 0;
	status = EepromReadBlock(block->id, block);
	if (status == 0x03)
	{
		status = EepromWriteBlock(block);
	}
}

void fade_through()
{
	FadeOut(FRAMES_PER_FADE, true);
	ClearVram();
	FadeIn(FRAMES_PER_FADE, false);
}

void level_transition(u8 index)
{
	FadeOut(FRAMES_PER_FADE, true);
	ClearVram();
	clear_sprites();
	Print(8, 12, (char*) strLevels+index*16);
	FadeIn(1, true);
	LBWaitSeconds(TEXT_LINGER);
	FadeOut(1, true);
	ClearVram();
	FadeIn(FRAMES_PER_FADE, false);
	load_level(index);
	clearNetBuffers();
}

void clear_sprites()
{
	for(char i = 0; i < MAX_SPRITES; i++)
	{
		MapSprite2(i, map_none, 0);
	}
}

void save_eeprom(struct EepromBlockStruct* block)
/*
 * Save to EEPROM
 */
{
	EepromWriteBlock(block);
}

void save_score()
{
	u8 cur_delta = 0;
	u8 tmp_score[5];
	u8 save_score[5];
	u8 save_delta = 0;
	u8 saved = 0;
	Player* p_win = &player1;
	Player* p_lose = &player2;

	if (player1.netMessage.score < player2.netMessage.score)
	{
		p_win = &player2;
		p_lose = &player1;
	}
	save_score[0] = p_win->handle_id;
	save_score[1] = p_lose->handle_id;
	save_score[2] = p_win->netMessage.score;
	save_score[3] = p_lose->netMessage.score;
	save_score[4] = (game.boss_fight_status == BOSS_FIGHT_WON) ? 1 : 0;
	save_delta = p_win->netMessage.score - p_lose->netMessage.score;

	for (u8 i = 0; i < 28; i += 5)
	{
		if (saved)
		{
			memcpy(tmp_score, &scores.data[i], 5);
			memcpy(&scores.data[i], save_score, 5);
			memcpy(save_score, tmp_score, 5);
		}
		else
		{
			cur_delta = scores.data[i+2] - scores.data[i+3];
			if (save_delta > cur_delta)
			{
				memcpy(tmp_score, &scores.data[i], 5);
				memcpy(&scores.data[i], save_score, 5);
				memcpy(save_score, tmp_score, 5);
				saved = 1;
			}
		}
	}
	save_eeprom(&scores);
}

void exit_game()
{
    save_score();
	fade_through();
	init_game_state();
	load_tank_rank();
}

void position_shot(Player* player, Shot* shot)
{
	switch (shot->shared.direction)
	{
		case D_UP:
			shot->shared.x = player->netMessage.shared.x + 400;
			shot->shared.y = player->netMessage.shared.y;
			break;
		case D_RIGHT:
			shot->shared.x = player->netMessage.shared.x + 800;
			shot->shared.y = player->netMessage.shared.y + 400;
			break;
		case D_DOWN:
			shot->shared.x = player->netMessage.shared.x + 400;
			shot->shared.y = player->netMessage.shared.y + 800;
			break;
		case D_LEFT:
			shot->shared.x = player->netMessage.shared.x;
			shot->shared.y = player->netMessage.shared.y + 400;
			break;
	}
}

void print_level_score(Player* winner, Player* loser)
{
	LBPrintStr(4, 14, &winner->handle[0], 3);
	Print(8, 14, (char*) strOwns);
	LBPrintStr(13, 14, &loser->handle[0], 3);
	Print(17, 14, (char*) strBy);
	PrintByte(22, 14, winner->netMessage.level_score ,true);
	PrintChar(23, 14, '-');
	PrintByte(26, 14, loser->netMessage.level_score ,true);
}

void print_final_score(Player* winner, Player* loser)
{
    Print(9, 12, (char*) strFinalScore);
    LBPrintStr(4, 14, &winner->handle[0], 3);
    Print(8, 14, (char*) strOwns);
    LBPrintStr(13, 14, &loser->handle[0], 3);
    Print(17, 14, (char*) strBy);
    PrintByte(22, 14, winner->netMessage.score ,true);
    PrintChar(23, 14, '-');
    PrintByte(26, 14, loser->netMessage.score ,true);
	if (game.boss_fight_status == BOSS_FIGHT_WON)
	{
		PrintChar(28, 14, '*');
	}
}

char shoot_pressed(JoyPadState* p)
{
	return (p->pressed & BTN_A) || (p->pressed & BTN_B);
}

u16 get_delta(Player* p, SpriteShared* s)
{
	if (p->goal == 0)
		return s->speed / FRAME_TIME_INVERTED;
	return (s->speed + (s->speed / AI_SPEED_FACTOR_INVERTED)) / FRAME_TIME_INVERTED;
}

void update_player(JoyPadState* p, Player* player)
{
	Shot* shot;
	
	player->netMessage.shared.recoiled = 0;
	player->old_active_shots = player->active_shots;
	if ((p->pressed & BTN_START) && (game.boss_fight_status == 0))
	{
#if JAMMA
#else
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		game.paused = game.paused ^ 1;
		send_smart_net_message(player, p, NETPAUSETOGGLE);
		load_level_tiles(false);
#endif
	}
	if (!(game.paused || (player->flags & EXPLODING_FLAG)))
	{
		player->netMessage.shared.speed = player->max_speed;
		if ((p->held & BTN_UP))
		{
			player->netMessage.shared.direction = D_UP;
			player->netMessage.shared.y -= get_delta(player, &player->netMessage.shared);
		}
		else if ((p->held & BTN_RIGHT))
		{
			player->netMessage.shared.direction = D_RIGHT;
			player->netMessage.shared.x += get_delta(player, &player->netMessage.shared);
		}
		else if ((p->held & BTN_DOWN))
		{
			player->netMessage.shared.direction = D_DOWN;
			player->netMessage.shared.y += get_delta(player, &player->netMessage.shared);
		}
		else if ((p->held & BTN_LEFT))
		{
			player->netMessage.shared.direction = D_LEFT;
			player->netMessage.shared.x -= get_delta(player, &player->netMessage.shared);
		}
		else
		{
			player->netMessage.shared.speed = 0;
		}
		if (shoot_pressed(p) && (player->active_shots < MAX_SHOTS))
		{
			for (u8 i = 0; i < MAX_SHOTS; i++)
			{
				shot = &player->shot[i];
				if (!shot->active)
				{
					send_smart_net_message(player, p, NETSHOOT);
					if (player->has_rocket)
					{
						init_shot_state(shot, ROCKET_SHOT);
						set_shot_animations(shot, ROCKET_SHOT);
						LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_ROCKET);
					}
					else
					{
						init_shot_state(shot, BASIC_SHOT);
						set_shot_animations(shot, BASIC_SHOT);
						LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_CANNONBALL);
					}
					player->active_shots = 1;
					shot->shared.direction = player->netMessage.shared.direction;
					position_shot(player, shot);
					shot->active = 1;
					if (player->has_over_speed)
					{
						shot->shared.speed = SHOT_OVER_SPEED;
					}
					break;
				}
			}
		}
	}
	
	if (!game.paused)
	{
		/* Update Shot */
		for (u8 i = 0; i < MAX_SHOTS; i++)
		{
			shot = &player->shot[i];
			if (shot->active)
			{
				switch (shot->shared.direction)
				{
					case D_UP: shot->shared.y -= get_delta(player, &shot->shared); break;
					case D_RIGHT: shot->shared.x += get_delta(player, &shot->shared); break;
					case D_DOWN: shot->shared.y += get_delta(player, &shot->shared); break;
					case D_LEFT: shot->shared.x -= get_delta(player, &shot->shared); break;
					default: break;
				}
				shot->distance += (shot->distance <= DISTANCE_TO_ARM) ? get_delta(player, &shot->shared) : 0;
				collision_detect_shot(player, shot);
			}
		}
	}
	else
	{
		if (p->pressed & BTN_X)
		{
			send_smart_net_message(player, p, NETEXIT);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
			exit_game();
		}
	}
}

void resolve_scoring()
{
	u8 next_level;
	
	if (game.current_level < LEVEL_COUNT - 1)
	{
		if (player1.netMessage.level_score >= MAX_LEVEL_SCORE && !(player2.flags & EXPLODING_FLAG))
		{
			next_level = game.current_level + 1;
			LBHideAllSprites();
			load_level_tiles(true);
			print_level_score(&player1, &player2);
			LBWaitSeconds(TEXT_LINGER);
			player1.netMessage.level_score = 0;
			player2.netMessage.level_score = 0;
			level_transition(next_level);
		}
		else if (player2.netMessage.level_score >= MAX_LEVEL_SCORE && !(player1.flags & EXPLODING_FLAG))
		{
			next_level = game.current_level + 1;
			LBHideAllSprites();
			load_level_tiles(true);
			print_level_score(&player2, &player1);
			LBWaitSeconds(TEXT_LINGER);
			player1.netMessage.level_score = 0;
			player2.netMessage.level_score = 0;
			level_transition(next_level);
		}
	}
	else
	{
		if ((player1.netMessage.level_score >= MAX_LEVEL_SCORE) || (player2.netMessage.level_score >= MAX_LEVEL_SCORE))
		{
			// Tie Breaker
			if (player1.netMessage.score == player2.netMessage.score) return;
			
			if (game.boss_fight_status == 0)
			{
				// Initiate boss fight
				game.boss_fight_status = BOSS_FIGHT_SCOPE_LOADING;
				if (player1.netMessage.score > player2.netMessage.score)
				{
					game.boss_fight_player = &player1;
					game.boss_fight_joypad = &player1.netMessage.joyPadState;
					game.boss_fight_player_hud = 0;
					kill_player(&player2, 15);
					player_spawn(&player2);
					player2.flags = player2.flags ^ EXPLODING_FLAG;
				}
				else
				{
					game.boss_fight_player = &player2;
					game.boss_fight_joypad = &player2.netMessage.joyPadState;
					game.boss_fight_player_hud = 15;
					kill_player(&player1, 0);
					player_spawn(&player1);
					player1.flags = player1.flags ^ EXPLODING_FLAG;
				}
				scope_animation.tile_index = 15 + 5*30;
				return;
			}
			
			// Print level score
			LBHideAllSprites();
			load_level_tiles(true);
			if (player1.netMessage.level_score > player2.netMessage.level_score)
				print_level_score(&player1, &player2);
			else
				print_level_score(&player2, &player1);
			LBWaitSeconds(TEXT_LINGER);
			player1.netMessage.level_score = 0;
			player2.netMessage.level_score = 0;
			
			// Print game score and exit
			if (player1.netMessage.score > player2.netMessage.score)
				print_final_score(&player1, &player2);
			else
				print_final_score(&player2, &player1);
			LBWaitSeconds(TEXT_LINGER);
			exit_game();
		}
	}
}

void render_hud(Player* player, u8 x)
{	
	LBPrintStr(x+10, 0, player->handle, 3);
	Print(x, 0, (char*) strScore);
	Print(x, 1, (char*) strTotal);
	
}

void render_score(Player* player, u8 x)
{
	PrintByte(x+8, 0, player->netMessage.level_score, false);
	PrintByte(x+8, 1, player->netMessage.score, false);
}

void render_player(Player* player, u8 sprite_index)
{
	MoveSprite(sprite_index, player->netMessage.shared.x / 100, player->netMessage.shared.y / 100, 2, 2);
}

void render_shot(Player* player, u8 sprite_index)
{
	if (player->active_shots > 0)
	{
		for (u8 i = 0; i < MAX_SHOTS; i++)
		{
			MoveSprite(sprite_index, player->shot[i].shared.x / 100, player->shot[i].shared.y / 100, 1, 1);
			sprite_index++;
		}
	}
}

void render_tile_explosions(TileAnimations* ta)
{	
	char* map;
	
	for (u8 i = 0; i < TILE_ANIMATIONS_LENGTH; i++)
	{
		if (ta->anims[i].tile_index != 0)
		{
			map = LBGetNextFrame(&ta->anims[i].anim);
			if (ta->anims[i].anim.looped)
			{
				SetTile(ta->anims[i].tile_index % 30, 3 + ta->anims[i].tile_index / 30, 0);
				ta->anims[i].tile_index = 0;
			}
			else
			{
				DrawMap2(ta->anims[i].tile_index % 30,
						3 + ta->anims[i].tile_index / 30, 
						(const char*) map
				);
			}
		}
	}
}

u8 render_scope(TileAnimation* ta)
{
	char *map;
	
	map = LBGetNextFrameReverse(&ta->anim);
	if (ta->anim.looped)
	{
		DrawMap2(ta->tile_index % 30, 3 + ta->tile_index / 30, map_water);
	}
	else
	{
		DrawMap2(ta->tile_index % 30, 3 + ta->tile_index / 30, (const char*) map);
	}
	return ta->anim.looped;
}

char tank_map(Player* player, char sprite_index)
{
	char* t_map = 0;
	u8 t_flags = 0;

	if (player->flags & EXPLODING_FLAG)
	{
		t_map = LBGetNextFrame(&player->exp_anim);
		t_flags = 0;
		if (player->exp_anim.looped)
		{
			player->flags = player->flags ^ EXPLODING_FLAG;
			t_map = (char*) map_tank_blank;
			player_spawn(player);
		}
	}
	else
	{
		if (player->grace_frame != FRAMES_PER_GRACE)
		{
			player->grace_frame++;
		}
		switch (player->netMessage.shared.direction)
		{
			case D_UP: t_map = LBGetNextFrame(&player->up_anim); t_flags = 0; break;
			case D_RIGHT: t_map = LBGetNextFrame(&player->right_anim); t_flags = 0; break;
			case D_DOWN: t_map = LBGetNextFrame(&player->up_anim); t_flags = SPRITE_FLIP_Y; break;
			case D_LEFT: t_map = LBGetNextFrame(&player->right_anim); t_flags = SPRITE_FLIP_X; break;
			default: t_map = LBGetNextFrame(&player->up_anim); t_flags = 0; break;
		}
		if ((player->grace_frame != FRAMES_PER_GRACE) && (game.toggle_blank))
		{
			t_map = (char*) map_tank_blank;
		}
		game.toggle_counter--;
		if (game.toggle_counter == 0)
		{
			game.toggle_counter = FRAMES_PER_BLANK;
			game.toggle_blank = game.toggle_blank ^ 1;
		}
	}
	MapSprite2(sprite_index, (const char*) t_map, t_flags);
	sprite_index += 4;
	return sprite_index;
}

char shot_map(Player* player, char sprite_index)
{
	char* s_map = 0;
	u8 s_flags = 0;
	Shot* shot;

	for (u8 i = 0; i < MAX_SHOTS; i++)
	{
		shot = &player->shot[i];
		if (shot->active)
		{
			switch (shot->shared.direction)
			{
				case D_UP: s_map = LBGetNextFrame(&player->shot[i].up_anim); s_flags = 0; break;
				case D_RIGHT: s_map = LBGetNextFrame(&player->shot[i].right_anim); s_flags = 0; break;
				case D_DOWN: s_map = LBGetNextFrame(&player->shot[i].up_anim); s_flags = SPRITE_FLIP_Y; break;
				case D_LEFT: s_map = LBGetNextFrame(&player->shot[i].right_anim); s_flags = SPRITE_FLIP_X; break;
				default: s_map = LBGetNextFrame(&player->shot[i].up_anim); s_flags = 0; break;
			}
		}
		else
		{
			s_map = (char*) map_tank_blank;
		}
		MapSprite2(sprite_index, (const char*) s_map, s_flags);
		sprite_index++;
	}
	return sprite_index;
}

/* Collision Detection */
void recoil_sprite(SpriteShared* sprite)
{
	u8 tile;
	
	if (sprite->direction == D_UP)
	{
		tile = (sprite->y / 800) + 1;
		sprite->y = tile * 800;
	}
	else if (sprite->direction == D_RIGHT)
	{
		tile = sprite->x / 800;
		sprite->x = tile * 800;
	}
	else if (sprite->direction == D_DOWN)
	{
		tile = sprite->y / 800;
		sprite->y = tile * 800;
	}
	else
	{
		tile = (sprite->x / 800) + 1;
		sprite->x = tile * 800;
	}
	sprite->recoiled = 1;
}

void recoil_sprite_fine(Player* p, SpriteShared* sprite)
{	
	u16 speed = get_delta(p, sprite);
	
	if (sprite->direction == D_UP)
	{
		sprite->y += speed;
	}
	else if (sprite->direction == D_RIGHT)
	{
		sprite->x -= speed;
	}
	else if (sprite->direction == D_DOWN)
	{
		sprite->y -= speed;
	}
	else
	{
		sprite->x += speed;
	}
	sprite->recoiled = 1;
}

u8 solid_square_tile(int tile_index)
{
	u8 tile = level.level_map[tile_index];
	
	if (tile == L_BRICK) return tile;
	if (tile == L_METAL) return tile;
	if (tile == L_FENCE) return tile;

	return 0;
}

u8 solid_directional_tile(int tile_index)
{
	u8 tile = level.level_map[tile_index];

	if (tile == L_TL) return tile;
	if (tile == L_BR) return tile;
	if (tile == L_TR) return tile;
	if (tile == L_BL) return tile;
	
	return 0;
}

u8 solid_tile(int tile_index)
{
	u8 tile = level.level_map[tile_index];
	
	if (tile == L_BRICK) return tile;
	if (tile == L_METAL) return tile;
	if (tile == L_FENCE) return tile;
	return solid_directional_tile(tile_index);
}

u8 collides_directional_tile(int tile_index, u16 x, u16 y, u16 width, u16 height)
{
	u8 tile = level.level_map[tile_index];
	u16 tile_x = (tile_index % 30) * 800;
	u16 tile_y = (tile_index / 30 + 3) * 800;

	/*if ((tile == L_TL) || (tile == L_BR))
	{
		if (LBLineIntersect(tile_x, tile_y+799, tile_x+799, tile_y, x, y, x, y+height-1)) return tile;
		if (LBLineIntersect(tile_x, tile_y+799, tile_x+799, tile_y, x, y, x+width-1, y)) return tile;
		if (LBLineIntersect(tile_x, tile_y+799, tile_x+799, tile_y, x+width-1, y, x+width-1, y+height-1)) return tile;
		if (LBLineIntersect(tile_x, tile_y+799, tile_x+799, tile_y, x, y+height-1, x+width-1, y+height-1)) return tile;
	}
	else if ((tile == L_TR) || (tile == L_BL))
	{
		if (LBLineIntersect(tile_x, tile_y, tile_x+799, tile_y+799, x, y, x, y+height-1)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+799, tile_y+799, x, y, x+width-1, y)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+799, tile_y+799, x+width-1, y, x+width-1, y+height-1)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+799, tile_y+799, x, y+height-1, x+width-1, y+height-1)) return tile;
	}
	
	return 0;*/
	if (tile == L_TR)
	{
		if (x+width-1 < tile_x+800 && x+width-1 >= tile_x && y >= tile_y && y < tile_y+800)
		{
			if (y <= tile_y+(x+width-1-tile_x)) return 1;
		}
		else if (x >= tile_x && x < tile_x+800 && y >= tile_y && y < tile_y+800)
		{
			if (x+width >= tile_x+800) return 1;
			else if (y <= tile_y+(x+width-1-tile_x)) return 1;
		}
		else if (x+width-1 < tile_x+800 && x+width-1 >= tile_x && y+height-1 >= tile_y && y+height-1 < tile_y+800)
		{
			if (y <= tile_y) return 1;
			else if (y <= tile_y+(x+width-1-tile_x)) return 1;
		}
	}
	
	else if (tile == L_TL)
	{
		if (x >= tile_x && x < tile_x+800 && y >= tile_y && y < tile_y+800)
		{
			if (y < tile_y+(tile_x+800-x)) return 1;
		}
		else if (x+width-1 < tile_x+800 && x+width-1 >= tile_x && y >= tile_y && y < tile_y+800)
		{
			if (x <= tile_x) return 1;
			else if (y < tile_y+(tile_x+800-x)) return 1;
		}
		else if (x >= tile_x && x < tile_x+800 && y+height-1 >= tile_y && y+height-1 < tile_y+800)
		{
			if (y <= tile_y) return 1;
			else if (y < tile_y+(tile_x+800-x)) return 1;
		}
	}
	
	else if (tile == L_BL)
	{
		if (x >= tile_x && x < tile_x+800 && y+height-1 >= tile_y && y+height-1 < tile_y+800)
		{
			if (y+height-1 >= tile_y+(x-tile_x)) return 1;
		}
		else if (x >= tile_x && x < tile_x+800 && y >= tile_y && y < tile_y+800)
		{
			if (y+height >= tile_y+800) return 1;
			else if (y+height-1 >= tile_y+(x-tile_x)) return 1;
		}
		else if (x+width-1 >= tile_x && x+width-1 < tile_x+800 && y+height-1 >= tile_y && y+height-1 < tile_y+800)
		{
			if (x < tile_x) return 1;
			else if (y+height-1 >= tile_y+(x-tile_x)) return 1;
		}
	}
	
	else if (tile == L_BR)
	{
		if (x+width-1 >= tile_x && x+width-1 < tile_x+800 && y+height-1 >= tile_y && y+height-1 < tile_y+800)
		{
			if (y+height-1 >= tile_y+(tile_x+800-(x+width))) return 1;
		}
		else if (x >= tile_x && x < tile_x+800 && y+height-1 >= tile_y && y+height-1 < tile_y+800)
		{
			if (x+width >= tile_x+800) return 1;
			else if (y+height-1 >= tile_y+(tile_x+800-(x+width))) return 1;
		}
		else if (x+width-1 >= tile_x && x+width-1 < tile_x+800 && y >= tile_y && y < tile_y+800)
		{
			if (y+height >= tile_y+800) return 1;
			else if (y+height-1 >= tile_y+(tile_x+800-(x+width))) return 1;
		}
	}
	return 0;
}

u8 player_shot(Player* p, Shot* shot)
{
	return LBCollides(p->netMessage.shared.x+100,p->netMessage.shared.y+100,1400,1400,shot->shared.x+200,shot->shared.y+200,400,400) &&
		   p->grace_frame == FRAMES_PER_GRACE &&
		   shot->distance > DISTANCE_TO_ARM;
}

u8 turret_shot(Turret* t, Shot* shot)
{
	return LBCollides(t->shared.x,t->shared.y,800,800,shot->shared.x+200,shot->shared.y+200,400,400) && t->lives > 0;
}

u8 collision_detect_boundries(SpriteShared* sprite)
{
	if (sprite->x < 0  || sprite->x + 800 > 24000 ||
	    sprite->y < 2400 || sprite->y + 800 > 22400)
	{
		return 1;
	}
	return 0;
}

void drop_item(int tile_index, const char* map, u8 item_type)
{
	u8 x = tile_index % 30;
	u8 y = 3 + tile_index / 30;
	
	if (level.level_map[tile_index] == L_EMPTY)
	{
		DrawMap2(x, y, map);
		level.level_map[tile_index] = item_type;
	}
	else if (level.level_map[tile_index+1] == L_EMPTY)
	{
		DrawMap2(x+1, y, map);
		level.level_map[tile_index+1] = item_type;
	}
	else if (level.level_map[tile_index+30] == L_EMPTY)
	{
		DrawMap2(x, y+1, map);
		level.level_map[tile_index+30] = item_type;
	}
	else if (level.level_map[tile_index+31] == L_EMPTY)
	{
		DrawMap2(x+1, y+1, map);
		level.level_map[tile_index+31] = item_type;
	}
}

void kill_player(Player* player, u8 hud_x)
{
	u8 x = player->netMessage.shared.x / 800;
	u8 y = player->netMessage.shared.y / 800 - 3;
	int tile_index = (y * 30) + x;

	if (player->has_over_speed)
	{
		SetTile(hud_x+10, 1, 0);
		drop_item(tile_index, map_speed_itm, L_SPEED);
		player->max_speed = MAX_SPEED;
	}
	if (player->has_rocket)
	{
		SetTile(hud_x+11, 1, 0);
		drop_item(tile_index, map_rocket_itm, L_ROCKET);
	}
	player->has_over_speed = false;
	player->has_rocket = false;
	player->flags = player->flags | EXPLODING_FLAG;
}

void get_interesting_tile_indexes_shot(int* tiles, u8 x, u8 y, u8 direction)
{
	int tile_root = (y * 30) + x;
	if (direction == D_UP)
	{
		tiles[0] = tile_root;
		tiles[1] = tiles[0]+1;
	}
	else if (direction == D_RIGHT)
	{
		tiles[0] = tile_root + 1;
		tiles[1] = tiles[0]+30;
	}
	else if (direction == D_DOWN)
	{
		tiles[0] = tile_root + 30;
		tiles[1] = tiles[0]+1;
	}
	else
	{
		tiles[0] = tile_root;
		tiles[1] = tiles[0]+30;
	}
}

void explode_tile(TileAnimations* ta, int tile_index)
{
	SetTile(tile_index % 30, 3 + tile_index / 30, 0);
	if (ta->anims[ta->next_available].tile_index != 0)
	{
		SetTile(ta->anims[ta->next_available].tile_index % 30, 3 + ta->anims[ta->next_available].tile_index / 30, 0);
	}
	ta->anims[ta->next_available].tile_index = tile_index;
	ta->anims[ta->next_available].anim.current_anim = 0;
	ta->next_available++;
	if (ta->next_available == TILE_ANIMATIONS_LENGTH)
	{
		ta->next_available = 0;
	}
}

void richochet(u8 tile_type, SpriteShared* sprite)
{	
	switch (tile_type)
	{
		case L_TL:
			if (sprite->direction == D_UP || sprite->direction == D_DOWN)
				sprite->direction = D_RIGHT;
			else
				sprite->direction = D_DOWN;
			break;
		case L_TR:
			if (sprite->direction == D_UP || sprite->direction == D_DOWN)
				sprite->direction = D_LEFT;
			else
				sprite->direction = D_DOWN;
			break;
		case L_BL:
			if (sprite->direction == D_DOWN || sprite->direction == D_UP)
				sprite->direction = D_RIGHT;
			else
				sprite->direction = D_UP;
			break;
		case L_BR:
			if (sprite->direction == D_DOWN || sprite->direction == D_UP)
				sprite->direction = D_LEFT;
			else
				sprite->direction = D_UP;
			break;
	}
}

void collision_detect_shot(Player* player, Shot* shot)
{	 
	int tiles[2] = {0, 0};
	u8 x = shot->shared.x / 800;
	u8 y = shot->shared.y / 800 - 3;
	u8 tile;
	u8 hud_x;
	Player* p = 0;
    u8 hit = 0;
	u8 brick_index = 0;
	u8 angle_tile = 0;
	
	get_interesting_tile_indexes_shot(tiles, x, y, shot->shared.direction);
	
	/* Level boundries first */
	if (collision_detect_boundries(&shot->shared))
	{
		init_shot_state(shot, shot->shot_type);
		player->active_shots = 0;
		return;
	}
	
	/* Player interaction */
	if (player_shot(&player1, shot) && !(player1.flags & EXPLODING_FLAG) && !is_net_player(&player1))
	{
		p = &player1;
		hud_x = 0;
		player2.netMessage.level_score++;
		player2.netMessage.score++;
		render_score(&player2, 15);
		send_net_message(NETHIT, 0, 0);
	}
	else if (player_shot(&player2, shot) && !(player2.flags & EXPLODING_FLAG) && !(game.boss_fight_status) && !is_net_player(&player2))
	{
		p = &player2;
		hud_x = 15;
		player1.netMessage.level_score++;
		player1.netMessage.score++;
		render_score(&player1, 0);
		send_net_message(NETHIT, 0, 0);
	}
	else if (game.boss_fight_status == BOSS_FIGHT)
	{
		if (turret_shot(&turret1, shot))
		{
			turret1.lives--;
			init_shot_state(shot, shot->shot_type);
			game.boss_fight_player->active_shots = 0;
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_TANK_EXPLODE);
		}
		else if (turret_shot(&turret2, shot))
		{
			turret2.lives--;
			init_shot_state(shot, shot->shot_type);
			game.boss_fight_player->active_shots = 0;
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_TANK_EXPLODE);
		}
	}
	if (p)
	{
		init_shot_state(shot, shot->shot_type);
		player->active_shots = 0;
		kill_player(p, hud_x);
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_TANK_EXPLODE);
		return;
	}
	
	/* Tile interaction */
	for (u8 i = 0; i < 2; i++)
	{
		tile = level.level_map[tiles[i]];
		if (tile == L_EMPTY) continue;
		
		if (solid_directional_tile(tiles[i]) && collides_directional_tile(tiles[i], shot->shared.x+200, shot->shared.y+200,400,400))
		{
			hit = hit | HIT_ANGLE;
			angle_tile = tile;
		}
		else if (tile == L_BRICK && LBCollides(shot->shared.x+200,shot->shared.y+200,400,400,(tiles[i]%30)*800,(tiles[i]/30)*800+2400,800,800))
		{
			hit = hit | HIT_BRICK;
			brick_index = i;
		}
		else if (tile == L_METAL && LBCollides(shot->shared.x+200,shot->shared.y+200,400,400,(tiles[i]%30)*800,(tiles[i]/30)*800+2400,800,800))
        {
		    hit = hit | HIT_METAL;
        }
	}
	
	if (hit & HIT_ANGLE)
	{
		recoil_sprite_fine(player, &shot->shared);
		richochet(angle_tile, &shot->shared);
		shot->rebounds--;
		if (shot->rebounds <= 0)
		{
			init_shot_state(shot, shot->shot_type);
			player->active_shots = 0;
		}
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_METAL);
		//shot->shared.speed = 0;
	}
	else if ((hit & HIT_BRICK) /*&& !is_net_player(player)*/)
	{
		explode_tile(&tile_animations, tiles[brick_index]);
		level.level_map[tiles[brick_index]] = L_EMPTY;
		shot->hit_count--;
		if (shot->hit_count <= 0)
		{
			init_shot_state(shot, shot->shot_type);
			player->active_shots = 0;
		}
		//send_net_message(NETBLOCKHIT, tiles[brick_index] % 30, tiles[brick_index] / 30);
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_BRICK_EXPLODE);
		//shot->shared.speed = 0;
	}
	else if (hit & HIT_METAL)
	{
        init_shot_state(shot, shot->shot_type);
        player->active_shots = 0;
        LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_METAL);
	}
}

void get_interesting_tile_indexes(int* tiles, u8 x, u8 y, u8 direction)
{
	u16 tile_root = (y * 30) + x;
	if (direction == D_UP)
	{
		tiles[0] = tile_root;
		tiles[1] = tiles[0]+1;
		tiles[2] = tiles[0]+2;
	}
	else if (direction == D_RIGHT)
	{
		tiles[0] = tile_root + 2;
		tiles[1] = tiles[0]+30;
		tiles[2] = tiles[0]+60;
	}
	else if (direction == D_DOWN)
	{
		tiles[0] = tile_root + 60;
		tiles[1] = tiles[0]+1;
		tiles[2] = tiles[0]+2;
	}
	else
	{
		tiles[0] = tile_root;
		tiles[1] = tiles[0]+30;
		tiles[2] = tiles[0]+60;
	}
}

void explode_player(Player* player, Player* other_player, u8 hud_x, u8 other_player_hud_x)
{
	if (!(other_player->flags & EXPLODING_FLAG))
	{
		player->netMessage.level_score++;
		player->netMessage.score++;
		render_score(player, hud_x);
		kill_player(other_player, other_player_hud_x);
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_TANK_EXPLODE);
	}
}

void slide(Player* player, u8 collision_tile, int tile)
{
	u16 tile_x = (tile % 30 * 800);
	u16 tile_y = (tile / 30 + 3) * 800;
	if (player->netMessage.shared.direction == D_UP || player->netMessage.shared.direction == D_DOWN)
	{
		if (collision_tile == 0 && ((player->netMessage.shared.x - tile_x) > 400))
			player->netMessage.shared.x = player->netMessage.shared.x / 100 * 100 + 100;
		else if (collision_tile == 2 && ((tile_x - player->netMessage.shared.x) > 1200))
			player->netMessage.shared.x = player->netMessage.shared.x / 100 * 100 - 100;
	}
	else
	{
		if (collision_tile == 0 && ((player->netMessage.shared.y - tile_y) > 400))
			player->netMessage.shared.y = player->netMessage.shared.y / 100 * 100 + 100;
		else if (collision_tile == 2 && ((tile_y - player->netMessage.shared.y) > 1200))
			player->netMessage.shared.y = player->netMessage.shared.y / 100 * 100 - 100;
	}
}

char collision_detect_player(Player* player, u8 hud_x)
{
	int tiles[3] = {0,0,0};
	u8 x = player->netMessage.shared.x / 800;
	u8 y = player->netMessage.shared.y / 800 - 3;
	u8 hit_water = 0;
	char explode = 0;
	u8 collision_tile = 0;
	char collision_count = 0;
	u8 tile_x;
	u8 tile_y;
	
	get_interesting_tile_indexes(tiles, x, y, player->netMessage.shared.direction);
	
	/* Level boundries first */
	if (collision_detect_boundries(&player->netMessage.shared))
	{
		recoil_sprite(&player->netMessage.shared);
		player->netMessage.shared.speed = 0;
		return explode;
	}

	/* Tile interaction */
	for (u8 i = 0; i < 3; i++)
	{
		tile_x = tiles[i] % 30;
		tile_y = 3 + tiles[i] / 30;
		
		if (solid_directional_tile(tiles[i]) && collides_directional_tile(tiles[i], player->netMessage.shared.x, player->netMessage.shared.y, 1600, 1600))
		{
			(player->handle_id == 9) ? recoil_sprite(&player->netMessage.shared) : recoil_sprite_fine(player, &player->netMessage.shared);
			player->netMessage.shared.speed = 0;
		}
		else if (solid_square_tile(tiles[i]) && LBCollides(player->netMessage.shared.x,player->netMessage.shared.y,1600,1600,tile_x*800,tile_y*800,800,800))
		{
			collision_count++;
			collision_tile = i;
			player->netMessage.shared.speed = 0;
		}
		else if (level.level_map[tiles[i]] == L_WATER && LBCollides(player->netMessage.shared.x,player->netMessage.shared.y,1600,1600,tile_x*800,tile_y*800,800,800))
		{
			player->max_speed = WATER_SPEED;
			hit_water = 1;
		}
		else if (level.level_map[tiles[i]] == L_SCOPE && LBCollides(player->netMessage.shared.x,player->netMessage.shared.y,1600,1600,tile_x*800,tile_y*800,800,800))
		{
			player->max_speed = WATER_SPEED;
			hit_water = 1;
		}
		else if (level.level_map[tiles[i]] == L_SPEED && !(player->flags & EXPLODING_FLAG) && !is_net_player(player))
		{
			send_net_message(NETITEMSPEED, tile_x, tile_y);
			level.level_map[tiles[i]] = L_EMPTY;
			player->max_speed = OVER_SPEED;
			player->has_over_speed = true;
			DrawMap2(hud_x+10, 1, map_speed_itm);
			SetTile(tile_x, tile_y, 0);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_ITEM);
		}
		else if (level.level_map[tiles[i]] == L_ROCKET && !(player->flags & EXPLODING_FLAG) && !is_net_player(player))
		{
			send_net_message(NETITEMROCKET, tile_x, tile_y);
			level.level_map[tiles[i]] = L_EMPTY;
			player->has_rocket = true;
			DrawMap2(hud_x+11, 1, map_rocket_itm);
			SetTile(tile_x, tile_y, 0);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_ITEM);
		}
		else if (level.level_map[tiles[i]] == L_EXPLODE && !(player->flags & EXPLODING_FLAG) && !is_net_player(player))
		{
			send_net_message(NETITEMBOMB, tile_x, tile_y);
			level.level_map[tiles[i]] = L_EMPTY;
			SetTile(tile_x, tile_y, 0);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_ITEM);
			explode = 1;
		}
		
		if (!hit_water)
		{
			player->max_speed = MAX_SPEED;
			if (player->has_over_speed) player->max_speed = OVER_SPEED;
		}
	}
	
	// Slide
	if (collision_count) recoil_sprite(&player->netMessage.shared);
	if (collision_count == 1)
	{
		slide(player, collision_tile, tiles[collision_tile]);
	}
	return explode;
}

void load_level_tiles(u8 blank)
{
	u8 x;
	u8 y;
	
	for (int i = 0; i < 30*25; i++)
	{
		x = i % 30;
		y = 3 + i / 30;
		if (blank)
		{
			DrawMap2(x, y, map_tile_none);
		}
		else
		{
			switch (level.level_map[i])
			{
				case L_BRICK: DrawMap2(x, y, map_brick); break;
				case L_METAL: DrawMap2(x, y, map_metal); break;
				case L_TL: DrawMap2(x, y, map_metal_tl); break;
				case L_TR: DrawMap2(x, y, map_metal_tr); break;
				case L_BL: DrawMap2(x, y, map_metal_bl); break;
				case L_BR: DrawMap2(x, y, map_metal_br); break;
				case L_SPEED: DrawMap2(x, y, map_speed_itm); break;
				case L_EXPLODE: DrawMap2(x, y, map_explode_itm); break;
				case L_ROCKET: DrawMap2(x, y, map_rocket_itm); break;
				case L_TURF: DrawMap2(x, y, map_turf); break;
				case L_WATER: DrawMap2(x, y, map_water); break;
				case L_SCOPE: DrawMap2(x, y, map_water); scope_animation.tile_index = i; break;
				case L_FENCE: DrawMap2(x, y, map_fence); break;
				default : SetTile(x, y, 0); break;
			}
		}
	}
}

void prep_player(Player* p, u16 x, u16 y)
{
	p->spawn_x = x;
	p->spawn_y = y;
	p->netMessage.level_score = 0;
	p->has_over_speed = false;
	p->has_rocket = false;
	p->max_speed = MAX_SPEED;
	player_init_shot_state(p);
	player_spawn(p);
}

void load_level(int level_number)
{
    u16 level_start = level_number*30*25;
	u16 x;
	u16 y;

	game.scope_counter = 0;
	init_tile_animations(&tile_animations);
	init_scope_animation(&scope_animation);
	init_sub_animation(&sub_animation);
	game.current_screen = LEVEL;
	clear_sprites();
	game.current_level = level_number;
	for (u16 i = 0; i < 30*25; i++)
	{
		x = (i % 30) * 800;
		y = (i / 30 + 3) * 800;
		level.level_map[i] = pgm_read_byte(&level_data[level_start+i]);
		if (level.level_map[i] == L_P1_SPAWN)
		{
			prep_player(&player1, x, y);
		}
		if (level.level_map[i] == L_P2_SPAWN)
		{
			prep_player(&player2, x, y);
		}
	}
	render_hud(&player1, 0);
	render_hud(&player2, 15);
	render_score(&player1, 0);
	render_score(&player2, 15);
	Print(14, 0, (char*) strVertSep);
	Print(14, 1, (char*) strVertSep);
	Print(14, 2, (char*) strVertSep);
	load_level_tiles(false);
}

void render_boss_fight_scope_load()
{
	if (render_scope(&scope_animation))
	{
		game.boss_fight_status = BOSS_FIGHT_SUB_LOADING;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_ALARM);
	}
}

void render_boss_fight_sub_load()
{
	char *map;
	map = LBGetNextFrameReverse(&(sub_animation.anim));
	DrawMap2(1, 4, (const char*) map);
	if (sub_animation.anim.reversing)
	{
		game.boss_fight_status = BOSS_FIGHT;
		init_turret(&turret1, BOSS_TURRET_1_RIGHT_LIMIT, 7200);
		init_turret(&turret2, BOSS_TURRET_2_RIGHT_LIMIT, 7200);
	}
}

void render_boss_fight_sub_sinking()
{
	char *map;
	map = LBGetNextFrameReverse(&(sub_animation.anim));
	if (sub_animation.anim.current_anim == 0) DrawMap2(1, 4, (const char*) map);
	if (sub_animation.anim.looped)
	{
		game.boss_fight_status = BOSS_FIGHT_WON;
	}
}

void render_boss_turret(Turret* t, char sprite_index)
{
	MoveSprite(sprite_index, t->shared.x / 100, t->shared.y / 100, 1, 1);
}

void render_boss_turret_shot(Turret* t, char sprite_index)
{
	MoveSprite(sprite_index, t->shot[0].shared.x / 100, t->shot[0].shared.y / 100, 1, 1);
}

void update_turret(Turret *t, u16 left_limit, u16 right_limit)
{
	u8 x = t->shared.x / 800;
	u8 y = t->shared.y / 800 - 3;
	int tile_index = (y * 30) + x;
	
	if (t->lives <= 0)
	{
		explode_tile(&tile_animations, tile_index);
		level.level_map[tile_index] = L_EMPTY;
	}
	else if (t->shared.direction == D_LEFT)
	{
		if (t->shared.x < left_limit)
		{
			t->shared.direction = D_RIGHT;
			t->shared.speed = BOSS_TURRET_SPEED;
		}
		else
		{
			t->shared.x -= t->shared.speed / FRAME_TIME_INVERTED;
		}
	}
	else if (t->shared.direction == D_RIGHT)
	{
		if (t->shared.x > right_limit)
		{
			t->shared.direction = D_LEFT;
			t->shared.speed = BOSS_TURRET_SPEED;
		}
		else
		{
			t->shared.x += t->shared.speed / FRAME_TIME_INVERTED;
		}
	}
}

void update_turret_shot(Turret* t, Shot* s)
{	
	if (t->lives <= 0)
	{
		s->active = 0;
		return;
	}
	if (!s->active)
	{
		s->active = 1;
		s->shared.x = t->shared.x+300;
		s->shared.y = t->shared.y+300;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_CANNONBALL);
	}
	s->shared.y += BOSS_TURRET_SHOT_SPEED / FRAME_TIME_INVERTED;
	
	/* Level boundries first */
	if (s->shared.y + 800 > 21600)
	{
		s->active = 0;
		return;
	}
	
	/* Player interaction */	
	if (player_shot(game.boss_fight_player, s) && !(game.boss_fight_player->flags & EXPLODING_FLAG) && !is_net_player(game.boss_fight_player))
	{
		game.boss_fight_player_lives--;
		if (game.boss_fight_player_lives <= 0)
		{
			game.boss_fight_status = BOSS_FIGHT_LOST;
		}
		kill_player(game.boss_fight_player, game.boss_fight_player_hud);
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_TANK_EXPLODE);
		send_net_message(NETTURRETHIT, 0, 0);
	}
}

char* turret_map(Turret* t)
{
	if (t->lives <= 0) return (char*) map_none;
	return (char*) map_sub_turret;
}

char* turret_shot_map(Turret* t)
{
	if (t->lives <= 0) return (char*) map_none;
	return (char*) map_sub_shot;
}

void update_level(JoyPadState* p1, JoyPadState* p2)
{
	char p1_index = 0;
	char p2_index = 0;
	char p1_shot_index = 0;
	char p2_shot_index = 0;
	char t1_index = 0;
	char t2_index = 0;
	char t1_shot_index = 0;
	char t2_shot_index = 0;
	u16 held = 0;

	if (game.paused)
	{
		// Render
		LBHideAllSprites();
		DrawMap2(8, 12, (const char*) map_pause);
		Print(12, 13, (char*) strPaused);
		Print(11, 14, (char*) strExit);
		
		// Update
		update_player(p1, &player1);
		update_player(p2, &player2);
	}
	else if (game.boss_fight_status == BOSS_FIGHT_SCOPE_LOADING)
	{
		// Render
		render_boss_fight_scope_load();
		p2_index = tank_map(game.boss_fight_player, p1_index);
		MapSprite2(p2_index, map_tank_blank, 0);
		p1_shot_index = p2_index + 4;
		p2_shot_index = shot_map(game.boss_fight_player, p1_shot_index);
		MapSprite2(p2_shot_index, map_none, 0);
		shot_map(game.boss_fight_player, p1_shot_index);
		render_player(game.boss_fight_player, p1_index);
		render_shot(game.boss_fight_player, p1_shot_index);
		render_shot(&player2, p2_shot_index);
		render_tile_explosions(&tile_animations);
		
		// Update
		update_player(game.boss_fight_joypad, game.boss_fight_player);
		collision_detect_player(game.boss_fight_player, game.boss_fight_player_hud);
		
	}
	else if (game.boss_fight_status == BOSS_FIGHT_SUB_LOADING)
	{
		// Render
		render_boss_fight_sub_load();
		p2_index = tank_map(game.boss_fight_player, p1_index);
		MapSprite2(p2_index, map_tank_blank, 0);
		p1_shot_index = p2_index + 4;
		p2_shot_index = shot_map(game.boss_fight_player, p1_shot_index);
		MapSprite2(p2_shot_index, map_none, 0);
		shot_map(game.boss_fight_player, p1_shot_index);
		render_player(game.boss_fight_player, p1_index);
		render_shot(game.boss_fight_player, p1_shot_index);
		render_shot(&player2, p2_shot_index);
		render_tile_explosions(&tile_animations);
		
		// Update
		update_player(game.boss_fight_joypad, game.boss_fight_player);
		collision_detect_player(game.boss_fight_player, game.boss_fight_player_hud);
	}
	else if (game.boss_fight_status == BOSS_FIGHT)
	{
		if ((turret1.lives <= 0) && (turret2.lives <= 0))
		{
			game.boss_fight_status = BOSS_FIGHT_SUB_SINKING;
		}
		
		
		// Render
		p1_shot_index = tank_map(game.boss_fight_player, p1_index);
		t1_index = shot_map(game.boss_fight_player, p1_shot_index);
		t1_shot_index = t1_index+1;
		t2_index = t1_index+2;
		t2_shot_index = t1_index+3;
		MapSprite2(t1_index, turret_map(&turret1), 0);
		MapSprite2(t1_shot_index, turret_shot_map(&turret1), 0);
		MapSprite2(t2_index, turret_map(&turret2), 0);
		MapSprite2(t2_shot_index, turret_shot_map(&turret2), 0);
		
		render_player(game.boss_fight_player, p1_index);
		render_shot(game.boss_fight_player, p1_shot_index);
		render_tile_explosions(&tile_animations);
		render_boss_turret(&turret1, t1_index);
		render_boss_turret_shot(&turret1, t1_shot_index);
		render_boss_turret(&turret2, t2_index);
		render_boss_turret_shot(&turret2, t2_shot_index);
		
		// Update
		update_turret(&turret1, BOSS_TURRET_1_LEFT_LIMIT, BOSS_TURRET_1_RIGHT_LIMIT);
		update_turret(&turret2, BOSS_TURRET_2_LEFT_LIMIT, BOSS_TURRET_2_RIGHT_LIMIT);
		update_turret_shot(&turret1, &turret1.shot[0]);
		update_turret_shot(&turret2, &turret2.shot[0]);
		update_player(game.boss_fight_joypad, game.boss_fight_player);
		collision_detect_player(game.boss_fight_player, game.boss_fight_player_hud);
	}
	else if (game.boss_fight_status == BOSS_FIGHT_SUB_SINKING)
	{
		// Render
		render_boss_fight_sub_sinking();
		p2_index = tank_map(game.boss_fight_player, p1_index);
		MapSprite2(p2_index, map_tank_blank, 0);
		p1_shot_index = p2_index + 4;
		p2_shot_index = shot_map(game.boss_fight_player, p1_shot_index);
		MapSprite2(p2_shot_index, map_none, 0);
		shot_map(game.boss_fight_player, p1_shot_index);
		render_player(game.boss_fight_player, p1_index);
		render_shot(game.boss_fight_player, p1_shot_index);
		render_shot(&player2, p2_shot_index);
		render_tile_explosions(&tile_animations);
		
		// Update
		update_player(game.boss_fight_joypad, game.boss_fight_player);
		collision_detect_player(game.boss_fight_player, game.boss_fight_player_hud);
		if (game.boss_fight_status != BOSS_FIGHT_SUB_SINKING)
		{
			resolve_scoring();
		}
	}
	else if (game.boss_fight_status == BOSS_FIGHT_LOST)
	{
		resolve_scoring();
	}
	else if (game.boss_fight_status == 0)
	{
		p2_index = tank_map(&player1, p1_index);
		p1_shot_index = tank_map(&player2, p2_index);
		p2_shot_index = shot_map(&player1, p1_shot_index);
		shot_map(&player2, p2_shot_index);
		render_player(&player1, p1_index);
		render_player(&player2, p2_index);
		render_shot(&player1, p1_shot_index);
		render_shot(&player2, p2_shot_index);
		render_tile_explosions(&tile_animations);
		if (game.scope_counter > SCOPE_REVEAL && scope_animation.tile_index > 0)
		{
			if (render_scope(&scope_animation)) game.scope_counter = 0;
		}
		game.scope_counter++;
		
		// Update
		update_player(p1, &player1);
		update_player(p2, &player2);
		resolve_scoring();
		if (collision_detect_player(&player1, 0)) explode_player(&player1, &player2, 0, 15);
		if (collision_detect_player(&player2, 15)) explode_player(&player2, &player1, 15, 0);
	}
	
	if (game.selection == CPUVCPU) 
	{
		game.demo_counter++;
		held = ReadJoypad(0);
		if (ReadJoypad(0) || ReadJoypad(1) || (game.demo_counter >= DEMO_LENGTH))
		{
#if JAMMA
			handle_coin_insert();
			game.demo_counter = 0;
			if (credits_available() > 0) {
				game.demo_counter = 0;
				fade_through();
				init_game_state();
				load_splash();
			} else {
				exit_game();
			}
#else
			game.demo_counter = 0;
			fade_through();
			init_game_state();
			load_splash();
#endif
		}
	}
}

void load_splash()
{
	game.current_screen = SPLASH;
	clear_sprites();
#if JAMMA
    if (credits_available() == 1) {
        Print(7, 13, (char*) str1Player);
    } else if (credits_available()) {
        Print(7, 13, (char*) str1Player);
		Print(7, 14, (char*) str2Player);
    } else {
		Print(9, 13, (char*) strInsertCoin);
	}
	Print(5, 22, (char*) strCopyright);
	Print(18, 25, (char*) strCreditCount);
    LBPrintByte(27, 25, credits_available(), false);
#else
	if (wifi_status == WIFI_OK)
	{
		cleanupWifi();
	}
	Print(7, 13, (char*) str1Player);
	Print(7, 14, (char*) str2Player);
	if (wifi_status == WIFI_OK) {
		Print(7, 15, (char*) strHostNetGame);
		Print(7, 16, (char*) strJoinNetGame);
	}
	Print(7, 17, (char*) strHighscores);
	Print(5, 26, (char*) strCopyright);
	MapSprite2(0, map_right_arrow, 0);
#endif
	DrawMap2(4, 5, (const char*) map_splash);
}

char select_pressed(JoyPadState* p)
{
#if JAMMA
	if (p == &player2.netMessage.joyPadState) return player1.netMessage.joyPadState.pressed & BTN_SELECT;
	return p->pressed & BTN_START;
#else
	return (p->pressed & BTN_A) || (p->pressed & BTN_START);
#endif
}

void update_splash(JoyPadState* p1, JoyPadState* p2)
/*
 * Splash or title screen
 */
{		// Render
#if JAMMA
	
	// Update
	Print(18, 25, (char*) strCreditCount);
    LBPrintByte(27, 25, credits_available(), false);
	if (credits_available() == 1) {
        Print(7, 13, (char*) str1Player);
    } else if (credits_available()) {
        Print(7, 13, (char*) str1Player);
		Print(7, 14, (char*) str2Player);
    } else {
		Print(9, 13, (char*) strInsertCoin);
	}
	if (p1->pressed) game.demo_counter = 0;
	if (select_pressed(p1) && credits_available())
	{
		acquire_credit();
		game.selection = PVCPU;
		game.demo_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_eeprom(&handles);
		load_handle_select();
		return;
	}
	else if (select_pressed(p2) && credits_available() > 1)
	{
		acquire_credit();
		acquire_credit();
		game.selection = PVP;
		game.demo_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_eeprom(&handles);
		load_handle_select();
	}
	else if (game.demo_counter >= DEMO_WAIT && !credits_available())
	{
		game.demo_counter = 0;
		if (game.demo_choice % 2 == 0)
		{
			game.selection = CPUVCPU;
			player1.handle_id = 9;
			memcpy(player1.handle, &handles.data[9*3], 3);
			player2.handle_id = 9;
			memcpy(player2.handle, &handles.data[9*3], 3);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
			clear_sprites();
			fade_through();
			level_transition(LBRandom(0, 10));
		}
		else
		{
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
			fade_through();
			load_eeprom(&scores);
			load_tank_rank();
		}
		game.demo_choice++;
		return;
		
	}
	game.demo_counter++;
#else
	switch (game.selection)
	{
		case PVCPU:
			MoveSprite(0, 6*8, 13*8, 1, 1);
			break;
		case PVP:
			MoveSprite(0, 6*8, 14*8, 1, 1);
			break;
		case HOSTNETGAME:
			MoveSprite(0, 6*8, 15*8, 1, 1);
			break;
		case JOINNETGAME:
			MoveSprite(0, 6*8, 16*8, 1, 1);
			break;
		case TR:
			MoveSprite(0, 6*8, 17*8, 1, 1);
			break;
	}
	Print(6, 21, (char*) strSelectHandle);

	// Update
	if (p1->pressed) game.demo_counter = 0;
	
	if (p1->pressed & BTN_UP)
	{
		game.selection--;
		if (game.selection == JOINNETGAME && wifi_status != WIFI_OK) game.selection -= 2;
		if (game.selection < PVCPU) game.selection = PVCPU;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if (p1->pressed & BTN_DOWN)
	{
		game.selection++;
		if (game.selection == HOSTNETGAME && wifi_status != WIFI_OK) game.selection += 2;
		if (game.selection > TR) game.selection = TR;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if (select_pressed(p1) && ((game.selection == PVCPU) || (game.selection == PVP)))
	{
		game.demo_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_eeprom(&handles);
		load_handle_select();
		return;
	}
	else if (select_pressed(p1) && (game.selection == HOSTNETGAME))
	{
		game.demo_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_host_net_game();
		return;
	}
	else if (select_pressed(p1) && (game.selection == JOINNETGAME))
	{
		game.demo_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_join_net_game();
		return;
	}
	else if (select_pressed(p1) && (game.selection == TR))
	{
		game.demo_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_eeprom(&scores);
		load_tank_rank();
		return;
	}
	else if (game.demo_counter >= DEMO_WAIT)
	{
		game.demo_counter = 0;
		if (game.demo_choice % 2 == 0)
		{
			game.selection = CPUVCPU;
			player1.handle_id = 9;
			memcpy(player1.handle, &handles.data[9*3], 3);
			player2.handle_id = 9;
			memcpy(player2.handle, &handles.data[9*3], 3);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
			clear_sprites();
			fade_through();
			level_transition(LBRandom(0, 10));
		}
		else
		{
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
			fade_through();
			load_eeprom(&scores);
			load_tank_rank();
		}
		game.demo_choice++;
		return;
		
	}
	game.demo_counter++;
#endif
}

void load_tank_rank()
{
	u8 y = 7;
	u8 rank = 1;
	
	game.current_screen = TANK_RANK;
	clear_sprites();
	DrawMap2(7, 1, map_green_tank);
	DrawMap2(20, 1, map_blue_tank);
	Print(10, 2, (char*) strHighscores);
	for (u8 i = 0; i < 25; i += 5)
	{
		PrintByte(2, y, rank, false);
		PrintChar(3, y, '.');
		LBPrintStr(5, y, &handles.data[scores.data[i]*3], 3);
		Print(9, y, (char*) strOwns);
		LBPrintStr(14, y, &handles.data[scores.data[i+1]*3], 3);
		Print(18, y, (char*) strBy);
		PrintByte(23, y, scores.data[i+2] ,true);
		PrintChar(24, y, '-');
		PrintByte(27, y, scores.data[i+3] ,true);
		if (scores.data[i+4])
			PrintChar(29, y, '*');
		else
			PrintChar(29, y, ' ');
		y += 3;
		rank += 1;
	}
#if JAMMA
#else
	Print(3, 22, (char*) strReset);
	Print(10, 24, (char*) strCancelHandle);
#endif
}

void update_tank_rank(JoyPadState* p1)
{
#if JAMMA
	// Update
	if (ReadJoypad(0) ||ReadJoypad(1))
	{
		game.tank_rank_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_splash();
	}
	if ((p1->held & BTN_SL) && (p1->held_cycles == 255))
	{
		game.tank_rank_counter = 0;
	    LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	    init_scores(&scores);
	    init_handles(&handles);
	    save_eeprom(&scores);
	    save_eeprom(&handles);
	    load_tank_rank();
	}
	
	if (game.tank_rank_counter > TANK_RANK_LENGTH)
	{
		game.tank_rank_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_splash();
	}
	game.tank_rank_counter++;
#else
	// Update
	if (p1->pressed & BTN_X)
	{
		game.tank_rank_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_splash();
	}
	if ((p1->held & BTN_SL) && (p1->held_cycles == 255))
	{
		game.tank_rank_counter = 0;
	    LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	    init_scores(&scores);
	    init_handles(&handles);
	    save_eeprom(&scores);
	    save_eeprom(&handles);
	    load_tank_rank();
	}
	
	if (game.tank_rank_counter > TANK_RANK_LENGTH)
	{
		game.tank_rank_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_splash();
	}
	game.tank_rank_counter++;
#endif
}


void _handle_select_helper(HandleSelectState* ps, JoyPadState* p, Player* player)
{	
	if ((p->pressed & BTN_UP) && (ps->select_state == SELECTING))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		ps->handle_id--;
		if (ps->handle_id < 0) ps->handle_id = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == SELECTING))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		ps->handle_id++;
		if (ps->handle_id > 8) ps->handle_id = 8;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if (select_pressed(p) && (ps->select_state == SELECTING))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		ps->select_state = EDITING;
		memcpy(ps->handle, &handles.data[ps->handle_id*3], 3);
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if ((p->pressed & BTN_RIGHT) && (ps->select_state == EDITING))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		ps->char_index++;
		if (ps->char_index > 2) ps->char_index = 2;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if ((p->pressed & BTN_LEFT) && (ps->select_state == EDITING))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		ps->char_index--;
		if (ps->char_index < 0) ps->char_index = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if ((p->pressed & BTN_UP) && (ps->select_state == EDITING))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		ps->handle[(u8) ps->char_index]--;
		if (ps->handle[(u8) ps->char_index] < 'A') ps->handle[(u8) ps->char_index] = 'Z';
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == EDITING))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		ps->handle[(u8) ps->char_index]++;
		if (ps->handle[(u8) ps->char_index] > 'Z') ps->handle[(u8) ps->char_index] = 'A';
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if (select_pressed(p) && (ps->select_state == EDITING))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		player->handle_id = ps->handle_id;
		memcpy(player->handle, ps->handle, 3);
		memcpy(&handles.data[ps->handle_id*3], ps->handle, 3);
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		save_eeprom(&handles);
		ps->select_state = CONFIRMED;
	}
#if JAMMA
#else
	else if ((p->pressed & BTN_X) && (ps->select_state == EDITING))
	{
		ps->select_state = SELECTING;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		send_smart_net_message(player, p, NETHANDLESELECT);
	}
	else if ((p->pressed & BTN_X) && (ps->select_state == CONFIRMED))
	{
		ps->select_state = EDITING;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		send_smart_net_message(player, p, NETHANDLESELECT);
	}
	else if ((p->pressed & BTN_X))
	{
		send_smart_net_message(player, p, NETHANDLESELECT);
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_splash();
	}
#endif
}

void _handle_select_render_helper(HandleSelectState* ps, JoyPadState* p, u8 x_offset, u8 idx)
{
	u8 tmp[3] = {' ', ' ', ' '};
	if (ps->select_state == SELECTING)
	{
		MapSprite2(idx, map_right_arrow, 0);
		MapSprite2(idx+1, map_none, 0);
		MoveSprite(idx, x_offset*8, (8 + ps->handle_id)*8, 1, 1);
	}
	else if (ps->select_state == EDITING)
	{
		MapSprite2(idx, map_down_arrow, 0);
		MapSprite2(idx+1, map_up_arrow, 0);
		MoveSprite(idx, (x_offset+5+ps->char_index)*8, (8 + ps->handle_id - 1)*8, 1, 1);
		MoveSprite(idx+1, (x_offset+5+ps->char_index)*8, (8 + ps->handle_id + 1)*8, 1, 1);
		memcpy(tmp, ps->handle, 3);
	}
	else if (ps->select_state == CONFIRMED)
	{
		PrintChar(x_offset+6, 5, '(');
		LBPrintStr(x_offset+7, 5, ps->handle, 3);
		PrintChar(x_offset+10, 5, ')');
		MapSprite2(idx, map_none, 0);
		MapSprite2(idx+1, map_none, 0);
	}
	LBPrintStr(x_offset+5, (8 + ps->handle_id), tmp, 3);
}

void load_handle_select()
{
	p1s.select_state = SELECTING;
	p2s.select_state = SELECTING;
	p1s.handle_id = 0;
	p2s.handle_id = 0;
	p1s.char_index = 0;
	p2s.char_index = 0;
	game.current_screen = HANDLE_SELECT;
	clear_sprites();
	DrawMap2(3, 4, map_green_tank);
	DrawMap2(20, 4, map_blue_tank);
	Print(9, 1, (char*) strHandlesTitle);
	Print(6, 5, (char*) strPlayer1);
	Print(23, 5, (char*) strPlayer2);
	for (int i = 0; i < 27; i += 1)
	{
		PrintChar((i % 3) + 3, 8 + (i / 3), handles.data[i]);
		PrintChar(20 + (i % 3), 8 + (i / 3), handles.data[i]);
	}
#if JAMMA
	Print(6, 22, (char*) strSelectHandle);
	Print(6, 24, (char*) strChangeHandle);
#else
	Print(5, 21, (char*) strSelectHandle);
	Print(5, 22, (char*) strConfirmHandle);
	Print(5, 23, (char*) strCancelHandle);
	Print(5, 24, (char*) strChangeHandle);
#endif
	clearNetBuffers();
}

void update_handle_select(JoyPadState* p1, JoyPadState* p2)
{
	u8 start_game = 0;

	// Render
	_handle_select_render_helper(&p1s, p1, 2, 6);
	if (game.selection != PVCPU && game.selection != CPUVCPU)
	{
		_handle_select_render_helper(&p2s, p2, 19, 8);
	}

	// Update
	_handle_select_helper(&p1s, p1, &player1);
	if (p1s.select_state == CONFIRMED) start_game = 1;
	if (game.selection != PVCPU && game.selection != CPUVCPU)
	{
		_handle_select_helper(&p2s, p2, &player2);
		if (p2s.select_state != CONFIRMED) start_game = 0;
	}
	if (start_game)
	{
		if (game.selection == PVCPU)
		{
			player2.handle_id = 9;
			memcpy(player2.handle, &handles.data[9*3], 3);
		}
		level_transition(0);
	}
}

#if JAMMA
#else

void load_host_net_game()
{
	game.current_screen = HOST_NET_GAME;
	clear_sprites();
	if (hostNetGame((char*)gameId) == WIFI_OK)
	{
		Print(5, 1, (char*) strShareGameId);
		LBPrintStr(10, 10, gameId, 8);
		Print(2, 18, (char*) strWaitingForNetOppenent);
		DrawMap2(7, 10, map_green_tank);
		DrawMap2(19, 10, map_blue_tank);
	}
	else
	{
		Print(7, 10, (char*) strNetworkError);
	}
	Print(9, 23, (char*) strCancelHandle);
}

void update_host_net_game(JoyPadState* p1)
{
	if (p1->pressed & BTN_X)
	{
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_splash();
	} 
	else if (player2.netMessage.code == NETJOINED)
	{
		game.demo_counter = 0;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_eeprom(&handles);
		load_handle_select();
	}
}

void load_join_net_game()
{
	game.current_screen = JOIN_NET_GAME;
	clear_sprites();
	Print(5, 1, (char*) strEnterGameId);
	LBPrintStr(10, 10, gameId, 8);
	DrawMap2(7, 10, map_green_tank);
	DrawMap2(19, 10, map_blue_tank);
	Print(5, 22, (char*) strConfirmHandle);
	Print(9, 23, (char*) strCancelHandle);
	gameIdIndex = 2;
}

void update_join_net_game(JoyPadState* p1)
{
	MapSprite2(0, map_down_arrow, 0);
	MapSprite2(1, map_up_arrow, 0);
	MoveSprite(0, 8*10 + gameIdIndex*8, 9*8, 1, 1);
	MoveSprite(1, 8*10 + gameIdIndex*8, 11*8, 1, 1);
	LBPrintStr(10, 10, (u8*) gameId, 8);
		
	if (p1->pressed & BTN_X)
	{
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
		fade_through();
		load_splash();
	}
	else if (select_pressed(p1))
	{
		Print(7, 18, (char*) strConnecting);
		if (joinNetGame((char*)gameId) == WIFI_OK)
		{
			player2.netMessage.code = NETJOINED;
			sendNetMessage(&player2.netMessage);
			game.demo_counter = 0;
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
			fade_through();
			load_eeprom(&handles);
			load_handle_select();
		}
		else
		{
			Print(7, 18, (char*) strNetworkError);
		}
	}
	else if ((p1->pressed & BTN_UP))
	{
		gameId[gameIdIndex]--;
		if ((gameId[gameIdIndex] < 'A') && (gameId[gameIdIndex] > '9')) gameId[gameIdIndex] = '9';
		if (gameId[gameIdIndex] < '0') gameId[gameIdIndex] = 'Z';
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if ((p1->pressed & BTN_DOWN))
	{
		gameId[gameIdIndex]++;
		if ((gameId[gameIdIndex] > '9') && (gameId[gameIdIndex] < 'A')) gameId[gameIdIndex] = 'A';
		if (gameId[gameIdIndex] > 'Z') gameId[gameIdIndex] = '0';
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if ((p1->pressed & BTN_RIGHT))
	{
		gameIdIndex++;
		if (gameIdIndex > 7) gameIdIndex = 7;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
	else if ((p1->pressed & BTN_LEFT))
	{
		gameIdIndex--;
		if (gameIdIndex < 2) gameIdIndex= 2;
		LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_NAVIGATE);
	}
}
#endif

u16 button_map(u16 number)
{
	if (number == 0) return BTN_UP;
	if (number == 1) return BTN_DOWN;
	if (number == 2) return BTN_LEFT;
	if (number == 3) return BTN_RIGHT;
	return BTN_UP;
}

char crash_and_turn(char current_x, char current_y, u8 recoiled, Player* player, JoyPadState* p)
/* 
 * Move in the direction of the goal. Move along the wall using left hand rule when hitting one
 */
{	
	if (player->feeling_my_way)
	{
		if ((p->held & BTN_UP) && !(solid_tile(current_y * 30 + current_x - 1) || solid_tile((current_y+1) * 30 + current_x - 1) || solid_tile((current_y+2) * 30 + current_x - 1)))
		{
			p->held = BTN_LEFT;
			recoil_sprite(&player->netMessage.shared);
			recoiled = 0;
		}
		else if ((p->held & BTN_LEFT) && !(solid_tile((current_y+2) * 30 + current_x) || solid_tile((current_y+2) * 30 + current_x+1) || solid_tile((current_y+2) * 30 + current_x+2)))
		{
			p->held = BTN_DOWN;
			recoil_sprite(&player->netMessage.shared);
			recoiled = 0;
		}
		else if ((p->held & BTN_DOWN) && !(solid_tile((current_y) * 30 + current_x+2) || solid_tile((current_y+1) * 30 + current_x+2) || solid_tile((current_y+2) * 30 + current_x+2)))
		{
			p->held = BTN_RIGHT;
			recoil_sprite(&player->netMessage.shared);
			recoiled = 0;
		}
		else if ((p->held & BTN_RIGHT) && !(solid_tile((current_y-1) * 30 + current_x) || solid_tile((current_y-1) * 30 + current_x+1) || solid_tile((current_y-1) * 30 + current_x+2)))
		{
			p->held = BTN_UP;
			recoil_sprite(&player->netMessage.shared);
			recoiled = 0;
		}
		if (player->goal_direction & p->held)
		{
			player->feeling_my_way = 0;
			recoiled = 0;
		}
	}
	if (recoiled)
	{
		if (p->held & BTN_LEFT)
		{
			p->held = BTN_UP;
			player->feeling_my_way = 1;
		}
		else if (p->held & BTN_UP)
		{
			p->held = BTN_RIGHT;
			player->feeling_my_way = 1;
		}
		else if (p->held & BTN_RIGHT)
		{
			p->held = BTN_DOWN;
			player->feeling_my_way = 1;
		}
		else if (p->held & BTN_DOWN)
		{
			p->held = BTN_LEFT;
			player->feeling_my_way = 1;
		}
	}

	if ((player->goal_direction == BTN_UP || player->goal_direction == BTN_DOWN) && current_y == player->goal) return 1;
	if ((player->goal_direction == BTN_LEFT || player->goal_direction == BTN_RIGHT) && current_x == player->goal) return 1;
	
	return 0;
}

u16 get_cpu_goal_direction(Player* player, char distance_x, char distance_y)
{
	char abs_distance_x = (distance_x < 0) ? -distance_x : distance_x;
	char abs_distance_y = (distance_y < 0) ? -distance_y : distance_y;
	u16 direction = BTN_UP;
	
	if (player->tank_tactic == TACTIC_TANK_ATTACK)
	{
		if (abs_distance_x > abs_distance_y)
		{
			direction = BTN_LEFT;
			if (distance_x > 0) direction = BTN_RIGHT;
		}
		else
		{
			direction = BTN_UP;
			if (distance_y > 0) direction = BTN_DOWN;
		}
	}
	else
	{
		if (abs_distance_x > abs_distance_y)
		{
			direction = BTN_RIGHT;
			if (distance_x > 0) direction = BTN_LEFT;
		}
		else
		{
			direction = BTN_DOWN;
			if (distance_y > 0) direction = BTN_UP;
		}
	}
	
	return direction;
}

void get_cpu_joypad_state(Player* player, Player* other_player, JoyPadState* p)
{
	// Update joy pad state artificially for a CPU player using crash and turn pathfinding and custom
	// strategies.
	char moved = 1;
	char goal_x;
	char goal_y;
	char distance_x;
	char distance_y;
	char player_x;
	char player_y;
	
	goal_x = other_player->netMessage.shared.x / 800;
	goal_y = other_player->netMessage.shared.y / 800 - 3;
	player_x = player->netMessage.shared.x / 800;
	player_y =  player->netMessage.shared.y / 800 - 3;
	distance_x = goal_x - player_x;
	distance_y = goal_y - player_y;
	
	if (player->grace_frame == 0)
	{
		p->held = 0;
		return;
	}
	
	// Shot
	if (shoot_pressed(p))
	{
		p->pressed = 0;
	}
	if (global_frame_counter % DEFAULT_FRAMES_PER_SHOT == 0 && player->grace_frame > 50)
	{
		p->pressed = BTN_B;
	}
		
	// Determine goal
	if ((global_frame_counter % DEFAULT_FRAMES_PER_GOAL == 0) || player->grace_frame == 10 || player->goal_reached)
	{
		player->goal_reached = 0;
		player->feeling_my_way = 0;
		
		if (distance_x >= -2 && distance_x <= 2 && distance_y >= -2 && distance_y <= 2)
		{
			// Dont get too close
			player->goal_direction = button_map(LBRandom(0, 4));
			player->goal = LBRandom(5, 18);
		}
		else
		{
			player->goal_direction = get_cpu_goal_direction(player, distance_x, distance_y);
			player->goal = goal_x;
			if (player->goal_direction == BTN_UP || player->goal_direction == BTN_DOWN) player->goal = goal_y;
		}
		p->held = player->goal_direction;
	}
	
	// Monitor movement
	if (player->netMessage.shared.x != player->old_x)
		player->deadlock_count_x = 0;
	else 
		player->deadlock_count_x++;
	if (player->netMessage.shared.y != player->old_y)
		player->deadlock_count_y = 0;
	else
		player->deadlock_count_y++;
	player->old_x = player->netMessage.shared.x;
	player->old_y = player->netMessage.shared.y;
	
	// Break tactical deadlock
	if (player->deadlock_count_x >= FRAMES_PER_DEADLOCK)
	{
		p->held = button_map(LBRandom(2, 4));
		player->deadlock_count_x = 0;
	}
	else if (player->deadlock_count_y >= FRAMES_PER_DEADLOCK)
	{
		p->held = button_map(LBRandom(0, 2));
		player->deadlock_count_y = 0;
	}
	else player->goal_reached = crash_and_turn(player->netMessage.shared.x / 800, player->netMessage.shared.y / 800 - 3, player->netMessage.shared.recoiled, player, p);
	
	// Re-act to player shot
	if (player->shot_tactic == TACTIC_SHOT_EVADE && other_player->old_active_shots < other_player->active_shots)
	{
		if (other_player->netMessage.shared.y < player->netMessage.shared.y && other_player->netMessage.shared.x < player->netMessage.shared.x)
		{
			if (other_player->netMessage.shared.direction == D_DOWN && player->netMessage.shared.direction == D_LEFT)
			{
				p->held = BTN_RIGHT;
				player->goal_reached = 0;
				player->feeling_my_way = 0;
			}
			if (other_player->netMessage.shared.direction == D_RIGHT && player->netMessage.shared.direction == D_UP)
			{
				player->goal_reached = 0;
				player->feeling_my_way = 0;
				p->held = BTN_DOWN;
			}
		}
		else if (other_player->netMessage.shared.y < player->netMessage.shared.y && other_player->netMessage.shared.x > player->netMessage.shared.x)
		{
			if (other_player->netMessage.shared.direction == D_DOWN && player->netMessage.shared.direction == D_RIGHT)
			{
				player->goal_reached = 0;
				player->feeling_my_way = 0;
				p->held = BTN_LEFT;
			}
			if (other_player->netMessage.shared.direction == D_LEFT && player->netMessage.shared.direction == D_UP)
			{
				player->goal_reached = 0;
				player->feeling_my_way = 0;
				p->held = BTN_DOWN;
			}
		}
		else if (other_player->netMessage.shared.y > player->netMessage.shared.y && other_player->netMessage.shared.x < player->netMessage.shared.x)
		{
			if (other_player->netMessage.shared.direction == D_UP && player->netMessage.shared.direction == D_LEFT)
			{
				player->goal_reached = 0;
				player->feeling_my_way = 0;
				p->held = BTN_RIGHT;
			}
			if (other_player->netMessage.shared.direction == D_RIGHT && player->netMessage.shared.direction == D_DOWN)
			{
				player->goal_reached = 0;
				player->feeling_my_way = 0;
				p->held = BTN_UP;
			}
		}
		else if (other_player->netMessage.shared.y > player->netMessage.shared.y && other_player->netMessage.shared.x > player->netMessage.shared.x)
		{
			if (other_player->netMessage.shared.direction == D_UP && player->netMessage.shared.direction == D_RIGHT)
			{
				player->goal_reached = 0;
				player->feeling_my_way = 0;
				p->held = BTN_LEFT;
			}
			if (other_player->netMessage.shared.direction == D_LEFT && player->netMessage.shared.direction == D_DOWN){
				player->goal_reached = 0;
				player->feeling_my_way = 0;
				p->held = BTN_UP;
			}
		}
	}
}
void stream_text_middle(const char* dialogue, u8 y, u16 delay)
{
	u8 x, ln, c;
	
	while (pgm_read_byte(dialogue) != '#')
	{
		ln = strnlen_P(dialogue, 255);
		x = 15 - ln / 2;
		while ((c = pgm_read_byte(dialogue++)))
		{
#if JAMMA
			handle_coin_insert();
#endif
			LBPrintStr(x++, y, &c, 1);
			LBWaitUs(delay);
		}
		y++;
	}
}

void load_credits()
{
	fade_through();
	stream_text_middle((const char*) strCredits, 5, 100);
#if JAMMA
	wifi_status = WIFI_TIMEOUT;
#else
	wifi_status = activateNet();
#endif
	LBWaitSeconds(4);
	fade_through();
}

#if JAMMA
void read_dip_switches() {
    scores.id = EEPROM_DIP_SWITCH_ID;
    load_eeprom(&scores);
    extract_dip_switches(scores.data[0]);
} 
#endif


void send_smart_net_message(Player* player, JoyPadState* p, u8 code)
{
	if (game.selection == HOSTNETGAME && player == &player1)
	{
		send_net_message(code, 0, 0);
	}
	else if (game.selection == JOINNETGAME && player == &player2)
	{
		send_net_message(code, 0, 0);
	}
}

void send_net_message(u8 code, u8 object_pos_x, u8 object_pos_y)
{	
	NetMessage* netMessage = &player1.netMessage;
	
	if (game.selection != HOSTNETGAME && game.selection != JOINNETGAME) return;
	if (game.selection == JOINNETGAME)
	{
		netMessage = &player2.netMessage;
	}
	netMessage->code = code;
	netMessage->object_pos_x = object_pos_x;
	netMessage->object_pos_y = object_pos_y;
	sendNetMessage(netMessage);
}

void get_net_message()
{
	Player* player = &player2;
	JoyPadState* state = &player2.netMessage.joyPadState;
	NetMessage* netMessage = &player2.netMessage;
	Player* otherPlayer = &player1;
	u8 playerHudX = 15;
	u8 otherPlayerHudX = 0;
	if (game.selection != HOSTNETGAME && game.selection != JOINNETGAME) return;
	if (game.selection == JOINNETGAME)
	{
		player = &player1;
		state = &player1.netMessage.joyPadState;
		netMessage = &player1.netMessage;
		otherPlayer = &player2;
		playerHudX = 0;
		otherPlayerHudX = 15;
	}
	netMessage->code = NETNODATA;
	
	if (getNetMessage(netMessage) != WIFI_NODATA)
	{
		// Act on message code
		if (netMessage->code == NETHIT)
		{
			init_shot_state(&otherPlayer->shot[0], otherPlayer->shot[0].shot_type);
			otherPlayer->active_shots = 0;
			otherPlayer->netMessage.level_score++;
			otherPlayer->netMessage.score++;
			render_score(otherPlayer, otherPlayerHudX);
			kill_player(player, playerHudX);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_TANK_EXPLODE);
		}
		else if (netMessage->code == NETTURRETHIT)
		{
			game.boss_fight_player_lives--;
			if (game.boss_fight_player_lives <= 0)
			{
				game.boss_fight_status = BOSS_FIGHT_LOST;
			}
			kill_player(game.boss_fight_player, game.boss_fight_player_hud);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_TANK_EXPLODE);
		}
		else if (netMessage->code == NETITEMSPEED)
		{
			level.level_map[netMessage->object_pos_y * 30 + netMessage->object_pos_x] = L_EMPTY;
			player->max_speed = OVER_SPEED;
			player->has_over_speed = true;
			DrawMap2(playerHudX+10, 1, map_speed_itm);
			SetTile(netMessage->object_pos_x, netMessage->object_pos_y, 0);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_ITEM);
		}
		else if (netMessage->code == NETITEMROCKET)
		{
			level.level_map[netMessage->object_pos_y * 30 + netMessage->object_pos_x] = L_EMPTY;
			player->has_rocket = true;
			DrawMap2(playerHudX+11, 1, map_rocket_itm);
			SetTile(netMessage->object_pos_x, netMessage->object_pos_y, 0);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_ITEM);
		}
		else if (netMessage->code == NETITEMBOMB)
		{
			level.level_map[netMessage->object_pos_y * 30 + netMessage->object_pos_x] = L_EMPTY;
			SetTile(netMessage->object_pos_x, netMessage->object_pos_y, 0);
			if (!(otherPlayer->flags & EXPLODING_FLAG))
			{
				kill_player(otherPlayer, otherPlayerHudX);
				LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_TANK_EXPLODE);
			}
			player->netMessage.level_score++;
			player->netMessage.score++;
			render_score(player, playerHudX);
			LBPlaySound(game.selection, player1.flags, player2.flags, PATCH_ITEM);
		}
	}
	else
	{
		state->pressed = 0;
	}
}

u8 is_net_player(Player* player)
{
	if (game.selection == HOSTNETGAME && player == &player2) return 1;
	if (game.selection == JOINNETGAME && player == &player1) return 1;
	return 0;
}

void record_player_posture(Player* player)
{
	player->old_held = player->netMessage.joyPadState.held;
}

u8 player_posture_changed(Player* player)
{
	if ((player->old_held & BTN_UP) != (player->netMessage.joyPadState.held & BTN_UP)) return 1;
	if ((player->old_held & BTN_DOWN) != (player->netMessage.joyPadState.held & BTN_DOWN)) return 1;
	if ((player->old_held & BTN_LEFT) != (player->netMessage.joyPadState.held & BTN_LEFT)) return 1;
	if ((player->old_held & BTN_RIGHT) != (player->netMessage.joyPadState.held & BTN_RIGHT)) return 1;
	return 0;
}

void clearNetBuffers()
{
	if (game.selection == HOSTNETGAME || game.selection == JOINNETGAME)
	{
		InitUartTxBuffer();
		InitUartRxBuffer();
	}
}

void count_frames()
{
	frames++;
}

int main()
{
	// Initialize
    GetPrngNumber(GetTrueRandomSeed());
	InitMusicPlayer(my_patches);
	SetMasterVolume(0xff);
	SetTileTable(tiles_data);
	SetSpritesTileTable(sprites_data);
	SetFontTilesIndex(TILES_DATA_SIZE);
	FadeIn(FRAMES_PER_FADE, false);
	ClearVram();
#if JAMMA
	read_dip_switches();
#endif
	init_scores(&scores);
	init_handles(&handles);
	init_game_state();
	load_credits();
	load_splash();
	
	SetUserPreVsyncCallback(&count_frames);
	
	while (1)
	{
		waitForVSync();
		frames = 0;
		get_net_message();
		switch (game.current_screen)
		{
			case SPLASH:
				LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
				update_splash(&player1.netMessage.joyPadState, &player2.netMessage.joyPadState);
				break;
			case TANK_RANK:
				LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
				update_tank_rank(&player1.netMessage.joyPadState);
				break;
			case HANDLE_SELECT:
				if (game.selection == HOSTNETGAME)
				{
					LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
				}
				else if (game.selection == JOINNETGAME)
				{
					LBGetJoyPadState(&player2.netMessage.joyPadState, 0);
				}
				else
				{
					LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
					LBGetJoyPadState(&player2.netMessage.joyPadState, 1);
				}
				update_handle_select(&player1.netMessage.joyPadState, &player2.netMessage.joyPadState);
				break;
#if JAMMA
#else
			case HOST_NET_GAME:
				LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
				update_host_net_game(&player1.netMessage.joyPadState);
				break;
			case JOIN_NET_GAME:
				LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
				update_join_net_game(&player1.netMessage.joyPadState);
				break;
#endif
			case LEVEL:
				if (game.selection == PVCPU)
				{
					LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
					get_cpu_joypad_state(&player2, &player1, &player2.netMessage.joyPadState);
				}
				else if (game.selection == CPUVCPU)
				{
					get_cpu_joypad_state(&player1, &player2, &player1.netMessage.joyPadState);
					get_cpu_joypad_state(&player2, &player1, &player2.netMessage.joyPadState);
				}
				else if (game.selection == HOSTNETGAME)
				{
					record_player_posture(&player1);
					LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
					if (player_posture_changed(&player1)) send_smart_net_message(&player1, &player1.netMessage.joyPadState, NETPOSCHANGE);
					
				}
				else if (game.selection == JOINNETGAME)
				{
					record_player_posture(&player2);
					LBGetJoyPadState(&player2.netMessage.joyPadState, 0);
					if (player_posture_changed(&player2)) send_smart_net_message(&player2, &player2.netMessage.joyPadState, NETPOSCHANGE);
				}
				else
				{
					LBGetJoyPadState(&player1.netMessage.joyPadState, 0);
					LBGetJoyPadState(&player2.netMessage.joyPadState, 1);
				}
				update_level(&player1.netMessage.joyPadState, &player2.netMessage.joyPadState);
				break;
			default:
				break;
		}
		global_frame_counter++;
	}
}
