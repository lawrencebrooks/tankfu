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
#include "data/levels.map.inc"
#include "types.h"
#include "strings.h"
#include "utils.h"
#include "macros.h"

// Globals
Game game = {
	.paused = 0
};
JoyPadState p1;
JoyPadState p2;

Player player1 = {
	.banter_frame = FRAMES_PER_BANTER,
	.grace_frame = FRAMES_PER_GRACE,
	.banter_index = 0,
	.score = 0,
	.level_score = 0,
	.direction = D_UP,
	.speed = 0,
	.max_speed = MAX_SPEED,

	/* Tracks animation (Up) */
	.up_anim.current_anim = 0,
	.up_anim.anim_count = 1,
	.up_anim.frames_per_anim = FRAMES_PER_ANIM,
	.up_anim.frame_count = 0,
	.up_anim.anims = {(char*)map_tank1_up_0},

	/* Tracks animation (Down) */
	.right_anim.current_anim = 0,
	.right_anim.anim_count = 1,
	.right_anim.frames_per_anim = FRAMES_PER_ANIM,
	.right_anim.frame_count = 0,
	.right_anim.anims = {(char*)map_tank1_right_0},

	/* Explosion Animation */
	.exp_anim.current_anim = 0,
	.exp_anim.anim_count = 3,
	.exp_anim.frames_per_anim = FRAMES_PER_ANIM,
	.exp_anim.frame_count = 0,
	.exp_anim.anims = {(char*)map_explosion_0, (char*)map_explosion_1, (char*)map_explosion_2},

	/* Shot */
	.active_shots = 0,
	.shot = {
		{
			.shot_type = BASIC_SHOT,
			.x = OFF_SCREEN,
			.y = 0,
			.rebounds = SHOT_REBOUNDS,
			.active = 0,
			.speed = SHOT_SPEED,
			.direction = D_UP,
			.up_anim.current_anim = 0,
			.up_anim.anim_count = 1,
			.up_anim.frames_per_anim = FRAMES_PER_ANIM,
			.up_anim.frame_count = 0,
			.up_anim.anims = {(char*)map_ball},
			.up_anim.current_anim = 0,
			.right_anim.anim_count = 1,
			.right_anim.frames_per_anim = FRAMES_PER_ANIM,
			.right_anim.frame_count = 0,
			.right_anim.anims = {(char*)map_ball}
		},
		{
			.shot_type = BASIC_SHOT,
			.x = OFF_SCREEN,
			.y = 0,
			.rebounds = SHOT_REBOUNDS,
			.active = 0,
			.speed = SHOT_SPEED,
			.direction = D_UP,
			.up_anim.current_anim = 0,
			.up_anim.anim_count = 1,
			.up_anim.frames_per_anim = FRAMES_PER_ANIM,
			.up_anim.frame_count = 0,
			.up_anim.anims = {(char*)map_ball},
			.right_anim.anim_count = 1,
			.right_anim.frames_per_anim = FRAMES_PER_ANIM,
			.right_anim.frame_count = 0,
			.right_anim.anims = {(char*)map_ball}
		}
	}

};
Player player2 = {
	.banter_frame = FRAMES_PER_BANTER,
	.grace_frame = FRAMES_PER_GRACE,
	.banter_index = 0,
	.score = 0,
	.level_score = 0,
	.direction = D_UP,
	.speed = 0,
	.max_speed = MAX_SPEED,

	/* Tracks animation (Up) */
	.up_anim.current_anim = 0,
	.up_anim.anim_count = 1,
	.up_anim.frames_per_anim = FRAMES_PER_ANIM,
	.up_anim.frame_count = 0,
	.up_anim.anims = {(char*)map_tank2_up_0},

	/* Tracks animation (Down) */
	.right_anim.current_anim = 0,
	.right_anim.anim_count = 1,
	.right_anim.frames_per_anim = FRAMES_PER_ANIM,
	.right_anim.frame_count = 0,
	.right_anim.anims = {(char*)map_tank2_right_0},

	/* Explosion Animation */
	.exp_anim.current_anim = 0,
	.exp_anim.anim_count = 3,
	.exp_anim.frames_per_anim = FRAMES_PER_ANIM,
	.exp_anim.frame_count = 0,
	.exp_anim.anims = {(char*)map_explosion_0, (char*)map_explosion_1, (char*)map_explosion_2},

	/* Shot */
	.active_shots = 0,
	.shot = {
		{
			.shot_type = BASIC_SHOT,
			.x = OFF_SCREEN,
			.y = 0,
			.rebounds = SHOT_REBOUNDS,
			.active = 0,
			.speed = SHOT_SPEED,
			.direction = D_UP,
			.up_anim.current_anim = 0,
			.up_anim.anim_count = 1,
			.up_anim.frames_per_anim = FRAMES_PER_ANIM,
			.up_anim.frame_count = 0,
			.up_anim.anims = {(char*)map_ball},
			.right_anim.anim_count = 1,
			.right_anim.frames_per_anim = FRAMES_PER_ANIM,
			.right_anim.frame_count = 0,
			.right_anim.anims = {(char*)map_ball}
		},
		{
			.shot_type = BASIC_SHOT,
			.x = OFF_SCREEN,
			.y = 0,
			.rebounds = SHOT_REBOUNDS,
			.active = 0,
			.speed = SHOT_SPEED,
			.direction = D_UP,
			.up_anim.current_anim = 0,
			.up_anim.anim_count = 1,
			.up_anim.frames_per_anim = FRAMES_PER_ANIM,
			.up_anim.frame_count = 0,
			.up_anim.anims = {(char*)map_ball},
			.right_anim.anim_count = 1,
			.right_anim.frames_per_anim = FRAMES_PER_ANIM,
			.right_anim.frame_count = 0,
			.right_anim.anims = {(char*)map_ball}
		}
	}
};

Level level = {
	.buffer_size = 0,
	.render_all = 1,
	.render_index = 0
};
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
int random_seed;

int random(int from, int to)
/*
 * Return a random number between 'from' and 'to'.
 */
{
	static u8 shift_count = 0;
	int shifted = random_seed >> shift_count;
	int delta = to - from;

	shift_count++;
	if (shift_count >= 16) shift_count = 0;

	return from + ((delta + shifted) % delta);
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

void reset_player_state(Player* s)
{
	s->banter_frame = FRAMES_PER_BANTER;
	s->banter_index = 0;
	s->score = 0;
	s->level_score = 0;
}

void reset_game_state()
{
	game.current_screen = SPLASH;
	game.current_level = 0;
	game.level_count = LEVEL_COUNT;
	game.selection = PVCPU;
	game.paused = 0;
	reset_player_state(&player1);
	reset_player_state(&player2);
}

void player_level_init(Player* player)
{
	player->level_score = 0;
	player->grace_frame = 0;
	player->x = player->spawn_x;
	player->y = player->spawn_y;
	player->direction = D_UP;
	player->speed = 0;
}

void load_level(int level_number)
{
    int level_start = level_number*30*25;

	fade_through();
	game.current_screen = LEVEL;
	game.current_level = 0;
	game.level_count = LEVEL_COUNT;
	level.render_all = 1;
	level.render_index = 0;
	for (int i = 0; i < 30*25; i++)
	{
		level.level_map[i] = pgm_read_byte(&level_data[level_start+i]);
		if (level.level_map[i] == L_P1_SPAWN)
		{
			player1.spawn_x = (i % 30) * 8;
			player1.spawn_y = (i / 30) * 8 + 3*8;
			player_level_init(&player1);
		}
		if (level.level_map[i] == L_P2_SPAWN)
		{
			player2.spawn_x = (i % 30) * 8;
			player2.spawn_y = (i / 30) * 8 + 3*8;
			player_level_init(&player2);
		}
	}
	clear_sprites();
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

void update_level_helper(JoyPadState* p, Player* player)
{
	Shot* shot;

	if ((p->pressed & BTN_START))
	{
		game.paused = game.paused ^ 1;
	}
	if (!game.paused)
	{
		if ((p->pressed & BTN_SR) && (player->banter_frame == FRAMES_PER_BANTER))
		{
			player->banter_frame = 0;
			player->banter_index = (u8) random(0, 9);
		}
		player->speed = player->max_speed;
		if ((p->held & BTN_UP))
		{
			player->direction = D_UP;
			player->y -= FRAME_TIME * player->speed;
		}
		else if ((p->held & BTN_RIGHT))
		{
			player->direction = D_RIGHT;
			player->x += FRAME_TIME * player->speed;
		}
		else if ((p->held & BTN_DOWN))
		{
			player->direction = D_DOWN;
			player->y += FRAME_TIME * player->speed;
		}
		else if ((p->held & BTN_LEFT))
		{
			player->direction = D_LEFT;
			player->x -= FRAME_TIME * player->speed;
		}
		else
		{
			player->speed = 0;
		}
		if ((p->pressed & BTN_A) && (player->active_shots < MAX_SHOTS))
		{
			for (u8 i = 0; i < MAX_SHOTS; i++)
			{
				shot = &player->shot[i];
				if (!shot->active)
				{
					player->active_shots++;
					shot->direction = player->direction;
					shot->x = player->x + 4;
					shot->y = player->y + 4;
					shot->active = 1;
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
				switch (shot->direction)
				{
					case D_UP: shot->y -= FRAME_TIME * shot->speed; break;
					case D_RIGHT: shot->x += FRAME_TIME * shot->speed; break;
					case D_DOWN: shot->y += FRAME_TIME * shot->speed; break;
					case D_LEFT: shot->x -= FRAME_TIME * shot->speed; break;
					default: break;
				}
			}
		}
	}
	else
	{
		if (p->pressed & BTN_X)
		{
			save_score();
			fade_through();
			reset_game_state();
			game.current_screen = TANK_RANK;
		}
		level.render_all = 1;
	}
}

void render_score(Player* player, u8 x, u8 banter_x)
{
	LBPrintStr(x+10, 0, player->handle, 3);
	Print(x, 0, strScore);
	PrintByte(x+8, 0, player->level_score, false);
	Print(x, 1, strTotal);
	PrintByte(x+8, 1, player->score, false);

	// Banter
	if (player->banter_frame != FRAMES_PER_BANTER)
	{
		Print(banter_x, 2, banter_map[player->banter_index]);
		player->banter_frame++;
	}
	else
	{
		Print(banter_x, 2, strBanterClear);
	}
}

void render_player(Player* player, u8 sprite_index)
{
	MoveSprite(sprite_index, player->x, player->y, 2, 2);
}

void render_shot(Player* player, u8 sprite_index)
{
	for (u8 i = 0; i < MAX_SHOTS; i++)
	{
		MoveSprite(sprite_index, player->shot[i].x, player->shot[i].y, 1, 1);
		sprite_index++;
	}
}

char tank_map(Player* player, char sprite_index)
{
	char* t_map = 0;
	u8 t_flags = 0;
	static u8 toggle_counter = FRAMES_PER_BLANK;
	static u8 toggle_blank = 0;
	char looped;

	if (player->grace_frame != FRAMES_PER_GRACE)
	{
		player->grace_frame++;
	}
	switch (player->direction)
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
			switch (shot->direction)
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

int first_index()
{
	int result = 0;

	if (level.render_all)
	{
		result = 0;
	}
	else
	{
		result = level.render_buffer[level.render_index];
		if (level.buffer_size == 0) result = 30*25;
	}
	return result;
}

int inc_index(int* i)
{
	int result;
	if (level.render_all)
	{
		result = *i;
		*i = *i + 1;
	}
	else
	{
		result = level.render_buffer[level.render_index];
		level.render_index++;
		if (level.render_index == level.buffer_size)
		{
			*i = 30*25;
		}
		else
		{
			*i = level.render_buffer[level.render_index];
		}
	}
	return result;
}

u8 solid_tile(int tile_index, Player* player)
{
	u8 tile = level.level_map[tile_index];
	u8 tile_x = (tile_index % 30) * 8;
	u8 tile_y = (tile_index / 30 + 3) * 8;

	if (tile == L_BRICK) return 1;
	if (tile == L_METAL) return 1;
	if ((tile == L_TL) || (tile == L_BR))
	{
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, player->x, player->y, player->x, player->y+14)) return 1;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, player->x, player->y, player->x+14, player->y)) return 1;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, player->x+14, player->y, player->x+14, player->y+14)) return 1;
		if (LBLineIntersect(tile_x, tile_y+7, tile_x+7, tile_y, player->x, player->y+14, player->x+14, player->y+14)) return 1;
	}
	if ((tile == L_TR) || (tile == L_BL))
	{
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, player->x, player->y, player->x, player->y+14)) return 1;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, player->x, player->y, player->x+14, player->y)) return 1;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, player->x+14, player->y, player->x+14, player->y+14)) return 1;
		if (LBLineIntersect(tile_x, tile_y, tile_x+7, tile_y+7, player->x, player->y+14, player->x+14, player->y+14)) return 1;
	}

	return 0;
}

void collision_detect_tiles(Player* player)
{
	int tiles[8] = {0,0,0,0,0,0,0,0};
	u8 x = player->x / 8;
	u8 y = player->y / 8 - 3;

	tiles[0] = (y * 30) + x;
	tiles[1] = tiles[0]+2;
	tiles[2] = tiles[0] + 60;
	tiles[3] = tiles[1] + 60;
	tiles[4] = tiles[0]+1;
    tiles[5] = tiles[1]+30;
	tiles[6] = tiles[2]+1;
	tiles[7] = tiles[0]+30;

	for (u8 i = 0; i < 8; i++)
	{
		if (solid_tile(tiles[i], player))
		{
			if (player->direction == D_UP)
			{
				player->y += FRAME_TIME * player->speed;
			}
			if (player->direction == D_RIGHT)
			{
				player->x -= FRAME_TIME * player->speed;
			}
			if (player->direction == D_DOWN)
			{
				player->y -= FRAME_TIME * player->speed;
			}
			if (player->direction == D_LEFT)
			{
				player->x += FRAME_TIME * player->speed;
			}
			player->speed = 0;
		}
	}
}

void update_level(JoyPadState* p1, JoyPadState* p2)
{
	u8 x;
	u8 y;
	char p1_index = 0;
	char p2_index = 0;
	char p1_shot_index = 0;
	char p2_shot_index = 0;

	// Render
	if (game.paused)
	{
		DrawMap2(8, 12, (const char*) map_pause);
		Print(12, 13, strPaused);
		Print(11, 14, strExit);
	}
	else
	{
		p2_index = tank_map(&player1, p1_index);
		p1_shot_index = tank_map(&player2, p2_index);
		p2_shot_index = shot_map(&player1, p1_shot_index);
		shot_map(&player2, p2_shot_index);
		render_score(&player1, 0, 15);
		render_score(&player2, 15, 0);
		Print(14, 0, strVertSep);
		Print(14, 1, strVertSep);
		Print(14, 2, strVertSep);

		for(int i = first_index(); i < 30*25; inc_index(&i))
		{
			x = i % 30;
			y = 3 + i / 30;
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
		level.render_all = 0;
		render_player(&player1, p1_index);
		render_player(&player2, p2_index);
		render_shot(&player1, p1_shot_index);
		render_shot(&player2, p2_shot_index);
	}

	// Update
	update_level_helper(p1, &player1);
	update_level_helper(p2, &player2);
	collision_detect_tiles(&player1);
	collision_detect_tiles(&player2);
}

void update_splash(JoyPadState* p1, JoyPadState* p2)
/*
 * Splash or title screen
 */
{
	clear_sprites();
	Print(7, 13, str1Player);
	Print(7, 14, str2Player);
	Print(7, 15, strHighscores);
	Print(4, 26, strCopyright);
	DrawMap2(4, 5, (const char*) map_splash);
	MapSprite2(0, map_ball, 0);

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
	}
	else if (p1->pressed & BTN_DOWN)
	{
		game.selection++;
		if (game.selection > TR) game.selection = TR;
	}
	else if ((p1->pressed & BTN_A) && ((game.selection == PVCPU) || (game.selection == PVP)))
	{
		p1s.select_state = SELECTING;
		p2s.select_state = SELECTING;
		fade_through();
		load_eeprom(&handles);
		game.current_screen = HANDLE_SELECT;
		return;
	}
	else if ((p1->pressed & BTN_A) && (game.selection == TR))
	{
		fade_through();
		load_eeprom(&scores);
		game.current_screen = TANK_RANK;
		return;
	}
}

void update_tank_rank(JoyPadState* p1, JoyPadState* p2)
{
	u8 y = 7;
	u8 rank = 1;

	// Render
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

	// Update
	if (p1->pressed & BTN_X)
	{
		fade_through();
		game.current_screen = SPLASH;
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
		game.current_screen = SPLASH;
	}
}

void _handle_select_render_helper(HandleSelectState* ps, JoyPadState* p, u8 x_offset, u8 idx)
{
	u8 tmp[3] = {' ', ' ', ' '};
	if (ps->select_state == SELECTING)
	{
		MapSprite2(idx, map_ball, 0);
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
	}
	LBPrintStr(x_offset+5, (8 + ps->handle_id), tmp, 3);
}

void update_handle_select(JoyPadState* p1, JoyPadState* p2)
{
	u8 start_game = 0;

	// Render
	clear_sprites();
	MapSprite2(0, map_tank1_up_0, 0);
	MapSprite2(4, map_tank2_up_0, 0);
	MoveSprite(0, 3*8, 4*8, 2, 2);
	MoveSprite(4, 20*8, 4*8, 2, 2);
	_handle_select_render_helper(&p1s, p1, 2, 8);
	if (game.selection == PVP)
	{
		_handle_select_render_helper(&p2s, p2, 19, 10);
	}
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
		load_level(0);
	}
}

int get_random_seed()
{
	// Needs replacing with actual random seed.
	return 32767;
}

int main()
{
	// Initialize
	SetMasterVolume(0);
	StopSong();
	random_seed = get_random_seed();
	SetTileTable(tiles_data);
	SetSpritesTileTable(sprites_data);
	SetFontTilesIndex(TILES_DATA_SIZE);
	FadeIn(FRAMES_PER_FADE, false);
	reset_game_state();

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
