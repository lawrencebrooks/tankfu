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
#ifndef PATCHES_H
#define PATCHES_H

#define PATCH_BRICK_EXPLODE 0
#define PATCH_CANNONBALL 1
#define PATCH_ITEM 2
#define PATCH_METAL 3
#define PATCH_NAVIGATE 4
#define PATCH_ROCKET 5
#define PATCH_TANK_EXPLODE 6
#define PATCH_ALARM 7


#define PCM_CHANNEL 4

const char ad_tank_explode[] PROGMEM={
	0,PC_ENV_VOL,127,
	0,PC_WAVE,3,
	0,PC_ENV_SPEED,-1, 
	0,PC_PITCH,65,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4,
	3,PC_ENV_VOL,100,
	0,PC_PITCH,60,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4, 
	3,PC_ENV_VOL,80,
	0,PC_PITCH,55,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4,
	3,PC_ENV_VOL,50,
	0,PC_PITCH,50,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4,
	3,PC_ENV_VOL,40,
	0,PC_PITCH,45,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4,
	3,PC_ENV_VOL,20,
	0,PC_PITCH,40,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4,
	1,PC_NOTE_CUT,0,
	0,PATCH_END
};

const char ad_brick_explode[] PROGMEM={
	0,PC_ENV_VOL,127,
	0,PC_WAVE,3,
	0,PC_ENV_SPEED,-1, 
	//1,PC_NOTE_DOWN,4,
	0,PC_ENV_VOL,100,
	0,PC_PITCH,50,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4,
	3,PC_ENV_VOL,80,
	0,PC_PITCH,45,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4,
	3,PC_ENV_VOL,60,
	0,PC_PITCH,40,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	1,PC_NOTE_DOWN,4,
	//1,PC_NOTE_DOWN,4,
	1,PC_NOTE_CUT,0,
	0,PATCH_END
};

const char ad_cannonball[] PROGMEM={
	0,PC_ENV_VOL,127,
	0,PC_PITCH,50,
	0,PC_WAVE,3,
	0,PC_ENV_SPEED,-16,
	0,PC_SLIDE_SPEED,12,
	0,PC_SLIDE,-24,
	8,PC_ENV_SPEED,-32,
	0,PATCH_END
};

const char ad_navigate[] PROGMEM={
	0,PC_WAVE,4,
	0,PC_ENV_VOL,0x70,
	0,PC_ENV_SPEED,-40,
	0,PC_PITCH,60,
	1,PC_NOTE_CUT,0,
	0,PATCH_END
};

const char ad_alarm[] PROGMEM ={
	0,PC_WAVE,2,
	0,PC_NOTE_DOWN,50, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_DOWN,1,
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1, 
	1,PC_NOTE_UP,1,
	1,PC_NOTE_CUT,0,
	0,PATCH_END
};

const struct PatchStruct my_patches[] PROGMEM = {
  {0,NULL,ad_brick_explode,0,0},
  {0,NULL,ad_cannonball,0,0},
  {0,NULL,ad_navigate,0,0},
  {0,NULL,ad_navigate,0,0},
  {0,NULL,ad_navigate,0,0},
  {0,NULL,ad_cannonball,0,0},
  {0,NULL,ad_tank_explode,0,0},
  {0,NULL,ad_alarm,0,0}
};

#endif
