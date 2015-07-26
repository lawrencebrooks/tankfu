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
#ifndef PATCHES_MAP_H
#define PATCHES_MAP_H

#define PATCH_BANTER 0
#define PATCH_BRICK_EXPLODE 1
#define PATCH_CANNONBALL 2
#define PATCH_ITEM 3
#define PATCH_LEVEL_CLEAR 4
#define PATCH_LEVEL_START 5
#define PATCH_METAL 6
#define PATCH_NAVIGATE 7
#define PATCH_ROCKET 8
#define PATCH_SPLASH 9
#define PATCH_TANK_EXPLODE 10
#define PATCH_TRACKS 11
#define PATCH_SILENCE 12


#define PCM_CHANNEL 4
const struct PatchStruct my_patches[] PROGMEM = {
  {2,ad_banter,0,sizeof(ad_banter)-2,sizeof(ad_banter)-1},
  {2,ad_brick_explode,0,sizeof(ad_brick_explode)-2,sizeof(ad_brick_explode)-1},
  {2,ad_cannonball,0,sizeof(ad_cannonball)-2,sizeof(ad_cannonball)-1},
  {2,ad_item,0,sizeof(ad_item)-2,sizeof(ad_item)-1},
  {2,ad_level_clear,0,sizeof(ad_level_clear)-2,sizeof(ad_level_clear)-1},
  {2,ad_level_start,0,sizeof(ad_level_start)-2,sizeof(ad_level_start)-1},
  {2,ad_metal,0,sizeof(ad_metal)-2,sizeof(ad_metal)-1},
  {2,ad_navigate,0,sizeof(ad_navigate)-2,sizeof(ad_navigate)-1},
  {2,ad_cannonball,0,sizeof(ad_cannonball)-2,sizeof(ad_cannonball)-1},
  {2,ad_splash,0,sizeof(ad_splash)-2,sizeof(ad_splash)-1},
  {2,ad_brick_explode,0,sizeof(ad_brick_explode)-2,sizeof(ad_brick_explode)-1},
  {2,ad_tracks,0,sizeof(ad_tracks)-2,sizeof(ad_tracks)-1},
  {2,ad_silence,0,0,0},
};

#endif
