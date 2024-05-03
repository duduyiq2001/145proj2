 
#include "keypad.h"
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

	DDRA = 1; // Set Data Direction Register A to output
	PORTA = 0; // Set all bits in Port A to low

	// Set the row (r) to "0"
	clear_port(&PORTA, r+4);
	// Set the column (c) to "high"
	set_port(&PORTA,c);
	
	DDRA = 0;
	if (/*GPIO @ c = 0*/  get_pin(PINA,c)) {    // Check if the corresponding pin is high
		return 1;
	}

	return 0;
}