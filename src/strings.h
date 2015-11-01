/*
 * All printable strings
 *
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
#ifndef LB_STRINGS_H
#define LB_STRINGS_H


// String indexes
#define strCopyright 0
#define str1Player 21
#define str2Player 35
#define strHighscores 52
#define strHandlesTitle 62
#define strUnderline 74
#define strVertSep 86
#define strPlayer1 88
#define strPlayer2 91
#define strSelectHandle 94
#define strConfirmHandle 105
#define strCancelHandle 117
#define strReset 128
#define strChangeHandle 153
#define strOwns 168
#define strBy 173
#define strFinalScore 176
#define banter_map 188
#define strBanterClear 338
#define strScore 353
#define strTotal 360
#define strExit 367
#define strPaused 376
#define strLevels 383


// Many strings
const char strMap [] PROGMEM="2015 Lawrence Brooks\0"
"Player vs CPU\0"
"Player vs Player\0"
"Tank Rank\0"
"Edit Handle\0"
"___________\0"
"|\0"
"P1\0"
"P2\0"
"Select - A\0"
"Confirm - A\0"
"Cancel - X\0"
"Reset Defaults - SL (5s)\0"
"Edit - UP/DOWN\0"
"Owns\0"
"By\0"
"Final Score\0"
"Such Fail     \0"
"LOL           \0"
"Broken button?\0"
"Try at least  \0"
"Too easy      \0"
"*YAWN*        \0"
"Noob          \0"
"That's it?    \0"
"Need help?    \0"
"Pfft          \0"
"              \0"
"Score:\0"
"Total:\0"
"Bail - X\0"
"Paused\0"
"   Boot Camp   \0"
"   Velocity    \0"
"    Digger     \0"
"Act 1 They Meet\0"
"   Richochet   \0"
" The Honey Pot \0"
"  Focal Point  \0"
"It's Not Fair! \0"
"  Much Better  \0"
"   Face Off    \0"
"     Test      ";

// Default handles and scores
const unsigned char default_handles[] PROGMEM = {
    // 1. UZE
    // 2. LJB
    // 3. AAA
    // 4. BBB
    // 5. CCC
    // 6. DDD
    // 7. EEE
    // 8. FFF
    // 9. GGG
    // 10. CPU
    0x55, 0x5a, 0x45,
    0x4c, 0x4a, 0x42,
    0x41, 0x41, 0x41,
    0x42, 0x42, 0x42,
    0x43, 0x43, 0x43,
    0x44, 0x44, 0x44,
    0x45, 0x45, 0x45,
    0x46, 0x46, 0x46,
    0x47, 0x47, 0x47,
    0x43, 0x50, 0x55
};

const unsigned char default_scores[] PROGMEM = {
    // 1. owns 2. by 20 - 13
    // 2. owns 3. by 20 - 14
    // 3. owns 4. by 20 - 15
    // 4. owns 5. by 20 - 16
    // 5. owns 6. by 20 - 17
    // 6. owns 7. by 20 - 18
    // 7. owns 1. by 20 - 19
    0, 1, 20, 13,
    1, 2, 20, 14,
    2, 3, 20, 15,
    3, 4, 20, 16,
    4, 5, 20, 17,
    5, 6, 20, 18,
    6, 0, 20, 19,
    0, 0
};

#endif
