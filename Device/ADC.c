#include "ADC.h"

uint8  setbit = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC初始化
//  @param      adcn            选择ADC通道
//  @param      speed      		ADC时钟频率
//  @return     void
//  Sample usage:               adc_init(ADC_P10,ADC_SYSclk_DIV_2);//初始化P1.0为ADC功能,ADC时钟频率：SYSclk/2
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADC_Name adcn, ADC_CLK speed, ADC_bit msbit)
{
	setbit = msbit;
	ADC_CONTR |= 1 << 7;	//1 ：打开 ADC 电源
	if (adcn > 15) 
	{
		adcn = adcn - 16;
		//IO口需要设置为高阻输入
		P3M0 &= ~(1 << (adcn & 0x07));
		P3M1 |= (1 << (adcn & 0x07));


	}
	else {
		if ((adcn >> 3) == 1) //P0.0
		{
			//IO口需要设置为高阻输入
			P0M0 &= ~(1 << (adcn & 0x07));
			P0M1 |= (1 << (adcn & 0x07));
		}
		else if ((adcn >> 3) == 0) //P1.0	
		{
			//IO口需要设置为高阻输入
			P1M0 &= ~(1 << (adcn & 0x07));
			P1M1 |= (1 << (adcn & 0x07));
		}
	}

	ADCCFG |= speed & 0x0F;	//ADC时钟频率SYSclk/2/speed&0x0F;

	ADCCFG |= 1 << 5;		//转换结果右对齐。 ADC_RES 保存结果的高 2 位， ADC_RESL 保存结果的低 8 位。
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC转换一次
//  @param      adcn            选择ADC通道
//  @param      resolution      分辨率
//  @return     void
//  Sample usage:               adc_convert(ADC_P10, ADC_10BIT);
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_read(ADC_Name adcn)
{
	uint16 adc_value;
	if (adcn > 15)adcn = adcn - 8;

	ADC_CONTR &= (0xF0);	//清除ADC_CHS[3:0] ： ADC 模拟通道选择位
	ADC_CONTR |= adcn;

	ADC_CONTR |= 0x40;  // 启动 AD 转换
	while (!(ADC_CONTR & 0x20));  // 查询 ADC 完成标志
	ADC_CONTR &= ~0x20;  // 清完成标志


	adc_value = ADC_RES;  //存储 ADC 的 10 位结果的高 2 位
	adc_value <<= 8;
	adc_value |= ADC_RESL;  //存储 ADC 的 10 位结果的低 8 位

	ADC_RES = 0;
	ADC_RESL = 0;

	adc_value >>= setbit;//取多少位


	return adc_value;
}
