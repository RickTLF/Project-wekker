/*
 * timer.h
 *
 *  Created on: 1 okt. 2016
 *      Author: Mandrake
 */

#ifndef TIMER_H_
#define TIMER_H_

void timerMicrosInit(unsigned int matchValue);
void startTimer(void);
unsigned long readTimer(void);
void resetTimer(void);
void TIMER0_IRQHandler(void);
void stopTimer(void);

#endif /* TIMER_H_ */
