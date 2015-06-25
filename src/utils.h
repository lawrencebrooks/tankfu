/*
 * Author: Lawrence Brooks
 */
#ifndef LB_UTILS_H
#define LB_UTILS_H

typedef struct sJoyPadState {
	unsigned int pressed;
	unsigned int released;
	unsigned int held;
} JoyPadState;

typedef struct sAnimation {
	u8 current_anim;			// Current animation
	u8 anim_count;			// Total animation count
	u8 frames_per_anim;		// Animation lifetime in amount of render frames
	u8 frame_count;			// Render frame counter
	char* anims[3];
} Animation;

char* LBGetNextFrame(Animation* anim, char* looped)
{
	*looped = 0;
	anim->frame_count += 1;
	if (anim->frame_count < anim->frames_per_anim)
	{
		return anim->anims[anim->current_anim];
	}
	anim->frame_count = 0;
	anim->current_anim = (anim->current_anim + 1) % anim->anim_count;
	if (anim->current_anim == 0) *looped = 1;
	return anim->anims[anim->current_anim];
}

void LBGetJoyPadState(JoyPadState* p1, JoyPadState* p2)
/*
 * Get the current joy pad button state for p1 and p2
 */
{
	static unsigned int p1_prev = 0;
	static unsigned int p2_prev = 0;

	p1->held = ReadJoypad(0);
	p1->pressed = p1->held & (p1->held ^ p1_prev);
	p1->released = p1_prev & (p1->held ^ p1_prev);
	p1_prev = p1->held;
	p2->held = ReadJoypad(1);
	p2->pressed = p2->held & (p2->held ^ p2_prev);
	p2->released = p2_prev & (p2->held ^ p2_prev);
	p2_prev = p2->held;
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

u8 LBCollides(u8 x1, u8 y1, u8 width1, u8 height1,
						 u8 x2, u8 y2, u8 width2, u8 height2)
{
	if (y1 + height1 < y2) return 0;
	if (y1 > y2 + height2) return 0;
	if (x1 + width1 < x2) return 0;
	if (x1 > x2 + width2) return 0;
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

int LBRandom(int from, int to)
/*
 * Return a random number between 'from' and 'to'.
 */
{
	static int random_seed = 32767; // A very deterministic random seed...
	static u8 shift_count = 0;
	int shifted = random_seed >> shift_count;
	int delta = to - from;

	shift_count++;
	if (shift_count >= 16) shift_count = 0;

	return from + ((delta + shifted) % delta);
}

#endif
