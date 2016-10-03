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

#define PCONP 		(*(unsigned int *) 0x400FC0C4)				// power
#define PCLKSEL0	(*(unsigned int *) 0x400FC1A8)				// clock
#define ISER0 		(*(unsigned int *) 0xE000E100)				// interrupt

#define I2C0CONSET 			(*(unsigned int *) 0x4001C000) 		// control set
#define I2C0STAT			(*(unsigned int *) 0x4001C004) 		// status
#define I2C0DAT 			(*(unsigned int *) 0x4001C008) 		// data
#define I2C0ADR0 			(*(unsigned int *) 0x4001C00C) 		// slave address
#define I2C0SCLH 			(*(unsigned int *) 0x4001C010) 		// SCH duty cycle (high time)
#define I2C0SCLL			(*(unsigned int *) 0x4001C014) 		// SCL duty cycle (low time)
#define I2C0CONCLR 			(*(unsigned int *) 0x4001C018) 		// clear
#define I2C0MMCTRL 			(*(unsigned int *) 0x4001C01C) 		// monitor mode
#define I2C0ADR1			(*(unsigned int *) 0x4001C020) 		// not used
#define I2C0ADR2 			(*(unsigned int *) 0x4001C024) 		// not used
#define I2C0DATA_BUFFER	 	(*(unsigned int *) 0x4001C02C) 		// buffer, receives ack/nack + bits of I2DAT
#define I2C0MASK0			(*(unsigned int *) 0x4001C030) 		// determine address match

#define READ				1
#define WRITE				0

// TODO: add pins through PINSEL ... etc.
// TODO: finish i2c protocol methods
// TODO: implement methods to easily control rtc

// TODO: add prototypes here
void masterTransmitByte(unsigned char address, unsigned char byte);
void masterTransmitData(unsigned char address, unsigned char data);
void masterReadByte(unsigned char address);
void loadSlaveAddress(unsigned char address, unsigned char readWriteBit);
void clearSiBit(void);
void clearStartFlag(void);
void masterReadData(unsigned char sendStop, unsigned char cntBytes);
void transmitStart(void);
void assertAck(void);
void assertNotAck(void);
void addData(unsigned char data);
void transmitStopCondition(void);
unsigned char getI2CStatus(void);
unsigned char getI2CData(void);
void setHighTimePeriod(unsigned char time);
void setLowTimePeriod(unsigned char time);

//*****************************************************************************
//
// Before master transmitter mode can be entered, the I2C must be enabled.
// Then the SI bit must be cleared.
//
// After writing the slave address, the STA bit should be cleared.
//
//*****************************************************************************

void masterTransmitByte(unsigned char address, unsigned char byte) {
	// enable I2C
	I2C0CONSET |= (1 << 6);
	// clear SI bit
	clearSiBit();
	// load slave address and set data direction bit
	loadSlaveAddress(address, WRITE);
	// clear STA flag
	clearStartFlag();
	/* after each byte is transmitted,
	 * an acknowledge bit is received */
	// TODO: add actions for receiving ack
}

void masterTransmitData(unsigned char address, unsigned char data) {

}

//*****************************************************************************
//*****************************************************************************

void masterReadByte(unsigned char address) {
	// master always transmits a start condition
	transmitStart();
	// load slave address and set data direction bit
	loadSlaveAddress(address, READ);
	// clear the SI bit
	clearSiBit();
}

//*****************************************************************************
//
// Loads the slave address and determines whether the master should
// either read or write to the specified device.
// This method should be called after transmitting a start or
// repeated start condition.
//
//*****************************************************************************

void loadSlaveAddress(unsigned char address, unsigned char readWriteBit) {
	I2C0DAT = (address << 1) | readWriteBit;
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
	I2C0CONCLR |= (1 << 3);
}

void clearStartFlag(void) {
	I2C0CONCLR |= (1 << 5);
}

//*****************************************************************************
// Receives the amount of bytes specified in cntBytes.
//*****************************************************************************

void masterReadData(unsigned char sendStop, unsigned char cntBytes) {

}

void i2cInit(void) {
	// power I2C interface power/clock
	PCONP |= (1 << 7);
	// select clock: PCLK
	PCLKSEL0 |= (1 << 14);
	// select pins through PINSEL (no pull-up, no pull down) and pinmode od (open drain)

	// Enable the I2C interrupt
	ISER0 |= (1 << 10);
}

void transmitStart(void) {
	// enable I2C and transmit start condition
	I2C0CONSET |= (1 << 6) | (1 << 5);
}

//*****************************************************************************
//
// By transmitting the ack bit, the master is indicating that
// more data transmitted by the slave is expected. (check)
//
//*****************************************************************************

void assertAck(void) {
	I2C0CONSET |= (1 << 2);
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
	I2C0DAT = data;
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
	return I2C0STAT;
}

//*****************************************************************************
//*****************************************************************************
unsigned char getI2CData(void) {
	return I2C0DAT;
}


void setHighTimePeriod(unsigned char time) {
	I2C0SCLH = time;
}

void setLowTimePeriod(unsigned char time) {
	I2C0SCLL = time;
}

void I2C0_IRQHandler(void) {

}
