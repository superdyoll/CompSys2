/* COMP2215 15/16: Task 02---SKELETON */

#include <avr/io.h>
#include <stdio.h>
#include "lcd.h"

void init(void);

void print_f(char *fmt, ...);

void main(void) {
    init();
    print_f("Hello my name la\n");
    print_f("DIGIT %u \n",20);
    display_string("Hello Southampton!\n");
    display_string("Hello UK!\n");
    display_color(GOLD, BLACK);
    display_string("Hello World!\n");
}

static char* bf;
static char buf[12];
static unsigned int num;
static char uc;
static char zs;

static void out(char c) {
    *bf++ = c;
    }

static void outDgt(char dgt) {
	out(dgt+(dgt<10 ? '0' : (uc ? 'A' : 'a')-10));
	zs=1;
    }
	
static void divOut(unsigned int div) {
    unsigned char dgt=0;
	num &= 0xffff; // just for testing the code  with 32 bit ints
	while (num>=div) {
		num -= div;
		dgt++;
		}
	if (zs || dgt>0) 
		outDgt(dgt);
    }	

void print_f(char *fmt, ...) {
    va_list va;
    char ch;
    char* p;

    va_start(va,fmt);

    while ((ch=*(fmt++))) {
	if (ch!='%') {
            display_char(ch);
	}
	else{
	    char lz=0;
	    char w=0;
	    ch=*(fmt++);
	    if (ch=='0') {
	        ch=*(fmt++);
		lz=1;
	    }
	    if (ch>='0' && ch<='9') {
		w=0;
		while (ch>='0' && ch<='9') {
		    w=(((w<<2)+w)<<1)+ch-'0';
		    ch=*fmt++;
		}
	    }
	    bf=buf;
	    p=bf;
	    zs=0;
	    switch (ch){
		//case 0:
		    //goto abort;
		case 'u':
		case 'd':
		    num=va_arg(va, unsigned int);
		    if (ch=='d' && (int)num<0){
			num = -(int)num;
			out('-');
		    }
		    divOut(10000);
		    divOut(1000);
		    divOut(100);
		    divOut(10);
		    outDgt(num);
		    break;
		case '%' :
		    out('%');
		default:
		    break;
	    }
	    *bf=0;
            bf=p;
            while (*bf++ && w > 0)
		w--;
	    while (w-- > 0) 
		display_char(lz ? '0' : ' ');
	    while ((ch= *p++))
		display_char(ch);
	}
    }
    //abort:;
    va_end(va);
}

void init(void) {
    /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;

    init_lcd();
}
