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

#endif
