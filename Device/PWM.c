#include "PWM.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM_gpio配置
//  @param      pwmch       PWM通道
//  @return     void
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_gpio(PWM_CH pwmch)
{
	switch (pwmch)
	{
		case PWM1P_P10:
		{
			pinMode(P1_0, GPIO_PP);
			break;
		}
		case PWM1N_P11:
		{
			pinMode(P1_1, GPIO_PP);
			break;
		}
		case PWM1P_P20:
		{
			pinMode(P2_0, GPIO_PP);
			break;
		}
		case PWM1N_P21:
		{
			pinMode(P2_1, GPIO_PP);
			break;
		}
		case PWM1P_P60:
		{
			pinMode(P6_0, GPIO_PP);
			break;
		}
		case PWM1N_P61:
		{
			pinMode(P6_1, GPIO_PP);
			break;
		}

		case PWM2P_P12:
		{
			pinMode(P1_2, GPIO_PP);
			break;
		}
		case PWM2N_P13:
		{
			pinMode(P1_3, GPIO_PP);
			break;
		}
		case PWM2P_P22:
		{
			pinMode(P2_2, GPIO_PP);
			break;
		}
		case PWM2N_P23:
		{
			pinMode(P2_3, GPIO_PP);
			break;
		}
		case PWM2P_P62:
		{
			pinMode(P6_2, GPIO_PP);
			break;
		}
		case PWM2N_P63:
		{
			pinMode(P6_3, GPIO_PP);
			break;
		}

		case PWM3P_P14:
		{
			pinMode(P1_4, GPIO_PP);
			break;
		}
		case PWM3N_P15:
		{
			pinMode(P1_5, GPIO_PP);
			break;
		}
		case PWM3P_P24:
		{
			pinMode(P2_4, GPIO_PP);
			break;
		}
		case PWM3N_P25:
		{
			pinMode(P2_5, GPIO_PP);
			break;
		}
		case PWM3P_P64:
		{
			pinMode(P6_4, GPIO_PP);
			break;
		}
		case PWM3N_P65:
		{
			pinMode(P6_5, GPIO_PP);
			break;
		}
		case PWM4P_P16:
		{
			pinMode(P1_6, GPIO_PP);
			break;
		}
		case PWM4N_P17:
		{
			pinMode(P1_7, GPIO_PP);
			break;
		}
		case PWM4P_P26:
		{
			pinMode(P2_6, GPIO_PP);
			break;
		}
		case PWM4N_P27:
		{
			pinMode(P2_7, GPIO_PP);
			break;
		}
		case PWM4P_P66:
		{
			pinMode(P6_6, GPIO_PP);
			break;
		}
		case PWM4N_P67:
		{
			pinMode(P6_7, GPIO_PP);
			break;
		}
		case PWM4P_P34:
		{
			pinMode(P3_4, GPIO_PP);
			break;
		}
		case PWM4N_P33:
		{
			pinMode(P3_3, GPIO_PP);
			break;
		}
		case PWM5_P20:
		{
			pinMode(P2_0, GPIO_PP);
			break;
		}
		case PWM5_P17:
		{
			pinMode(P1_7, GPIO_PP);
			break;
		}
		case PWM5_P00:
		{
			pinMode(P0_0, GPIO_PP);
			break;
		}
		case PWM5_P74:
		{
			pinMode(P7_4, GPIO_PP);
			break;
		}
		case PWM6_P21:
		{
			pinMode(P2_1, GPIO_PP);
			break;
		}
		case PWM6_P54:
		{
			pinMode(P5_4, GPIO_PP);
			break;
		}
		case PWM6_P01:
		{
			pinMode(P0_1, GPIO_PP);
			break;
		}
		case PWM6_P75:
		{
			pinMode(P7_5, GPIO_PP);
			break;
		}
		case PWM7_P22:
		{
			pinMode(P2_2, GPIO_PP);
			break;
		}
		case PWM7_P33:
		{
			pinMode(P3_3, GPIO_PP);
			break;
		}
		case PWM7_P02:
		{
			pinMode(P0_2, GPIO_PP);
			break;
		}
		case PWM7_P76:
		{
			pinMode(P7_6, GPIO_PP);
			break;
		}
		case PWM8_P23:
		{
			pinMode(P2_3, GPIO_PP);
			break;
		}
		case PWM8_P34:
		{
			pinMode(P3_4, GPIO_PP);
			break;
		}
		case PWM8_P03:
		{
			pinMode(P0_3, GPIO_PP);
			break;
		}
		case PWM8_P77:
		{
			pinMode(P7_7, GPIO_PP);
			break;
		}
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM初始化
//  @param      pwmch       PWM通道
//  @param      freq        PWM频率64Hz-3MHz)
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           
//							pwm_init(PWM0_P00, 100, 5000);     //通道PWM0  引脚P0.0  频率100  占空比5000
//							PWM_DUTY_MAX为10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(PWM_CH pwmch, uint32 freq, uint16 duty)
{

	uint16 match_temp;
	uint16 period_temp;
	uint16 freq_div = 0;

	P_SW2 |= 0x80;

	//GPIO端口配置
	pwm_set_gpio(pwmch);

	freq_div = ((uint32)(sys_clk / freq)) >> 16;				//分频

	period_temp = (sys_clk / freq) / (freq_div + 1) - 1;		//周期时间

	match_temp = period_temp * ((float)duty / PWM_DUTY_MAX);	//占空比

	if (PWM5_P20 <= pwmch)				//PWM5-8
	{

		PWM2_ENO |= (1 << ((2 * ((pwmch >> 4) - 4))));					//使能输出
		PWM2_PS |= ((pwmch & 0x03) << ((2 * ((pwmch >> 4) - 4))));		//输出脚选择

		// 配置通道输出使能和极性	
		(*(unsigned char volatile xdata*)(PWM2_CCER1_ADDR + (((pwmch >> 4) - 4) >> 1))) |= (1 << (((pwmch >> 4) & 0x01) * 4));

		//通道模式配置
		(*(unsigned char volatile xdata*)(PWM2_CCMR1_ADDR + ((pwmch >> 4) - 4))) |= 0x06 << 4;	//
		(*(unsigned char volatile xdata*)(PWM2_CCMR1_ADDR + ((pwmch >> 4) - 4))) |= 1 << 3;		//PWM模式2

		//设置周期时间（高字节先写入）
		//PWM2_ARR = (uint16)period_temp;
		PWM2_ARRH = period_temp >> 8;
		PWM2_ARRL = period_temp;
		//PWM2_ARR=2000;

		//PWM预分频（高字节先写入）
		PWM2_PSCRH = freq_div >> 8;
		PWM2_PSCRL = freq_div;

		//设置占空比（高字节先写入）
		(*(unsigned char volatile xdata*)(PWM2_CCR1_ADDR + 2 * ((pwmch >> 4) - 4))) = match_temp >> 8;
		(*(unsigned char volatile xdata*)(PWM2_CCR1_ADDR + 2 * ((pwmch >> 4) - 4) + 1)) = match_temp;
		
		PWM2_BKR = 0x80; 	//使能主输出
		PWM2_CR1 = 0x01;	//PWM开始计时
	}
	else
	{
		PWM1_ENO |= (1 << (pwmch & 0x01)) << ((pwmch >> 4) * 2);	//使能输出	
		PWM1_PS |= ((pwmch & 0x07) >> 1) << ((pwmch >> 4) * 2);    //输出脚选择


		// 配置通道输出使能和极性
		(*(unsigned char volatile xdata*)(PWM1_CCER1_ADDR + (pwmch >> 5))) |= (1 << ((pwmch & 0x01) * 2 + ((pwmch >> 4) & 0x01) * 0x04));


		(*(unsigned char volatile xdata*)(PWM1_CCMR1_ADDR + (pwmch >> 4))) |= 0x06 << 4;	
		(*(unsigned char volatile xdata*)(PWM1_CCMR1_ADDR + (pwmch >> 4))) |= 1 << 3;		//PWM模式2

		//设置周期时间（高字节先写入）
		//PWM1_ARR = period_temp;
		PWM1_ARRH = period_temp >> 8;
		PWM1_ARRL = period_temp;

		//PWM预分频（高字节先写入）
		PWM1_PSCRH = freq_div >> 8;
		PWM1_PSCRL = freq_div;

		//设置占空比（高字节先写入）
		(*(unsigned char volatile xdata*)(PWM1_CCR1_ADDR + 2 * (pwmch >> 4))) = match_temp >> 8;
		(*(unsigned char volatile xdata*)(PWM1_CCR1_ADDR + 2 * (pwmch >> 4) + 1)) = match_temp;

		PWM1_BKR = 0x80; 	//使能主输出
		PWM1_CR1 = 0x01;	//PWM开始计时
	}

	//P_SW2 &= 0x7F;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM调整占空比
//  @param      pwmch       PWM引脚
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_duty(PWM0_P00, 5000);     //通道PWM0  引脚P0.0  占空比5000
//							
//-------------------------------------------------------------------------------------------------------------------
void pwm_duty(PWM_CH pwmch, uint16 duty)
{
	uint16 match_temp;

	//	P_SW2 |= 0x80;
	if (PWM5_P20 <= pwmch)				//PWM5-8
	{
		match_temp = PWM2_ARRH;
		match_temp = match_temp << 8;
		match_temp = match_temp + PWM2_ARRL;
		match_temp = match_temp * ((float)duty / PWM_DUTY_MAX);				//占空比
		(*(unsigned char volatile xdata*)(PWM2_CCR1_ADDR + 2 * ((pwmch >> 4) - 4))) = match_temp >> 8;
		(*(unsigned char volatile xdata*)(PWM2_CCR1_ADDR + 2 * ((pwmch >> 4) - 4) + 1)) = match_temp;
	}
	else
	{
		match_temp = PWM1_ARRH;
		match_temp = match_temp << 8;
		match_temp = match_temp + PWM1_ARRL;
		match_temp = match_temp *((float)duty / PWM_DUTY_MAX);				//占空比
		(*(unsigned char volatile xdata*)(PWM1_CCR1_ADDR + 2 * (pwmch >> 4))) = match_temp >> 8;
		(*(unsigned char volatile xdata*)(PWM1_CCR1_ADDR + 2 * (pwmch >> 4) + 1)) = match_temp;
	}
	//	P_SW2 &= ~0x80;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM调整频率和占空比
//  @param      pwmch       PWM通道
//  @param      freq        PWM频率
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_freq(PWM0_P00, 50, 5000);     //通道PWM0  引脚P0.0  频率50  占空比5000
//-------------------------------------------------------------------------------------------------------------------
void pwm_freq_duty(PWM_CH pwmch, uint16 freq, uint16 duty)
{
	uint16 match_temp;
	uint16 period_temp;
	uint16 freq_div = 0;

	freq_div = (sys_clk / freq) >> 15;								//分频
	period_temp = sys_clk / freq / (freq_div + 1);					//频率

	//match_temp = period_temp * duty;
	//match_temp = match_temp / PWM_DUTY_MAX;
	match_temp = period_temp * ((float)duty / PWM_DUTY_MAX);	//占空比

//	P_SW2 |= 0x80;
	if (PWM5_P20 <= pwmch)				//PWM5-8
	{
		//周期（高字节先写入）
		//PWM2_ARR = (uint16)period_temp;
		PWM2_ARRH = period_temp >> 8;
		PWM2_ARRL = period_temp;
		//PWM预分频（高字节先写入）
		PWM2_PSCRH = freq_div>>8;
		PWM2_PSCRL = freq_div;
		//占空比（高字节先写入）
		//(*(unsigned int volatile xdata*)(PWM2_CCR1_ADDR + 2 * ((pwmch >> 4) - 4))) = match_temp;
		(*(unsigned char volatile xdata*)(PWM2_CCR1_ADDR + 2 * ((pwmch >> 4) - 4))) = match_temp >> 8;
		(*(unsigned char volatile xdata*)(PWM2_CCR1_ADDR + 2 * ((pwmch >> 4) - 4) + 1)) = match_temp;
		
	}
	else
	{
		//周期（高字节先写入）
		//PWM2_ARR = (uint16)period_temp;
		PWM1_ARRH = period_temp >> 8;
		PWM1_ARRL = period_temp;
		//PWM预分频（高字节先写入）
		PWM1_PSCR = freq_div;
		//占空比（高字节先写入）
		//(*(unsigned int volatile xdata*)(PWM1_CCR1_ADDR + 2 * (pwmch >> 4))) = match_temp;
		(*(unsigned char volatile xdata*)(PWM1_CCR1_ADDR + 2 * (pwmch >> 4))) = match_temp >> 8;
		(*(unsigned char volatile xdata*)(PWM1_CCR1_ADDR + 2 * (pwmch >> 4) + 1)) = match_temp;
		
	}
	//	P_SW2 &= ~0x80;
}
