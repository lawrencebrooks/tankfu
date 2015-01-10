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
#define CONFIRMED 2

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
	// 8. FFF
	// 9. GGG
	// 10. HHH
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
		0x48, 0x48, 0x48,
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
	Print(7, 13, str1Player);
	Print(7, 14, str2Player);
	Print(7, 15, strHighscores);
	Print(4, 26, strCopyright);
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
	}

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
}

void update_tank_rank(JoyPadState* p1, JoyPadState* p2)
{
	unsigned char y = 7;
	unsigned char rank = 1;

	// Update
	if (p1->pressed & BTN_X)
	{
		fade_through();
		game.current_screen = SPLASH;
		return;
	}
	// Render
	clear_sprites();
	MapSprite(0, map_tank1_up_0);
	MapSprite(4, map_tank2_up_0);
	MoveSprite(0, 7*8, 1*8, 2, 2);
	MoveSprite(4, 20*8, 1*8, 2, 2);
	Print(10, 2, strHighscores);
	for (unsigned char i = 0; i < 20; i += 4)
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
}


unsigned char _handle_select_helper(HandleSelectState* ps, JoyPadState* p, Player* player)
{
	if ((p->pressed & BTN_UP) && (ps->select_state == SELECTING))
	{
		ps->handle_id--;
		if (ps->handle_id < 0) ps->handle_id = 0;
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == SELECTING))
	{
		ps->handle_id++;
		if (ps->handle_id > 9) ps->handle_id = 9;
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
		ps->handle[(unsigned char) ps->char_index]--;
		if (ps->handle[(unsigned char) ps->char_index] < 'A') ps->handle[(unsigned char) ps->char_index] = 'A';
	}
	else if ((p->pressed & BTN_DOWN) && (ps->select_state == EDITING))
	{
		ps->handle[(unsigned char) ps->char_index]++;
		if (ps->handle[(unsigned char) ps->char_index] > 'Z') ps->handle[(unsigned char) ps->char_index] = 'Z';
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
		return 0;
	}
	return 1;
}

void _handle_select_render_helper(HandleSelectState* ps, JoyPadState* p, unsigned char x_offset, unsigned char idx)
{
	unsigned char tmp[3] = {' ', ' ', ' '};
	if (ps->select_state == SELECTING)
	{
		MapSprite(idx, map_ball);
		MoveSprite(idx, x_offset*8, (7 + ps->handle_id)*8, 1, 1);
	}
	else if (ps->select_state == EDITING)
	{
		MapSprite(idx, map_ball);
		MapSprite(idx+1, map_ball);
		MoveSprite(idx, (x_offset+5+ps->char_index)*8, (7 + ps->handle_id - 1)*8, 1, 1);
		MoveSprite(idx+1, (x_offset+5+ps->char_index)*8, (7 + ps->handle_id + 1)*8, 1, 1);
		LBCopyChars(tmp, ps->handle, 3);
	}
	else if (ps->select_state == CONFIRMED)
	{
		PrintChar(x_offset+6, 4, '(');
		LBPrintStr(x_offset+7, 4, ps->handle, 3);
		PrintChar(x_offset+10, 4, ')');
	}
	LBPrintStr(x_offset+5, (7 + ps->handle_id), tmp, 3);
}

void update_handle_select(JoyPadState* p1, JoyPadState* p2)
{
	unsigned char do_render = 0;
	unsigned char start_game = 0;

	// Update
	do_render = _handle_select_helper(&p1s, p1, &player1);
	if (p1s.select_state == CONFIRMED) start_game = 1;
	if ((game.selection == PVP) && (do_render))
	{
		do_render = _handle_select_helper(&p2s, p2, &player2);
		if (p2s.select_state != CONFIRMED) start_game = 0;
	}

	// Render
	if (do_render)
	{
		clear_sprites();
		MapSprite(0, map_tank1_up_0);
		MapSprite(4, map_tank2_up_0);

		// Position sprites
		MoveSprite(0, 3*8, 3*8, 2, 2);
		MoveSprite(4, 20*8, 3*8, 2, 2);
		_handle_select_render_helper(&p1s, p1, 2, 8);
		if (game.selection == PVP)
		{
			_handle_select_render_helper(&p2s, p2, 19, 10);
		}

		// Print
		Print(4, 1, strHandlesTitle);
		Print(6, 4, strPlayer1);
		Print(23, 4, strPlayer2);
		//Print(1, 5, strUnderline);
		//Print(18, 5, strUnderline);
		for (int i = 0; i < 30; i += 1)
		{
			PrintChar((i % 3) + 3, 7 + (i / 3), handles.data[i]);
			PrintChar(20 + (i % 3), 7 + (i / 3), handles.data[i]);
		}

		// Instructions
		Print(7, 20, strSelectHandle);
		Print(7, 21, strConfirmHandle);
		Print(7, 22, strCancelHandle);
		Print(7, 23, strChangeHandle);
	}

	// Start Game
	if (start_game)
	{

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
				update_level(&p1, &p2);
				break;
			default:
				break;
		}
	}
}
