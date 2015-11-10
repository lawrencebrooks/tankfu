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
#include "types.h"
#include "strings.h"
#include "utils.h"
#include "macros.h"

/* Utilities */
void load_eeprom(struct EepromBlockStruct* block);
void fade_through();
void level_transition(u8 index);
void clear_sprites();
void save_eeprom(struct EepromBlockStruct* block);
void exit_game();
void print_level_score(Player* winner, Player* loser);

/* Initializers */
void init_player(Player* p, const char* map_tank_up_0, const char* map_tank_right_0);

/* Collision Detection */
void collision_detect_shot(Player* player, Shot* shot);

/* Screen loaders */
void load_splash();
void load_tank_rank();
void load_handle_select();
void load_level(int level_number);
void load_level_tiles(u8 blank);

// Globals
Game game;
Player player1;
Player player2;
JoyPadState p1;
JoyPadState p2;
Level level;
TileAnimations tile_animations;
TileAnimation scope_animation;
u16 global_frame_counter = 1;

struct EepromBlockStruct handles;
struct EepromBlockStruct scores;

HandleSelectState p1s = {
	.handle_id = 0,
	.char_index = 0,
	.select_state = SELECTING,
};
HandleSelectState p2s = {
	.handle_id = 0,
	.char_index = 0,
	.select_state = SELECTING,
};

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
	s->shared.x = OFF_SCREEN;
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
	s->up_anim.anims[0] = (shot_type == BASIC_SHOT) ? (char*) map_ball : (char*) map_rocket_up_0;
	s->up_anim.anims[1] = (shot_type == BASIC_SHOT) ? (char*) map_ball : (char*) map_rocket_up_1;
	s->up_anim.current_anim = 0;
	s->right_anim.anim_count = 2;
	s->right_anim.frames_per_anim = FRAMES_PER_ANIM;
	s->right_anim.frame_count = 0;
	s->right_anim.looped = 0;
	s->right_anim.reversing = 0;
	s->right_anim.anims[0] = (shot_type == BASIC_SHOT) ? (char*) map_ball : (char*) map_rocket_right_0;
	s->right_anim.anims[1] = (shot_type == BASIC_SHOT) ? (char*) map_ball : (char*) map_rocket_right_1;
}

void init_player(Player* p, const char* map_tank_up_0, const char* map_tank_right_0)
{
	p->banter_frame = FRAMES_PER_BANTER;
	p->grace_frame = FRAMES_PER_GRACE;
	p->banter_index = 0;
	p->score = 0;
	p->level_score = 0;
	p->shared.direction = D_UP;
	p->shared.speed = 0;
	p->shared.recoiled = 0;
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
	init_player(&player1, map_tank1_up_0, map_tank1_right_0);
	init_player(&player2, map_tank2_up_0, map_tank2_right_0);
}

/* Utilities */
void player_spawn(Player* player)
{
	player->grace_frame = 0;
	player->shared.x = player->spawn_x;
	player->shared.y = player->spawn_y;
	player->shared.direction = D_UP;
	player->shared.speed = 0;
	player->shared.recoiled = 0;
	
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

	if (player1.score < player2.score)
	{
		p_win = &player2;
		p_lose = &player1;
	}
	save_score[0] = p_win->handle_id;
	save_score[1] = p_lose->handle_id;
	save_score[2] = p_win->score;
	save_score[3] = p_lose->score;
	save_score[4] = 0;
	save_delta = p_win->score - p_lose->score;

	for (u8 i = 0; i < 28; i += 5)
	{
		if (saved)
		{
			LBCopyChars(tmp_score, &scores.data[i], 5);
			LBCopyChars(&scores.data[i], save_score, 5);
			LBCopyChars(save_score, tmp_score, 5);
		}
		else
		{
			cur_delta = scores.data[i+2] - scores.data[i+3];
			if (save_delta > cur_delta)
			{
				LBCopyChars(tmp_score, &scores.data[i], 5);
				LBCopyChars(&scores.data[i], save_score, 5);
				LBCopyChars(save_score, tmp_score, 5);
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
	SetSpriteVisibility(true);
	init_game_state();
	load_tank_rank();
}

void position_shot(Player* player, Shot* shot)
{
	switch (shot->shared.direction)
	{
		case D_UP:
			shot->shared.x = player->shared.x + 4;
			shot->shared.y = player->shared.y;
			break;
		case D_RIGHT:
			shot->shared.x = player->shared.x + 8;
			shot->shared.y = player->shared.y + 4;
			break;
		case D_DOWN:
			shot->shared.x = player->shared.x + 4;
			shot->shared.y = player->shared.y + 8;
			break;
		case D_LEFT:
			shot->shared.x = player->shared.x;
			shot->shared.y = player->shared.y + 4;
			break;
	}
}

void print_level_score(Player* winner, Player* loser)
{
	LBPrintStr(4, 14, &winner->handle[0], 3);
	Print(8, 14, (char*) strOwns);
	LBPrintStr(13, 14, &loser->handle[0], 3);
	Print(17, 14, (char*) strBy);
	PrintByte(22, 14, winner->level_score ,true);
	PrintChar(23, 14, '-');
	PrintByte(26, 14, loser->level_score ,true);
}

void print_final_score(Player* winner, Player* loser)
{
    Print(9, 13, (char*) strFinalScore);
    LBPrintStr(4, 14, &winner->handle[0], 3);
    Print(8, 14, (char*) strOwns);
    LBPrintStr(13, 14, &loser->handle[0], 3);
    Print(17, 14, (char*) strBy);
    PrintByte(22, 14, winner->score ,true);
    PrintChar(23, 14, '-');
    PrintByte(26, 14, loser->score ,true);
}


void update_level_helper(JoyPadState* p, Player* player, Player* other_player, u8 hud_x)
{
	Shot* shot;
	u8 next_level;
	Player* tmp;

	player->shared.recoiled = 0;
	if ((p->pressed & BTN_START))
	{
		SFX_NAVIGATE;
		game.paused = game.paused ^ 1;
		load_level_tiles(false);
	}
	if (!(game.paused || (player->flags & EXPLODING_FLAG)))
	{
		if ((p->pressed & BTN_SR) && (player->banter_frame == FRAMES_PER_BANTER))
		{
			player->banter_frame = 0;
			player->banter_index = (u8) LBRandom(0, 9);
			SFX_BANTER;
		}
		player->shared.speed = player->max_speed;
		if ((p->held & BTN_UP))
		{
			player->shared.direction = D_UP;
			player->shared.y -= FRAME_TIME * player->shared.speed;
		}
		else if ((p->held & BTN_RIGHT))
		{
			player->shared.direction = D_RIGHT;
			player->shared.x += FRAME_TIME * player->shared.speed;
		}
		else if ((p->held & BTN_DOWN))
		{
			player->shared.direction = D_DOWN;
			player->shared.y += FRAME_TIME * player->shared.speed;
		}
		else if ((p->held & BTN_LEFT))
		{
			player->shared.direction = D_LEFT;
			player->shared.x -= FRAME_TIME * player->shared.speed;
		}
		else
		{
			player->shared.speed = 0;
		}
		if ((p->pressed & BTN_A) && (player->active_shots < MAX_SHOTS))
		{
			for (u8 i = 0; i < MAX_SHOTS; i++)
			{
				shot = &player->shot[i];
				if (!shot->active)
				{
					if (player->has_rocket)
					{
						init_shot_state(shot, ROCKET_SHOT);
						set_shot_animations(shot, ROCKET_SHOT);
						SFX_ROCKET;
					}
					else
					{
						init_shot_state(shot, BASIC_SHOT);
						set_shot_animations(shot, BASIC_SHOT);
						SFX_CANNONBALL;
					}
					player->active_shots++;
					shot->shared.direction = player->shared.direction;
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

		/* Update Shot */
		for (u8 i = 0; i < MAX_SHOTS; i++)
		{
			shot = &player->shot[i];
			if (shot->active)
			{
				switch (shot->shared.direction)
				{
					case D_UP: shot->shared.y -= FRAME_TIME * shot->shared.speed; break;
					case D_RIGHT: shot->shared.x += FRAME_TIME * shot->shared.speed; break;
					case D_DOWN: shot->shared.y += FRAME_TIME * shot->shared.speed; break;
					case D_LEFT: shot->shared.x -= FRAME_TIME * shot->shared.speed; break;
					default: break;
				}
				shot->distance += (shot->distance <= DISTANCE_TO_ARM) ? FRAME_TIME * shot->shared.speed : 0;
				collision_detect_shot(player, shot);
			}
		}
	}
	else
	{
		if (p->pressed & BTN_X)
		{
			SFX_NAVIGATE;
			exit_game();
		}
	}
	
	// Level transition
	if ((player->level_score >= MAX_LEVEL_SCORE) && !(other_player->flags & EXPLODING_FLAG))
	{
	    next_level = game.current_level + 1;

	    // Tie breaker
	    if ((next_level >= LEVEL_COUNT) && (other_player->score == player->score)) return;

		load_level_tiles(true);
		SetSpriteVisibility(false);
		print_level_score(player, other_player);
		LBWaitSeconds(TEXT_LINGER);
		player->level_score = 0;
		other_player->level_score = 0;
		SFX_LEVEL_CLEAR;
		if (next_level >= LEVEL_COUNT)
		{
		    if (other_player->score > player->score)
		    {
		        tmp = player;
		        player = other_player;
		        other_player = tmp;
		    }
		    print_final_score(player, other_player);
		    LBWaitSeconds(TEXT_LINGER);
			exit_game();
		}
		else
		{
			level_transition(next_level);
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
	PrintByte(x+8, 0, player->level_score, false);
	PrintByte(x+8, 1, player->score, false);
}

u8 render_banter(Player* player, u8 banter_x, u8 clear_banter)
{
	// Banter
	if (player->banter_frame != FRAMES_PER_BANTER)
	{
		if (player->banter_frame == 0)
		{
			Print(banter_x, 2, (char*) banter_map+player->banter_index*15);
		}
		clear_banter = 1;
		player->banter_frame++;
	}
	else if (clear_banter)
	{
		Print(banter_x, 2, (char*) strBanterClear);
		clear_banter = 0;
	}
	return clear_banter;
}

void render_player(Player* player, u8 sprite_index)
{
	MoveSprite(sprite_index, player->shared.x, player->shared.y, 2, 2);
}

void render_shot(Player* player, u8 sprite_index)
{
	if (player->active_shots > 0)
	{
		for (u8 i = 0; i < MAX_SHOTS; i++)
		{
			MoveSprite(sprite_index, player->shot[i].shared.x, player->shot[i].shared.y, 1, 1);
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

char tank_map(Player* player, char sprite_index)
{
	char* t_map = 0;
	u8 t_flags = 0;
	static u8 toggle_counter = FRAMES_PER_BLANK;
	static u8 toggle_blank = 0;

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
		switch (player->shared.direction)
		{
			case D_UP: t_map = LBGetNextFrame(&player->up_anim); t_flags = 0; break;
			case D_RIGHT: t_map = LBGetNextFrame(&player->right_anim); t_flags = 0; break;
			case D_DOWN: t_map = LBGetNextFrame(&player->up_anim); t_flags = SPRITE_FLIP_Y; break;
			case D_LEFT: t_map = LBGetNextFrame(&player->right_anim); t_flags = SPRITE_FLIP_X; break;
			default: t_map = LBGetNextFrame(&player->up_anim); t_flags = 0; break;
		}
		if ((player->grace_frame != FRAMES_PER_GRACE) && (toggle_blank))
		{
			t_map = (char*) map_tank_blank;
		}
		toggle_counter--;
		if (toggle_counter == 0)
		{
			toggle_counter = FRAMES_PER_BLANK;
			toggle_blank = toggle_blank ^ 1;
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
		tile = ((u8) sprite->y / 8) + 1;
		sprite->y = tile * 8;
	}
	else if (sprite->direction == D_RIGHT)
	{
		tile = sprite->x / 8;
		sprite->x = tile * 8;
	}
	else if (sprite->direction == D_DOWN)
	{
		tile = sprite->y / 8;
		sprite->y = tile * 8;
	}
	else
	{
		tile = ((u8) sprite->x / 8) + 1;
		sprite->x = tile * 8;
	}
	sprite->recoiled = 1;
}

void recoil_sprite_fine(SpriteShared* sprite)
{	
	if (sprite->direction == D_UP)
	{
		sprite->y += FRAME_TIME * sprite->speed;
	}
	else if (sprite->direction == D_RIGHT)
	{
		sprite->x -= FRAME_TIME * sprite->speed;
	}
	else if (sprite->direction == D_DOWN)
	{
		sprite->y -= FRAME_TIME * sprite->speed;
	}
	else
	{
		sprite->x += FRAME_TIME * sprite->speed;
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

u8 solid_tile(int tile_index)
{
	u8 tile = level.level_map[tile_index];
	
	if (tile == L_BRICK) return tile;
	if (tile == L_METAL) return tile;
	if (tile == L_FENCE) return tile;
	if (tile == L_TL) return tile;
	if (tile == L_BR) return tile;
	if (tile == L_TR) return tile;
	if (tile == L_BL) return tile;

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

u8 collides_directional_tile(int tile_index, u8 x, u8 y, u8 width, u8 height)
{
	u8 tile = level.level_map[tile_index];
	u8 tile_x = (tile_index % 30) * 8;
	u8 tile_y = (tile_index / 30 + 3) * 8;

	if ((tile == L_TL) || (tile == L_BR))
	{
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, x, y, x, y+height-1)) return tile;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, x, y, x+width-1, y)) return tile;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, x+width-1, y, x+width-1, y+height-1)) return tile;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, x, y+height-1, x+width-1, y+height-1)) return tile;
	}
	else if ((tile == L_TR) || (tile == L_BL))
	{
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, x, y, x, y+height-1)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, x, y, x+width-1, y)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, x+width-1, y, x+width-1, y+height-1)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, x, y+height-1, x+width-1, y+height-1)) return tile;
	}
	
	return 0;
}

u8 player_shot(Player* p, Shot* shot)
{
	return LBCollides(p->shared.x+1,p->shared.y+1,14,14,shot->shared.x+2,shot->shared.y+2,4,4) &&
		   p->grace_frame == FRAMES_PER_GRACE &&
		   shot->distance > DISTANCE_TO_ARM;
}

u8 collision_detect_boundries(SpriteShared* sprite)
{
	if (sprite->x < 0  || sprite->x + 8 > 240 ||
	    sprite->y < 24 || sprite->y + 8 > 224)
	{
		return 1;
	}
	return 0;
}

void drop_item(int tile_index, const char* map, u8 item_type)
{
	if (level.level_map[tile_index] == L_EMPTY)
	{
		DrawMap2(tile_index % 30, 3 + tile_index / 30, map);
		level.level_map[tile_index] = item_type;
	}
	else if (level.level_map[tile_index+1] == L_EMPTY)
	{
		DrawMap2(tile_index % 30 + 1, 3 + tile_index / 30, map);
		level.level_map[tile_index+1] = item_type;
	}
	else if (level.level_map[tile_index+30] == L_EMPTY)
	{
		DrawMap2(tile_index % 30, 3 + tile_index / 30 + 1, map);
		level.level_map[tile_index+30] = item_type;
	}
	else if (level.level_map[tile_index+31] == L_EMPTY)
	{
		DrawMap2(tile_index % 30 + 1, 3 + tile_index / 30 + 1, map);
		level.level_map[tile_index+31] = item_type;
	}
}

void kill_player(Player* player, u8 hud_x)
{
	u8 x = player->shared.x / 8;
	u8 y = player->shared.y / 8 - 3;
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
	if (direction == D_UP)
	{
		tiles[0] = (y * 30) + x;
		tiles[1] = tiles[0]+1;
	}
	else if (direction == D_RIGHT)
	{
		tiles[0] = (y * 30) + x + 1;
		tiles[1] = tiles[0]+30;
	}
	else if (direction == D_DOWN)
	{
		tiles[0] = (y * 30) + x + 30;
		tiles[1] = tiles[0]+1;
	}
	else
	{
		tiles[0] = (y * 30) + x;
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
	u8 x = shot->shared.x / 8;
	u8 y = shot->shared.y / 8 - 3;
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
		player->active_shots--;
		return;
	}
	
	/* Player interaction */
	if (player_shot(&player1, shot) && !(player1.flags & EXPLODING_FLAG))
	{
		p = &player1;
		hud_x = 0;
		player2.level_score++;
		player2.score++;
		render_score(&player2, 15);
	}
	else if (player_shot(&player2, shot) && !(player2.flags & EXPLODING_FLAG))
	{
		p = &player2;
		hud_x = 15;
		player1.level_score++;
		player1.score++;
		render_score(&player1, 0);
	}
	if (p)
	{
		init_shot_state(shot, shot->shot_type);
		player->active_shots--;
		kill_player(p, hud_x);
		SFX_TANK_EXPLODE;
		return;
	}
	
	/* Tile interaction */
	for (u8 i = 0; i < 2; i++)
	{
		tile = level.level_map[tiles[i]];
		if (tile == L_EMPTY) continue;
		
		if (solid_directional_tile(tiles[i]) && collides_directional_tile(tiles[i], shot->shared.x+2, shot->shared.y+2,4,4))
		{
			hit = hit | HIT_ANGLE;
			angle_tile = tile;
		}
		else if (tile == L_BRICK && LBCollides(shot->shared.x+2,shot->shared.y+2,4,4,(tiles[i]%30)*8,(tiles[i]/30)*8+24,8,8))
		{
			hit = hit | HIT_BRICK;
			brick_index = i;
		}
		else if (tile == L_METAL && LBCollides(shot->shared.x+2,shot->shared.y+2,4,4,(tiles[i]%30)*8,(tiles[i]/30)*8+24,8,8))
        {
		    hit = hit | HIT_METAL;
        }
	}
	
	if (hit & HIT_ANGLE)
	{
		recoil_sprite_fine(&shot->shared);
		richochet(angle_tile, &shot->shared);
		shot->rebounds--;
		if (shot->rebounds <= 0)
		{
			init_shot_state(shot, shot->shot_type);
			player->active_shots--;
		}
		SFX_METAL;
	}
	else if (hit & HIT_BRICK)
	{
		explode_tile(&tile_animations, tiles[brick_index]);
		level.level_map[tiles[brick_index]] = L_EMPTY;
		shot->hit_count--;
		if (shot->hit_count <= 0)
		{
			init_shot_state(shot, shot->shot_type);
			player->active_shots--;
		}
		SFX_BRICK_EXPLODE;
	}
	else if (hit & HIT_METAL)
	{
        init_shot_state(shot, shot->shot_type);
        player->active_shots--;
        SFX_METAL;
	}
}

void get_interesting_tile_indexes(int* tiles, u8 x, u8 y, u8 direction)
{
	if (direction == D_UP)
	{
		tiles[0] = (y * 30) + x;
		tiles[1] = tiles[0]+1;
		tiles[2] = tiles[0]+2;
	}
	else if (direction == D_RIGHT)
	{
		tiles[0] = (y * 30) + x + 2;
		tiles[1] = tiles[0]+30;
		tiles[2] = tiles[0]+60;
	}
	else if (direction == D_DOWN)
	{
		tiles[0] = (y * 30) + x + 60;
		tiles[1] = tiles[0]+1;
		tiles[2] = tiles[0]+2;
	}
	else
	{
		tiles[0] = (y * 30) + x;
		tiles[1] = tiles[0]+30;
		tiles[2] = tiles[0]+60;
	}
}

void collision_detect_player(Player* player, Player* other_player, u8 hud_x, u8 other_player_hud_x)
{
	int tiles[3] = {0,0,0};
	u8 x = player->shared.x / 8;
	u8 y = player->shared.y / 8 - 3;
	u8 hit_water = 0;
	
	get_interesting_tile_indexes(tiles, x, y, player->shared.direction);
	
	/* Level boundries first */
	if (collision_detect_boundries(&player->shared))
	{
		recoil_sprite(&player->shared);
		player->shared.speed = 0;
		return;
	}

	/* Tile interaction */
	for (u8 i = 0; i < 3; i++)
	{
		if (solid_directional_tile(tiles[i]) && collides_directional_tile(tiles[i], player->shared.x, player->shared.y, 16, 16))
		{
			(player->handle_id == 9) ? recoil_sprite(&player->shared) : recoil_sprite_fine(&player->shared);
			player->shared.speed = 0;
		}
		else if (solid_square_tile(tiles[i]) && LBCollides(player->shared.x,player->shared.y,16,16,(tiles[i]%30)*8,(tiles[i]/30+3)*8,8,8))
		{
			recoil_sprite(&player->shared);
			player->shared.speed = 0;
		}
		else if (level.level_map[tiles[i]] == L_WATER && LBCollides(player->shared.x,player->shared.y,16,16,(tiles[i]%30)*8,(tiles[i]/30+3)*8,8,8))
		{
			player->max_speed = WATER_SPEED;
			hit_water = 1;
		}
		else if (level.level_map[tiles[i]] == L_SCOPE && LBCollides(player->shared.x,player->shared.y,16,16,(tiles[i]%30)*8,(tiles[i]/30+3)*8,8,8))
		{
			player->max_speed = WATER_SPEED;
			hit_water = 1;
		}
		else if (level.level_map[tiles[i]] == L_SPEED && !(player->flags & EXPLODING_FLAG))
		{
			level.level_map[tiles[i]] = L_EMPTY;
			player->max_speed = OVER_SPEED;
			player->has_over_speed = true;
			DrawMap2(hud_x+10, 1, map_speed_itm);
			SetTile(tiles[i] % 30, 3 + tiles[i] / 30, 0);
			SFX_ITEM;
		}
		else if (level.level_map[tiles[i]] == L_ROCKET && !(player->flags & EXPLODING_FLAG))
		{
			level.level_map[tiles[i]] = L_EMPTY;
			player->has_rocket = true;
			DrawMap2(hud_x+11, 1, map_rocket_itm);
			SetTile(tiles[i] % 30, 3 + tiles[i] / 30, 0);
			SFX_ITEM;
		}
		else if (level.level_map[tiles[i]] == L_EXPLODE && !(player->flags & EXPLODING_FLAG))
		{
			level.level_map[tiles[i]] = L_EMPTY;
			SetTile(tiles[i] % 30, 3 + tiles[i] / 30, 0);
			SFX_ITEM;
			if (!(other_player->flags & EXPLODING_FLAG))
			{
				player->level_score++;
				player->score++;
				render_score(player, hud_x);
				kill_player(other_player, other_player_hud_x);
			}
		}
		
		if (!hit_water)
		{
			player->max_speed = MAX_SPEED;
			if (player->has_over_speed) player->max_speed = OVER_SPEED;
		}
	}
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
				case L_SCOPE: DrawMap2(x, y, map_water); break;
				case L_FENCE: DrawMap2(x, y, map_fence); break;
				default : SetTile(x, y, 0); break;
			}
		}
	}
}

void load_level(int level_number)
{
    int level_start = level_number*30*25;

	game.current_screen = LEVEL;
	clear_sprites();
	game.current_level = level_number;
	for (int i = 0; i < 30*25; i++)
	{
		level.level_map[i] = pgm_read_byte(&level_data[level_start+i]);
		if (level.level_map[i] == L_P1_SPAWN)
		{
			player1.spawn_x = (i % 30) * 8;
			player1.spawn_y = (i / 30) * 8 + 3*8;
			player1.level_score = 0;
			player1.has_over_speed = false;
			player1.has_rocket = false;
			player1.max_speed = MAX_SPEED;
			player_init_shot_state(&player1);
			player_spawn(&player1);
		}
		if (level.level_map[i] == L_P2_SPAWN)
		{
			player2.spawn_x = (i % 30) * 8;
			player2.spawn_y = (i / 30) * 8 + 3*8;
			player2.level_score = 0;
			player2.has_over_speed = false;
			player2.has_rocket = false;
			player2.max_speed = MAX_SPEED;
			player_init_shot_state(&player2);
			player_spawn(&player2);
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
	SFX_LEVEL_START;
}

void update_level(JoyPadState* p1, JoyPadState* p2)
{
	char p1_index = 0;
	char p2_index = 0;
	char p1_shot_index = 0;
	char p2_shot_index = 0;
	u16 held = 0;
	static u8 clear_banter_1 = 1;
	static u8 clear_banter_2 = 1;
	static u16 demo_counter = 0;

	// Render
	if (game.paused)
	{
		SetSpriteVisibility(false);
		DrawMap2(8, 12, (const char*) map_pause);
		Print(12, 13, (char*) strPaused);
		Print(11, 14, (char*) strExit);
	}
	else
	{
		SetSpriteVisibility(true);
		p2_index = tank_map(&player1, p1_index);
		p1_shot_index = tank_map(&player2, p2_index);
		p2_shot_index = shot_map(&player1, p1_shot_index);
		shot_map(&player2, p2_shot_index);
		clear_banter_1 = render_banter(&player1, 15, clear_banter_1);
		clear_banter_2 = render_banter(&player2, 0, clear_banter_2);
		render_player(&player1, p1_index);
		render_player(&player2, p2_index);
		render_shot(&player1, p1_shot_index);
		render_shot(&player2, p2_shot_index);
		render_tile_explosions(&tile_animations);
	}

	// Update
	update_level_helper(p1, &player1, &player2, 15);
	update_level_helper(p2, &player2, &player1, 0);
	collision_detect_player(&player1, &player2, 0, 15);
	collision_detect_player(&player2, &player1, 15, 0);
	
	if (game.selection == CPUVCPU) 
	{
		demo_counter++;
		held = ReadJoypad(0);
	}
	if (game.selection == CPUVCPU &&
	    (((held & BTN_X) ||
		 (held & BTN_START) ||
		 (held & BTN_SL) ||
		 (held & BTN_SR) ||
		 (held & BTN_SELECT) ||
		 (held & BTN_Y) ||
		 (held & BTN_B)) ||
		demo_counter >= DEMO_LENGTH)
		)
	{
		demo_counter = 0;
		fade_through();
		init_game_state();
		load_splash();
	}
}

void load_splash()
{
	game.current_screen = SPLASH;
	clear_sprites();
	Print(7, 13, (char*) str1Player);
	Print(7, 14, (char*) str2Player);
	Print(7, 15, (char*) strHighscores);
	Print(5, 26, (char*) strCopyright);
	DrawMap2(4, 5, (const char*) map_splash);
	MapSprite2(0, map_right_arrow, 0);
	SFX_SPLASH;
}

void update_splash(JoyPadState* p1, JoyPadState* p2)
/*
 * Splash or title screen
 */
{
	static u16 demo_counter = 0;
	static u8 demo_choice = 0;
	
	// Render
	switch (game.selection)
	{
		case PVCPU:
			MoveSprite(0, 6*8, 13*8, 1, 1);
			break;
		case PVP:
			MoveSprite(0, 6*8, 14*8, 1, 1);
			break;
		case TR:
			MoveSprite(0, 6*8, 15*8, 1, 1);
			break;
	}
	Print(9, 21, (char*) strSelectHandle);

	// Update
	if (p1->pressed) demo_counter = 0;
	
	if (p1->pressed & BTN_UP)
	{
		game.selection--;
		if (game.selection < PVCPU) game.selection = PVCPU;
		SFX_NAVIGATE;
	}
	else if (p1->pressed & BTN_DOWN)
	{
		game.selection++;
		if (game.selection > TR) game.selection = TR;
		SFX_NAVIGATE;
	}
	else if ((p1->pressed & BTN_A) && ((game.selection == PVCPU) || (game.selection == PVP)))
	{
		demo_counter = 0;
		p1s.select_state = SELECTING;
		p2s.select_state = SELECTING;
		SFX_NAVIGATE;
		fade_through();
		load_eeprom(&handles);
		load_handle_select();
		return;
	}
	else if ((p1->pressed & BTN_A) && (game.selection == TR))
	{
		demo_counter = 0;
		SFX_NAVIGATE;
		fade_through();
		load_eeprom(&scores);
		load_tank_rank();
		return;
	}
	else if (demo_counter >= DEMO_WAIT)
	{
		demo_counter = 0;
		if (demo_choice % 2 == 0)
		{
			game.selection = CPUVCPU;
			player1.handle_id = 9;
			LBCopyChars(player1.handle, &handles.data[9*3], 3);
			player2.handle_id = 9;
			LBCopyChars(player2.handle, &handles.data[9*3], 3);
			SFX_NAVIGATE;
			clear_sprites();
			fade_through();
			level_transition(LBRandom(0, 9));
		}
		else
		{
			SFX_NAVIGATE;
			fade_through();
			load_eeprom(&scores);
			load_tank_rank();
		}
		demo_choice++;
		return;
		
	}
	demo_counter++;
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
		y += 3;
		rank += 1;
	}
	Print(3, 22, (char*) strReset);
	Print(10, 24, (char*) strCancelHandle);
}

void update_tank_rank(JoyPadState* p1, JoyPadState* p2)
{
	static u16 tank_rank_counter = 0;
	
	// Update
	if (p1->pressed & BTN_X)
	{
		tank_rank_counter = 0;
		SFX_NAVIGATE;
		fade_through();
		load_splash();
	}
	if ((p1->held & BTN_SL) && (p1->held_cycles == 255))
	{
		tank_rank_counter = 0;
	    SFX_NAVIGATE;
	    init_scores(&scores);
	    init_handles(&handles);
	    save_eeprom(&scores);
	    save_eeprom(&handles);
	    load_tank_rank();
	}
	
	if (tank_rank_counter > TANK_RANK_LENGTH)
	{
		tank_rank_counter = 0;
		SFX_NAVIGATE;
		fade_through();
		load_splash();
	}
	tank_rank_counter++;
}


void _handle_select_helper(HandleSelectState* ps, JoyPadState* p, Player* player)
{
	if ((p->pressed & BTN_UP) && (ps->select_state == SELECTING))
	{
		ps->handle_id--;
		if (ps->handle_id < 0) ps->handle_id = 0;
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == SELECTING))
	{
		ps->handle_id++;
		if (ps->handle_id > 8) ps->handle_id = 8;
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_A) && (ps->select_state == SELECTING))
	{
		ps->select_state = EDITING;
		LBCopyChars(ps->handle, &handles.data[ps->handle_id*3], 3);
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_RIGHT) && (ps->select_state == EDITING))
	{
		ps->char_index++;
		if (ps->char_index > 2) ps->char_index = 2;
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_LEFT) && (ps->select_state == EDITING))
	{
		ps->char_index--;
		if (ps->char_index < 0) ps->char_index = 0;
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_UP) && (ps->select_state == EDITING))
	{
		ps->handle[(u8) ps->char_index]--;
		if (ps->handle[(u8) ps->char_index] < 'A') ps->handle[(u8) ps->char_index] = 'A';
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == EDITING))
	{
		ps->handle[(u8) ps->char_index]++;
		if (ps->handle[(u8) ps->char_index] > 'Z') ps->handle[(u8) ps->char_index] = 'Z';
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_A) && (ps->select_state == EDITING))
	{
		player->handle_id = ps->handle_id;
		LBCopyChars(player->handle, ps->handle, 3);
		LBCopyChars(&handles.data[ps->handle_id*3], ps->handle, 3);
		SFX_NAVIGATE;
		save_eeprom(&handles);
		ps->select_state = CONFIRMED;
	}
	else if ((p->pressed & BTN_X) && (ps->select_state == EDITING))
	{
		ps->select_state = SELECTING;
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_X) && (ps->select_state == CONFIRMED))
	{
		ps->select_state = EDITING;
		SFX_NAVIGATE;
	}
	else if ((p->pressed & BTN_X))
	{
		SFX_NAVIGATE;
		fade_through();
		load_splash();
	}
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
		LBCopyChars(tmp, ps->handle, 3);
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
	Print(8, 21, (char*) strSelectHandle);
	Print(8, 22, (char*) strConfirmHandle);
	Print(8, 23, (char*) strCancelHandle);
	Print(8, 24, (char*) strChangeHandle);
}

void update_handle_select(JoyPadState* p1, JoyPadState* p2)
{
	u8 start_game = 0;

	// Render
	_handle_select_render_helper(&p1s, p1, 2, 6);
	if (game.selection == PVP)
	{
		_handle_select_render_helper(&p2s, p2, 19, 8);
	}

	// Update
	_handle_select_helper(&p1s, p1, &player1);
	if (p1s.select_state == CONFIRMED) start_game = 1;
	if (game.selection == PVP)
	{
		_handle_select_helper(&p2s, p2, &player2);
		if (p2s.select_state != CONFIRMED) start_game = 0;
	}
	if (start_game)
	{
		if (game.selection == PVCPU)
		{
			player2.handle_id = 9;
			LBCopyChars(player2.handle, &handles.data[9*3], 3);
		}
		level_transition(0);
	}
}

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
			recoil_sprite(&player->shared);
			recoiled = 0;
		}
		else if ((p->held & BTN_LEFT) && !(solid_tile((current_y+2) * 30 + current_x) || solid_tile((current_y+2) * 30 + current_x+1) || solid_tile((current_y+2) * 30 + current_x+2)))
		{
			p->held = BTN_DOWN;
			recoil_sprite(&player->shared);
			recoiled = 0;
		}
		else if ((p->held & BTN_DOWN) && !(solid_tile((current_y) * 30 + current_x+2) || solid_tile((current_y+1) * 30 + current_x+2) || solid_tile((current_y+2) * 30 + current_x+2)))
		{
			p->held = BTN_RIGHT;
			recoil_sprite(&player->shared);
			recoiled = 0;
		}
		else if ((p->held & BTN_RIGHT) && !(solid_tile((current_y-1) * 30 + current_x) || solid_tile((current_y-1) * 30 + current_x+1) || solid_tile((current_y-1) * 30 + current_x+2)))
		{
			p->held = BTN_UP;
			recoil_sprite(&player->shared);
			recoiled = 0;
		}
		if (player->goal_direction & p->held)
		{
			player->feeling_my_way = 0;
			recoiled = 0;
		}
	}
	if ((p->held & BTN_LEFT) && recoiled)
	{
		p->held = BTN_UP;
		player->feeling_my_way = 1;
	}
	else if ((p->held & BTN_UP) && recoiled)
	{
		p->held = BTN_RIGHT;
		player->feeling_my_way = 1;
	}
	else if ((p->held & BTN_RIGHT) && recoiled)
	{
		p->held = BTN_DOWN;
		player->feeling_my_way = 1;
	}
	else if ((p->held & BTN_DOWN) && recoiled)
	{
		p->held = BTN_LEFT;
		player->feeling_my_way = 1;
	}

	if ((player->goal_direction == BTN_UP || player->goal_direction == BTN_DOWN) && current_y == player->goal) return 1;
	if ((player->goal_direction == BTN_LEFT || player->goal_direction == BTN_RIGHT) && current_x == player->goal) return 1;
	
	return 0;
}

u16 get_cpu_goal_direction(char distance_x, char distance_y)
{
	char abs_distance_x = (distance_x < 0) ? -distance_x : distance_x;
	char abs_distance_y = (distance_y < 0) ? -distance_y : distance_y;
	u16 direction = BTN_UP;
	
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
	
	goal_x = other_player->shared.x / 8;
	goal_y = other_player->shared.y / 8 - 3;
	player_x = player->shared.x / 8;
	player_y =  player->shared.y / 8 - 3;
	distance_x = goal_x - player_x;
	distance_y = goal_y - player_y;
	
	if (player->grace_frame == 0)
	{
		p->held = 0;
		return;
	}
	
	// Shot
	if (p->pressed & BTN_A)
	{
		p->pressed = 0;
	}
	if (global_frame_counter % DEFAULT_FRAMES_PER_SHOT == 0 && player->grace_frame > 50)
	{
		p->pressed = BTN_A;
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
			player->goal_direction = get_cpu_goal_direction(distance_x, distance_y);
			player->goal = goal_x;
			if (player->goal_direction == BTN_UP || player->goal_direction == BTN_DOWN) player->goal = goal_y;
		}
		p->held = player->goal_direction;
	}
	
	// Monitor movement
	if (player->shared.x != player->old_x)
		player->deadlock_count_x = 0;
	else 
		player->deadlock_count_x++;
	if (player->shared.y != player->old_y)
		player->deadlock_count_y = 0;
	else
		player->deadlock_count_y++;
	player->old_x = player->shared.x;
	player->old_y = player->shared.y;
	
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
	else player->goal_reached = crash_and_turn(player->shared.x / 8, player->shared.y / 8 - 3, player->shared.recoiled, player, p);
}

int main()
{
	// Initialize
	InitMusicPlayer(my_patches);
	SetMasterVolume(0xff);
	SetTileTable(tiles_data);
	SetSpritesTileTable(sprites_data);
	SetFontTilesIndex(TILES_DATA_SIZE);
	FadeIn(FRAMES_PER_FADE, false);
	ClearVram();
	init_scores(&scores);
	init_handles(&handles);
	init_game_state();
	init_tile_animations(&tile_animations);
	init_scope_animation(&scope_animation);
	load_splash();
	
	while (1)
	{
		WaitVsync(1);
		switch (game.current_screen)
		{
			case SPLASH:
				LBGetJoyPadState(&p1, 0);
				update_splash(&p1, &p2);
				break;
			case TANK_RANK:
				LBGetJoyPadState(&p1, 0);
				update_tank_rank(&p1, &p2);
				break;
			case HANDLE_SELECT:
				LBGetJoyPadState(&p1, 0);
				LBGetJoyPadState(&p2, 1);
				update_handle_select(&p1, &p2);
				break;
			case LEVEL:
				if (game.selection == PVCPU)
				{
					LBGetJoyPadState(&p1, 0);
					get_cpu_joypad_state(&player2, &player1, &p2);
				}
				else if (game.selection == CPUVCPU)
				{
					get_cpu_joypad_state(&player1, &player2, &p1);
					get_cpu_joypad_state(&player2, &player1, &p2);
				}
				else
				{
					LBGetJoyPadState(&p1, 0);
					LBGetJoyPadState(&p2, 1);
				}
				update_level(&p1, &p2);
				break;
			default:
				break;
		}
		global_frame_counter++;
	}
}
