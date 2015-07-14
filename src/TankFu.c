/*
 * Game: Tank Fu
 * Author: Lawrence Brooks
 */
#include <uzebox.h>
#include <avr/pgmspace.h>
#include "data/tiles.pic.inc"
#include "data/sprites.pic.inc"
#include "data/tiles.map.inc"
#include "data/sprites.map.inc"
#include "data/patches.h"
#include "data/levels.map.inc"
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

struct EepromBlockStruct handles = {
	.id = EEPROM_HANDLES_ID,
	// 1. UZE
	// 2. LJB
	// 3. AAA
	// 4. BBB
	// 5. CCC
	// 6. DDD
	// 7. EEE
	// 8. FFF
	// 9. GGG
	// 10. CPU
	.data = {
		0x55, 0x5a, 0x45,
		0x4c, 0x4a, 0x42,
		0x41, 0x41, 0x41,
		0x42, 0x42, 0x42,
		0x43, 0x43, 0x43,
		0x44, 0x44, 0x44,
		0x45, 0x45, 0x45,
		0x46, 0x46, 0x46,
		0x47, 0x47, 0x47,
		0x43, 0x50, 0x55,
	}
};

struct EepromBlockStruct scores = {
	.id = EEPROM_TANK_RANK_ID,
	// 1. owns 2. by 20 - 10
	// 2. owns 3. by by 20 - 11
	// 3. owns 4. by 20 - 12
	// 4. owns 5. by 20 - 13
	// 5. owns 6. by 20 - 14
	// 6. owns 7. by 20 - 15
	// 7. owns 1. by 20 - 16
	.data = {
		0, 1, 20, 10,
		1, 2, 20, 11,
		2, 3, 20, 12,
		3, 4, 20, 13,
		4, 5, 20, 14,
		5, 6, 20, 15,
		6, 0, 20, 16,
		0, 0
	}
};

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
		ta->anims[i].anim.anims[0] = (char*)map_tile_exp_0;
		ta->anims[i].anim.anims[1] = (char*)map_tile_exp_1;
		ta->anims[i].anim.anims[2] = (char*)map_tile_exp_2;
	}
}

void init_shot_state(Shot* s, u8 shot_type)
{
	s->shared.speed = SHOT_SPEED;
	s->shared.direction = D_UP;
	s->active = 0;
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
	s->up_anim.anims[0] = (shot_type == BASIC_SHOT) ? (char*) map_ball : (char*) map_rocket_up_0;
	s->up_anim.anims[1] = (shot_type == BASIC_SHOT) ? (char*) map_ball : (char*) map_rocket_up_1;
	s->up_anim.current_anim = 0;
	s->right_anim.anim_count = 2;
	s->right_anim.frames_per_anim = FRAMES_PER_ANIM;
	s->right_anim.frame_count = 0;
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
	p->max_speed = MAX_SPEED;
	p->has_over_speed = false;
	p->has_rocket = false;
	p->flags = 0;

	/* Tracks animation (Up) */
	p->up_anim.current_anim = 0;
	p->up_anim.anim_count = 1;
	p->up_anim.frames_per_anim = FRAMES_PER_ANIM;
	p->up_anim.frame_count = 0;
	p->up_anim.anims[0] = (char*)map_tank_up_0;

	/* Tracks animation (Down) */
	p->right_anim.current_anim = 0;
	p->right_anim.anim_count = 1;
	p->right_anim.frames_per_anim = FRAMES_PER_ANIM;
	p->right_anim.frame_count = 0;
	p->right_anim.anims[0] = (char*)map_tank_right_0;

	/* Explosion Animation */
	p->exp_anim.current_anim = 0;
	p->exp_anim.anim_count = 3;
	p->exp_anim.frames_per_anim = FRAMES_PER_ANIM;
	p->exp_anim.frame_count = 0;
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
	Print(9, 12, &strLevels[index*12]);
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
	u8 tmp_score[4];
	u8 save_score[4];
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
	save_delta = p_win->score - p_lose->score;

	for (u8 i = 0; i < 28; i += 4)
	{
		if (saved)
		{
			LBCopyChars(tmp_score, &scores.data[i], 4);
			LBCopyChars(&scores.data[i], save_score, 4);
			LBCopyChars(save_score, tmp_score, 4);
		}
		else
		{
			cur_delta = scores.data[i+2] - scores.data[i+3];
			if (save_delta > cur_delta)
			{
				LBCopyChars(tmp_score, &scores.data[i], 4);
				LBCopyChars(&scores.data[i], save_score, 4);
				LBCopyChars(save_score, tmp_score, 4);
				saved = 1;
			}
		}
	}
	save_eeprom(&scores);
}

void exit_game()
{
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
			shot->shared.y = player->shared.y - 8;
			break;
		case D_RIGHT:
			shot->shared.x = player->shared.x + 16;
			shot->shared.y = player->shared.y + 4;
			break;
		case D_DOWN:
			shot->shared.x = player->shared.x + 4;
			shot->shared.y = player->shared.y + 16;
			break;
		case D_LEFT:
			shot->shared.x = player->shared.x - 8;
			shot->shared.y = player->shared.y + 4;
			break;
	}
}

void print_level_score(Player* winner, Player* loser)
{
	LBPrintStr(4, 14, &winner->handle[0], 3);
	Print(8, 14, strOwns);
	LBPrintStr(13, 14, &loser->handle[0], 3);
	Print(17, 14, strBy);
	PrintByte(22, 14, winner->level_score ,true);
	PrintChar(23, 14, '-');
	PrintByte(26, 14, loser->level_score ,true);
}

void update_level_helper(JoyPadState* p, Player* player, Player* other_player, u8 hud_x)
{
	Shot* shot;
	u8 next_level;

	if ((p->pressed & BTN_START))
	{
		game.paused = game.paused ^ 1;
		load_level_tiles(false);
	}
	if (!(game.paused || (player->flags & EXPLODING_FLAG)))
	{
		if ((p->pressed & BTN_SR) && (player->banter_frame == FRAMES_PER_BANTER))
		{
			player->banter_frame = 0;
			player->banter_index = (u8) LBRandom(0, 9);
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
					}
					else
					{
						init_shot_state(shot, BASIC_SHOT);
						set_shot_animations(shot, BASIC_SHOT);
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
				collision_detect_shot(player, shot);
			}
		}
	}
	else
	{
		if (p->pressed & BTN_X)
		{
			save_score();
			exit_game();
		}
	}
	
	// Level transition
	if ((player->level_score == MAX_LEVEL_SCORE) && !(other_player->flags & EXPLODING_FLAG))
	{
		save_score();
		load_level_tiles(true);
		SetSpriteVisibility(false);
		print_level_score(player, other_player);
		LBWaitSeconds(TEXT_LINGER);
		player->level_score = 0;
		other_player->level_score = 0;
		next_level = game.current_level + 1;
		if (next_level >= LEVEL_COUNT)
		{
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
	Print(x, 0, strScore);
	Print(x, 1, strTotal);
	
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
			Print(banter_x, 2, &banter_map[player->banter_index*15]);
		}
		clear_banter = 1;
		player->banter_frame++;
	}
	else if (clear_banter)
	{
		Print(banter_x, 2, strBanterClear);
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
	char looped;
	char* map;
	
	for (u8 i = 0; i < TILE_ANIMATIONS_LENGTH; i++)
	{
		if (ta->anims[i].tile_index != 0)
		{
			map = LBGetNextFrame(&ta->anims[i].anim, &looped);
			if (looped)
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
	char looped;

	if (player->flags & EXPLODING_FLAG)
	{
		t_map = LBGetNextFrame(&player->exp_anim, &looped);
		t_flags = 0;
		if (looped)
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
			case D_UP: t_map = LBGetNextFrame(&player->up_anim, &looped); t_flags = 0; break;
			case D_RIGHT: t_map = LBGetNextFrame(&player->right_anim, &looped); t_flags = 0; break;
			case D_DOWN: t_map = LBGetNextFrame(&player->up_anim, &looped); t_flags = SPRITE_FLIP_Y; break;
			case D_LEFT: t_map = LBGetNextFrame(&player->right_anim, &looped); t_flags = SPRITE_FLIP_X; break;
			default: t_map = LBGetNextFrame(&player->up_anim, &looped); t_flags = 0; break;
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
	char looped = 0;
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
				case D_UP: s_map = LBGetNextFrame(&player->shot[i].up_anim, &looped); s_flags = 0; break;
				case D_RIGHT: s_map = LBGetNextFrame(&player->shot[i].right_anim, &looped); s_flags = 0; break;
				case D_DOWN: s_map = LBGetNextFrame(&player->shot[i].up_anim, &looped); s_flags = SPRITE_FLIP_Y; break;
				case D_LEFT: s_map = LBGetNextFrame(&player->shot[i].right_anim, &looped); s_flags = SPRITE_FLIP_X; break;
				default: s_map = LBGetNextFrame(&player->shot[i].up_anim, &looped); s_flags = 0; break;
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
	if (sprite->direction == D_UP)
	{
		sprite->y += FRAME_TIME * sprite->speed;
	}
	if (sprite->direction == D_RIGHT)
	{
		sprite->x -= FRAME_TIME * sprite->speed;
	}
	if (sprite->direction == D_DOWN)
	{
		sprite->y -= FRAME_TIME * sprite->speed;
	}
	if (sprite->direction == D_LEFT)
	{
		sprite->x += FRAME_TIME * sprite->speed;
	}
}

u8 solid_square_tile(int tile_index)
{
	u8 tile = level.level_map[tile_index];
	
	if (tile == L_BRICK) return tile;
	if (tile == L_METAL) return tile;

	return 0;
}

u8 solid_directional_tile(int tile_index, u8 x, u8 y, u8 width, u8 height)
{
	u8 tile = level.level_map[tile_index];
	u8 tile_x = (tile_index % 30) * 8;
	u8 tile_y = (tile_index / 30 + 3) * 8;

	if ((tile == L_TL) || (tile == L_BR))
	{
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, x, y, x, y+height)) return tile;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, x, y, x+width, y)) return tile;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, x+width, y, x+width, y+height)) return tile;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, x, y+height, x+width, y+height)) return tile;
	}
	if ((tile == L_TR) || (tile == L_BL))
	{
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, x, y, x, y+height)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, x, y, x+width, y)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, x+width, y, x+width, y+height)) return tile;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, x, y+height, x+width, y+height)) return tile;
	}
	
	return 0;
}

u8 player_shot(Player* p, Shot* shot)
{
	return LBCollides(p->shared.x, p->shared.y, 14, 14, shot->shared.x, shot->shared.y, 7, 7) && p->grace_frame == FRAMES_PER_GRACE;
}

u8 collision_detect_boundries(SpriteShared* sprite)
{
	if (sprite->x < 0  || sprite->x + 7 > 240 ||
	    sprite->y < 24 || sprite->y + 7 > 224)
	{
		return 1;
	}
	return 0;
}

void kill_player(Player* player, u8 hud_x)
{
	u8 x = player->shared.x / 8;
	u8 y = player->shared.y / 8 - 3;
	int tile_index = (y * 30) + x;

	if (player->has_over_speed)
	{
		SetTile(hud_x+10, 1, 0);
		DrawMap2(tile_index % 30, 3 + tile_index / 30 + 1, map_speed_itm);
		level.level_map[tile_index +30] = L_SPEED;
		player->max_speed = MAX_SPEED;
	}
	if (player->has_rocket)
	{
		SetTile(hud_x+11, 1, 0);
		DrawMap2(tile_index % 30 + 1, 3 + tile_index / 30 + 1, map_rocket_itm);
		level.level_map[tile_index +31] = L_ROCKET;
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

void collision_detect_shot(Player* player, Shot* shot)
{	 
	int tiles[2] = {0, 0};
	u8 x = shot->shared.x / 8;
	u8 y = shot->shared.y / 8 - 3;
	u8 tile;
	u8 hud_x;
	Player* p = 0;
	
	get_interesting_tile_indexes_shot(tiles, x, y, shot->shared.direction);
	
	/* Level boundries first */
	if (collision_detect_boundries(&shot->shared))
	{
		init_shot_state(shot, shot->shot_type);
		player->active_shots--;
		return;
	}
	
	/* Player interaction */
	if (player_shot(&player1, shot))
	{
		p = &player1;
		hud_x = 0;
		player2.level_score++;
		player2.score++;
		render_score(&player2, 15);
	}
	else if (player_shot(&player2, shot))
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
		return;
	}
	
	/* Tile interaction */
	for (u8 i = 0; i < 2; i++)
	{
		tile = level.level_map[tiles[i]];
		if (tile == L_EMPTY) continue;
		if (tile == L_METAL)
		{
			recoil_sprite(&shot->shared);
			init_shot_state(shot, shot->shot_type);
			player->active_shots--;
			break;
		}
		else if (tile == L_BRICK)
		{
			explode_tile(&tile_animations, tiles[i]);
			recoil_sprite(&shot->shared);
			level.level_map[tiles[i]] = L_EMPTY;
			shot->hit_count--;
			if (shot->hit_count <= 0)
			{
				init_shot_state(shot, shot->shot_type);
				player->active_shots--;
			}
			break;
		}
		else if (solid_directional_tile(tiles[i], shot->shared.x, shot->shared.y, 7, 7))
		{
			recoil_sprite(&shot->shared);
			switch (tile)
			{
				case L_TL:
					if (shot->shared.direction == D_UP)
						shot->shared.direction = D_RIGHT;
					else
						shot->shared.direction = D_DOWN;
					break;
				case L_TR:
					if (shot->shared.direction == D_UP)
						shot->shared.direction = D_LEFT;
					else
						shot->shared.direction = D_DOWN;
					break;
				case L_BL:
					if (shot->shared.direction == D_DOWN)
						shot->shared.direction = D_RIGHT;
					else
						shot->shared.direction = D_UP;
					break;
				case L_BR:
					if (shot->shared.direction == D_DOWN)
						shot->shared.direction = D_LEFT;
					else
						shot->shared.direction = D_UP;
					break;
			}
			shot->rebounds--;
			if (shot->rebounds <= 0)
			{
				init_shot_state(shot, shot->shot_type);
				player->active_shots--;
			}
			break;
		}
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
		if (solid_square_tile(tiles[i]) || solid_directional_tile(tiles[i], player->shared.x, player->shared.y, 7, 14))
		{
			recoil_sprite(&player->shared);
			player->shared.speed = 0;
		}
		else if (level.level_map[tiles[i]] == L_SPEED)
		{
			level.level_map[tiles[i]] = L_EMPTY;
			player->max_speed = OVER_SPEED;
			player->has_over_speed = true;
			DrawMap2(hud_x+10, 1, map_speed_itm);
			SetTile(tiles[i] % 30, 3 + tiles[i] / 30, 0);
		}
		else if (level.level_map[tiles[i]] == L_ROCKET)
		{
			level.level_map[tiles[i]] = L_EMPTY;
			player->has_rocket = true;
			DrawMap2(hud_x+11, 1, map_rocket_itm);
			SetTile(tiles[i] % 30, 3 + tiles[i] / 30, 0);
		}
		else if (level.level_map[tiles[i]] == L_EXPLODE)
		{
			level.level_map[tiles[i]] = L_EMPTY;
			SetTile(tiles[i] % 30, 3 + tiles[i] / 30, 0);
			player->level_score++;
			player->score++;
			render_score(player, hud_x);
			kill_player(other_player, other_player_hud_x);
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
	Print(14, 0, strVertSep);
	Print(14, 1, strVertSep);
	Print(14, 2, strVertSep);
	load_level_tiles(false);
}

void update_level(JoyPadState* p1, JoyPadState* p2)
{
	char p1_index = 0;
	char p2_index = 0;
	char p1_shot_index = 0;
	char p2_shot_index = 0;
	static u8 clear_banter_1 = 1;
	static u8 clear_banter_2 = 1;

	// Render
	if (game.paused)
	{
		SetSpriteVisibility(false);
		DrawMap2(8, 12, (const char*) map_pause);
		Print(12, 13, strPaused);
		Print(11, 14, strExit);
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
}

void load_splash()
{
	game.current_screen = SPLASH;
	clear_sprites();
	Print(7, 13, str1Player);
	Print(7, 14, str2Player);
	Print(7, 15, strHighscores);
	Print(4, 26, strCopyright);
	DrawMap2(4, 5, (const char*) map_splash);
	MapSprite2(0, map_ball, 0);
}

void update_splash(JoyPadState* p1, JoyPadState* p2)
/*
 * Splash or title screen
 */
{
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
	Print(9, 21, strSelectHandle);

	// Update
	if (p1->pressed & BTN_UP)
	{
		game.selection--;
		if (game.selection < PVCPU) game.selection = PVCPU;
		//TriggerFx(PATCH_NAVIGATE, 0xff, true);
		//TriggerNote(PCM_CHANNEL,PATCH_NAVIGATE,23,0xcf);
	}
	else if (p1->pressed & BTN_DOWN)
	{
		game.selection++;
		if (game.selection > TR) game.selection = TR;
		//TriggerFx(PATCH_NAVIGATE, 0xff, true);
		//TriggerNote(PCM_CHANNEL,PATCH_NAVIGATE,23,0xcf);
	}
	else if ((p1->pressed & BTN_A) && ((game.selection == PVCPU) || (game.selection == PVP)))
	{
		p1s.select_state = SELECTING;
		p2s.select_state = SELECTING;
		fade_through();
		load_eeprom(&handles);
		load_handle_select();
		return;
	}
	else if ((p1->pressed & BTN_A) && (game.selection == TR))
	{
		fade_through();
		load_eeprom(&scores);
		load_tank_rank();
		return;
	}
}

void load_tank_rank()
{
	u8 y = 7;
	u8 rank = 1;
	
	game.current_screen = TANK_RANK;
	clear_sprites();
	MapSprite2(0, map_tank1_up_0, 0);
	MapSprite2(4, map_tank2_up_0, 0);
	MoveSprite(0, 7*8, 1*8, 2, 2);
	MoveSprite(4, 20*8, 1*8, 2, 2);
	Print(10, 2, strHighscores);
	for (u8 i = 0; i < 20; i += 4)
	{
		PrintByte(2, y, rank, false);
		PrintChar(3, y, '.');
		LBPrintStr(5, y, &handles.data[scores.data[i]*3], 3);
		Print(9, y, strOwns);
		LBPrintStr(14, y, &handles.data[scores.data[i+1]*3], 3);
		Print(18, y, strBy);
		PrintByte(23, y, scores.data[i+2] ,true);
		PrintChar(24, y, '-');
		PrintByte(27, y, scores.data[i+3] ,true);
		y += 3;
		rank += 1;
	}
	Print(10, 23, strCancelHandle);
}

void update_tank_rank(JoyPadState* p1, JoyPadState* p2)
{
	// Update
	if (p1->pressed & BTN_X)
	{
		fade_through();
		load_splash();
	}
}


void _handle_select_helper(HandleSelectState* ps, JoyPadState* p, Player* player)
{
	if ((p->pressed & BTN_UP) && (ps->select_state == SELECTING))
	{
		ps->handle_id--;
		if (ps->handle_id < 0) ps->handle_id = 0;
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == SELECTING))
	{
		ps->handle_id++;
		if (ps->handle_id > 8) ps->handle_id = 8;
	}
	else if ((p->pressed & BTN_A) && (ps->select_state == SELECTING))
	{
		ps->select_state = EDITING;
		LBCopyChars(ps->handle, &handles.data[ps->handle_id*3], 3);
	}
	else if ((p->pressed & BTN_RIGHT) && (ps->select_state == EDITING))
	{
		ps->char_index++;
		if (ps->char_index > 2) ps->char_index = 2;
	}
	else if ((p->pressed & BTN_LEFT) && (ps->select_state == EDITING))
	{
		ps->char_index--;
		if (ps->char_index < 0) ps->char_index = 0;
	}
	else if ((p->pressed & BTN_UP) && (ps->select_state == EDITING))
	{
		ps->handle[(u8) ps->char_index]--;
		if (ps->handle[(u8) ps->char_index] < 'A') ps->handle[(u8) ps->char_index] = 'A';
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == EDITING))
	{
		ps->handle[(u8) ps->char_index]++;
		if (ps->handle[(u8) ps->char_index] > 'Z') ps->handle[(u8) ps->char_index] = 'Z';
	}
	else if ((p->pressed & BTN_A) && (ps->select_state == EDITING))
	{
		player->handle_id = ps->handle_id;
		LBCopyChars(player->handle, ps->handle, 3);
		LBCopyChars(&handles.data[ps->handle_id*3], ps->handle, 3);
		save_eeprom(&handles);
		ps->select_state = CONFIRMED;
	}
	else if ((p->pressed & BTN_X) && (ps->select_state == EDITING))
	{
		ps->select_state = SELECTING;
	}
	else if ((p->pressed & BTN_X) && (ps->select_state == CONFIRMED))
		{
			ps->select_state = EDITING;
		}
	else if ((p->pressed & BTN_X))
	{
		fade_through();
		load_splash();
	}
}

void _handle_select_render_helper(HandleSelectState* ps, JoyPadState* p, u8 x_offset, u8 idx)
{
	u8 tmp[3] = {' ', ' ', ' '};
	if (ps->select_state == SELECTING)
	{
		MapSprite2(idx, map_ball, 0);
		MapSprite2(idx+1, map_none, 0);
		MoveSprite(idx, x_offset*8, (8 + ps->handle_id)*8, 1, 1);
	}
	else if (ps->select_state == EDITING)
	{
		MapSprite2(idx, map_ball, 0);
		MapSprite2(idx+1, map_ball, 0);
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
	MapSprite2(0, map_tank1_up_0, 0);
	MapSprite2(4, map_tank2_up_0, 0);
	MoveSprite(0, 3*8, 4*8, 2, 2);
	MoveSprite(4, 20*8, 4*8, 2, 2);
	Print(9, 1, strHandlesTitle);
	Print(6, 5, strPlayer1);
	Print(23, 5, strPlayer2);
	for (int i = 0; i < 27; i += 1)
	{
		PrintChar((i % 3) + 3, 8 + (i / 3), handles.data[i]);
		PrintChar(20 + (i % 3), 8 + (i / 3), handles.data[i]);
	}
	Print(8, 21, strSelectHandle);
	Print(8, 22, strConfirmHandle);
	Print(8, 23, strCancelHandle);
	Print(8, 24, strChangeHandle);
}

void update_handle_select(JoyPadState* p1, JoyPadState* p2)
{
	u8 start_game = 0;

	// Render
	_handle_select_render_helper(&p1s, p1, 2, 8);
	if (game.selection == PVP)
	{
		_handle_select_render_helper(&p2s, p2, 19, 10);
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

int main()
{
	// Initialize
	InitMusicPlayer(my_patches);
	TriggerNote(PCM_CHANNEL,PATCH_NAVIGATE,23,0xff);
	SetTileTable(tiles_data);
	SetSpritesTileTable(sprites_data);
	SetFontTilesIndex(TILES_DATA_SIZE);
	FadeIn(FRAMES_PER_FADE, false);
	ClearVram();
	init_game_state();
	init_tile_animations(&tile_animations);
	load_splash();
	
	while (1)
	{
		WaitVsync(1);
		LBGetJoyPadState(&p1, &p2);
		switch (game.current_screen)
		{
			case SPLASH:
				update_splash(&p1, &p2);
				break;
			case TANK_RANK:
				update_tank_rank(&p1, &p2);
				break;
			case HANDLE_SELECT:
				update_handle_select(&p1, &p2);
				break;
			case LEVEL:
				/* p2 should be replaced by AI input for Player v CPU */
				update_level(&p1, &p2);
				break;
			default:
				break;
		}
	}
}
