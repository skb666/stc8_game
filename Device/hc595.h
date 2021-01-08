#ifndef _HC595_H
#define _HC595_H	
	
#include "sys.h"

/*引脚定义*/
#define 		HC595_DS           P44        //SI
#define         HC595_DS_MODE      {P4M1&=~0x10;P4M0|=0x10;}	//推挽输出

#define 		HC595_STCP          P43        //RCK
#define         HC595_STCP_MODE     {P4M1&=~0x08;P4M0|=0x08;}	//推挽输出

#define 		HC595_SHCP          P42        //SCK
#define         HC595_SHCP_MODE     {P4M1&=~0x04;P4M0|=0x04;}	//推挽输出

void hc595_init();                  //595初始化
void hc595_disable();               //595输出禁止
void hc595_enable_nix();            //595使能数码管
void hc595_enable_matrix();         //595使能点阵
void hc595_bit_select(uint8 index); //595发送位选
void hc595_bit_disable();			//消影

#endif

