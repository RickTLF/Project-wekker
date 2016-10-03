#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

// TODO: insert other include files here
#include "display.h"
#include "irSensor.h"
#include "realTimeClock.h"
#include "speaker.h"
#include "timer.h"

// TODO: insert other definitions and declarations here

int main(void) {
	displayInit();

    while(1) {
    	testLedDisplay();

    }
    return 0 ;
}
