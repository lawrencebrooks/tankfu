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
#define PATCH_ALARM 13


#define PCM_CHANNEL 4

const char ad_banter[] PROGMEM={
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xfe, 0xfe,
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x00, 0x00, 0x01, 0x02,
  0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x01, 0x02, 0x00, 0x00, 0xff,
  0xff, 0xfe, 0xfe, 0xfd, 0xfd, 0xfd, 0xfc, 0xfd, 0xfb, 0xfc, 0xfc, 0xfb,
  0xfb, 0xf9, 0xfb, 0xfa, 0xfb, 0xfa, 0xfd, 0xfd, 0xff, 0x00, 0x02, 0x03,
  0x06, 0x06, 0x08, 0x08, 0x09, 0x08, 0x07, 0x08, 0x05, 0x04, 0x04, 0x01,
  0xff, 0xff, 0xfc, 0xfb, 0xfa, 0xf8, 0xf9, 0xf7, 0xf7, 0xf8, 0xf7, 0xf5,
  0xf7, 0xf6, 0xf7, 0xf8, 0xf8, 0xfa, 0xfb, 0xfd, 0xff, 0x00, 0x03, 0x05,
  0x06, 0x09, 0x0a, 0x0c, 0x0d, 0x0e, 0x0d, 0x0e, 0x0d, 0x0c, 0x09, 0x08,
  0x04, 0x01, 0xfe, 0xfa, 0xf7, 0xf4, 0xf1, 0xf0, 0xf1, 0xef, 0xf0, 0xf2,
  0xf1, 0xf3, 0xf6, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe, 0xff, 0x02, 0x03, 0x05,
  0x08, 0x08, 0x0c, 0x14, 0x10, 0x12, 0x16, 0x14, 0x0f, 0x0d, 0x07, 0x04,
  0xfc, 0xf5, 0xf6, 0xf1, 0xeb, 0xef, 0xf2, 0xee, 0xf4, 0xf8, 0xf8, 0xfa,
  0xfd, 0xff, 0x00, 0xfe, 0xfd, 0x00, 0xfb, 0xf9, 0xf8, 0xf8, 0xf6, 0xf7,
  0xf9, 0xfe, 0xfe, 0x06, 0x11, 0x13, 0x15, 0x1c, 0x1b, 0x19, 0x15, 0x0e,
  0x0a, 0x02, 0xf5, 0xf3, 0xf2, 0xe6, 0xe8, 0xeb, 0xeb, 0xee, 0xf3, 0xf7,
  0xfb, 0x01, 0x02, 0x07, 0x08, 0x05, 0x05, 0x03, 0xfc, 0xf9, 0xf7, 0xf4,
  0xf3, 0xf1, 0xf6, 0xf9, 0xfc, 0x09, 0x0e, 0x11, 0x1b, 0x1c, 0x1a, 0x1b,
  0x12, 0x0d, 0x09, 0xfb, 0xf3, 0xf5, 0xe9, 0xe5, 0xea, 0xe9, 0xeb, 0xf2,
  0xf5, 0xf9, 0x03, 0x03, 0x08, 0x0d, 0x09, 0x08, 0x05, 0x00, 0xfa, 0xf5,
  0xf2, 0xef, 0xef, 0xf0, 0xf3, 0xf8, 0x05, 0x0e, 0x0f, 0x1b, 0x21, 0x1b,
  0x1f, 0x19, 0x0e, 0x0c, 0xff, 0xf4, 0xf3, 0xea, 0xe0, 0xe6, 0xe5, 0xe6,
  0xed, 0xf4, 0xf8, 0x00, 0x07, 0x09, 0x11, 0x11, 0x0c, 0x0c, 0x06, 0xfe,
  0xf8, 0xf3, 0xec, 0xed, 0xea, 0xec, 0xf1, 0xf7, 0x07, 0x0c, 0x12, 0x1e,
  0x20, 0x1d, 0x1f, 0x16, 0x10, 0x0b, 0xfd, 0xf5, 0xf4, 0xe7, 0xe4, 0xe7,
  0xe6, 0xe7, 0xf0, 0xf5, 0xfa, 0x03, 0x07, 0x0d, 0x11, 0x0f, 0x0b, 0x0b,
  0x03, 0xfa, 0xf7, 0xef, 0xeb, 0xeb, 0xe8, 0xeb, 0xf1, 0xf8, 0x09, 0x0d,
  0x14, 0x1f, 0x22, 0x1e, 0x1f, 0x18, 0x10, 0x0c, 0xfa, 0xf7, 0xf2, 0xe5,
  0xe4, 0xe8, 0xe5, 0xe8, 0xf2, 0xf3, 0xfc, 0x03, 0x07, 0x0c, 0x10, 0x0c,
  0x0c, 0x08, 0x00, 0xf9, 0xf6, 0xed, 0xe9, 0xea, 0xe6, 0xeb, 0xf0, 0xf5,
  0x08, 0x0f, 0x13, 0x1e, 0x28, 0x20, 0x22, 0x1e, 0x15, 0x0f, 0x01, 0xf9,
  0xf6, 0xe8, 0xe3, 0xe7, 0xe4, 0xe4, 0xee, 0xf1, 0xf6, 0xfd, 0x04, 0x0b,
  0x0e, 0x0d, 0x0d, 0x0b, 0x03, 0xfe, 0xf9, 0xf3, 0xec, 0xea, 0xe8, 0xea,
  0xec, 0xf0, 0xfc, 0x0c, 0x0f, 0x17, 0x24, 0x27, 0x20, 0x24, 0x1f, 0x15,
  0x0d, 0x00, 0xfb, 0xf1, 0xe6, 0xe4, 0xe5, 0xe0, 0xe7, 0xeb, 0xee, 0xf5,
  0xfe, 0x04, 0x08, 0x0b, 0x0c, 0x0c, 0x06, 0x04, 0xff, 0xfa, 0xf3, 0xf0,
  0xec, 0xea, 0xea, 0xed, 0xf3, 0xf6, 0x07, 0x0f, 0x14, 0x1f, 0x27, 0x23,
  0x27, 0x21, 0x1a, 0x13, 0x06, 0xfc, 0xf6, 0xe7, 0xe5, 0xe3, 0xde, 0xe2,
  0xe7, 0xe8, 0xf1, 0xf7, 0xff, 0x04, 0x08, 0x0c, 0x0e, 0x08, 0x08, 0x04,
  0xfe, 0xf7, 0xf4, 0xf0, 0xed, 0xe9, 0xec, 0xef, 0xf4, 0xf7, 0x06, 0x11,
  0x16, 0x1d, 0x28, 0x28, 0x24, 0x24, 0x1c, 0x15, 0x06, 0xfd, 0xf8, 0xea,
  0xe2, 0xe4, 0xe1, 0xdf, 0xe6, 0xea, 0xef, 0xf5, 0xfb, 0x03, 0x06, 0x09,
  0x0b, 0x0a, 0x06, 0x05, 0xfe, 0xf9, 0xf5, 0xf2, 0xed, 0xed, 0xee, 0xf0,
  0xf4, 0xf8, 0xff, 0x05, 0x0f, 0x16, 0x1c, 0x20, 0x25, 0x23, 0x1e, 0x19,
  0x13, 0x0a, 0x00, 0xfb, 0xf3, 0xed, 0xea, 0xe9, 0xe8, 0xea, 0xec, 0xf0,
  0xf2, 0xf8, 0xfb, 0xfe, 0xff, 0x02, 0x01, 0xfe, 0xfe, 0xfc, 0xf9, 0xf6,
  0xf6, 0xf6, 0xf4, 0xf8, 0xf9, 0xfb, 0xff, 0x02, 0x06, 0x08, 0x0b, 0x0d,
  0x0f, 0x13, 0x14, 0x12, 0x14, 0x15, 0x10, 0x0d, 0x0c, 0x07, 0x00, 0x01,
  0xfb, 0xf7, 0xf4, 0xf3, 0xef, 0xef, 0xee, 0xee, 0xea, 0xee, 0xef, 0xef,
  0xf2, 0xf5, 0xf7, 0xf8, 0xfd, 0x00, 0x01, 0x01, 0x06, 0x04, 0x04, 0x05,
  0x06, 0x05, 0x03, 0x04, 0x04, 0x01, 0x02, 0x04, 0x03, 0x04, 0x08, 0x07,
  0x09, 0x0b, 0x0b, 0x0c, 0x0a, 0x0c, 0x09, 0x06, 0x06, 0x02, 0xfe, 0xfa,
  0xf9, 0xf5, 0xf2, 0xef, 0xf1, 0xee, 0xee, 0xf0, 0xf1, 0xf2, 0xf7, 0xf9,
  0xfb, 0xff, 0x01, 0x03, 0x04, 0x05, 0x04, 0x05, 0x04, 0x05, 0x02, 0x03,
  0x02, 0x02, 0x02, 0x01, 0x02, 0x01, 0xff, 0x01, 0x00, 0x00, 0x02, 0x02,
  0x03, 0x02, 0x04, 0x04, 0x03, 0x03, 0x02, 0x03, 0x01, 0xfe, 0xfe, 0xfc,
  0xfb, 0xf9, 0xf9, 0xf7, 0xf8, 0xf8, 0xf7, 0xf9, 0xfa, 0xfb, 0xfc, 0xfe,
  0x00, 0x00, 0x03, 0x02, 0x03, 0x05, 0x03, 0x04, 0x02, 0x02, 0xff, 0xff,
  0xfe, 0xfc, 0xfc, 0xfb, 0xfc, 0xfb, 0xfd, 0xfd, 0xff, 0x00, 0x01, 0x02,
  0x03, 0x03, 0x04, 0x04, 0x04, 0x03, 0x03, 0x00, 0xff, 0xfe, 0xfc, 0xfb,
  0xf9, 0xfa, 0xf9, 0xfa, 0xfa, 0xfd, 0xfd, 0x00, 0x01, 0x03, 0x04, 0x05,
  0x04, 0x06, 0x05, 0x05, 0x03, 0x03, 0x00, 0xff, 0xfc, 0xfc, 0xfc, 0xf9,
  0xfa, 0xfa, 0xfb, 0xfb, 0xfc, 0xfd, 0xfd, 0xff, 0xff, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0xfd, 0xfe, 0xfd, 0xfe, 0xfd, 0xfe,
  0xfe, 0x00, 0x00, 0x01, 0x01, 0x02, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00,
  0xfe, 0xfe, 0x00, 0xfe, 0xff, 0x00, 0x00, 0xff, 0x01, 0x00, 0x01, 0x00,
  0x01, 0x00, 0xff, 0xfd, 0xfd, 0xfb, 0xfb, 0xfa, 0xfb, 0xfb, 0xfc, 0xfc,
  0xfe, 0x00, 0xff, 0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x00, 0x00, 0xfe,
  0xfe, 0xfd, 0xfc, 0xfc, 0xff, 0xff, 0xfe, 0xfe, 0xff, 0xfe, 0x00, 0x00,
  0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00,
  0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xfe, 0x00,
  0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff,
  0xff, 0xfe, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xff, 0xfe,
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
  0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xfe, 0xfd, 0xfe,
  0xfe, 0xfd, 0xfe, 0xfe, 0xfd, 0xfe, 0xfd, 0xfe, 0xfe, 0xfd, 0xff, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x02, 0x02, 0x03,
  0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x02, 0x01, 0x01, 0xff, 0xff,
  0xfd, 0xfd, 0xfc, 0xfa, 0xfa, 0xf8, 0xf9, 0xf8, 0xf9, 0xf9, 0xf8, 0xfa,
  0xfb, 0xfa, 0xfc, 0xfd, 0xfd, 0xff, 0xfe, 0xff, 0x00, 0x00, 0x01, 0xff,
  0x01, 0x00, 0x01, 0x00, 0x02, 0x02, 0x04, 0x05, 0x07, 0x08, 0x09, 0x09,
  0x0c, 0x0b, 0x0a, 0x09, 0x09, 0x06, 0x01, 0x00, 0xfe, 0xfa, 0xf6, 0xf4,
  0xf3, 0xf0, 0xf1, 0xf1, 0xf2, 0xf2, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe, 0xff,
  0xff, 0x01, 0x01, 0x00, 0xff, 0xff, 0xfe, 0xfb, 0xfd, 0xfc, 0xfb, 0xfa,
  0xfd, 0xfe, 0x02, 0x02, 0x0a, 0x10, 0x10, 0x15, 0x1b, 0x17, 0x15, 0x14,
  0x11, 0x0a, 0x02, 0xfe, 0xf8, 0xf0, 0xec, 0xeb, 0xe8, 0xe8, 0xe9, 0xee,
  0xef, 0xf2, 0xfa, 0xfd, 0x00, 0x05, 0x09, 0x09, 0x08, 0x09, 0x06, 0xff,
  0xfd, 0xfb, 0xf7, 0xf3, 0xf3, 0xf3, 0xf1, 0xf1, 0xf5, 0xf5, 0xfa, 0xfe,
  0x04, 0x09, 0x13, 0x1a, 0x1c, 0x21, 0x26, 0x21, 0x1d, 0x1b, 0x11, 0x08,
  0x00, 0xf6, 0xed, 0xe5, 0xe1, 0xde, 0xdd, 0xde, 0xe4, 0xe9, 0xef, 0xf4,
  0xff, 0x03, 0x09, 0x10, 0x11, 0x12, 0x12, 0x0e, 0x0a, 0x02, 0xfe, 0xf8,
  0xf2, 0xed, 0xed, 0xea, 0xeb, 0xec, 0xf0, 0xf2, 0xf8, 0xfd, 0x02, 0x0b,
  0x19, 0x1e, 0x20, 0x2b, 0x2e, 0x25, 0x23, 0x20, 0x14, 0x08, 0xfd, 0xf5,
  0xe6, 0xdd, 0xda, 0xd5, 0xd5, 0xd7, 0xde, 0xe4, 0xec, 0xf4, 0x02, 0x06,
  0x0e, 0x16, 0x1a, 0x19, 0x1a, 0x15, 0x0f, 0x06, 0xff, 0xf9, 0xef, 0xeb,
  0xe8, 0xe6, 0xe5, 0xe6, 0xe8, 0xee, 0xf3, 0xf8, 0x01, 0x0b, 0x1f, 0x1f,
  0x26, 0x33, 0x32, 0x29, 0x2c, 0x23, 0x16, 0x08, 0xff, 0xf2, 0xe0, 0xd8,
  0xd3, 0xcd, 0xcc, 0xd3, 0xd7, 0xdf, 0xe6, 0xf5, 0x01, 0x08, 0x13, 0x1e,
  0x1e, 0x22, 0x20, 0x1c, 0x13, 0x0a, 0x02, 0xf8, 0xed, 0xe9, 0xe3, 0xe0,
  0xdf, 0xe0, 0xe2, 0xe9, 0xee, 0xf6, 0xff, 0x15, 0x20, 0x20, 0x32, 0x3c,
  0x32, 0x31, 0x32, 0x24, 0x15, 0x08, 0xfe, 0xeb, 0xdb, 0xd6, 0xcf, 0xc8,
  0xca, 0xcf, 0xd4, 0xdc, 0xe6, 0xf8, 0x00, 0x0c, 0x1a, 0x21, 0x22, 0x27,
  0x22, 0x1d, 0x14, 0x0b, 0x02, 0xf5, 0xef, 0xe8, 0xe1, 0xde, 0xdd, 0xdd,
  0xe2, 0xe7, 0xef, 0xf5, 0x0c, 0x1b, 0x1b, 0x2b, 0x3c, 0x34, 0x32, 0x36,
  0x2c, 0x1b, 0x10, 0x06, 0xf5, 0xe2, 0xda, 0xd3, 0xc7, 0xc8, 0xcb, 0xcc,
  0xd4, 0xdd, 0xee, 0xf6, 0x04, 0x15, 0x1c, 0x20, 0x29, 0x26, 0x21, 0x1a,
  0x13, 0x09, 0xfd, 0xf6, 0xef, 0xe5, 0xe1, 0xe0, 0xdc, 0xde, 0xe4, 0xea,
  0xf2, 0x0b, 0x13, 0x17, 0x2a, 0x38, 0x2e, 0x35, 0x35, 0x2a, 0x1d, 0x14,
  0x08, 0xf8, 0xe7, 0xe1, 0xd5, 0xcb, 0xcc, 0xcb, 0xcb, 0xd0, 0xdc, 0xe9,
  0xee, 0x00, 0x12, 0x13, 0x1f, 0x26, 0x23, 0x21, 0x1b, 0x18, 0x0c, 0x02,
  0xfe, 0xf5, 0xe9, 0xe7, 0xe4, 0xdf, 0xe0, 0xe4, 0xe9, 0xf8, 0x07, 0x0d,
  0x18, 0x2c, 0x2b, 0x2c, 0x33, 0x2e, 0x24, 0x1c, 0x14, 0x05, 0xf7, 0xed,
  0xe3, 0xd5, 0xd2, 0xcf, 0xcc, 0xcd, 0xd3, 0xde, 0xe3, 0xf0, 0x03, 0x0a,
  0x11, 0x1d, 0x20, 0x1d, 0x1e, 0x1b, 0x16, 0x0c, 0x05, 0x01, 0xf4, 0xef,
  0xeb, 0xe7, 0xe2, 0xe6, 0xe6, 0xef, 0x00, 0x04, 0x0c, 0x21, 0x24, 0x22,
  0x2e, 0x2a, 0x22, 0x1d, 0x17, 0x0c, 0xff, 0xf6, 0xef, 0xe3, 0xda, 0xd9,
  0xd4, 0xd1, 0xd2, 0xdd, 0xe0, 0xe6, 0xf8, 0x02, 0x05, 0x12, 0x18, 0x17,
  0x19, 0x18, 0x17, 0x0f, 0x0b, 0x07, 0x00, 0xf8, 0xf6, 0xf1, 0xec, 0xea,
  0xee, 0xea, 0xf7, 0x06, 0x03, 0x0d, 0x22, 0x1b, 0x1d, 0x26, 0x21, 0x17,
  0x16, 0x10, 0x06, 0xfb, 0xf6, 0xef, 0xe3, 0xe1, 0xde, 0xdb, 0xd6, 0xdb,
  0xe4, 0xe4, 0xed, 0xfc, 0xff, 0x06, 0x10, 0x13, 0x13, 0x13, 0x16, 0x13,
  0x0b, 0x0a, 0x07, 0xff, 0xfc, 0xfa, 0xf6, 0xf0, 0xf0, 0xf3, 0xee, 0xfa,
  0x07, 0x03, 0x0d, 0x1c, 0x1b, 0x18, 0x20, 0x1c, 0x14, 0x0f, 0x0e, 0x03,
  0xfb, 0xf5, 0xef, 0xe6, 0xe0, 0xe0, 0xdc, 0xd9, 0xde, 0xe5, 0xe5, 0xef,
  0xfb, 0xff, 0x03, 0x0f, 0x11, 0x10, 0x11, 0x16, 0x10, 0x0b, 0x0a, 0x09,
  0xfe, 0xfd, 0xfd, 0xf6, 0xf3, 0xf6, 0xf5, 0xf2, 0xf7, 0x02, 0x05, 0x05,
  0x11, 0x19, 0x16, 0x17, 0x1d, 0x17, 0x0e, 0x10, 0x0b, 0xff, 0xfa, 0xf5,
  0xed, 0xe5, 0xe3, 0xe1, 0xdd, 0xdd, 0xe4, 0xe6, 0xea, 0xf5, 0xfb, 0x00,
  0x09, 0x0e, 0x10, 0x11, 0x15, 0x13, 0x0e, 0x0e, 0x0a, 0x04, 0xff, 0xff,
  0xf9, 0xf6, 0xf5, 0xf6, 0xf4, 0xf5, 0xfa, 0xfd, 0xff, 0x03, 0x0b, 0x0e,
  0x0e, 0x16, 0x17, 0x15, 0x15, 0x15, 0x0d, 0x06, 0x02, 0xf9, 0xf3, 0xee,
  0xe7, 0xe4, 0xe1, 0xe2, 0xe1, 0xe5, 0xe9, 0xf0, 0xf4, 0xfc, 0x03, 0x09,
  0x0d, 0x12, 0x12, 0x12, 0x11, 0x10, 0x0b, 0x06, 0x04, 0xfe, 0xfa, 0xf7,
  0xf4, 0xf3, 0xf2, 0xf3, 0xf6, 0xf6, 0xfb, 0xff, 0x04, 0x07, 0x0c, 0x0f,
  0x10, 0x12, 0x11, 0x10, 0x0d, 0x09, 0x04, 0x00, 0xfc, 0xf6, 0xf1, 0xef,
  0xed, 0xec, 0xee, 0xef, 0xf3, 0xf7, 0xfa, 0x00, 0x04, 0x06, 0x09, 0x0b,
  0x0c, 0x0a, 0x0b, 0x08, 0x07, 0x03, 0x01, 0xfc, 0xfa, 0xf6, 0xf5, 0xf3,
  0xf4, 0xf4, 0xf4, 0xf7, 0xf9, 0xfd, 0x00, 0x02, 0x06, 0x0a, 0x0a, 0x0c,
  0x0c, 0x0c, 0x0a, 0x07, 0x06, 0x01, 0xfc, 0xfb, 0xf6, 0xf4, 0xf4, 0xf2,
  0xf4, 0xf5, 0xf8, 0xfa, 0xfe, 0x01, 0x05, 0x06, 0x0a, 0x0b, 0x0c, 0x0b,
  0x0a, 0x09, 0x05, 0x03, 0x01, 0xfc, 0xf9, 0xf7, 0xf4, 0xf2, 0xf1, 0xf3,
  0xf3, 0xf3, 0xf7, 0xfa, 0xfb, 0xff, 0x01, 0x04, 0x06, 0x07, 0x09, 0x08,
  0x08, 0x06, 0x05, 0x01, 0xff, 0xfc, 0xfb, 0xf8, 0xf8, 0xf7, 0xf8, 0xf9,
  0xfb, 0xfc, 0xff, 0x02, 0x04, 0x06, 0x07, 0x08, 0x0a, 0x09, 0x09, 0x07,
  0x05, 0x03, 0x02, 0xfd, 0xfc, 0xfa, 0xf8, 0xf6, 0xf8, 0xf5, 0xf6, 0xf9,
  0xf8, 0xfb, 0xfd, 0xfe, 0x02, 0x03, 0x04, 0x05, 0x06, 0x04, 0x05, 0x04,
  0x01, 0x00, 0xfd, 0xfc, 0xfb, 0xf9, 0xf9, 0xf8, 0xfa, 0xfa, 0xfc, 0xfd,
  0x00, 0x02, 0x03, 0x05, 0x06, 0x06, 0x06, 0x07, 0x05, 0x05, 0x03, 0x00,
  0xff, 0xfd, 0xfc, 0xf9, 0xfa, 0xf8, 0xf8, 0xf9, 0xf9, 0xfb, 0xfc, 0xfc,
  0xff, 0xff, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x01, 0x00,
  0xfe, 0xfd, 0xfc, 0xfa, 0xfb, 0xfa, 0xfa, 0xfb, 0xfc, 0xfc, 0xfe, 0xff,
  0x00, 0x01, 0x02, 0x04, 0x04, 0x05, 0x05, 0x03, 0x01, 0x02, 0xff, 0xff,
  0xfd, 0xfd, 0xfa, 0xfb, 0xfa, 0xfa, 0xfa, 0xfc, 0xfd, 0xd0, 0x00, 0x00,
  0x00
};
const char ad_brick_explode[] PROGMEM={
	0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x05, 0x04, 0x03, 0x06,
  0x02, 0xfc, 0xfe, 0xfb, 0xfa, 0xfb, 0xf7, 0xf6, 0xf8, 0xf8, 0xfb, 0xff,
  0x00, 0x05, 0x07, 0x06, 0x06, 0x08, 0x09, 0x08, 0x03, 0xff, 0xfe, 0xfd,
  0xfe, 0xfc, 0xf8, 0xfb, 0xfb, 0xfc, 0x01, 0x00, 0xfd, 0xfd, 0xff, 0x01,
  0x03, 0x04, 0x02, 0xff, 0x00, 0x00, 0xff, 0x01, 0x02, 0xfe, 0xfe, 0x03,
  0x03, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x00, 0x00, 0xfe, 0xff, 0xfe, 0xfc,
  0x01, 0x04, 0xff, 0xfc, 0xfd, 0x01, 0x00, 0xfd, 0xff, 0xfd, 0xff, 0x03,
  0xff, 0xfe, 0x01, 0xff, 0xfe, 0x02, 0x03, 0xff, 0xfd, 0x00, 0xff, 0xff,
  0x01, 0xff, 0xfe, 0xfc, 0xfc, 0xfc, 0xfb, 0x01, 0x05, 0x06, 0x09, 0x0b,
  0x08, 0x04, 0x01, 0xff, 0xfd, 0xfa, 0xf8, 0xf8, 0xf7, 0xf8, 0xf8, 0xfa,
  0xfe, 0x01, 0xff, 0xff, 0x03, 0x04, 0x04, 0x05, 0x06, 0x06, 0x04, 0x03,
  0x01, 0x00, 0xff, 0xfe, 0xfd, 0xfd, 0xff, 0xfe, 0xfc, 0xfd, 0xfd, 0xfc,
  0xfc, 0xfd, 0xff, 0x02, 0x08, 0x06, 0x04, 0x03, 0xfe, 0xfd, 0xfb, 0xfa,
  0xfb, 0xf8, 0xf8, 0xfa, 0xf8, 0xfc, 0x01, 0x03, 0x05, 0x06, 0x08, 0x08,
  0x07, 0x05, 0x03, 0x04, 0x04, 0x01, 0xfa, 0xf9, 0xfc, 0xfb, 0xfa, 0xfc,
  0xfa, 0xfd, 0xfe, 0xfc, 0x00, 0x01, 0x01, 0x05, 0x06, 0x01, 0x05, 0x03,
  0x00, 0x02, 0x00, 0x00, 0x02, 0xfd, 0xfd, 0xfe, 0xf7, 0xfa, 0xff, 0xfe,
  0xff, 0xff, 0xfd, 0x02, 0x01, 0xff, 0xff, 0x01, 0x03, 0x00, 0x00, 0x04,
  0x01, 0x00, 0x02, 0xfe, 0xfd, 0xfd, 0xfc, 0xfa, 0xfc, 0x05, 0x03, 0xfe,
  0x01, 0x00, 0xfd, 0x00, 0x01, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0xff,
  0xfb, 0xfa, 0xfd, 0xfc, 0xfb, 0xfc, 0xff, 0x00, 0x06, 0x0c, 0x0a, 0x0b,
  0x0c, 0x07, 0x04, 0x01, 0xfd, 0xf9, 0xf3, 0xf2, 0xf6, 0xf6, 0xf6, 0xf9,
  0xfb, 0xfc, 0xff, 0xff, 0x00, 0x05, 0x07, 0x07, 0x07, 0x08, 0x07, 0x04,
  0x02, 0x03, 0x01, 0xff, 0xff, 0xfc, 0xfa, 0xfc, 0xfb, 0xfa, 0xfc, 0xfe,
  0xfe, 0xfd, 0xfe, 0xfd, 0xfd, 0xff, 0x01, 0x01, 0x03, 0x05, 0x03, 0x01,
  0x02, 0x03, 0x01, 0x00, 0x02, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x01, 0x0a, 0x12, 0x09, 0xfe, 0xf5, 0xf0, 0xed, 0xee, 0xf1, 0xf1, 0xf0,
  0xf2, 0xf7, 0xfe, 0x08, 0x11, 0x12, 0x0f, 0x0f, 0x0e, 0x0c, 0x0b, 0x08,
  0x05, 0x02, 0xfc, 0xfa, 0xf2, 0xef, 0xf2, 0xf4, 0x01, 0x00, 0xf5, 0xfb,
  0x04, 0xff, 0x00, 0x05, 0x06, 0x02, 0x01, 0x02, 0xfe, 0xfd, 0x02, 0x00,
  0x04, 0x0f, 0x0a, 0x02, 0xff, 0xff, 0x03, 0x01, 0xf9, 0xf5, 0xfa, 0xfc,
  0xf7, 0xf6, 0xfe, 0x02, 0x01, 0xff, 0x03, 0x01, 0xfe, 0xff, 0x00, 0x00,
  0xfe, 0xfc, 0xfd, 0x01, 0x02, 0xff, 0x00, 0x07, 0x06, 0x03, 0xff, 0xfd,
  0xfe, 0xfe, 0xfa, 0xfa, 0xfe, 0xfd, 0xfa, 0xfc, 0x00, 0x00, 0xfe, 0xfe,
  0xff, 0x00, 0x01, 0xfe, 0xf8, 0xfe, 0x0f, 0x11, 0x0d, 0x10, 0x0e, 0x09,
  0x05, 0xff, 0xfb, 0xf8, 0xf3, 0xf0, 0xf2, 0xf3, 0xf4, 0xf5, 0xf9, 0xfd,
  0xfc, 0xfe, 0x02, 0x03, 0x03, 0x05, 0x06, 0x09, 0x0b, 0x08, 0x04, 0x03,
  0x04, 0x03, 0xfe, 0xfb, 0xfe, 0xff, 0xfb, 0xfa, 0xfc, 0xfc, 0xfb, 0xfb,
  0xfc, 0xfa, 0xf8, 0xfa, 0xfd, 0x01, 0x05, 0x05, 0x04, 0x04, 0x04, 0x02,
  0x02, 0x05, 0x06, 0x03, 0x03, 0x03, 0x01, 0xfe, 0xfe, 0xff, 0x01, 0x00,
  0xfe, 0xfb, 0xfb, 0xfb, 0xfb, 0xf9, 0xfb, 0xfe, 0xfd, 0xfd, 0xfb, 0x02,
  0x13, 0x18, 0x0d, 0x00, 0xf8, 0xf5, 0xf2, 0xf2, 0xf9, 0xf9, 0xef, 0xee,
  0xf9, 0x01, 0x07, 0x0a, 0x0b, 0x0c, 0x09, 0x03, 0xff, 0x01, 0x07, 0x08,
  0x01, 0xfb, 0x00, 0xff, 0xf4, 0xf9, 0x01, 0x01, 0xf9, 0xf3, 0x02, 0x0b,
  0xff, 0xfd, 0x05, 0x0c, 0x10, 0xff, 0xfb, 0x02, 0xfb, 0xf7, 0xfb, 0xff,
  0x02, 0x03, 0xfd, 0xfb, 0x01, 0x02, 0x02, 0xfe, 0xfd, 0x04, 0xfd, 0xfa,
  0x00, 0x00, 0xff, 0xff, 0x01, 0x02, 0xfe, 0xfa, 0xf8, 0xfe, 0xff, 0x00,
  0xfc, 0xfc, 0x03, 0x00, 0xfd, 0xfe, 0x05, 0x05, 0xfe, 0xfe, 0x05, 0x05,
  0xff, 0xfa, 0xfd, 0x05, 0x03, 0x01, 0x01, 0x00, 0x01, 0xf8, 0xf7, 0xfc,
  0xfe, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x01, 0x00, 0x03, 0x03, 0xfb,
  0xf8, 0xf4, 0xf0, 0x04, 0x17, 0x17, 0x0f, 0x09, 0x0d, 0x0b, 0x06, 0x02,
  0xfa, 0xf3, 0xee, 0xeb, 0xee, 0xf2, 0xf2, 0xf5, 0xf8, 0xfa, 0xff, 0xfe,
  0x00, 0x04, 0x06, 0x0b, 0x0c, 0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02,
  0xfe, 0xfb, 0xfc, 0xfe, 0xfc, 0xfb, 0xfd, 0xfc, 0xfb, 0xfa, 0xf9, 0xfb,
  0xfd, 0xfe, 0xfe, 0x01, 0x07, 0x06, 0x01, 0x02, 0x05, 0x06, 0x03, 0x03,
  0x03, 0x00, 0xfd, 0xfc, 0xfb, 0xff, 0xff, 0xff, 0x01, 0xfe, 0xfd, 0xfe,
  0xfe, 0xff, 0x00, 0xfe, 0xfe, 0xfc, 0xfa, 0xfc, 0xfd, 0xfd, 0x07, 0x19,
  0x18, 0x0a, 0xff, 0xf9, 0xf5, 0xf2, 0xf1, 0xf1, 0xf1, 0xef, 0xf1, 0xf8,
  0xfe, 0x05, 0x0b, 0x08, 0x06, 0x0c, 0x0d, 0x05, 0x03, 0x0c, 0x08, 0x00,
  0xff, 0xfc, 0xf8, 0xf6, 0xfa, 0x02, 0x00, 0x00, 0x02, 0x04, 0x01, 0xfe,
  0x02, 0x07, 0x02, 0xfb, 0xfa, 0xfe, 0x00, 0xf9, 0xfb, 0x02, 0x00, 0xfe,
  0x03, 0xfe, 0xf7, 0x02, 0x03, 0x02, 0x07, 0x04, 0xff, 0xfe, 0xfe, 0x02,
  0xfc, 0x00, 0x08, 0xfd, 0xf8, 0xf9, 0xfb, 0xf6, 0xf9, 0xff, 0xfe, 0xfc,
  0x00, 0x05, 0xf8, 0xff, 0x0a, 0x00, 0x07, 0x04, 0x02, 0xfe, 0xff, 0x03,
  0x03, 0x01, 0x06, 0xfe, 0xfb, 0x06, 0x02, 0xfc, 0xff, 0xfb, 0xf6, 0xf6,
  0xfc, 0xff, 0xfc, 0x00, 0x01, 0xff, 0x02, 0x07, 0x01, 0xfc, 0x04, 0x05,
  0xfc, 0x00, 0x05, 0xfd, 0xfe, 0xff, 0xfe, 0xfd, 0xf9, 0xf8, 0xee, 0xfc,
  0x14, 0x14, 0x11, 0x0f, 0x0a, 0x07, 0x04, 0x00, 0xf8, 0xf3, 0xf5, 0xf2,
  0xef, 0xf0, 0xf3, 0xf4, 0xf7, 0xfc, 0xfe, 0x01, 0x04, 0x08, 0x09, 0x0a,
  0x09, 0x0b, 0x0a, 0x07, 0x05, 0x04, 0x01, 0xfe, 0xfb, 0xfa, 0xff, 0xff,
  0xfb, 0xfc, 0xfd, 0xfd, 0xfa, 0xfb, 0xfc, 0xfe, 0xfd, 0xfe, 0xfe, 0x00,
  0x05, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x03, 0x00,
  0xfe, 0x01, 0x02, 0x02, 0xff, 0x00, 0x01, 0xfd, 0xfe, 0xff, 0xfe, 0xfa,
  0xfb, 0xff, 0x00, 0xfe, 0xfb, 0xfe, 0x01, 0x00, 0xff, 0x0b, 0x20, 0x17,
  0x0b, 0xff, 0xef, 0xeb, 0xf1, 0xf0, 0xf3, 0xf2, 0xf0, 0xed, 0xf0, 0xfb,
  0x00, 0x06, 0x0f, 0x0f, 0x0f, 0x0f, 0x0d, 0x10, 0x0c, 0x0b, 0x08, 0x00,
  0xf6, 0xf2, 0xec, 0xf1, 0xfe, 0xfd, 0xfc, 0xfc, 0xfc, 0x06, 0x02, 0xfe,
  0x06, 0x02, 0x07, 0x04, 0xf9, 0x01, 0x02, 0xfc, 0xfe, 0x00, 0x08, 0x0a,
  0xfa, 0xfc, 0xfa, 0xfb, 0x07, 0xfb, 0xfb, 0xfe, 0xfd, 0x01, 0xfc, 0xfd,
  0x02, 0x03, 0x05, 0x04, 0x00, 0xff, 0xfd, 0xf8, 0x03, 0x00, 0xf5, 0xf9,
  0xfc, 0xf7, 0xfa, 0x01, 0x07, 0x0e, 0x03, 0x03, 0x06, 0x00, 0x03, 0xff,
  0xfd, 0xfe, 0xfc, 0xfd, 0x00, 0xfb, 0xfe, 0xfc, 0xf6, 0xfd, 0x02, 0x05,
  0x04, 0xff, 0x02, 0x02, 0x00, 0x03, 0x03, 0x03, 0xfc, 0xfa, 0xfe, 0x01,
  0xfc, 0x00, 0x06, 0x03, 0xff, 0xfb, 0xfc, 0xfd, 0x00, 0x00, 0xfe, 0x00,
  0x02, 0xfd, 0xfe, 0xfe, 0xfb, 0xfe, 0xf3, 0xf6, 0x0c, 0x10, 0x10, 0x0e,
  0x08, 0x0a, 0x06, 0x01, 0xfe, 0xf8, 0xf5, 0xf3, 0xf2, 0xf2, 0xf1, 0xf2,
  0xf7, 0xfb, 0x00, 0x04, 0x01, 0x02, 0x05, 0x08, 0x07, 0x0b, 0x11, 0x0f,
  0x05, 0xff, 0x03, 0x00, 0xfa, 0xfa, 0xff, 0x03, 0xff, 0xfb, 0xfa, 0xf7,
  0xf6, 0xf8, 0xf7, 0xfa, 0xff, 0x01, 0xfd, 0xfa, 0x01, 0x06, 0x05, 0x02,
  0x05, 0x07, 0x05, 0x00, 0x01, 0x05, 0x06, 0x03, 0x01, 0x00, 0xfe, 0xfd,
  0xfe, 0x00, 0xfe, 0xfa, 0xf9, 0xf8, 0xfa, 0xfc, 0xff, 0x02, 0x02, 0xfe,
  0xfc, 0xfd, 0x00, 0x02, 0x02, 0x04, 0x04, 0x02, 0x00, 0x04, 0x03, 0x07,
  0x17, 0x17, 0x0b, 0x00, 0xf5, 0xec, 0xe9, 0xea, 0xea, 0xec, 0xf0, 0xf3,
  0xf6, 0xf7, 0xfb, 0x06, 0x10, 0x11, 0x13, 0x14, 0x13, 0x11, 0x0b, 0x08,
  0x06, 0x03, 0xfc, 0xf9, 0xf6, 0xef, 0xf1, 0xfa, 0xfd, 0xfb, 0xfc, 0xfe,
  0xfa, 0xfa, 0x02, 0x04, 0x03, 0x08, 0x08, 0x03, 0x01, 0x01, 0x01, 0x04,
  0x05, 0xfd, 0xfa, 0xfc, 0xf9, 0xfb, 0xff, 0x01, 0x02, 0xfd, 0x01, 0x02,
  0xfb, 0x00, 0x07, 0x01, 0x04, 0x04, 0xf9, 0xfb, 0xf9, 0xf5, 0xfb, 0xfa,
  0x04, 0xfd, 0xfe, 0x02, 0xfe, 0x05, 0x06, 0x0c, 0x0d, 0x06, 0x06, 0x00,
  0xfe, 0xfb, 0xf8, 0xf8, 0xf8, 0xf9, 0xfa, 0xf7, 0xf4, 0xf6, 0xf8, 0xfe,
  0x00, 0x07, 0x09, 0x08, 0x09, 0x07, 0x04, 0x07, 0x04, 0x04, 0x04, 0xff,
  0x01, 0x00, 0xfc, 0xfb, 0xfb, 0xfd, 0xfe, 0xfc, 0xf9, 0xfb, 0xf8, 0xf9,
  0xfc, 0xfe, 0x02, 0x02, 0x00, 0xfe, 0xff, 0x02, 0x02, 0x01, 0x03, 0x03,
  0xfc, 0xf6, 0xfc, 0x0b, 0x0f, 0x0d, 0x0d, 0x09, 0x0a, 0x09, 0x02, 0xfe,
  0xf6, 0xee, 0xee, 0xef, 0xf2, 0xf6, 0xf9, 0xfc, 0xf9, 0xfb, 0xfc, 0xff,
  0x06, 0x08, 0x0c, 0x10, 0x0e, 0x0b, 0x08, 0x02, 0x01, 0x02, 0x03, 0x00,
  0xfe, 0xfb, 0xf6, 0xf7, 0xf7, 0xf8, 0xfc, 0xfc, 0xfc, 0xf7, 0xf8, 0xf8,
  0xfb, 0xff, 0x03, 0x09, 0x0b, 0x06, 0x04, 0x06, 0x06, 0x02, 0x00, 0x00,
  0xfe, 0xfe, 0xfe, 0xff, 0x01, 0x00, 0xff, 0xfe, 0xfd, 0xfe, 0xfd, 0xfd,
  0xfe, 0xfe, 0xff, 0x00, 0xff, 0xfd, 0xff, 0xfe, 0xfb, 0xfd, 0x00, 0x02,
  0x02, 0x03, 0x06, 0x05, 0x04, 0x03, 0x01, 0xff, 0x01, 0x01, 0xff, 0xff,
  0x01, 0xfc, 0xf9, 0xf9, 0xf7, 0xf7, 0xfa, 0xff, 0x0d, 0x18, 0x0e, 0x02,
  0xfc, 0xf1, 0xef, 0xf5, 0xf4, 0xf5, 0xf9, 0xfc, 0xfd, 0xff, 0x05, 0x06,
  0x06, 0x0c, 0x0b, 0x08, 0x09, 0x09, 0x08, 0x07, 0x02, 0xfe, 0xfb, 0xf4,
  0xf0, 0xf1, 0xf5, 0xfc, 0xfe, 0xfc, 0x02, 0x01, 0xfe, 0x01, 0x05, 0x05,
  0x03, 0x05, 0x05, 0x01, 0x01, 0x02, 0x01, 0x00, 0x05, 0x05, 0xfd, 0xfa,
  0xf9, 0xf4, 0xf7, 0x00, 0x00, 0xff, 0xfe, 0x00, 0xfe, 0xfc, 0x04, 0x06,
  0x01, 0x05, 0x05, 0x00, 0x01, 0xff, 0xfd, 0xff, 0xfc, 0xf9, 0xfb, 0xfb,
  0xfd, 0xfd, 0xfd, 0x04, 0x03, 0x04, 0x05, 0xfe, 0xfe, 0xff, 0x01, 0x01,
  0xfb, 0xff, 0x04, 0x00, 0xfd, 0xfe, 0xfa, 0xfc, 0xfd, 0xff, 0x03, 0x02,
  0x06, 0x03, 0xff, 0x04, 0x01, 0xfe, 0xff, 0xff, 0xfd, 0xfd, 0xff, 0xff,
  0xfd, 0xfe, 0x01, 0xfc, 0xfe, 0x00, 0x00, 0x03, 0x01, 0x00, 0x03, 0x03,
  0x01, 0xfe, 0xfd, 0x00, 0xfe, 0xfb, 0xfd, 0xfd, 0xff, 0xfb, 0xf7, 0xff,
  0x05, 0x06, 0x09, 0x0a, 0x0d, 0x0e, 0x0a, 0x03, 0xfe, 0xf5, 0xf0, 0xf1,
  0xf6, 0xf9, 0xf9, 0xfb, 0xfb, 0xfb, 0xfc, 0xfd, 0xff, 0x04, 0x05, 0x06,
  0x08, 0x07, 0x06, 0x04, 0x05, 0x05, 0x03, 0x03, 0xff, 0xfd, 0xfa, 0xfd,
  0xfb, 0xf9, 0xfd, 0xfe, 0xfe, 0xfb, 0xf9, 0xfa, 0xfa, 0xfa, 0xfe, 0x04,
  0x07, 0x05, 0x01, 0x01, 0x02, 0xff, 0x01, 0x02, 0x01, 0x00, 0x00, 0x01,
  0x02, 0x02, 0x01, 0x00, 0x00, 0x02, 0x01, 0xfe, 0xff, 0x00, 0x01, 0xfc,
  0xfa, 0xfc, 0xfa, 0xfa, 0xfc, 0xfc, 0xfe, 0x01, 0x03, 0x06, 0x07, 0x06,
  0x05, 0x04, 0x00, 0xfd, 0xfe, 0x00, 0x00, 0x01, 0x02, 0xff, 0xfc, 0xfb,
  0xfb, 0xf9, 0xfa, 0xfd, 0xfd, 0xfe, 0x00, 0x02, 0x02, 0x00, 0x01, 0x00,
  0x00, 0x03, 0x03, 0x02, 0x02, 0x01, 0x00, 0xff, 0xff, 0x01, 0xff, 0xfe,
  0xff, 0x05, 0x0c, 0x01, 0xfa, 0xf9, 0xf5, 0xf3, 0xf6, 0xf8, 0xfa, 0xff,
  0xff, 0xff, 0x02, 0x02, 0x02, 0x03, 0x04, 0x04, 0x06, 0x07, 0x08, 0x08,
  0x06, 0x05, 0x03, 0xfd, 0xfc, 0xfc, 0xf6, 0xf6, 0xfa, 0xfa, 0xf8, 0xfb,
  0xfd, 0xfc, 0xfe, 0x01, 0x02, 0x03, 0x03, 0x03, 0x05, 0x06, 0x05, 0x08,
  0x06, 0x02, 0x04, 0xfe, 0xf9, 0xfb, 0xfa, 0xfc, 0xfd, 0xfd, 0xfe, 0xff,
  0xfb, 0xfa, 0xfd, 0xfc, 0xfc, 0xff, 0x01, 0x01, 0x03, 0x02, 0x01, 0x05,
  0x02, 0xfe, 0x04, 0x03, 0xff, 0x04, 0x03, 0x00, 0x02, 0x01, 0xfe, 0xfc,
  0xfd, 0xfc, 0xfa, 0xfd, 0xfd, 0xfc, 0xfe, 0xfb, 0xfc, 0xfb, 0xfa, 0xfe,
  0xff, 0x00, 0x05, 0x05, 0x05, 0x06, 0x05, 0x06, 0x04, 0x04, 0x02, 0x01,
  0x00
};
const char ad_cannonball[] PROGMEM={
  0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x01, 0x02, 0x03, 0x03,
  0x03, 0x03, 0x03, 0x01, 0x00, 0xfe, 0xfd, 0xfc, 0xfa, 0xfa, 0xf9, 0xf9,
  0xf9, 0xfa, 0xfa, 0xfb, 0xfd, 0xfe, 0xff, 0x01, 0x02, 0x03, 0x03, 0x03,
  0x03, 0x02, 0x01, 0x00, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff,
  0xff, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x04, 0x04, 0x04, 0x03, 0x02,
  0x02, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe,
  0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x00, 0x01, 0x02, 0x03, 0x03, 0x04,
  0x03, 0x03, 0x02, 0x01, 0x00, 0xfe, 0xfd, 0xfb, 0xf9, 0xf8, 0xf7, 0xf6,
  0xf6, 0xf7, 0xf8, 0xfa, 0xfc, 0xfe, 0x00, 0x02, 0x04, 0x05, 0x06, 0x07,
  0x07, 0x07, 0x06, 0x05, 0x03, 0x01, 0xff, 0xfc, 0xfa, 0xf9, 0xf8, 0xf8,
  0xf9, 0xfb, 0xfc, 0xfe, 0x00, 0x02, 0x03, 0x04, 0x05, 0x05, 0x06, 0x05,
  0x05, 0x04, 0x02, 0x01, 0xff, 0xfe, 0xfe, 0xfd, 0xfd, 0xfd, 0xfe, 0xff,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe,
  0xfd, 0xfd, 0xfd, 0xfe, 0xff, 0x00, 0x02, 0x04, 0x06, 0x07, 0x07, 0x07,
  0x06, 0x05, 0x03, 0x00, 0xfd, 0xfb, 0xf8, 0xf7, 0xf5, 0xf4, 0xf4, 0xf4,
  0xf5, 0xf7, 0xf9, 0xfb, 0xfe, 0x01, 0x04, 0x07, 0x09, 0x0a, 0x0b, 0x0a,
  0x08, 0x06, 0x04, 0x01, 0xff, 0xfc, 0xfa, 0xf9, 0xf8, 0xf7, 0xf7, 0xf8,
  0xf9, 0xfb, 0xfd, 0xff, 0x02, 0x04, 0x06, 0x07, 0x07, 0x07, 0x06, 0x04,
  0x02, 0x01, 0x00, 0xff, 0xfe, 0xfd, 0xfd, 0xfd, 0xfd, 0xfe, 0xfe, 0xff,
  0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0xff, 0xfe, 0xfe, 0xfe,
  0xfe, 0xfe, 0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x07,
  0x06, 0x05, 0x03, 0x00, 0xfd, 0xfa, 0xf8, 0xf5, 0xf4, 0xf3, 0xf2, 0xf3,
  0xf4, 0xf6, 0xf8, 0xfa, 0xfd, 0x00, 0x03, 0x06, 0x08, 0x0a, 0x0b, 0x0b,
  0x0a, 0x09, 0x07, 0x04, 0x02, 0xff, 0xfc, 0xfa, 0xf9, 0xf8, 0xf7, 0xf7,
  0xf8, 0xf9, 0xfb, 0xfd, 0x00, 0x02, 0x03, 0x05, 0x06, 0x06, 0x06, 0x05,
  0x04, 0x03, 0x02, 0x01, 0x00, 0xff, 0xfe, 0xfd, 0xfd, 0xfd, 0xfd, 0xfe,
  0xff, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0xff, 0xff, 0xfe,
  0xfe, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02,
  0x02, 0x03, 0x03, 0x03, 0x02, 0x01, 0x00, 0xfe, 0xfc, 0xfb, 0xfa, 0xf9,
  0xf9, 0xf9, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff, 0x01, 0x02, 0x03,
  0x04, 0x04, 0x05, 0x04, 0x04, 0x03, 0x02, 0x01, 0x00, 0xfe, 0xfd, 0xfd,
  0xfc, 0xfc, 0xfc, 0xfd, 0xfd, 0xfe, 0xff, 0x00, 0x01, 0x01, 0x02, 0x02,
  0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0xff, 0xfe, 0xfe,
  0xfd, 0xfe, 0xfe, 0xfe, 0xff, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfe, 0xfe,
  0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
  0xff, 0x00, 0x01, 0x01, 0x02, 0x01, 0x01, 0x00, 0xff, 0xfe, 0xfe, 0xfd,
  0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfe, 0xfe, 0xff, 0x00,
  0x01, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x01, 0x00, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x00,
  0x01, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00
};
const char ad_item[] PROGMEM={
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0xff, 0x00,
  0x01, 0x01, 0x00, 0xff, 0xfe, 0xfe, 0xff, 0x01, 0x01, 0x00, 0xff, 0xfe,
  0xfe, 0xff, 0x00, 0x01, 0x01, 0xff, 0xfe, 0xfe, 0xff, 0x00, 0x02, 0x01,
  0x00, 0xfe, 0xfd, 0xfe, 0x00, 0x02, 0x02, 0x00, 0xfe, 0xfd, 0xfd, 0x00,
  0x02, 0x02, 0x01, 0xfe, 0xfc, 0xfd, 0x00, 0x02, 0x03, 0x01, 0xfe, 0xfc,
  0xfd, 0x00, 0x03, 0x03, 0x01, 0xfe, 0xfb, 0xfc, 0x00, 0x03, 0x04, 0x01,
  0xfd, 0xfb, 0xfc, 0x00, 0x03, 0x04, 0x01, 0xfd, 0xfb, 0xfc, 0x01, 0x04,
  0x04, 0x00, 0xfc, 0xfa, 0xfd, 0x01, 0x05, 0x04, 0x00, 0xfb, 0xfa, 0xfd,
  0x02, 0x06, 0x04, 0xff, 0xfa, 0xf9, 0xfe, 0x04, 0x07, 0x04, 0xfe, 0xf9,
  0xf9, 0xff, 0x05, 0x07, 0x03, 0xfc, 0xf8, 0xfa, 0x00, 0x06, 0x07, 0x01,
  0xfa, 0xf8, 0xfc, 0x03, 0x07, 0x05, 0xfe, 0xf8, 0xf8, 0xfe, 0x06, 0x08,
  0x03, 0xfb, 0xf7, 0xfa, 0x02, 0x08, 0x07, 0x00, 0xf8, 0xf7, 0xfd, 0x05,
  0x09, 0x05, 0xfc, 0xf6, 0xf8, 0x01, 0x08, 0x08, 0x01, 0xf8, 0xf6, 0xfc,
  0x06, 0x0a, 0x05, 0xfb, 0xf5, 0xf8, 0x02, 0x09, 0x08, 0x00, 0xf7, 0xf6,
  0xfd, 0x07, 0x0a, 0x04, 0xfa, 0xf5, 0xf9, 0x03, 0x0a, 0x08, 0xfe, 0xf5,
  0xf6, 0xff, 0x09, 0x0b, 0x03, 0xf8, 0xf3, 0xfa, 0x06, 0x0c, 0x07, 0xfb,
  0xf3, 0xf6, 0x02, 0x0b, 0x0a, 0x00, 0xf5, 0xf3, 0xfd, 0x09, 0x0d, 0x04,
  0xf7, 0xf2, 0xf9, 0x06, 0x0d, 0x08, 0xfb, 0xf2, 0xf5, 0x02, 0x0c, 0x0b,
  0x00, 0xf4, 0xf3, 0xfe, 0x0a, 0x0c, 0x03, 0xf7, 0xf2, 0xfa, 0x07, 0x0c,
  0x06, 0xfa, 0xf3, 0xf8, 0x04, 0x0c, 0x08, 0xfd, 0xf4, 0xf6, 0x01, 0x0a,
  0x09, 0xff, 0xf7, 0xf6, 0xfe, 0x07, 0x08, 0x02, 0xf9, 0xf7, 0xfd, 0x05,
  0x08, 0x03, 0xfb, 0xf8, 0xfc, 0x03, 0x06, 0x03, 0xfd, 0xfa, 0xfd, 0x01,
  0x03, 0x02, 0xfe, 0xfc, 0xfe, 0x01, 0x02, 0x00, 0xfe, 0xfe, 0x00, 0x02,
  0x01, 0xfe, 0xfc, 0xfe, 0x02, 0x04, 0x02, 0xfd, 0xfa, 0xfc, 0x03, 0x06,
  0x03, 0xfc, 0xf8, 0xfb, 0x03, 0x08, 0x05, 0xfd, 0xf7, 0xfa, 0x02, 0x07,
  0x06, 0xfe, 0xf8, 0xf9, 0x00, 0x06, 0x05, 0xff, 0xfa, 0xfa, 0xff, 0x04,
  0x05, 0x01, 0xfc, 0xfb, 0xfe, 0x03, 0x04, 0x01, 0xfd, 0xfc, 0xfe, 0x01,
  0x02, 0x01, 0xff, 0xfe, 0xfe, 0x00, 0x01, 0x01, 0x00, 0xfe, 0xfd, 0xff,
  0x01, 0x01, 0x00, 0xff, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
  0xff, 0xff, 0x00, 0x01, 0x00, 0xff, 0xfe, 0xfe, 0x00, 0x01, 0x01, 0xff,
  0xfe, 0xfe, 0x00, 0x02, 0x01, 0xff, 0xfd, 0xff, 0x01, 0x02, 0x00, 0xfe,
  0xfd, 0xff, 0x01, 0x02, 0x00, 0xfe, 0xfd, 0xff, 0x01, 0x02, 0x00, 0xfe,
  0xfe, 0x00, 0x01, 0x01, 0xff, 0xfe, 0xff, 0x00, 0x01, 0x00, 0xfe, 0xfe,
  0xff, 0x01, 0x01, 0xff, 0xfe, 0xfe, 0xff, 0x01, 0x01, 0x00, 0xfe, 0xfe,
  0xff, 0x00, 0x01, 0x01, 0xff, 0xfd, 0xfe, 0xff, 0x01, 0x02, 0x00, 0xfe,
  0xfd, 0xff, 0x01, 0x01, 0x00, 0xff, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x00
};
const char ad_level_clear[] PROGMEM={0x00,0x00};
const char ad_level_start[] PROGMEM={0x00,0x00};
const char ad_metal[] PROGMEM={
  0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xfe, 0x03, 0xfc, 0xed, 0xed, 0xed,
  0xed, 0x11, 0x0f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x0a, 0x11,
  0x11, 0x0d, 0x01, 0x08, 0xfa, 0x0b, 0xfb, 0xfc, 0xf6, 0x01, 0xf9, 0x00,
  0xf2, 0xf5, 0xfa, 0x02, 0x01, 0xff, 0xff, 0xfb, 0xfe, 0xf9, 0x03, 0xf7,
  0xff, 0xff, 0x07, 0xfb, 0xf6, 0xfb, 0xfa, 0x04, 0xff, 0x01, 0xf7, 0x07,
  0xf8, 0x01, 0xf2, 0xfd, 0xf8, 0x0a, 0xfd, 0xfa, 0xf7, 0xf4, 0x05, 0xff,
  0x03, 0xf4, 0x06, 0xfa, 0x0a, 0xf5, 0x03, 0xfa, 0x0c, 0x03, 0x08, 0xfd,
  0x01, 0x04, 0x02, 0x06, 0xfd, 0x02, 0xfe, 0x07, 0xf9, 0xfe, 0xf7, 0x01,
  0x03, 0x04, 0xff, 0xf9, 0xf4, 0x03, 0x02, 0xfa, 0xfa, 0x00, 0x02, 0x05,
  0xfd, 0x02, 0x02, 0x08, 0x08, 0x06, 0x03, 0x01, 0x01, 0xfd, 0x01, 0xf7,
  0x01, 0xfc, 0x03, 0xf9, 0xfe, 0xf3, 0xff, 0xfd, 0x02, 0xfe, 0xff, 0x00,
  0xff, 0x06, 0xfa, 0x04, 0xfc, 0x07, 0xfc, 0x02, 0xf4, 0x02, 0xff, 0x08,
  0x05, 0x04, 0x03, 0x04, 0x05, 0xfa, 0x03, 0xf3, 0xff, 0xf8, 0x00, 0xf7,
  0xfe, 0xfa, 0x03, 0x00, 0xfe, 0xff, 0xfe, 0x07, 0x01, 0x05, 0xfc, 0x00,
  0xfe, 0x0b, 0xff, 0x01, 0xfd, 0x02, 0x04, 0xff, 0xfe, 0xfc, 0xfe, 0xfb,
  0x01, 0xf8, 0xfe, 0xfd, 0x06, 0x01, 0x02, 0xf9, 0x02, 0x03, 0x04, 0x00,
  0xfd, 0xfe, 0xff, 0xfe, 0xfc, 0xfe, 0xfc, 0x03, 0x04, 0x02, 0xff, 0x00,
  0x00, 0x04, 0x01, 0x00, 0xfe, 0x00, 0xff, 0x02, 0xff, 0xfd, 0xfe, 0xfe,
  0xff, 0xfa, 0xfd, 0xfa, 0xff, 0xfc, 0x00, 0xfe, 0x02, 0xff, 0x03, 0x01,
  0x01, 0x03, 0x03, 0x04, 0x03, 0x02, 0xfd, 0x00, 0xfe, 0x00, 0xfd, 0xff,
  0xfd, 0xff, 0xfd, 0xfc, 0xfb, 0xfd, 0x00, 0xff, 0x00, 0xfd, 0x00, 0x00,
  0x03, 0x01, 0x02, 0x00, 0x00, 0x00, 0xfe, 0xfd, 0xfd, 0x00, 0x01, 0x03,
  0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0xff, 0x01, 0xff, 0xff, 0xfc,
  0x00, 0xff, 0x00, 0xfe, 0xfd, 0xfd, 0xfe, 0xff, 0xfd, 0x00, 0xfe, 0x03,
  0x00, 0x02, 0xff, 0x01, 0x02, 0x02, 0x01, 0xfe, 0xff, 0xfe, 0x01, 0xfe,
  0x00, 0xfc, 0x00, 0xfe, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x02, 0xfe, 0x00,
  0xfd, 0x02, 0xff, 0x02, 0xff, 0x01, 0x01, 0x02, 0x00, 0xfe, 0x00, 0xfe,
  0x02, 0xfe, 0x00, 0xfd, 0x00, 0xfd, 0x00, 0xfd, 0xff, 0xff, 0x00, 0x00,
  0xfe, 0xff, 0xfd, 0x01, 0xff, 0x01, 0xfe, 0x00, 0xff, 0x00, 0xff, 0xfe,
  0x00, 0x00, 0x02, 0x00, 0x01, 0xfe, 0x01, 0x00, 0x01, 0xff, 0xfe, 0xff,
  0xfe, 0xfe, 0xfd, 0xfe, 0xfd, 0x01, 0xff, 0x01, 0xff, 0x01, 0x01, 0x02,
  0x00, 0x00, 0x01, 0xfe, 0x00, 0xfd, 0xff, 0xfe, 0x01, 0x00, 0x00, 0xff,
  0xff, 0x00, 0xff, 0x00, 0xfe, 0x00, 0xfe, 0x00, 0xfe, 0xfe, 0xfe, 0x00,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0xff, 0x01, 0xff, 0x00, 0xff, 0x01, 0xff,
  0xff, 0xff, 0x00, 0x01, 0x00, 0x00, 0xff, 0x00, 0xfe, 0x00, 0xfe, 0xff,
  0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0x00, 0xff, 0x00, 0xff,
  0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x01,
  0xff, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
  0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0xff, 0x00,
  0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff,
  0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x00, 0x00, 0x01,
  0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x01, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xfe, 0xff,
  0xff, 0xff, 0x00, 0x00
};
const char ad_navigate[] PROGMEM={
  0x00, 0xfc, 0xfe, 0xfe, 0xf3, 0xed, 0xf0, 0x03, 0x17, 0x24, 0x18, 0x0f,
  0x09, 0x01, 0xf7, 0xf2, 0xf4, 0xf9, 0x00, 0xfb, 0xf4, 0xf0, 0xf5, 0xfc,
  0x02, 0x01, 0xfb, 0xf8, 0xfb, 0x02, 0x09, 0x0a, 0x07, 0x00, 0xff, 0xff,
  0x01, 0x00, 0x00, 0x02, 0x03, 0x03, 0x00, 0xff, 0x00, 0x03, 0x02, 0xff,
  0xfe, 0xff, 0xff, 0xfe, 0xfc, 0xfb, 0xfc, 0x01, 0x03, 0x03, 0x01, 0x00,
  0xff, 0xfe, 0xfe, 0xff, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
  0x02, 0x02, 0x00, 0xfe, 0xfd, 0xfc, 0xfc, 0xfb, 0xfa, 0xfd, 0x00, 0x00,
  0xfe, 0xfd, 0xfe, 0x00, 0x03, 0x05, 0x05, 0x04, 0x00, 0xfe, 0xfc, 0xfd,
  0xfe, 0x02, 0x08, 0x09, 0x03, 0xfa, 0xf7, 0xf8, 0xfd, 0xff, 0x00, 0x01,
  0x01, 0xfd, 0xfc, 0xfe, 0x00, 0x02, 0x03, 0x01, 0xfd, 0xfb, 0xfc, 0xff,
  0x01, 0x05, 0x04, 0x02, 0x01, 0x01, 0x00, 0x00, 0xff, 0xff, 0x01, 0x01,
  0x00, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x01, 0x01, 0xff, 0xfe, 0xfd, 0xfc,
  0xfc, 0xfe, 0x00, 0x01, 0x02, 0x02, 0x00, 0xff, 0xff, 0xfe, 0xfe, 0xff,
  0x00, 0x00, 0x00, 0x01, 0xff, 0xfd, 0xfc, 0xfe, 0x00, 0x01, 0x02, 0x01,
  0xff, 0xfe, 0xfe, 0xfd, 0x00, 0x02, 0x05, 0x04, 0x02, 0x00, 0xfe, 0xfe,
  0xfc, 0xfe, 0xff, 0x02, 0x03, 0x02, 0xfe, 0xfb, 0xfa, 0xfb, 0xfd, 0xfe,
  0x00, 0x01, 0x01, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0x00, 0x01, 0x0a,
  0x0a, 0x07, 0x00, 0xf8, 0xf3, 0xef, 0xf6, 0xfe, 0x0b, 0x10, 0x11, 0x0b,
  0x00, 0xf6, 0xee, 0xef, 0xf4, 0xff, 0x08, 0x0d, 0x0e, 0x0a, 0x03, 0xf9,
  0xf4, 0xf0, 0xf4, 0xfc, 0x04, 0x0c, 0x0d, 0x0d, 0x06, 0xfe, 0xf4, 0xef,
  0xf1, 0xf7, 0x02, 0x0a, 0x0e, 0x0d, 0x06, 0xfd, 0xf4, 0xf0, 0xf2, 0xfa,
  0x03, 0x0b, 0x0d, 0x0a, 0x04, 0xfd, 0xf8, 0xf5, 0xf6, 0xfb, 0x03, 0x09,
  0x0a, 0x08, 0x02, 0xfc, 0xf7, 0xf5, 0xf6, 0xfa, 0x00, 0x05, 0x07, 0x07,
  0x05, 0x02, 0xfe, 0xfb, 0xf8, 0xf9, 0xfd, 0x03, 0x08, 0x0a, 0x07, 0x00,
  0xf9, 0xf4, 0xf5, 0xf9, 0x01, 0x09, 0x0c, 0x0a, 0x03, 0xfc, 0xf7, 0xf5,
  0xf8, 0xfb, 0x00, 0x05, 0x09, 0x08, 0x04, 0x00, 0xfc, 0xfa, 0xf8, 0xfa,
  0xfd, 0x05, 0x0a, 0x0b, 0x06, 0xff, 0xf9, 0xf6, 0xf5, 0xf7, 0xfd, 0x04,
  0x0a, 0x0a, 0x05, 0xff, 0xf9, 0xf7, 0xf7, 0xfa, 0xfe, 0x04, 0x08, 0x08,
  0x05, 0x00, 0xfc, 0xfa, 0xfa, 0xfc, 0xff, 0x02, 0x05, 0x06, 0x04, 0x00,
  0xfb, 0xf8, 0xf8, 0xfb, 0xff, 0x03, 0x06, 0x07, 0x04, 0xff, 0xfb, 0xf8,
  0xfa, 0xfd, 0x01, 0x03, 0x04, 0x03, 0x01, 0x00, 0x00, 0x00
};
const char ad_rocket[] PROGMEM={0x00,0x00};
const char ad_splash[] PROGMEM ={
	0,PC_NOTE_CUT,0,
	0,PATCH_END
};
const char ad_tank_explode[] PROGMEM={0x00,0x00};
const char ad_tracks[] PROGMEM={0x00,0x00};
const char ad_silence[] PROGMEM={0x00,0x00};
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
	1,PC_NOTE_CUT,0,
	0,PATCH_END
};

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
  {0,0,ad_splash,0,0},
  {2,ad_brick_explode,0,sizeof(ad_brick_explode)-2,sizeof(ad_brick_explode)-1},
  {2,ad_tracks,0,sizeof(ad_tracks)-2,sizeof(ad_tracks)-1},
  {2,ad_silence,0,0,0},
  {0,0,ad_alarm,0,0},
};

#endif
