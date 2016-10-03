#include "irSensor.h"
#include "timer.h"

#define TOGGLE(bit)				((~bit) & 0x1)

unsigned volatile char cntBit = 0;
unsigned volatile char halfBit = 0;
unsigned int bufferData = 0;

void clearIrSensorInterrupt(void);
unsigned int irSensorAddBit(unsigned int buffer, unsigned char index, unsigned char value);
unsigned int getPreviousBit(unsigned char index, unsigned int byte);
void irSensorAddPreviousBit(void);
void irSensorAddToggleBit(void);
void receiveStartBit(void);
unsigned char reverseNibble(unsigned char byte);
void resetIrSensorValues(void);
unsigned int getBitCount(void);
unsigned int getBufferData(void);
unsigned char getToggleBit(void);
unsigned char getLastNibble(void);

// TODO: ask which pin will be used to read the ir sensor

void irSensorInit(unsigned char pin) {
	// initialize a timer
	timerMicrosInit(0);
	// enable interrupt
}

void clearIrSensorInterrupt(void) {

}

unsigned int irSensorAddBit(unsigned int buffer, unsigned char index, unsigned char value) {
	return ((value == 1) ? (buffer |= (1 << index)) : (buffer &= ~(1 << index)));
}

unsigned int getPreviousBit(unsigned char index, unsigned int byte) {
	return ((byte & (1 << (index - 1))) >> (index - 1));
}

//*****************************************************************************
//
// If long pulse occurred, a toggle is expected.
// If a short pulse (half a bit) occurred twice, the
// previous pulse is expected. However, receiving the previous bit
// (of the first interrupt) and a toggle bit may also occur.
//
// EXAMPLE:
//        ______
//       |      |
//  ~889 |      |
// ______|~889  |_
//
//*****************************************************************************

void irSensorAddPreviousBit(void) {
	if ((readTimer() >= 700) && (readTimer() <= 1100)) {

		// Half a bit has been received after 889 us
		halfBit++;

		// half bit + half bit = 1 bit
		if (halfBit == 2) {
			irSensorAddBit(bufferData, cntBit, getPreviousBit(cntBit, bufferData));
			cntBit++;
			halfBit = 0;
		}

	}
}

//*****************************************************************************
//
// Two different states may occur: half a bit may have already been received
// and is thus waiting for the other half, or a toggle bit has been received
// previously.
//
// A long pulse after two half bits is impossible. So, no programming need for
// that state but since the next pulse may be a long pulse, it makes it 3 half
// bits. In that case a previous bit and a toggle bit is to be expected.
//
// EXAMPLE: toggle bit
//  ____________
// |            |
// |            |
// |   ~1778	|_
//
// EXAMPLE: previous bit + toggle bit
//        ____________
//       |            |
//       |            |
// ______|~1778       |___
//
//*****************************************************************************
void irSensorAddToggleBit(void) {
	if ((readTimer() >= 1500) && (readTimer() <= 2000)) {

		// pulse width of one bit
		halfBit += 2;

		if (halfBit == 2) {
			bufferData = irSensorAddBit(bufferData, cntBit, TOGGLE(getPreviousBit(cntBit, bufferData)));
			cntBit++;
		}
		else if (halfBit == 3) {

			// Two bits to be added
			bufferData = irSensorAddBit(bufferData, cntBit, getPreviousBit(cntBit, bufferData));
			cntBit++;
			bufferData = irSensorAddBit(bufferData, cntBit, TOGGLE(getPreviousBit(cntBit, bufferData)));
			cntBit++;
		}
		halfBit = 0;
	}
}

/* Simply receive a start bit. When this occurs,
 * the timer should start measuring a low signal
 * pulse. */
void receiveStartBit(void) {

	// First bit received is always 1, so add 1 to data buffer
	if (cntBit == 0) {
		bufferData = irSensorAddBit(bufferData, cntBit, 1);
		cntBit++;
		startTimer();
	}
}

unsigned char reverseNibble(unsigned char byte) {
	unsigned char reversedNibble = 0;
	int i, j = 0;

	for (i = 3; i > -1; i--) {
		unsigned char thisBit = ((byte & (1 << i)) >> i);
		reversedNibble |= (thisBit << j);
		j++;
	}
	return reversedNibble;
}

/* Because we add the previous bit to buffer,
 * we need to wait for cntBit to be 14 to add
 * bit 13 to buffer. */
void resetIrSensorValues(void) {
	if (cntBit == 14) {
		stopTimer();
		cntBit = 0;
		halfBit = 0;
	}
}

unsigned int getBitCount(void) {
	return cntBit;
}

unsigned int getBufferData(void) {
	return bufferData;
}

unsigned char getToggleBit(void) {
	return ((bufferData & 0x4) >> 2);
}

unsigned char getLastNibble(void) {
	return reverseNibble(bufferData >> 10);
}

