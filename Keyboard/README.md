#Keyboard Library#
##How to use##
###User###
Press UP to go through the various modes
You can change letter using the scroll wheel.
The CENTER wheel will select.
Pressing RIGHT will add a space, LEFT will backspace, DOWN will create a new line.
###Programmer###
This keyboard has been designed to help making typing on the LaFortuna easier.

To use you must create a task on the os as such

	os_add_task(show_keyboard, 30, 1);

Then when you wish to use the keyboard simply call

	char *output = read_keyboard(output);

You must remember to allocate memory for output first.

##Known bugs##

Returning blocks of characters doesn't appear to work?! But i'm not sure why
