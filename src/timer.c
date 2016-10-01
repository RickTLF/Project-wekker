/*
 * timer.c
 *
 *  Created on: 1 okt. 2016
 *      Author: Mandrake
 */

#include "timer.h"

#define ISER0 				(*(unsigned int*) 0xE000E100) // interrupt set enable
#define T0IR 				(*(unsigned int*) 0x40004000) // used to clear interrupts
#define PCONP 				(*(unsigned int*) 0x400FC0C4) // power the peripheral
#define PCLKSEL0 			(*(unsigned int*) 0x400FC1A8)
#define T0TCR				(*(unsigned int*) 0x40004004) // timer control
#define T0TC				(*(unsigned int*) 0x40004008) //
#define T0PR 				(*(unsigned int*) 0x4000400C) //
#define T0MCR 				(*(unsigned int*) 0x40004014) // match control register
#define T0MR0 				(*(unsigned int*) 0x40004018) // match register

void resetTimerInterrupt(void);

void timerMicrosInit(unsigned int matchValue) {
	// power timer 0
	PCONP |= (1 << 1);
	// Enable timer 0 interrupt
	//ISER0 |= (1 << 1);
	// Interrupt on MR0
	//T0MCR |= (1 << 0);
	//T0MR0 = matchValue;

}

void startTimer(void) {
	T0TCR |= (1 << 0);
}

unsigned long readTimer(void) {
	return T0TC;
}

void stopTimer(void) {
	T0TCR |= ~(1 << 0);
}

void resetTimer(void) {
	T0TCR |= (1 << 1);
	T0TCR &= ~(1 << 1);
}

void resetTimerInterrupt(void) {
	T0IR |= (1 << 0);
}


void TIMER0_IRQHandler(void) {
	// TODO: your code here:
	resetTimer();
	resetTimerInterrupt();
}



