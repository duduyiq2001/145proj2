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
#include "timing.h"
#include <stdio.h>

#define TESTKEY 1
#define TESTLCD 0
 
void blink(){ 
	PORTB=0;

	wait_avr(500);

	PORTB = 1;

	wait_avr(500);
	PORTB=0;

	wait_avr(500);

}



void test_keypad(){
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



void test_clock(){
	lcd_init();
	avr_wait(50);
	DateTime clock;
	init_dt(&clock);
	print_dt(&clock);
	while(1){
		advance_dt(&clock);
		print_dt(&clock);
	}
}
int main(void)
{
   if(TESTKEY){
	   test_keypad();
   }
   if(TESTLCD){
	   test_clock();
   }
}