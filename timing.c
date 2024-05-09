#include "timing.h"
#include "lcd.h"
const char month_max_30_here[] = {4, 6, 9, 11}; //length 4

#define MONTHS_MAX_30_here 4

const char month_max_31_here[] = {1, 3, 5, 7, 8, 10, 12};

#define MONTHS_MAX_31_here 7

void advance_dt(DateTime *dt) {
	++dt->second;
	if (dt->second == 60) {
		++dt->minute;
		dt->second = 0;
		if(dt->minute == 60){
			++dt->hour;
			dt->minute = 0;
			if(dt->hour == 24){
				++dt->day;
				dt->hour = 0;

				char max_in_month = get_max_days_in_month(dt->month, (unsigned short)dt->year);


				if (max_in_month < dt->day) {
					dt -> day = 1;
					if (dt->month != 12) {
						(dt->month)++;
						} else {
						dt->month = 1;
						++dt->year;
					}
				}
				// if(dt->day == 366 || (dt->year % 4 == 0 && dt->day == 365)){
				// 	++dt->year;
				// 	dt->day = 1;
				// }
			}
		}
	}
}

void init_dt(DateTime *dt) {
	dt->year = 2024;
	dt->day = 6;
	dt->hour = 13;
	dt->minute = 46;
	dt->second = 0;
}

void init_dt_time(DateTime* dt, unsigned char hr, unsigned char min, unsigned char sec){
	dt->hour = hr;
	dt->minute = min;
	dt->second = sec;
}

void init_dt_date(DateTime* dt, int yr, unsigned char curr_month, unsigned char curr_day){
	dt->year = yr;
	dt->month = curr_month;
	dt->day = curr_day;
}


void init_dt_twelve_hr(DateTime_Twelve_hr *dt_twelve){
	init_dt(&(dt_twelve->dt));
	dt_twelve->am = true;
}

void advance_dt_twelve(DateTime_Twelve_hr *dt_twelve) {

	DateTime* dt = &(dt_twelve->dt);
	++dt->second;

	if (dt->second == 60) {
		++dt->minute;
		dt->second = 0;
		if(dt->minute == 60){
			++dt->hour;
			dt->minute = 0;
			if(dt->hour == 12){
				if(dt_twelve->am == true) {
					dt_twelve->am = false;
					
					} else {
					dt_twelve->am = true;
					++dt->day;

					char max_in_month = get_max_days_in_month(dt->month, (unsigned short)dt->year);


					if (max_in_month < dt->day) {
						dt -> day = 1;
						if (dt->month != 12) {
							(dt->month)++;
							} else {
							dt->month = 1;
							++dt->year;
						}
					}

					
				}


				
				// if(dt->day == 366 || (dt->year % 4 == 0 && dt->day == 365)){
				// 	++dt->year;
				// 	dt->day = 1;
				// }
			}
		}
	}
}

DateTime conv_twelve_to_military (DateTime_Twelve_hr *dt_twelve){
	if (dt_twelve->am == true) {
		return dt_twelve->dt;
	}
	DateTime tmp = dt_twelve->dt;
	tmp.hour += 12;
	return tmp;
	
}

DateTime_Twelve_hr conv_military_to_twelve (DateTime *dt){
	
	DateTime_Twelve_hr tmp;
	// init_dt_twelve(&tmp);
	if (dt->hour < 12) {
		tmp.dt = *dt;
		tmp.am = true;
		} else if (dt->hour == 12) {
		tmp.dt = *dt;
		tmp.am = false;
		} else {
		tmp.dt = *dt;
		tmp.dt.hour -= 12;
		tmp.am = false;
	}

	return tmp;
}

void print_dt_twelve(const DateTime_Twelve_hr *dt_twelve) {
	char buf[17];

	const DateTime* dt = &(dt_twelve->dt);
	// Print date on top row.
	lcd_pos(0, 0);
	sprintf(buf, "%04d-%02d-%02d",
	dt->year,
	dt->month,
	dt->day);
	lcd_puts2(buf);
	// Do similar thing to print time on bottom row.
	char* am_pm = (dt_twelve->am) ? "am" : "pm";

	lcd_pos(1,0);
	sprintf(buf, "%02d:%02d:%02d %s",
	dt->hour,
	dt->minute,
	dt->second,
	am_pm);
	lcd_puts2(buf);
}

void init_dt_twelve_time(DateTime_Twelve_hr* dt_twelve, unsigned char hr, unsigned char min, unsigned char sec, bool am) {
	DateTime* dt = &(dt_twelve->dt);
	init_dt_time(dt, hr, min, sec);
	dt_twelve->am = am;
}

void init_dt_twelve_date(DateTime_Twelve_hr* dt_twelve, int yr, unsigned char curr_month, unsigned char curr_day) {
	DateTime* dt = &(dt_twelve->dt);
	init_dt_date(dt, yr, curr_month, curr_day);
}

void init_dt_full(DateTime* dt, int yr, unsigned char curr_month, unsigned char curr_day, unsigned char hr, unsigned char min, unsigned char sec){

	init_dt_date(dt, yr, curr_month, curr_day);
	init_dt_time(dt, hr, min, sec);
}

void init_dt_twelve_full(DateTime_Twelve_hr* dt, int yr, unsigned char curr_month, unsigned char curr_day, unsigned char hr, unsigned char min, unsigned char sec, bool am){
	init_dt_twelve_date(dt, yr, curr_month, curr_day);
	init_dt_twelve_time(dt, hr, min, sec, am);
}

bool is_leap_yr(unsigned short yr) {
	if (yr % 400 == 0) {
		return true;
		} else if (yr % 100 == 0) {
		return false;
		} else if (yr%4 == 0){
		return true;
	}

	return false;
	
}


bool char_in_array( char needle, const char haystack[], int haystack_len){
	for (int i = 0 ; i < haystack_len; i++){
		if (needle == haystack[i]) {
			return true;
		}
	}
	return false;
}
char get_max_days_in_month (char month, unsigned short yr) {
	if (char_in_array(month, month_max_30_here, MONTHS_MAX_30_here)) {
		return 30;
	}

	if (char_in_array(month, month_max_31_here, MONTHS_MAX_31_here)) {
		return 31;
	}

	if (month == 2) {
		if (is_leap_yr(yr)) {
			return 29;
			} else {
			return 28;
		}
	}

	return 0;
}
void print_dt(const DateTime *dt) {
	char buf[17];
	// Print date on top row.
	lcd_pos(0, 0);
	sprintf(buf, "%04d-%02d-%02d",
	dt->year,
	dt->month,
	dt->day);
	lcd_puts2(buf);
	// Do similar thing to print time on bottom row.
	
	lcd_pos(1,0);
	sprintf(buf, "%02d:%02d:%02d",
	dt->hour,
	dt->minute,
	dt->second);
	lcd_puts2(buf);
}
