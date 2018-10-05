/*
 * uzenet.c
 *
 *  Created on: Oct 16, 2015
 *      Author: admin
 */
#ifndef UZENET_HH
#define UZENET_HH

#include <stdbool.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <uzebox.h>
#include "utils.h"

#define WIFI_OK 0
#define WIFI_TIMEOUT 1
#define WIFI_NODATA 2

#define TIMEOUT 10*60

u8 wifiSendP(const char* str){

	char c;
	while(str!=NULL){
		c=pgm_read_byte(str);
		if(c==0)break;
		while(UartSendChar(c)==-1); //block if buffer full
		str++;
	};

	return WIFI_OK;
}

u8 wifiSend(char* str){

	char c;
	while(str!=NULL){
		c=*str;
		if(c==0)break;
		while(UartSendChar(c)==-1); //block if buffer full
		str++;
	};
	return WIFI_OK;
}

u8 wifiSendBinary(char* str, u8 sz){

	char c;
	while(sz--){
		c=*str;
		while(UartSendChar(c)==-1); //block if buffer full
		str++;
	};
	return WIFI_OK;
}

u8 wifiGetIfAvailable(char* buffer, u8 expectedSize) {
	/*if (UartUnreadCount() < expectedSize) {
		return WIFI_NODATA;
	}
	while (expectedSize--) {
		*buffer = UartReadChar();
		buffer++;
	}
	return WIFI_OK;*/
	char c = -1;
	if (UartUnreadCount() > 0) {
		while (expectedSize--) {
			while(c == -1) {
				c = UartReadChar();
			}
			*buffer = c;
			buffer++;
			c = -1;
		}
	} else {
		return WIFI_NODATA;
	}
	return WIFI_OK;
}

u8 wifiGetPB(const char* str, char* rxbuf){
	u8 c;
	s16 r;
	const char* p=str;
	char* buf=rxbuf;
	ClearVsyncCounter();

	while(1){

		r=UartReadChar();
		if(r!=-1){

			c=r&(0xff);

			if(buf!=NULL){
				*buf=c;
				buf++;
			}

			if(c==pgm_read_byte(p)){
				p++;
				if(pgm_read_byte(p)==0){
					return WIFI_OK;
				}
			}else{
				//reset string compare
				p=str;
			}
		}

		if(GetVsyncCounter()>TIMEOUT){
			return WIFI_TIMEOUT;
		}
	}

}

u8 wifiGetPBT(const char* str, char* rxbuf, u16 wifi_timeout){
    u8 c;
    s16 r;
    const char* p=str;
    char* buf=rxbuf;
    ClearVsyncCounter();

    while(1){

        r=UartReadChar();
        if(r!=-1){

            c=r&(0xff);

            if(buf!=NULL){
                *buf=c;
                buf++;
            }

            if(c==pgm_read_byte(p)){
                p++;
                if(pgm_read_byte(p)==0){
                    return WIFI_OK;
                }
            }else{
                //reset string compare
                p=str;
            }
        }

        if(GetVsyncCounter()>wifi_timeout){
            return WIFI_TIMEOUT;
        }
    }

}

u8 wifiGetP(const char* strToWait){

	if(wifiGetPB(strToWait, NULL)==WIFI_TIMEOUT){
		return WIFI_TIMEOUT;
	}

	return WIFI_OK;
}


u8 wifiRequestP(const char* strToSend, const char* strToWait){
	wifiSendP(strToSend);
	if(wifiGetPB(strToWait, NULL)==WIFI_TIMEOUT){
		return WIFI_TIMEOUT;
	}

	return WIFI_OK;
}

u8 wifiRequest(char* strToSend, const char* strToWait){
	wifiSend(strToSend);
	if(wifiGetPB(strToWait, NULL)==WIFI_TIMEOUT){
		return WIFI_TIMEOUT;
	}

	return WIFI_OK;
}

u8 wifiRequestPT(const char* strToSend, const char* strToWait, u16 wifi_timeout){
    wifiSendP(strToSend);
    if(wifiGetPBT(strToWait, NULL, wifi_timeout)==WIFI_TIMEOUT){
        return WIFI_TIMEOUT;
    }

    return WIFI_OK;
}

const u16 bauds[] PROGMEM = {370,246,184,92,60,44,30};
u8 initWifi(){
    s8 i = 0;
    u8 result;
    UCSR0A=(1<<U2X0); // double speed mode
    UCSR0C=(1<<UCSZ01)+(1<<UCSZ00)+(0<<USBS0); //8-bit frame, no parity, 1 stop bit
    UCSR0B=(1<<RXEN0)+(1<<TXEN0); //Enable UART TX & RX
    do {
        UBRR0L=pgm_read_byte(((u8*) &(bauds[i % 7])));
        UBRR0H=pgm_read_byte(((u8*) &(bauds[i % 7]))+1);
        WaitVsync(1);
        result = wifiRequestPT(PSTR("AT\r\n"),PSTR("OK\r\n"), 30); 
        i++;
    } while ((result != WIFI_OK) && (i < 14));
    if (result == WIFI_OK) {
        result = wifiRequestPT(PSTR("AT+UART_CUR=14400,8,1,0,0\r\n"),PSTR("OK\r\n"), 2*60); 
        if (result == WIFI_OK) {
            UBRR0L=pgm_read_byte(((u8*) &(bauds[1])));
            UBRR0H=pgm_read_byte(((u8*) &(bauds[1]))+1); 
            WaitVsync(1);
        }
    }
    return result;
}

#endif




