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

#include "strings.h"

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
#define P2PBANTER 15

typedef struct ESP2866MessageStruct {
    u8 buffer[64];
} ESP2866Message;

u8 espCommand(ESP2866Message* response, const char* command) {
    return 0;
} 

#endif
