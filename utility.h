/*
 * utility.h
 *
 * 
 */
#ifndef UTILITY
#define UTILITY
#define XTAL_FRQ 8000000lu
#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))


void set_port(char* portname, char portnum);

void clear_port(char* portname, char portnum);

char get_pin(char* portname, char portnum);

 
 void wait_avr(unsigned short msec);
#endif
 

