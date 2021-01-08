#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"

/*
 * timer0 -> interrupt 1		1.00ms
 * timer1 -> interrupt 3		0.50ms
 * timer2 -> interrupt 12		0.25ms
 * timer3 -> interrupt 19		0.20ms
 * timer4 -> interrupt 20		0.01ms
*/

#define Timer0_Reload   (MAIN_Fosc / 1000)      //Timer 0 中断频率, 1000次/秒
#define Timer1_Reload   (MAIN_Fosc / 2000)      //Timer 1 中断频率, 2000次/秒
#define Timer2_Reload   (MAIN_Fosc / 4000)      //Timer 2 中断频率, 4000次/秒
#define Timer3_Reload   (MAIN_Fosc / 5000)      //Timer 3 中断频率, 5000次/秒
#define Timer4_Reload   (MAIN_Fosc / 10000)      //Timer 4 中断频率, 10000次/秒

void Timer0_init(void);
void Timer1_init(void);
void Timer2_init(void);
void Timer3_init(void);
void Timer4_init(void);

#endif
