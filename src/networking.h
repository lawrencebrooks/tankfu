/*
 * Program: Tank Fu
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

#ifndef NETWORKING_HH
#define NETWORKING_HH

#define P2PHIT 0
#define P2PSHOOT 1
#define P2PITEMSPEED 2
#define P2PITEMROCKET 3
#define P2PITEMBOMB 4
#define P2PPOSCHANGE 5
#define P2PBLOCKHIT 6
#define P2PLEVELEND 7
#define P2PIMREADY 9
#define P2PPAUSE 10
#define P2PRESUME 11
#define P2PEXIT 12
#define P2PHANDLESELECT 13
#define P2PHANDLESELECTDONE 14

typedef struct P2PMessageHeaderStruct {
    u8 code;
    u8 xpos;
    u8 ypos;
} P2PMessageHeader;

typedef struct P2PHitMessageStruct {
    P2PMessageHeader header;
} P2PHitMessage;


typedef struct P2PShootMessageStruct {
    P2PMessageHeader header;
} P2PShootMessage;

typedef struct P2PItemSpeedMessageStruct {
    P2PMessageHeader header;
} P2PItemSpeedMessage;

typedef struct P2PItemRocketMessageStruct {
    P2PMessageHeader header;
} P2PItemRocketMessage;

typedef struct P2PItemBombMessageStruct {
    P2PMessageHeader header;
} P2PItemBombMessage;

typedef struct P2PPosChangeMessageStruct {
    P2PMessageHeader header;
} P2PPosChangeMessage;

typedef struct P2PBlockHitMessageStruct {
    P2PMessageHeader header;
} P2PBlockHitMessage;

typedef struct P2PLevelEndMessageStruct {
    P2PMessageHeader header;
} P2PLevelEndMessage;

typedef struct P2PImReadyMessageStruct {
    P2PMessageHeader header;
} P2PImReadyMessage;

typedef struct P2PPauseMessageStruct {
    P2PMessageHeader header;
} P2PPauseMessage;

typedef struct P2PResumeMessageStruct {
    P2PMessageHeader header;
} P2PResumeMessage;

typedef struct P2PExitMessageStruct {
    P2PMessageHeader header;
} P2PExitMessage;

typedef struct P2PHandleSelectMessageStruct {
    P2PMessageHeader header;
} P2PHandleSelectMessage;

typedef struct P2PHandleSelectDoneMessageStruct {
    P2PMessageHeader header;
} P2PHandleSelectDoneMessage;

#endif
