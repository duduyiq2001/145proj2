/*
 * main.c
 *
 * Created: 5/6/2024 8:04:25 PM
 *  Author: Administrator
 */ 
/*
 * GccApplication2.c
 *
 * Created: 4/23/2024 10:58:22 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include "keypad.h"
#include <stdio.h>
 
 
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
    DDRB = 0x02; 
	PORTB = 0;
    while (1) 
    {
        //int a = get_key();
		while(is_pressed(3,3)){
			PORTB = 0X02;
		}
	   PORTB = 0; 		
	}
}