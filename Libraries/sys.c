#include "sys.h"
#include "hc595.h"
#include "led8.h"

uint32 sys_clk = 24000000;//设置PWM、定时器、串口、EEPROM频率参数

void InitMCU(){
	P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口

	led8_disable();			//LED Power OFF
    hc595_init(); 
   	hc595_disable();
	
	P41 = 0;				//关闭CMP灯
}
