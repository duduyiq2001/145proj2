 
#include "keypad.h"
#include "utility.h"
#include <avr/io.h>


 
int get_key() {
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (is_pressed(i, j)) {
				return i * 4 + j + 1;
			}
		}
	}

	return 0;
}

int is_pressed(int r, int c) {

	DDRA = 0x00; // Set Data Direction Register A to output
	PORTA = 0x00; // Set all bits in Port A to low
     r = 3-r;
	 c = 3-c;
	// Set the row (r) to "0"
	set_port(&DDRA, c);
	clear_port(&PORTA,c);
	// Set the column (c) to "high"
	clear_port(&DDRA, r+4);
	set_port(&PORTA,r+4);
	wait_avr(10);
	//DDRA = 0;
	if (/*GPIO @ c = 0*/  !get_pin(&PINA,r+4)) {    // Check if the corresponding pin is high
		wait_avr(10);
		return 1;
	}

	return 0;
}

 char get_char(){
	 
	 
	 
 }