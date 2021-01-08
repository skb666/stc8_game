#include "GPIO.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO设置引脚上拉电阻设置
//  @param      pin         选择引脚（P00-P77）
//  @param      pull        设置上下拉电阻 NOPULL:不设置 PULL4k:上拉
//  @return     void
//  Sample usage:           gpio_pull_set(P00,NOPULL);       // 设置P0.0引脚没有上下拉电阻
//-------------------------------------------------------------------------------------------------------------------
void pullMode(PIN_name pin, PULLUP pull)
{
	if (PULL4k == pull)
	{
		(*(unsigned char volatile xdata*)(PxPU_BASE_ADDR + (pin >> 4))) |= (1 << (pin & 0x0F));
	}
	else if (NOPULL == pull)
	{
		(*(unsigned char volatile xdata*)(PxPU_BASE_ADDR + (pin >> 4))) &= ~(1 << (pin & 0x0F));
	}
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO设置引脚模式
//  @param      pin         选择引脚（P0_0-P5_4）
//  @param      mode        引脚模式 GPIO:准双向口, GPIO_PP:推挽输出, INPUT:高阻输入, GPIO_OD:开漏输出
//  @return     void
//  Sample usage:           pinMode(P00,GPIO);       // 设置P0.0设置为双向IO
//-------------------------------------------------------------------------------------------------------------------
void pinMode(PIN_name pin, GPIOMODE mode)
{
	if (GPIO == mode)
	{
		if (0x00 == (pin & 0xF0))	//P0
		{
			P0M1 &= ~(1 << (pin & 0xF));
			P0M0 &= ~(1 << (pin & 0xF));
		}
		if (0x10 == (pin & 0xF0))	//P1
		{
			P1M1 &= ~(1 << (pin & 0xF));
			P1M0 &= ~(1 << (pin & 0xF));
		}
		if (0x20 == (pin & 0xF0))	//P2
		{
			P2M1 &= ~(1 << (pin & 0xF));
			P2M0 &= ~(1 << (pin & 0xF));
		}

		if (0x30 == (pin & 0xF0))	//P3
		{
			P3M1 &= ~(1 << (pin & 0xF));
			P3M0 &= ~(1 << (pin & 0xF));
		}
		if (0x40 == (pin & 0xF0))	//P4
		{
			P4M1 &= ~(1 << (pin & 0xF));
			P4M0 &= ~(1 << (pin & 0xF));
		}
		if (0x50 == (pin & 0xF0))	//P5
		{
			P5M1 &= ~(1 << (pin & 0xF));
			P5M0 &= ~(1 << (pin & 0xF));
		}
	}
	else if (GPIO_PP == mode)
	{
		if (0x00 == (pin & 0xF0))	//P0
		{
			P0M1 &= ~(1 << (pin & 0xF));
			P0M0 |= (1 << (pin & 0xF));
		}
		if (0x10 == (pin & 0xF0))	//P1
		{
			P1M1 &= ~(1 << (pin & 0xF));
			P1M0 |= (1 << (pin & 0xF));
		}
		if (0x20 == (pin & 0xF0))	//P2
		{
			P2M1 &= ~(1 << (pin & 0xF));
			P2M0 |= (1 << (pin & 0xF));
		}

		if (0x30 == (pin & 0xF0))	//P3
		{
			P3M1 &= ~(1 << (pin & 0xF));
			P3M0 |= (1 << (pin & 0xF));
		}
		if (0x40 == (pin & 0xF0))	//P4
		{
			P4M1 &= ~(1 << (pin & 0xF));
			P4M0 |= (1 << (pin & 0xF));
		}
		if (0x50 == (pin & 0xF0))	//P5
		{
			P5M1 &= ~(1 << (pin & 0xF));
			P5M0 |= (1 << (pin & 0xF));
		}
	}
	else if (INPUT == mode)
	{
		if (0x00 == (pin & 0xF0))	//P0
		{
			P0M1 |= (1 << (pin & 0xF));
			P0M0 &= ~(1 << (pin & 0xF));
		}
		if (0x10 == (pin & 0xF0))	//P1
		{
			P1M1 |= (1 << (pin & 0xF));
			P1M0 &= ~(1 << (pin & 0xF));
		}
		if (0x20 == (pin & 0xF0))	//P2
		{
			P2M1 |= (1 << (pin & 0xF));
			P2M0 &= ~(1 << (pin & 0xF));
		}

		if (0x30 == (pin & 0xF0))	//P3
		{
			P3M1 |= (1 << (pin & 0xF));
			P3M0 &= ~(1 << (pin & 0xF));
		}
		if (0x40 == (pin & 0xF0))	//P4
		{
			P4M1 |= (1 << (pin & 0xF));
			P4M0 &= ~(1 << (pin & 0xF));
		}
		if (0x50 == (pin & 0xF0))	//P5
		{
			P5M1 |= (1 << (pin & 0xF));
			P5M0 &= ~(1 << (pin & 0xF));
		}
	}
	else if (GPIO_OD == mode)
	{
		if (0x00 == (pin & 0xF0))	//P0
		{
			P0M1 |= (1 << (pin & 0xF));
			P0M0 |= (1 << (pin & 0xF));
		}
		if (0x10 == (pin & 0xF0))	//P1
		{
			P1M1 |= (1 << (pin & 0xF));
			P1M0 |= (1 << (pin & 0xF));
		}
		if (0x20 == (pin & 0xF0))	//P2
		{
			P2M1 |= (1 << (pin & 0xF));
			P2M0 |= (1 << (pin & 0xF));
		}

		if (0x30 == (pin & 0xF0))	//P3
		{
			P3M1 |= (1 << (pin & 0xF));
			P3M0 |= (1 << (pin & 0xF));
		}
		if (0x40 == (pin & 0xF0))	//P4
		{
			P4M1 |= (1 << (pin & 0xF));
			P4M0 |= (1 << (pin & 0xF));
		}
		if (0x50 == (pin & 0xF0))	//P5
		{
			P5M1 |= (1 << (pin & 0xF));
			P5M0 |= (1 << (pin & 0xF));
		}
	}
}
