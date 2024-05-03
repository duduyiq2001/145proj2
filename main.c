/*
 * GccApplication2.c
 *
 * Created: 4/23/2024 10:58:22 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include "keypad.h"
#include <stdio.h>
 
 #define XTAL_FRQ 8000000lu
 #define SET_BIT(p,i) ((p) |=  (1 << (i)))
 #define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
 #define GET_BIT(p,i) ((p) &   (1 << (i)))


 
void wait_avr(unsigned short msec){
	TCCR0 = 3;
	while(msec --){
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ/64)*0.001);
		SET_BIT(TIFR, TOV0);
		while(!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}
 
void blink(){ 
	PORTB=0;

	wait_avr(500);

	PORTB = 1;

	wait_avr(500);
	PORTB=0;

	wait_avr(500);

}

int main(void)
{
    /* Replace with your application code */
    DDRB = 1; 
	PORTB = 0;
    while (1) 
    {
        int a = get_key();
		//set_port(&PORTB, 0);
	//	PORTB = PORTB | (0x01 << 1);
	
		PORTB = 0x02;
		//PORTB = 3;
		//blink();
		//for (uint8_t i = 0; i < a; i++){
			
			//blink();
		//}
		
	}
}