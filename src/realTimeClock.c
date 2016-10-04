/*****************************************************************************
 *
 * PROJECT WEKKER 2016
 *
 * Author(s):
 * Rick Kock
 *
 * file name:
 * realTimeClock.c
 *
 * description:
 * program designed to control the DS chip. to control the chip, the lpc must
 * communicate using I2C
 *
*****************************************************************************/

#include "realTimeClock.h"

#define PCONP 		(*(unsigned int *) 0x400FC0C4)				// power
#define PCLKSEL1	(*(unsigned int *) 0x400FC1AC)				// clock
#define PINSEL0 	(*(unsigned int *) 0x4002C000)				// pin function
#define ISER0 		(*(unsigned int *) 0xE000E100)				// interrupt
#define PINMODE0 	(*(unsigned int *) 0x4002C040)				// select pin mode
#define PINMODE_OD0	(*(unsigned int *) 0x4002C068)				// select open drain mode

// TODO: change the names and registers according to I2C1
#define I2C1CONSET 			(*(unsigned int *) 0x4005C000) 		// control set
#define I2C1STAT			(*(unsigned int *) 0x4005C004) 		// status
#define I2C1DAT 			(*(unsigned int *) 0x4005C008) 		// data
#define I2C1SCLH 			(*(unsigned int *) 0x4005C010) 		// SCH duty cycle (high time)
#define I2C1SCLL			(*(unsigned int *) 0x4005C014) 		// SCL duty cycle (low time)
#define I2C1CONCLR 			(*(unsigned int *) 0x4005C018) 		// clear
#define I2C1DATA_BUFFER	 	(*(unsigned int *) 0x4005C02C) 		// buffer, receives ack/nack + bits of I2DAT
#define I2C1MASK0			(*(unsigned int *) 0x4005C030) 		// determine address match

#define READ				1
#define WRITE				0

// TODO: add pins through PINSEL ... etc.
// TODO: finish i2c protocol methods
// TODO: implement methods to easily control rtc

// TODO: add prototypes here
void masterTransmitData(unsigned char address, unsigned char data);
void masterReadByte(unsigned char address);
void masterReadData(unsigned char sendStop, unsigned char cntBytes);
void assertAck(void);
void assertNotAck(void);
void addData(unsigned char data);
void transmitStopCondition(void);
unsigned char getI2CData(void);
void setHighTimePeriod(unsigned char time);
void setLowTimePeriod(unsigned char time);

//*****************************************************************************
// I2C IMPLEMENTATION

/* For testing purposes, I2C 1 is used.
 * Use pin J6-9 as SDA and pin J6-10 as SCL
 */
//*****************************************************************************


void i2cInit(void) {
	// power I2C1 interface clock
	PCONP |= (1 << 19);
	// select clock: PCLK
	PCLKSEL1 |= (1 << 6);
	// select pins through PINSEL (no pull-up, no pull down) and pinmode od (open drain)
	PINSEL0 |= 0xF;	// Selecting functions SDA1 and SCL1
	PINMODE0 |= (1 << 1) | (1 << 3); // no pull up, no pull down
	PINMODE_OD0 |= (1 << 0) | (1 << 1); // set open drain mode
	// Enable the I2C1 interrupt
	ISER0 |= (1 << 11);
	// Set clock frequency
	setHighTimePeriod(100);
	setLowTimePeriod(100);
}

//*****************************************************************************
//
// Before master transmitter mode can be entered, the I2C must be enabled.
// Then the SI bit must be cleared.
//
// After writing the slave address, the STA bit should be cleared.
//
//*****************************************************************************

void enableI2C(void) {
	I2C1CONSET |= 0x40;
}

void masterTransmitByte(unsigned char address, unsigned char byte) {
	// enable I2C
	I2C1CONSET |= 0x40;
	// clear SI bit
	// clearSiBit();
	// load slave address and set data direction bit
	// loadSlaveAddress(address, WRITE);
	// clear STA flag
	// clearStartFlag();
	/* after each byte is transmitted,
	 * an acknowledge bit is received */
	// TODO: add actions for receiving ack
}

void masterTransmitData(unsigned char address, unsigned char data) {

}

//*****************************************************************************
//*****************************************************************************

/*
void masterReadByte(unsigned char address) {
	// master always transmits a start condition
	transmitStart();
	// load slave address and set data direction bit
	loadSlaveAddress(address, READ);
	// clear the SI bit
	clearSiBit();
}*/

//*****************************************************************************
//
// Loads the slave address and determines whether the master should
// either read or write to the specified device.
// This method should be called after transmitting a start or
// repeated start condition.
//
//*****************************************************************************

void loadSlaveAddress(unsigned char address, unsigned char readWriteBit) {
	I2C1DAT = (address << 1) | readWriteBit;
}

//*****************************************************************************
//
// After the start condition has been transmitted, the interrupt
// service routine must load the slave address and the data direction
// bit to the data register. Then the SI bit must be cleared.
//
// The SI bit must also be cleared after the master has determined
// the next step: transmitting an ack, or transmitting a nack. See
// [method] for more information.
//
// NOTE: the SI bit is cleared by writing 1 to the SIC bit in the
// I2CONCLR register
//
//*****************************************************************************

void clearSiBit(void) {
	I2C1CONCLR |= (1 << 3);
}

void clearStartFlag(void) {
	I2C1CONCLR |= (1 << 5);
}

//*****************************************************************************
// Receives the amount of bytes specified in cntBytes.
//*****************************************************************************

void masterReadData(unsigned char sendStop, unsigned char cntBytes) {

}

/*
void transmitStart(void) {
	// enable I2C and transmit start condition
	I2C1CONSET |= (1 << 6) | (1 << 5);
}*/
void transmitStart(void) {
	I2C1CONSET |= 0x20;
}


//*****************************************************************************
//
// By transmitting the ack bit, the master is indicating that
// more data transmitted by the slave is expected. (check)
//
//*****************************************************************************

void assertAck(void) {
	I2C1CONSET |= (1 << 2);
}

//*****************************************************************************
//
// If the last byte is to be expected, the master must transmit
// a not acknowledge.
//
//*****************************************************************************

void assertNotAck(void) {

}

void addData(unsigned char data) {
	I2C1DAT = data;
}

//*****************************************************************************
//
// After the master issued a not acknowledge, the master can signal the slave
// that the reading sequence is finished and that it needs to issue a stop or
// a repeated start.
//
//*****************************************************************************

void transmitStopCondition(void) {

}

//*****************************************************************************
//*****************************************************************************

unsigned char getI2CStatus(void) {
	return I2C1STAT;
}

//*****************************************************************************
//*****************************************************************************
unsigned char getI2CData(void) {
	return I2C1DAT;
}


void setHighTimePeriod(unsigned char time) {
	I2C1SCLH = time;
}

void setLowTimePeriod(unsigned char time) {
	I2C1SCLL = time;
}
