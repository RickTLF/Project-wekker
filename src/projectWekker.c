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
	i2cInit();
	enableI2C();
	// set up slave address
	loadSlaveAddress(0x8, 0);
	// setting STA bit
	transmitStart();
	// clear si and sta bit
	//clearSiBit();
	//clearStartFlag();

	while (1) {

	}
	return 0;
}

void I2C1_IRQHandler(void) {
	printf("Hello world!\n");
	printf("status: %u\n", getI2CStatus());
	clearSiBit();
	clearStartFlag();
}
