#include <stdio.h>
#include <avr/io.h> 
#include <stdlib.h>
#include "os.h"
#include "keyboard.h"

void test_keyboard();

void main(void){
	os_init();

	os_add_task( show_keyboard, 30, 1);

	sei();
	for(;;){}
}

void test_keyboard(void){
	char *output;
	
	output = (char *) malloc(MAX_OUTPUT);
	
	read_keyboard(output);

	display_string(output);

	display_string("\n\n\n\nCow");	

	free(output);	
}
