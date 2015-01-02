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

// Screens
#define SPLASH 0
#define TANK_RANK 1
#define HANDLE_SELECT 2
#define LEVEL 3

// Level macros
#define LEVEL_COUNT 1

// Play modes
#define PVP 0
#define PVCPU 1

// Fade In
#define FRAMES_PER_FADE 3

Game game;
Player player1;
Player player2;
Level level;

void resetGameState(Game* s)
{
	s->current_screen = SPLASH;
	s->current_level = 0;
	s->level_count = LEVEL_COUNT;
	s->play_mode = PVP;
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

void update_splash()
/*
 * Splash or title screen
 */
{
	MapSprite(0, map_ball);
	MoveSprite(0, 7*8, 13*8, 1, 1);
	Print(8, 13, str1Player);
	Print(8, 14, str2Player);
	Print(8, 15, strHighscores);
	Print(3, 26, strCopyright);
	DrawMap2(4, 5, (const char*) map_splash);
}

void update_tank_rank()
{

}

void update_handle_select()
{

}

void update_level()
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
		switch (game.current_screen)
		{
			case SPLASH:
				update_splash();
				break;
			case TANK_RANK:
				update_tank_rank();
				break;
			case HANDLE_SELECT:
				update_handle_select();
				break;
			case LEVEL:
				update_level();
				break;
			default:
				break;
		}
	}
}
