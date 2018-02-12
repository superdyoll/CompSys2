/* COMP2215 15/16 Task 7---Keyboard */

#include "keyboard.h"

int length = 0;
int letter = 0;
bool keyboard = true;
bool showing = true;
int mode = INIT_MODE;
char output[MAX_OUTPUT+1];
char *gl_buffer;

char *read_keyboard(char *buffer){
	showing = true;
	gl_buffer = buffer;
	while (showing){}
	return gl_buffer;
}

int show_keyboard (int state) {
	if (showing){
		if (get_switch_press(_BV(SWN))){
			// Change whether keyboard is showing
			if (mode == 4 || mode == 0){
				keyboard = !keyboard;
			}
		
			mode = (mode + 1) % 5;	
			
			// Hide keyboard
			rectangle clear_keyboard = {0,display.width-1, 0, 14};
			fill_rectangle(clear_keyboard,display.background);
		}
			if (keyboard){
				// Display keyboard
				if (mode == 1) {
       					display_string_xy(" a b c d e f g h i j k l m n o p q r s t u v w x y z\n\n",0,0);
				} else if (mode == 2) {
					display_string_xy(" A B C D E F G H I J K L M N O P Q R S T U V W X Y Z\n\n",0,0);
				} else if (mode == 3) {
					display_string_xy(" ! \" # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 :\n\n",0,0);
				} else if (mode == 4) {
					display_string_xy(" ; < = > ? @ [ \\ ] ^ _ ` { | } ~\n\n",0,0);
				}	
			} else {
				display_string_xy(" Press UP to show the keyboard, or CENTER to submit",0,0);
			}
		//}

		if (keyboard){
			// Move cursor
        		rectangle left = {0, (letter*12+6), 8,14};
			rectangle right = {(letter*12+11),display.width-1, 8, 14};
			fill_rectangle(left,display.background);
			fill_rectangle(right,display.background);
        		rectangle r = {(letter*12+6), (letter*12 + 11), 8, 14};
			fill_rectangle(r, RED);
		
			// SCROLL WHEEL
			letter += os_enc_delta();

			if (mode == 4){
				if (letter > 15){
					letter = 15;
				}
			}

			if(letter > 25){
				letter = 25;
			}

			if (letter < 0){
				letter = 0;
			}
		}
        		
		//SPACE When you press right
		if (get_switch_press(_BV(SWE))){
			if (keyboard){	
				if (length <= MAX_OUTPUT){
        	                	output[length] = ' ';
					//output = append(output, c);
					//display_char(c);
					length++;
        	                	output[length] = '\0';
					display_string_xy(output,0,16);
				} else {
					display_string("Overflow");
				}
			}
		}
	
		// Backspace on left
	       	if (get_switch_press(_BV(SWW))){
			if (keyboard){
				if (length > 0){
					length --;
					output[length] = ' ';
					display_string_xy(output,0,16);
					output[length] = '\0';
				}
			}
		}
	
		// New line on down
		if (get_switch_press(_BV(SWS))){
			if (keyboard){	
				// NEW LINE CHARACTER
				/*display_string("\n");
				length = 0;
				line ++;*/
				if (length <= MAX_OUTPUT){
					char c = '\n';
					output[length] = c;
					length++;
					output[length] = '\0';
					display_string_xy(output,0,16);
				} else {
					display_string("Overflow");
				}
			}
		}
		
		// Center Switch	
		if (get_switch_press(_BV(SWC))) {
			if (keyboard){
				if (length <= MAX_OUTPUT){
					char c;
					if (mode == 2){
						c = 65 + letter;
					} else if (mode == 3) {
						c = 33 + letter;
					} else if (mode == 4) {
						if (letter < 6) {
							c = 59 + letter;
						} else if (letter < 12) {
							c = 91 + (letter - 6);
						} else {
							c = 123 + (letter - 12);
						}
					} else {
						c = 97 + letter;
					}
					output[length]=c;
					// output = append(output, c);
					// display_char(c);
					length++;
					output[length]='\0';
					display_string_xy(output,0,16);
				} else {
					display_string("Overflow");
				}
			} else {
				showing = false;
				
				// Hide keyboard
				rectangle clear_keyboard = {0,display.width-1, 0, display.height -1};
				fill_rectangle(clear_keyboard,display.background);
				
				// Output
				gl_buffer = output;

				display_string_xy(output,0,0);
			}
		}
	}
	
	if (get_switch_press(_BV(SWC))) {
		showing = true;
	}
	
	return state;
}
