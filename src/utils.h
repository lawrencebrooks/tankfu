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
	unsigned char current_anim;			// Current animation
	unsigned char anim_count;			// Total animation count
	unsigned char frames_per_anim;		// Animation lifetime in amount of render frames
	unsigned char frame_count;			// Render frame counter
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

void LBCopyChars(unsigned char* dst, unsigned char *src, unsigned char count)
/*
 * Custom string copy
 */
{
	for (unsigned char i = 0; i < count; i++)
	{
		dst[i] = src[i];
	}
}

void LBPrintStr(unsigned char x, unsigned char y, unsigned char* txt, unsigned char count)
{
	for (unsigned char i = 0; i < count; i++)
	{
		PrintChar(x+i, y, txt[i]);
	}
}

unsigned char LBCollides(unsigned char x1, unsigned char y1, unsigned char width1, unsigned char height1,
						 unsigned char x2, unsigned char y2, unsigned char width2, unsigned char height2)
{
	if (y1 + height1 < y2) return 0;
	if (y1 > y2 + height2) return 0;
	if (x1 + width1 < x2) return 0;
	if (x1 > x2 + width2) return 0;
	return 1;
}

unsigned char LBLineIntersect(unsigned char line1x1, unsigned char line1y1, unsigned char line1x2, unsigned char line1y2,
							  unsigned char line2x1, unsigned char line2y1, unsigned char line2x2, unsigned char line2y2)
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

#endif
