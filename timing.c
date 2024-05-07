#include "timing.h"
#include "lcd.h"

void advance_dt(DateTime *dt) {
	++dt->second;
	if (dt->second == 60) {
		++dt->minute;
		if(dt->minute == 60){
			++dt->hour;
			dt->minute = 0;
			if(dt->hour == 24){
				++dt->day;
				dt->hour = 0;
				if(dt->day == 366 || (dt->year % 4 == 0 && dt->day == 365)){
					++dt->year;
					dt->day = 1;
				}
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
void print_dt(const DateTime *dt) {
	char buf[17];
	// Print date on top row.
	lcd_pos(0, 0);
	sprintf(buf, "%04d-%02d-%02d",
	dt->year,
	dt->month,
	dt->day);
	lcd_puts(buf);
	// Do similar thing to print time on bottom row.
	
	lcd_pos(1,0);
	sprintf(buf, "%04d-%02d-%02d",
	dt->hour,
	dt->minute,
	dt->second);
	lcd_puts(buf);
}
