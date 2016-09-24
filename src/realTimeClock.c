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
#define I2C0DATA_ BUFFER 	(*(unsigned int *) 0x4001C02C) 		// buffer, receives ack/nack + bits of I2DAT
#define I2C0MASK0			(*(unsigned int *) 0x4001C030) 		// determine address match

// TODO: add pins through PINSEL ... etc.

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
	// enable I2C
	I2C0CONSET |= (1 << 6);
	// enter master mode and transmit start condition
	I2C0CONSET |= (1 << 5);

}

void transmitStop(void) {
	// enable I2C
	I2C0CONSET |= (1 << 6);
	// enter master mode and transmit start condition
	I2C0CONSET |= (1 << 4);
}

// Clears interrupt
void clearI2CInterrupt(void) {
	I2C0CONCLR |= (1 << 3);
}

unsigned char getI2CStatus(void) {
	return I2C0STAT;
}

void transmitI2CData(unsigned char data) {
	I2C0DAT = data;
}

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
