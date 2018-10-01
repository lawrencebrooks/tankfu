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
#include "uzenet.h"

#define NETHIT 0
#define NETTURRETHIT 1
#define NETSHOOT 2
#define NETITEMSPEED 3
#define NETITEMROCKET 4
#define NETITEMBOMB 5
#define NETPOSCHANGE 6
#define NETBLOCKHIT 7
#define NETPAUSETOGGLE 8
#define NETEXIT 9
#define NETHANDLESELECT 10
#define NETJOINED 11
#define NETNODATA 12

typedef struct NetMessageStruct {
    u8 code;
    u16 held;
	u16 pressed;
	u8 object_pos_x;
	u8 object_pos_y;
	u8 score;
	u8 level_score;
	u8 hud_x;
	char handle_id;
	u8 handle[3];
	char char_index;
	u8 select_state;
	u8 direction;
	u8 speed;
	u8 recoiled;
	float pos_x;
	float pos_y;
	u8 zero;
} NetMessage;

u8 disablePassthroughMode() {
	u8 counter = 0;
	wifiSendP(PSTR("+++"));
	while(counter++ < 5) WaitUs(65535);
	InitUartTxBuffer();
	InitUartRxBuffer();
	if (wifiRequestPT(PSTR("AT+CIPMODE=0\r\n"),PSTR("OK\r\n"), 2*60) != WIFI_OK) return WIFI_TIMEOUT;
	if (wifiRequestPT(PSTR("AT+CIPCLOSE\r\n"),PSTR("OK\r\n"), 2*60) != WIFI_OK) return WIFI_TIMEOUT;
	return WIFI_OK;
}

u8 activateNet() {
	disablePassthroughMode();
	InitUartTxBuffer();
	InitUartRxBuffer();
	return initWifi();
}

u8 sendNetMessage(NetMessage* msg) {
	return wifiSend((char *) msg);
}

u8 getNetMessage(NetMessage* msg) {
	return wifiGetIfAvailable(msg, sizeof(msg));
}

u8 hostNetGame(char* ssid) {
	char buf[64];
	
	// Set SoftAP mode...
	if (wifiRequestP(PSTR("AT+CWMODE_CUR=2\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Disable DHCP...
	if (wifiRequestP(PSTR("AT+CWDHCP_CUR=0,0\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Set SopftAP IP address
	if (wifiRequestP(PSTR("AT+CIPAP_CUR=\"192.168.4.1\"\r\n"), PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Get SoftAP MAC address...
	wifiSendP(PSTR("AT+CIPAPMAC_CUR?\r\n"));
	if (wifiGetPB(PSTR("OK\r\n"), buf) != WIFI_TIMEOUT) {
		ssid[0] = 'T';
		ssid[1] = 'F';
		u8 idx = 2;
		for (u8 i = 43; i <= 49; i += 3) {
		   ssid[idx++] = buf[i];
		   ssid[idx++] = buf[i+1];
		}
		ssid[8] = 0;
	}
	ssid = strupr(ssid);
	sprintf(buf, "AT+CWSAP_CUR=\"%s\",\"T4nkFuN3t\",5,3,1\r\n", ssid);
	
	// Setup local access point...
	if (wifiRequest(buf,PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Activate UDP Passthrough mode
	if (wifiRequestP(PSTR("AT+CIPSTART=\"UDP\",\"192.168.4.2\",1001,2233,0\r\n"), PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	if (wifiRequestP(PSTR("AT+CIPMODE=1\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	wifiSendP(PSTR("AT+CIPSEND\r\n"));
	return WIFI_OK;
}

u8 joinNetGame(const char* ssid) {
	char buf[64];
	
	sprintf(buf, "AT+CWJAP_CUR=\"%s\",\"T4nkFuN3t\"\r\n", ssid);
	
	// Set Station mode...
	if (wifiRequestP(PSTR("AT+CWMODE_CUR=1\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Disable DHCP...
	if (wifiRequestP(PSTR("AT+CWDHCP_CUR=1,0\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// List access points...
	if (wifiRequestP(PSTR("AT+CWLAP\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Connect to access point...
	if (wifiRequest(buf,PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Set station IP address
	if (wifiRequestP(PSTR("AT+CIPSTA_CUR=\"192.168.4.2\"\r\n"), PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Activate UDP Passthrough mode
	if (wifiRequestP(PSTR("AT+CIPSTART=\"UDP\",\"192.168.4.1\",2233,1001\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	if (wifiRequestP(PSTR("AT+CIPMODE=1\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	wifiSendP(PSTR("AT+CIPSEND\r\n"));
	return WIFI_OK;
}

#endif
