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

// EEPROM ID's
#define EEPROM_HANDLES_ID 0x87
#define EEPROM_TANK_RANK_ID 0x88

// Screens
#define SPLASH 0
#define TANK_RANK 1
#define HANDLE_SELECT 2
#define LEVEL 3

// Level macros
#define LEVEL_COUNT 1

// Selections
#define PVCPU 0
#define PVP 1
#define TR 2

// Fade
#define FRAMES_PER_FADE 3

// Handle select states
#define SELECTING 0
#define EDITING 1

// General macros
#define MAX_SPRITES 13

// Globals
Game game;
JoyPadState p1;
JoyPadState p2;
Player player1;
Player player2;
Level level;
struct EepromBlockStruct handles = {
	.id = EEPROM_HANDLES_ID,
	// 1. UZE
	// 2. LJB
	// 3. AAA
	// 4. BBB
	// 5. CCC
	// 6. DDD
	// 7. EEE
	.data = {
		1, 0x55, 0x5a, 0x45,
		2, 0x4c, 0x4a, 0x42,
		3, 0x41, 0x41, 0x41,
		4, 0x42, 0x42, 0x42,
		5, 0x43, 0x43, 0x43,
		6, 0x44, 0x44, 0x44,
		7, 0x45, 0x45, 0x45,
		0, 0
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
		1, 2, 20, 10,
		2, 3, 20, 11,
		3, 4, 20, 12,
		4, 5, 20, 13,
		5, 6, 20, 14,
		6, 7, 20, 15,
		7, 1, 20, 16,
		0, 0
	}
};

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
	unsigned char status = 0;
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
		MapSprite(i, map_none);
	}
}

unsigned char* locate_handle(unsigned char handle_id)
/*
 * Find the start of the handle data referenced by handle_id
 */
{
	for (int i = 0; i < 28; i += 4)
	{
		if (handles.data[i] == handle_id)
		{
			return &handles.data[i+1];
		}
	}
	return 0;
}

void save_eeprom(struct EepromBlockStruct* block)
/*
 * Save to EEPROM
 */
{
	EepromWriteBlock(block);
}

void resetGameState(Game* s)
{
	s->current_screen = SPLASH;
	s->current_level = 0;
	s->level_count = LEVEL_COUNT;
	s->selection = PVCPU;
}

void resetPlayerState(Player* s)
{

}

void resetLevelSate(Level* s)
{

}

void resetShotState(Shot* s)
{

}

void resetAnimState(Animation* s)
{

}

void update_splash(JoyPadState* p1, JoyPadState* p2)
/*
 * Splash or title screen
 */
{
	clear_sprites();
	Print(8, 13, str1Player);
	Print(8, 14, str2Player);
	Print(8, 15, strHighscores);
	Print(3, 26, strCopyright);
	DrawMap2(4, 5, (const char*) map_splash);
	MapSprite(0, map_ball);

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
	else if ((p1->pressed & BTN_START) && ((game.selection == PVCPU) || (game.selection == PVP)))
	{
		fade_through();
		load_eeprom(&handles);
		game.current_screen = HANDLE_SELECT;
		return;
	}

	// Render
	switch (game.selection)
	{
		case PVCPU:
			MoveSprite(0, 7*8, 13*8, 1, 1);
			break;
		case PVP:
			MoveSprite(0, 7*8, 14*8, 1, 1);
			break;
		case TR:
			MoveSprite(0, 7*8, 15*8, 1, 1);
			break;
	}
}

void update_tank_rank(JoyPadState* p1, JoyPadState* p2)
{

}


unsigned char _handle_select_helper(HandleSelectState* ps, JoyPadState* p)
{
	if ((p->pressed & BTN_UP) && (ps->select_state == SELECTING))
	{
		ps->handle_id--;
		if (ps->handle_id < 1) ps->handle_id = 1;
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == SELECTING))
	{
		ps->handle_id++;
		if (ps->handle_id > 7) ps->handle_id = 7;
	}
	else if ((p->pressed & BTN_A) && (ps->select_state == SELECTING))
	{
		ps->select_state = EDITING;
	}
	else if ((p->pressed & BTN_X) && (ps->select_state == EDITING))
	{
		ps->select_state = SELECTING;
	}
	else if ((p->pressed & BTN_SELECT))
	{
		fade_through();
		game.current_screen = SPLASH;
		return 0;
	}
	return 1;
}

void _handle_select_render_helper(HandleSelectState* ps, JoyPadState* p, unsigned char x_offset, unsigned char idx)
{
	if (ps->select_state == SELECTING)
	{
		MapSprite(idx, map_ball);
		MoveSprite(idx, x_offset*8, (6 + ps->handle_id)*8, 1, 1);
	}
	else if (ps->select_state == EDITING)
	{
		MapSprite(idx, map_ball);
		MapSprite(idx+1, map_ball);
		MoveSprite(idx, (x_offset+4)*8, (6 + ps->handle_id - 1)*8, 1, 1);
		MoveSprite(idx+1, (x_offset+4)*8, (6 + ps->handle_id + 1)*8, 1, 1);
	}
}

void update_handle_select(JoyPadState* p1, JoyPadState* p2)
{
	unsigned char do_render = 0;
	static HandleSelectState p1s = {
		.handle_id = 1,
		.char_index = 0,
		.select_state = SELECTING,
	};
	static HandleSelectState p2s = {
		.handle_id = 1,
		.char_index = 0,
		.select_state = SELECTING,
	};

	// Update
	do_render = _handle_select_helper(&p1s, p1);
	if (game.selection == PVP)
	{
		do_render = _handle_select_helper(&p2s, p2);
	}

	// Render
	if (do_render)
	{
		clear_sprites();
		MapSprite(0, map_tank1_up_0);
		MapSprite(4, map_tank2_up_0);

		// Position sprites
		MoveSprite(0, 1*8, 3*8, 2, 2);
		MoveSprite(4, 18*8, 3*8, 2, 2);
		_handle_select_render_helper(&p1s, p1, 1, 8);
		if (game.selection == PVP)
		{
			_handle_select_render_helper(&p2s, p2, 18, 10);
		}

		// Print
		Print(4, 1, strHandlesTitle);
		Print(4, 4, strPlayer1);
		Print(21, 4, strPlayer2);
		Print(1, 5, strUnderline);
		Print(18, 5, strUnderline);
		for (int i = 0; i < 28; i += 1)
		{
			if ((i % 4) == 0) continue;
			PrintChar((i % 4) + 1, 7 + (i / 4), handles.data[i]);
			PrintChar(18 + (i % 4), 7 + (i / 4), handles.data[i]);
		}

		// Instructions
		Print(8, 20, strSelectHandle);
		Print(8, 21, strConfirmHandle);
		Print(8, 22, strCancelHandle);
		Print(8, 23, strChangeHandle);
	}
}

void update_level(JoyPadState* p1, JoyPadState* p2)
{

}

int main()
{
	// Initialize
	SetTileTable(tiles_data);
	SetSpritesTileTable(sprites_data);
	SetFontTilesIndex(TILES_DATA_SIZE);
	FadeIn(FRAMES_PER_FADE, false);
	resetGameState(&game);

	while (1)
	{
		WaitVsync(1);
		getJoyPadState(&p1, &p2);
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
				update_level(&p1, &p2);
				break;
			default:
				break;
		}
	}
}
