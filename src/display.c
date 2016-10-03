#include "display.h"

#define FIO1DIR 				(*(unsigned int*) 0x2009C020)
#define FIO1PIN 				(*(unsigned int*) 0x2009C034)
#define FIO1SET 				(*(unsigned int*) 0x2009C038)
#define FIO1CLR 				(*(unsigned int*) 0x2009C03C)

#define V_RST					20
#define V_CLK					19
#define H_DATA					18
#define H_CLK					23
#define H_STO					22
#define H_RST					21

unsigned int counter = 0;
unsigned int x = 0;
unsigned char toggle = 0;	//used to create lines of leds on and off

void writeDisplay(unsigned char pin, unsigned char value);

void displayInit(void) {
	// set all pins as output

	// V_rst: 20
	FIO1DIR |= (1 << V_RST);

	// V_clk: 19
	FIO1DIR |= (1 << V_CLK);

	// h_dta: 18
	FIO1DIR |= (1 << H_DATA);

	// h_clk: 23
	FIO1DIR |= (1 << H_CLK);

	// h_sto: 22
	FIO1DIR |= (1 << H_STO);

	// h_rst: 21
	FIO1DIR |= (1 << H_RST);
}

/**
 * The lpc1769 uses fioset to set pin value high and fioclear to
 * set pin value low.
 */
void writeDisplay(unsigned char pin, unsigned char value) {
	(value == 1) ? (FIO1SET |= (1 << pin)) : (FIO1CLR |= (1 << pin));
}

/**
 * Simple test method used to test if the hardware configuration works.
 * TODO: Arther must implement methods to get the display fully functioning
 */
void testLedDisplay(void) {
	writeDisplay(H_RST, 1);					//make sure Horizontal reset is inactive (low active)

	if (counter < 8) {						//as long as not every row is written
		toggle = 0;							//force toggle to zero
		while (x < 25) {					//fore every led (25 total)
			if(toggle){
				toggle = 0;					//toggle toggle
				writeDisplay(H_DATA, 0);	//set led on (low active)
			}
			else{
				toggle = 1;					//toggle toggle
				writeDisplay(H_DATA, 1);	//set led off (low active)
			}
			writeDisplay(H_CLK, 1);			//pulse horizontal clock (shift registers)
			writeDisplay(H_CLK, 0);

			x++;							//increment led counter
		}

		writeDisplay(H_STO, 0);				//pulse horizontal storage
		writeDisplay(H_STO, 1);
		writeDisplay(H_RST, 0);				//pulse horizontal reset
		writeDisplay(H_RST, 1);

		x = 0;								//reset led counter
		counter++;							//increment row counter
		writeDisplay(V_CLK, 1);				//pulse vertical clock
		writeDisplay(V_CLK, 0);
	} else {								//else (every row is written)
		writeDisplay(V_RST, 1);				//pulse vertical reset
		writeDisplay(V_RST, 0);
		counter = 0;						//reset row counter
	}
}
