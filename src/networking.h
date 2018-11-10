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
#include "types.h"

#define NETHIT 0
#define NETHITBYTURRET 1
#define NETSHOOT 2
#define NETITEMSPEED 3
#define NETITEMROCKET 4
#define NETITEMBOMB 5
#define NETPOSCHANGE 6
#define NETPAUSE 7
#define NETEXIT 8
#define NETHANDLESELECT 9
#define NETJOINED 10
#define NETNODATA 11
#define NETTURRETHIT 12
#define NETRESUME 13
#define NETBLOCKHIT 14
#define NETACK 15

u8 activateNet() {
	return initWifi();
}

u8 sendNetMessage(NetMessage* msg) {
	return wifiSendBinary((char *) msg, sizeof(*msg));
}

u8 getNetMessage(NetMessage* msg) {
	return wifiGetIfAvailable((char*)msg, sizeof(*msg));
}

u8 hostNetGame(char* ssid) {
	char buf[64];
	
	// Set SoftAP mode...
	if (wifiRequestP(PSTR("AT+CWMODE_CUR=2\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
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
	if (wifiRequestP(PSTR("AT+CIPSEND\r\n"),PSTR("OK\r\n\r\n>")) != WIFI_OK) return WIFI_TIMEOUT;
	return WIFI_OK;
}

u8 joinNetGame(char* ssid) {
	char buf[38];
	
	sprintf(buf, "AT+CWJAP_CUR=\"%s\",\"T4nkFuN3t\"\r\n", ssid);
	
	// Set Station mode...
	if (wifiRequestP(PSTR("AT+CWMODE_CUR=1\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Connect to access point...
	if (wifiRequest(buf,PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Set station IP address
	if (wifiRequestP(PSTR("AT+CIPSTA_CUR=\"192.168.4.2\"\r\n"), PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	// Activate UDP Passthrough mode
	if (wifiRequestP(PSTR("AT+CIPSTART=\"UDP\",\"192.168.4.1\",2233,1001\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	if (wifiRequestP(PSTR("AT+CIPMODE=1\r\n"),PSTR("OK\r\n")) != WIFI_OK) return WIFI_TIMEOUT;
	if (wifiRequestP(PSTR("AT+CIPSEND\r\n"),PSTR("OK\r\n\r\n>")) != WIFI_OK) return WIFI_TIMEOUT;
	return WIFI_OK;
}

#endif
