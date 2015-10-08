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

// Menus
const char strCopyright [] PROGMEM="2015 - Lawrence Brooks";
const char str1Player [] PROGMEM="Player vs CPU";
const char str2Player [] PROGMEM="Player vs Player";
const char strHighscores [] PROGMEM="Tank Rank";
const char strHandlesTitle [] PROGMEM="Edit Handle";
const char strUnderline[] PROGMEM="___________";
const char strVertSep[] PROGMEM="|";
const char strPlayer1 [] PROGMEM="P1";
const char strPlayer2 [] PROGMEM="P2";
const char strSelectHandle [] PROGMEM= "Select - A";
const char strConfirmHandle [] PROGMEM="Confirm - A";
const char strCancelHandle [] PROGMEM= "Cancel - X";
const char strReset [] PROGMEM= "Reset Defaults - SL (5s)";
const char strChangeHandle [] PROGMEM= "Edit - UP/DOWN";
const char strOwns [] PROGMEM = "Pwns";
const char strBy [] PROGMEM = "By";
const char strFinalScore [] PROGMEM="Final Score";

// Debug
const char strDebug[] PROGMEM="GD\0GL\0BT\0CX\0CY\0MV\0FW";
#define GD 0
#define GL 3
#define BT 6
#define CX 9
#define CY 12
#define MV 15
#define FW 18

// Banter
const char banter_map[] PROGMEM="You suck bro  \0"
	"LOL           \0"
	"Broken button?\0"
	"Try at least  \0"
	"Too easy      \0"
	"*YAWN*        \0"
	"A turkey shoot\0"
	"That's it?    \0"
	"Need help?    \0"
	"RTFM!         ";
const char strBanterClear[] PROGMEM="              ";

// In-Game
const char strScore [] PROGMEM = "Score:";
const char strTotal [] PROGMEM = "Total:";
const char strExit [] PROGMEM = "Bail - X";
const char strPaused [] PROGMEM = "Paused";

// Level names
const char strLevels[] PROGMEM="   Boot Camp   \0"
	"   Velocity    \0"
	"    Digger     \0"
	"Act 1 They Meet\0"
	"   Richochet   \0"
	" The Honey Pot \0"
	"  Focal Point  \0"
	"It's Not Fair! \0"
	"  Much Better  \0"
	"   Face Off    ";

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
