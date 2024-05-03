/*
 * CFile1.c
 *
 * Created: 5/2/2024 11:34:56 PM
 *  Author: Administrator
 */ 
#include "utility.h"


void set_port(char* portname, char portnum){
	*portname = *portname | 0x01 << portnum;
	
}

void clear_port(char* portname, char portnum){
	*portname = *portname & (!(0x01 << portnum));
	
}

char get_pin(char* portname, char portnum){
	
	return *portname & 0x01 << portnum;
}