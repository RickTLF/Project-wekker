/*
 * realTimeClock.h
 *
 *  Created on: 23 sep. 2016
 *      Author: Mandrake
 */

#ifndef REALTIMECLOCK_H_
#define REALTIMECLOCK_H_

void i2cInit(void);
void masterTransmitByte(unsigned char address, unsigned char byte);
void enableI2C(void);
void loadSlaveAddress(unsigned char address, unsigned char readWriteBit);
void transmitStart(void);
void clearSiBit(void);
void clearStartFlag(void);
unsigned char getI2CStatus(void);

#endif /* REALTIMECLOCK_H_ */
