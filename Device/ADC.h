#ifndef _ADC_H_
#define _ADC_H_

#include "sys.h"

extern uint8  setbit;

typedef enum
{
	ADC_P10 = 0,
	ADC_P11,
	ADC_P12, //仅做占位
	ADC_P13,
	ADC_P14,
	ADC_P15,
	ADC_P16,
	ADC_P17,

	ADC_P00,
	ADC_P01,
	ADC_P02,
	ADC_P03,
	ADC_P04,
	ADC_P05,
	ADC_P06,
	ADC_REF = 0x0f, //内部AD 1.19V

	ADC_P30,
	ADC_P31,
	ADC_P32,
	ADC_P33,
	ADC_P34,
	ADC_P35,
	ADC_P36,
	ADC_P37,

} ADC_Name;

//此枚举定义不允许用户修改
typedef enum
{
	ADC_SYSclk_DIV_2 = 0,
	ADC_SYSclk_DIV_4,
	ADC_SYSclk_DIV_6,
	ADC_SYSclk_DIV_8,
	ADC_SYSclk_DIV_10,
	ADC_SYSclk_DIV_12,
	ADC_SYSclk_DIV_14,
	ADC_SYSclk_DIV_16,
	ADC_SYSclk_DIV_18,
	ADC_SYSclk_DIV_20,
	ADC_SYSclk_DIV_22,
	ADC_SYSclk_DIV_24,
	ADC_SYSclk_DIV_26,
	ADC_SYSclk_DIV_28,
	ADC_SYSclk_DIV_30,
	ADC_SYSclk_DIV_32,
} ADC_CLK;


//此枚举定义不允许用户修改
typedef enum    // 枚举ADC通道
{
	ADC_12BIT = 0,    //12位分辨率
	ADC_11BIT,		//11位分辨率
	ADC_10BIT,		//10位分辨率
	ADC_9BIT,    	//9位分辨率
	ADC_8BIT,     	//8位分辨率
}ADC_bit;

void adc_init(ADC_Name adcn, ADC_CLK speed, ADC_bit msbit);
uint16 adc_read(ADC_Name adcn);

#endif