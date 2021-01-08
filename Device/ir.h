#ifndef __IR_H
#define __IR_H

#include <stdio.h>
#include "sys.h"
#include "delay.h"
#include "PWM.h"

#define IR_SEND_PIN 		    P20  //红外发射引脚
#define IR_SEND_PIN_OUT 	    {P2M1&=~0x01;P2M0|=0x01;}  //P20推挽输出
#define IR_SEND_PIN_INIT	    {P2M1|=0x01;P2M0&=~0x01;}   //P20高阻输入
#define IR_SEND_PWM     	    PWM1P_P20  
#define IR_REC_PIN 		        P36
#define IR_REC_PIN_MODE 	    {P3M1|=0x40;P3M0&=~0x40;}  //P36输入

/******************** 红外发射采样时间宏定义, 用户不要随意修改  *******************/
#define NEC_HDR_MARK	7400
#define NEC_HDR_SPACE	3650
#define NEC_BIT_MARK	360
#define NEC_ONE_SPACE	1310
#define NEC_ZERO_SPACE	360

/******************** 红外接收采样时间宏定义, 用户不要随意修改  *******************/
#define SysTick     10000       // 次/秒, 系统滴答频率, 在4000~16000之间
#define IR_SAMPLE_TIME      (1000000UL/SysTick)     //查询时间间隔, us, 红外接收要求在60us~250us之间
#if ((IR_SAMPLE_TIME <= 250) && (IR_SAMPLE_TIME >= 60))
#define D_IR_sample         IR_SAMPLE_TIME      //定义采样时间，在60us~250us之间
#endif

#define D_IR_SYNC_MAX       (15000/D_IR_sample) //SYNC max time
#define D_IR_SYNC_MIN       (9700 /D_IR_sample) //SYNC min time
#define D_IR_SYNC_DIVIDE    (12375/D_IR_sample) //decide data 0 or 1
#define D_IR_DATA_MAX       (3000 /D_IR_sample) //data max time
#define D_IR_DATA_MIN       (600  /D_IR_sample) //data min time
#define D_IR_DATA_DIVIDE    (1687 /D_IR_sample) //decide data 0 or 1
#define D_IR_BIT_NUMBER     32                  //bit number

extern bit _b_ir_press;                 //红外接收标志
extern xdata uint8  _ir_code;           //红外键码
extern xdata uint16 _user_code;         //用户码

void ir_send_nec(uint8 address, uint8 command);     //红外发射

void ir_rx_init();          //红外接收初始化
void ir_rec_callback();     //红外接收回调函数，需要放在100us的中断中，也可以通过宏定义修改
uint8 ir_rx_available();    //是否接收到红外信号
uint8 ir_rx_user_code();    //接收到的用户码
uint8 ir_rx_ircode();       //接收到的键码

#endif  //ir.h