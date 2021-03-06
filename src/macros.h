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

#ifndef LB_MACROS_H
#define LB_MACROS_H

// EEPROM ID's
#define EEPROM_HANDLES_ID 0x8A
#define EEPROM_TANK_RANK_ID 0x8B
#define EEPROM_DIP_SWITCH_ID 0xAB0C

// Screens
#define SPLASH 0
#define TANK_RANK 1
#define HANDLE_SELECT 2
#define LEVEL 3
#define HOST_NET_GAME 4
#define JOIN_NET_GAME 5

// Selections
#define PVCPU 0
#define PVP 1
#define HOSTNETGAME 2
#define JOINNETGAME 3
#define TR 4
#define CPUVCPU 6

// Frame counts
#if JAMMA
#define FRAMES_PER_FADE 0
#else
#define FRAMES_PER_FADE 3
#endif
#define FRAMES_PER_GRACE 120
#define FRAMES_PER_BLANK 20
#define FRAMES_PER_ANIM 5
#define FRAMES_PER_SCOPE 30
#define FRAMES_PER_SUB 60

// Handle select states
#define SELECTING 0
#define EDITING 1
#define CONFIRMED 2

// Movement
#define D_UP 0
#define D_RIGHT 1
#define D_DOWN 2
#define D_LEFT 3
#define MAX_SPEED 5000
#define OVER_SPEED 6500
#define WATER_SPEED 2500

// Shot
#define BASIC_SHOT 0
#define ROCKET_SHOT 1
#define BASIC_SHOT_HIT_COUNT 1
#define ROCKET_SHOT_HIT_COUNT 5
#define SHOT_REBOUNDS 4
#define SHOT_SPEED 12000
#define SHOT_OVER_SPEED 17000
#define MAX_SHOTS 1
#define DISTANCE_TO_ARM 800
#define HIT_METAL 1
#define HIT_BRICK 2
#define HIT_ANGLE 4

// General macros
#define FRAME_TIME 0.0166666
#define FRAME_TIME_INVERTED 60
#define TEXT_LINGER 4 // seconds
#define MAX_LEVEL_SCORE 10 
#define TILE_ANIMATIONS_LENGTH 2
#define DEMO_WAIT 600
#define DEMO_LENGTH 1800
#define TANK_RANK_LENGTH 900
#define SCOPE_REVEAL 1000

// Boss macros
#define BOSS_FIGHT_SCOPE_LOADING 1
#define BOSS_FIGHT_SUB_LOADING 2
#define BOSS_FIGHT 4
#define BOSS_FIGHT_WON 8
#define BOSS_FIGHT_LOST 16
#define BOSS_FIGHT_SUB_SINKING 32
#define BOSS_FIGHT_PLAYER_LIVES 2
#define BOSS_TURRET_LIVES 5
#define BOSS_TURRET_SPEED 9000
#define BOSS_TURRET_SHOT_SPEED 25000
#define BOSS_TURRET_SHOT 2
#define BOSS_TURRET_SHOT_HIT_COUNT 1
#define BOSS_TURRET_1_LEFT_LIMIT 4000
#define BOSS_TURRET_1_RIGHT_LIMIT 9600
#define BOSS_TURRET_2_LEFT_LIMIT 13600
#define BOSS_TURRET_2_RIGHT_LIMIT 19200

// Flags
#define EXPLODING_FLAG 1
#define ROCKET_FLAG 2
#define OVER_SPEED_FLAG 4

// AI Macros
#define DEFAULT_FRAMES_PER_GOAL 180
#define DEFAULT_FRAMES_PER_SHOT 10
#define FRAMES_PER_DEADLOCK 320
#define AI_SPEED_FACTOR 1.4
#define AI_SPEED_FACTOR_INVERTED 2
#define TACTIC_TANK_ATTACK 0
#define TACTIC_TANK_EVADE 1
#define TACTIC_SHOT_IGNORE 0
#define TACTIC_SHOT_EVADE 1

#endif
