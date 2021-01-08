#ifndef __LED8_H
#define __LED8_H

#include <STC8.h>

#define LED8                    P6
#define LED8_CONTROL_PIN        P40
#define LED8_CONTROL_MODE       {P4M1&=~0x01;P4M0|=0x01;}       //推挽输出


void led8_enable();     //使能led
void led8_disable();    //禁用led
void led8_run();        //流水灯

#endif
