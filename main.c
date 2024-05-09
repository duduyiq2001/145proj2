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
#include "utility.h"
#include "lcd.h"
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TESTKEY 0
#define TESTLCD 0
#define MONTH_LENGTH 2
#define DAY_LENGTH 2
#define YEAR_LENGTH 2
#define TIME_LENGTH 2
#define AM_LENGTH 1
#define WAIT_BTWN_INPUTS_MS 50
#define CHANGE_TIME_SYSTEM 'A'
#define CHANGE_TO_SET_DATE_TIME '#'

enum mode {
	NONE, SET_DATE_TIME, SWITCH_TIME
};

enum curr_time_system {
	HR_24, HR_12
};

enum curr_time_system CURR_TIME_SYSTEM = HR_24;
//default curr time system is set to 24 hr time

enum mode CURR_MODE = NONE;



void reset_mode() {
	CURR_MODE = NONE;
}

bool char_causes_mode_change(char in){
	return in == CHANGE_TIME_SYSTEM || in ==  CHANGE_TO_SET_DATE_TIME ;
}
bool char_causes_time_type_change (char in) {
	return in == CHANGE_TIME_SYSTEM;
}

//char causes intial is misnomered, jsut checks if char causes a curr mode change
bool char_causes_initial_change(char in) {
	return in == CHANGE_TO_SET_DATE_TIME;
}
void change_time_type() {
	if (CURR_TIME_SYSTEM == HR_24) {
		CURR_TIME_SYSTEM = HR_12;
		} else {
		CURR_TIME_SYSTEM = HR_24;
	}
}

void change_mode(char in){
	switch(in) {
		case CHANGE_TO_SET_DATE_TIME :
		CURR_MODE = CHANGE_TO_SET_DATE_TIME ;
		break;

		case CHANGE_TIME_SYSTEM :
		change_time_type();
		break;
	}
}



void wait_for_init_mode_change(){
	char input_char = '\0';
	while (!char_causes_initial_change(input_char)){

		if (char_causes_time_type_change(input_char)){
			change_time_type();
		}
		input_char = get_char();
		wait_avr(WAIT_BTWN_INPUTS_MS );
	}

	// change_mode(input_char);
}

// void wait_for_mode_change_notinit() {
// 	char in_char = '\0';
// 	while(!char_causes_mode_change(in_char)){
// 		in_char = get_char();
// 		wait_avr(WAIT_BTWN_INPUTS_MS );
// 	}
// }
const char month_max_30[] = {4, 6, 9, 11}; //length 4

#define MONTHS_MAX_30 4

const char month_max_31[] = {1, 3, 5, 7, 8, 10, 12};

#define MONTHS_MAX_31 7


// char mode = 0;

typedef unsigned char mini_uint;

unsigned short get_number (unsigned char length, unsigned char r, unsigned char c) {
	unsigned short ret_num = 0;
	mini_uint length_of_num = 0;
	while (length_of_num < length) {
		char in_char = get_char();
		wait_avr(WAIT_BTWN_INPUTS_MS);
		if (in_char >= '0' && in_char <= '9') {
			length_of_num += 1;
			ret_num *= 10;
			ret_num += in_char - '0';
			lcd_pos(r,c);
			lcd_put(in_char);
			c += 1;
			} else {
			continue;
		}
	}

	return ret_num;
}

bool validate_hr_24(mini_uint hr) {
	return hr >= 0 && hr <= 24;
}
bool validate_hr_12(mini_uint hr) {
	return hr >= 0 && hr <= 12;
}
bool validate_min(mini_uint min) {
	return min >= 0 && min <= 60;
}
bool validate_sec(mini_uint sec) {
	return validate_min(sec);
}

bool validate_month_day_yr (unsigned short yr, mini_uint month, mini_uint day){

	if (month > 12 || month == 0) {
		return false;
	}

	if (char_in_array(month, month_max_30, MONTHS_MAX_31 )){
		return day <= 30;
	}

	if (char_in_array(month, month_max_30, MONTHS_MAX_31 )){
		return day <= 31;
	}

	if (month == 2){
		mini_uint day_max_feb = (is_leap_yr(yr)) ? 29 : 28;
		return day <= day_max_feb;
	}

	return false;
	
}

bool validate_am(mini_uint am) {
	return am == 0 || am == 1;
}

DateTime build_dt_24() {
	DateTime tmp;
	mini_uint month;
	mini_uint day;
	short yr;
	do {
		lcd_clr();
		lcd_pos(0,0);
		lcd_puts2("yr/mm/d:");
		wait_avr(2000);
		month = (mini_uint) get_number(MONTH_LENGTH,0,0);
		day = (mini_uint) get_number(DAY_LENGTH,0,MONTH_LENGTH);
		yr = get_number(YEAR_LENGTH,0,MONTH_LENGTH + YEAR_LENGTH );
	} while (!validate_month_day_yr(yr, month, day));

	
	
	mini_uint mins;
	mini_uint hrs;
	mini_uint secs;
	do {
		lcd_clr();
		lcd_pos(0,0);
		lcd_puts2("hr/min/s:");
		wait_avr(2000);
		mins = (mini_uint) get_number(TIME_LENGTH,1,0);
		hrs = (mini_uint) get_number(TIME_LENGTH,1,TIME_LENGTH);
		secs = (mini_uint) get_number(TIME_LENGTH,1,TIME_LENGTH*2);
	} while (!validate_min(mins) || !validate_hr_24(hrs) || !validate_sec(secs));
	
	init_dt_full(&tmp, yr, month, day, hrs, mins, secs);
	return tmp;
	
}

DateTime_Twelve_hr build_dt_12() {
	DateTime_Twelve_hr tmp_12;
	mini_uint month;
	mini_uint day;
	short yr;
	do {
		lcd_clr();
		lcd_pos(0,0);
		lcd_puts2("yr/mm/d:");
		wait_avr(2000);
		month = (mini_uint) get_number(MONTH_LENGTH,0,0);
		day = (mini_uint) get_number(DAY_LENGTH,0,MONTH_LENGTH);
		yr = get_number(YEAR_LENGTH,0,MONTH_LENGTH + YEAR_LENGTH );
	} while (!validate_month_day_yr(yr, month, day));

	
	
	mini_uint mins;
	mini_uint hrs;
	mini_uint secs;
	mini_uint am;
	do {
		lcd_clr();
		lcd_pos(0,0);
		lcd_puts2("hr/min/s:");
		wait_avr(2000);
		mins = (mini_uint) get_number(TIME_LENGTH,1,0);
		hrs = (mini_uint) get_number(TIME_LENGTH,1,TIME_LENGTH);
		secs = (mini_uint) get_number(TIME_LENGTH,1,TIME_LENGTH*2);
		am = (mini_uint) get_number(AM_LENGTH,1, TIME_LENGTH*3);
	} while (!validate_min(mins) || !validate_hr_24(hrs) || !validate_sec(secs));
	

	init_dt_twelve_full(&tmp_12, yr, month, day, hrs, mins, secs, (bool) am);
	return tmp_12;
	
}
void alter_output_24(DateTime* dt){
	advance_dt(dt);
	print_dt(dt);
}

void alter_output_12(DateTime_Twelve_hr* dt_12){
	advance_dt_twelve(dt_12);
	print_dt_twelve(dt_12);
}


DateTime* hr_24_sm(DateTime* dt) {
	// returns last known state of the DateTime structure, this will be useful for interchanging between the two
	char in_char = '\0';
	while (CURR_TIME_SYSTEM == HR_24){
		alter_output_24(dt);

		in_char = get_char();
		if (char_causes_initial_change(in_char)) {
			*dt= build_dt_24();
			} else if (char_causes_time_type_change(in_char)){
			CURR_TIME_SYSTEM = HR_12;
			break;
		}
		wait_avr(1000);
	}
	return dt;
}

DateTime_Twelve_hr* hr_12_sm (DateTime_Twelve_hr* dt_12){
	
	// returns last known state of the DateTime structure, this will be useful for interchanging between the two
	char in_char = '\0';
	while (CURR_TIME_SYSTEM == HR_12){
		alter_output_12(dt_12);
		

		in_char = get_char();
		if (char_causes_initial_change(in_char)) {
			//char causes intial is misnomered, jsut checks if char causes a curr mode change
			*dt_12 = build_dt_12();
			} else if (char_causes_time_type_change(in_char)){
			CURR_TIME_SYSTEM = HR_24;
			break;
		}

		wait_avr(1000);
		
	}
	return dt_12;
}

void main_driver() {
	//initial state
	//wait for driver initialization
	wait_for_init_mode_change();

	//initialize these two, this code should be refactored using non-malloced shit
	// DateTime* dt_24 = malloc(sizeof(DateTime_Twelve_hr));
	// DateTime_Twelve_hr* dt_12 = (DateTime_Twelve_hr*) malloc(sizeof(DateTime_Twelve_hr));


	DateTime dt_24;
	DateTime_Twelve_hr dt_12;
	//intialize the counters whichever one is relevant
	if (CURR_TIME_SYSTEM == HR_12) {
		dt_12 = build_dt_12();
		} else {

		dt_24 = build_dt_24();
	}
	

	
	//enter the correct sm depending on whcih system one is currently operating in
	while ( 1 ) {
		if (CURR_TIME_SYSTEM == HR_12) {
			dt_24 = conv_twelve_to_military(hr_12_sm(&dt_12));

			} else if (CURR_TIME_SYSTEM == HR_24) {
			dt_12 = conv_military_to_twelve( hr_24_sm(&dt_24));
		}
	}

	// free(dt_12);
	// free(dt_24);
}

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
	lcd_clr();
	wait_avr(50);
	DateTime clock;
	init_dt(&clock);
	print_dt(&clock);
	while(1){
		wait_avr(1000);
		advance_dt(&clock);
		print_dt(&clock);
	}
}

void test_lcd(){
	lcd_init();
	lcd_clr();
	const char t[] = "1234";
	while(1){
		
		wait_avr(50);
		lcd_clr();
		lcd_pos(0, 0);
		lcd_puts2(t);
	}
}
int main(void)
{
	
	

    // if(TESTKEY){
 	//    test_keypad();
    // }
    // if(TESTLCD){
 	//    test_lcd();
    // }
    main_driver();
   
}