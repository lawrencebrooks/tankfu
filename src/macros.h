/*
 * Author: Lawrence Brooks
 */

#ifndef LB_MACROS_H
#define LB_MACROS_H

// EEPROM ID's
#define EEPROM_HANDLES_ID 0x87
#define EEPROM_TANK_RANK_ID 0x88

// Screens
#define SPLASH 0
#define TANK_RANK 1
#define HANDLE_SELECT 2
#define LEVEL 3

// Selections
#define PVCPU 0
#define PVP 1
#define TR 2

// Frame counts
#define FRAMES_PER_FADE 3
#define FRAMES_PER_BANTER 90
#define FRAMES_PER_GRACE 120
#define FRAMES_PER_BLANK 20
#define FRAMES_PER_ANIM 5

// Handle select states
#define SELECTING 0
#define EDITING 1
#define CONFIRMED 2

// Movement
#define D_UP 0
#define D_RIGHT 1
#define D_DOWN 2
#define D_LEFT 3
#define MAX_SPEED 50
#define OVER_SPEED 65

// Shot
#define BASIC_SHOT 0
#define ROCKET_SHOT 1
#define BASIC_SHOT_HIT_COUNT 1
#define ROCKET_SHOT_HIT_COUNT 5
#define SHOT_REBOUNDS 4
#define SHOT_SPEED 100
#define SHOT_OVER_SPEED 150
#define MAX_SHOTS 2
#define DISTANCE_TO_ARM 8

// General macros
#define FRAME_TIME 0.0166666
#define TEXT_LINGER 2 // seconds
#define MAX_LEVEL_SCORE 1
#define TILE_ANIMATIONS_LENGTH 2

// Flags
#define EXPLODING_FLAG 1
#define ROCKET_FLAG 2
#define OVER_SPEED_FLAG 4

// Sound Effects
#define SFX_BANTER TriggerNote(PCM_CHANNEL,PATCH_BANTER,30,0x5f)
#define SFX_BRICK_EXPLODE TriggerNote(PCM_CHANNEL,PATCH_BRICK_EXPLODE,23,0xdf)
#define SFX_CANNONBALL TriggerNote(PCM_CHANNEL,PATCH_CANNONBALL,23,0xff)
#define SFX_ITEM TriggerNote(PCM_CHANNEL,PATCH_ITEM,23,0xff)
#define SFX_LEVEL_CLEAR TriggerNote(PCM_CHANNEL,PATCH_LEVEL_CLEAR,23,0xff)
#define SFX_LEVEL_START TriggerNote(PCM_CHANNEL,PATCH_LEVEL_START,23,0xff)
#define SFX_METAL TriggerNote(PCM_CHANNEL,PATCH_METAL,23,0xff)
#define SFX_NAVIGATE TriggerNote(PCM_CHANNEL,PATCH_NAVIGATE,23,0xff)
#define SFX_ROCKET TriggerNote(PCM_CHANNEL,PATCH_ROCKET,23,0xff)
#define SFX_SPLASH TriggerNote(PCM_CHANNEL,PATCH_SPLASH,23,0xff)
#define SFX_TANK_EXPLODE TriggerNote(PCM_CHANNEL,PATCH_TANK_EXPLODE,16,0xff)
#define SFX_TRACKS TriggerNote(PCM_CHANNEL,PATCH_TRACKS,23,0xff)
#define SFX_SILENCE TriggerNote(PCM_CHANNEL,PATCH_SILENCE,23,0xff)

#endif
