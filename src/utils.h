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

typedef struct sJoyPadState {
	unsigned int pressed;
	unsigned int released;
	unsigned int held;
	unsigned char held_cycles;
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
	static unsigned int p_prev[2] = {0,0};

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

void LBCopyChars(u8* dst, u8 *src, u8 count)
/*
 * Custom string copy
 */
{
	for (u8 i = 0; i < count; i++)
	{
		dst[i] = src[i];
	}
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

u8 LBCollides(u8 x1, u8 y1, u8 width1, u8 height1,
						 u8 x2, u8 y2, u8 width2, u8 height2)
{
	if (y1 + height1 <= y2) return 0;
	if (y1 >= y2 + height2) return 0;
	if (x1 + width1 <= x2) return 0;
	if (x1 >= x2 + width2) return 0;
	return 1;
}

u8 LBLineIntersect(u8 line1x1, u8 line1y1, u8 line1x2, u8 line1y2,
							  u8 line2x1, u8 line2y1, u8 line2x2, u8 line2y2)
{
	float ua, ub;
	float denom;

	denom = ((line2y2 - line2y1) * (line1x2 - line1x1)) -
			 ((line2x2 - line2x1) * (line1y2 - line1y1));
	if (denom == 0) return 0;

	ua = (((line2x2 - line2x1) * (line1y1 - line2y1)) -
		 ((line2y2 - line2y1) * (line1x1 - line2x1))) / denom;
	ub = (((line1x2 - line1x1) * (line1y1 - line2y1)) -
		 ((line1y2 - line1y1) * (line1x1 - line2x1))) / denom;
	if ((ua < 0) || (ua > 1) || (ub < 0) || (ub > 1)) return 0;

	return 1;
}

int LBRandom(unsigned int from, unsigned int to)
/*
 * Return a random number between 'from' and 'to'.
 */
{
	static unsigned int random_seed = 0;
	if (random_seed == 0) random_seed = GetTrueRandomSeed();
	
	static u8 shift_count = 0;
	unsigned int shifted = random_seed >> shift_count;
	unsigned int delta = to - from;

	shift_count++;
	if (shift_count >= 16) shift_count = 0;

	return from + ((delta + shifted) % delta);
}

void LBWaitUs(u16 micro_seconds)
{
#if JAMMA
	micro_seconds = micro_seconds / 1500;
	for (;micro_seconds > 0; micro_seconds--) {
		WaitVsync(1);
		handle_coin_insert();
	}
#else
	WaitUs(micro_seconds);
#endif
}

void LBWaitSeconds(u8 seconds)
{
	for(u8 i = 0; i < seconds; i++)
	{
		LBWaitUs(65535);
	}
}

void LBHideAllSprites()
{
	for(int i = 0; i < MAX_SPRITES; i++)
	{
		sprites[i].x = (SCREEN_TILES_H*TILE_WIDTH);
	}
}

#endif
