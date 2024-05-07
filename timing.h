#ifndef TIMING
#define TIMING


typedef struct {
	int year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
} DateTime;


void init_dt(DateTime *dt);
void print_dt(const DateTime *dt);
void advance_dt(DateTime *dt);
#endif