/*
 * All printable strings
 */
#ifndef LB_STRINGS_H
#define LB_STRINGS_H

// Menus
const char strCopyright [] PROGMEM="2014 - Lawrence Brooks";
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
const char strChangeHandle [] PROGMEM= "Edit - UP/DOWN";
const char strOwns [] PROGMEM = "Pwns";
const char strBy [] PROGMEM = "By";

// Banter
const char strB1[] PROGMEM="You suck bro";
const char strB2[] PROGMEM="LOL";
const char strB3[] PROGMEM="Broken button?";
const char strB4[] PROGMEM="At least try";
const char strB5[] PROGMEM="Too easy";
const char strB6[] PROGMEM="*YAWN*";
const char strB7[] PROGMEM="A turkey shoot";
const char strB8[] PROGMEM="That's it?";
const char strB9[] PROGMEM="Need help?";
const char strB10[] PROGMEM="RTFM!";
const char strBanterClear[] PROGMEM="              ";

// In-Game
const char strScore [] PROGMEM = "Score:";
const char strTotal [] PROGMEM = "Total:";
const char strExit [] PROGMEM = "Bail - X";
const char strPaused [] PROGMEM = "Paused";

// Level names
const char strLevel1[] PROGMEM="Level   One";
const char strLevel2[] PROGMEM="Level   Two";
const char strLevel3[] PROGMEM="Level Three";
const char strLevel4[] PROGMEM="Level  Four";
const char strLevel5[] PROGMEM="Level  Five";
const char strLevel6[] PROGMEM="Level   Six";
const char strLevel7[] PROGMEM="Level Seven";
const char strLevel8[] PROGMEM="Level Eight";
const char strLevel9[] PROGMEM="Level  Nine";
const char strLevel10[] PROGMEM="Level   Ten";

const char* banter_map[] = {
	strB1,
	strB2,
	strB3,
	strB4,
	strB5,
	strB6,
	strB7,
	strB8,
	strB9,
	strB10
};
const char* level_names[] = {
	strLevel1,
	strLevel2,
	strLevel3,
	strLevel4,
	strLevel5,
	strLevel6,
	strLevel7,
	strLevel8,
	strLevel9,
	strLevel10
};

#endif
