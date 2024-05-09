#ifndef TIMING
#define TIMING
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	int year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
} DateTime;

typedef struct {
	DateTime dt;
	bool am;
} DateTime_Twelve_hr;

void init_dt(DateTime *dt);
void init_dt_time(DateTime* dt, unsigned char hr, unsigned char min, unsigned char sec);
void init_dt_date(DateTime* dt, int yr, unsigned char curr_month, unsigned char curr_day);
void print_dt(const DateTime *dt);
void advance_dt(DateTime *dt);
void print_dt_12(const DateTime_Twelve_hr *dt);
void init_dt_twelve_hr(DateTime_Twelve_hr *dt_twelve);
void advance_dt_twelve(DateTime_Twelve_hr *dt_twelve) ;
void print_dt_twelve(const DateTime_Twelve_hr *dt_twelve) ;
void init_dt_twelve_time(DateTime_Twelve_hr* dt, unsigned char hr, unsigned char min, unsigned char sec, bool am);
void init_dt_twelve_date(DateTime_Twelve_hr* dt, int yr, unsigned char curr_month, unsigned char curr_day);

void init_dt_full(DateTime* dt, int yr, unsigned char curr_month, unsigned char curr_day, unsigned char hr, unsigned char min, unsigned char sec);
void init_dt_twelve_full(DateTime_Twelve_hr* dt, int yr, unsigned char curr_month, unsigned char curr_day, unsigned char hr, unsigned char min, unsigned char sec, bool am);


DateTime conv_twelve_to_military (DateTime_Twelve_hr *dt_twelve);
DateTime_Twelve_hr conv_military_to_twelve (DateTime *dt);

bool is_leap_yr(unsigned short yr) ;

bool char_in_array( char needle, const char haystack[], int haystack_len);
char get_max_days_in_month (char month, unsigned short yr) ;


#endif