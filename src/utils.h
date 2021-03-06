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
#ifndef LB_UTILS_H
#define LB_UTILS_H

#if JAMMA
#include "jamma.h"
#endif

#include "macros.h"
#include "uzenet.h"

u16 p_prev[2] = {0,0};

typedef struct sJoyPadState {
	u16 pressed;
	u16 released;
	u16 held;
	u8 held_cycles;
} JoyPadState;

typedef struct sAnimation {
	u8 current_anim;		// Current animation
	u8 anim_count;			// Total animation count
	u8 frames_per_anim;		// Animation lifetime in amount of render frames
	u8 frame_count;			// Render frame counter
	u8 looped;
	u8 reversing;
	char* anims[3];
} Animation;

typedef struct sTileAnimation {
	Animation anim;
	int tile_index;
} TileAnimation;

char* LBGetNextFrame(Animation* anim)
{
	anim->looped = 0;
	anim->frame_count += 1;
	if (anim->frame_count < anim->frames_per_anim)
	{
		return anim->anims[anim->current_anim];
	}
	anim->frame_count = 0;
	anim->current_anim = (anim->current_anim + 1) % anim->anim_count;
	if (anim->current_anim == 0) anim->looped = 1;
	return anim->anims[anim->current_anim];
}

char* LBGetNextFrameReverse(Animation* anim)
{
	anim->looped = 0;
	anim->frame_count += 1;
	if (anim->frame_count < anim->frames_per_anim)
	{
		return anim->anims[anim->current_anim];
	}
	anim->frame_count = 0;
	if (anim->reversing)
	{
		anim->current_anim = anim->current_anim - 1;
		if (anim->current_anim == 0xff)
		{
			anim->current_anim = 0;
			anim->looped = 1;
			anim->reversing = 0;
		}
	}
	else
	{
		anim->current_anim = (anim->current_anim + 1) % anim->anim_count;
		if (anim->current_anim == 0) 
		{
			anim->reversing = 1;
			anim->current_anim = anim->anim_count - 1;
		}
	}
	return anim->anims[anim->current_anim];
}

void LBGetJoyPadState(JoyPadState* p, unsigned char index)
/*
 * Get the current joy pad button state for index controller
 */
{
	p->held = ReadJoypad(index);

	// Count held cycles
	if (p->held == 0 || p->held != p_prev[index])
	    p->held_cycles = 0;
	else
	    p->held_cycles += 1;

	p->pressed = p->held & (p->held ^ p_prev[index]);
	p->released = p_prev[index] & (p->held ^ p_prev[index]);
	p_prev[index] = p->held;
}

void LBPrintStr(u8 x, u8 y, u8* txt, u8 count)
{
	for (u8 i = 0; i < count; i++)
	{
		PrintChar(x+i, y, txt[i]);
	}
}

void LBPrintByte(u8 x, u8 y, u8 value, char pad)
{
	u8 tmp = 0;
	for (u8 i = 0; i < 3; i++)
	{
		tmp = value % 10 + 48;
		LBPrintStr(x--, y, &tmp, 1);
		value /= 10;
		if (!pad && value == 0) break;
	}
}

u8 LBCollides(u16 x1, u16 y1, u16 width1, u16 height1,
						 u16 x2, u16 y2, u16 width2, u16 height2)
{
	if (y1 + height1 <= y2) return 0;
	if (y1 >= y2 + height2) return 0;
	if (x1 + width1 <= x2) return 0;
	if (x1 >= x2 + width2) return 0;
	return 1;
}

u8 LBRandom(u8 from, u8 to)
/*
 * Return a random number between 'from' and 'to'.
 */
{
    u8 tmp = GetPrngNumber(0) % 256;
    return ((tmp) % (to - from + 1)) + from;
}

void LBWaitSeconds(u16 seconds, u8 netMessageSize)
{
	seconds *= 60;
	for(u8 i = 0; i < seconds; i++)
	{
		WaitVsync(1);
		wifiGetAndDiscard(netMessageSize);
#if JAMMA
		handle_coin_insert();
#endif
	}
}

void LBHideAllSprites()
{
	for(int i = 0; i < MAX_SPRITES; i++)
	{
		sprites[i].x = OFF_SCREEN;
	}
}


void LBPlaySound(u8 game_selection, u8 p1_flags, u8 p2_flags, u8 patch)
{
#if JAMMA
	if(no_demo_sound() && game_selection == CPUVCPU) {} else if (!((p1_flags & EXPLODING_FLAG) || (p2_flags & EXPLODING_FLAG))) TriggerFx(patch,0xff,true);
#else
	if (patch == PATCH_TANK_EXPLODE) TriggerFx(patch,0xff,true);
	else if (!((p1_flags & EXPLODING_FLAG) || (p2_flags & EXPLODING_FLAG))) TriggerFx(patch,0xff,true);
#endif
}

#endif
