/* COMP2215 15/16 Task 5---SKELETON */

#include "os.h"

#define STRING_LEN 52

int blink(int);
int update_dial(int);
int collect_delta(int);
int show_keyboard(int);
//int check_switches(int);
//void display_tail(int);

typedef enum { false, true } bool;

FIL File;  						/* FAT File */

int position = 0;
int letter = 0;
bool keyboard = false;
 

void main(void) {
    os_init();

    os_add_task( blink,            30, 1);
    os_add_task( collect_delta,   500, 1);
    os_add_task( show_keyboard,    30, 1);
  //  os_add_task( check_switches,  100, 1);
  //  os_add_task( display_tail,    100, 1);
     
    sei();
    for(;;){}
    
}


/*void display_tail(int state) {
 	if (get_switch_long(_BV(SWN))) {
		display_string("Outputting last 25 lines \n");
        	char str[STRING_LEN];
		UINT br;

		if (f_open(&File, "myfile.txt", FA_READ | FA_OPEN_ALWAYS) == FR_OK) {
			int start_position = f_size(&File) - 25;
			if (start_position < 0){
				start_position = 0;
			}
			while(start_position <= f_size(&File)){
				f_lseek(&File, start_position);
				f_read(&File, str, STRING_LEN-1, &br);
				display_string(str);
				start_position ++;
			}

			f_close(&File);
		} else {
			display_string("Can't write file! \n");	
		}
	}
}
*/
int collect_delta(int state) {
	position += os_enc_delta();
	return state;
}

int show_keyboard (int state) {
	if (get_switch_press(_BV(SWN))){
		keyboard = !keyboard;
		rectangle clear_keyboard = {0,display.width-1, 0, 14};
		fill_rectangle(clear_keyboard,display.background);
		if (keyboard){
        		display_string_xy(" a b c d e f g h i j k l m n o p q r s t u v w x y z\n\n",0,0);
		}	
		
	}
	if (keyboard){
        	rectangle left = {0, (letter*12+6), 8,14};
		rectangle right = {(letter*12+11),display.width-1, 8, 14};
		fill_rectangle(left,display.background);
		fill_rectangle(right,display.background);
        	rectangle r = {(letter*12+6), (letter*12 + 11), 8, 14};
		fill_rectangle(r, RED);
        	if (get_switch_press(_BV(SWE))){
			if (letter < 25){
				letter++;
			}
		}

        	if (get_switch_press(_BV(SWW))){
			if (letter > 0) {
				letter --;
			}
		}
		

		if (get_switch_long(_BV(SWC))) {
			char c = 97 + letter;
			display_char(c);
		}
	}
}

/*int check_switches(int state) {
	
	if (get_switch_press(_BV(SWN))) {
			display_string("North\n");
	}
		
	if (get_switch_press(_BV(SWE))) {
			display_string("East\n");
			rectangle rect = {12,16,12,16};
			fill_rectangle(rect,RED); 
	}
		
	if (get_switch_press(_BV(SWS))) {
			display_string("South\n");
	}
		
	if (get_switch_press(_BV(SWW))) {
			display_string("West\n");
	}
		
	if (get_switch_long(_BV(SWC))) {
		f_mount(&FatFs, "", 0);
		if (f_open(&File, "myfile.txt", FA_WRITE | FA_OPEN_ALWAYS) == FR_OK) {
			f_lseek(&File, f_size(&File));
			f_printf(&File, "Encoder position is: %d \r\n", position);
			f_close(&File);
			display_string("Wrote position\n");
		} else {
			display_string("Can't write file! \n");	
		}
		
	}

	if (get_switch_short(_BV(SWC))) {
			display_string("[S] Centre\n");
	}

	if (get_switch_rpt(_BV(SWN))) {
			display_string("[R] North\n");
	}
		
	if (get_switch_rpt(_BV(SWE))) {
			display_string("[R] East\n");
	}
		
	if (get_switch_rpt(_BV(SWS))) {
			display_string("[R] South\n");
	}
		
	if (get_switch_rpt(_BV(SWW))) {
			display_string("[R] West\n");
	}

	if (get_switch_rpt(SWN)) {
			display_string("[R] North\n");
	}


	if (get_switch_long(_BV(OS_CD))) {
		display_string("Detected SD card.\n");
	}

	return state;	
}

*/


int blink(int state) {
	static int light = 0;
	uint8_t level;
	
	if (light < -120) {
		state = 1;
	} else if (light > 254) {
		state = -20;
	}


	/* Compensate somewhat for nonlinear LED 
       output and eye sensitivity:
    */
	if (state > 0) {
		if (light > 40) {
			state = 2;
		}
		if (light > 100) {
			state = 5;
		}
	} else {
		if (light < 180) {
			state = -10;
		}
		if (light < 30) {
			state = -5;
		}
	}
	light += state;

	if (light < 0) {
		level = 0;
	} else if (light > 255) {
		level = 255;
	} else {
		level = light;
	}
	
	os_led_brightness(level);
	return state;
}

