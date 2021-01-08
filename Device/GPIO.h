#ifndef _GPIO_H_
#define _GPIO_H_

#include "sys.h"

typedef enum
{
	NOPULL = 0,
	PULL4k = 1,
}PULLUP;


typedef enum
{
	P0_0 = 0x00, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7,
	P1_0 = 0x10, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7,
	P2_0 = 0x20, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7,
	P3_0 = 0x30, P3_1, P3_2, P3_3, P3_4, P3_5, P3_6, P3_7,
	P4_0 = 0x40, P4_1, P4_2, P4_3, P4_4, P4_5, P4_6, P4_7,
	P5_0 = 0x50, P5_1, P5_2, P5_3, P5_4, P5_5, P5_6, P5_7,
	P6_0 = 0x60, P6_1, P6_2, P6_3, P6_4, P6_5, P6_6, P6_7,
	P7_0 = 0x70, P7_1, P7_2, P7_3, P7_4, P7_5, P7_6, P7_7,
}PIN_name;

typedef enum
{
	GPIO = 0,			//准双向口(弱上拉)
	GPIO_PP = 1,		//推挽输出
	INPUT = 2,	        //高阻输入
	GPIO_OD = 3,		//开漏输出
}GPIOMODE;

#define PxPU_BASE_ADDR  0xFE10 

void pullMode(PIN_name pin, PULLUP pull);
void pinMode(PIN_name pin, GPIOMODE mode);

#endif /* _STC12_H_ */

