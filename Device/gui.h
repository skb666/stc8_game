#ifndef __GUI_H
#define __GUI_H	

#include "sys.h"
#include <math.h>
#include "delay.h"
#include "tftlcd.h"

#define  u16   uint16
#define  u8    uint8

#define	app_pi	3.141592654

void calendar_circle_clock_drawpanel(uint16 x,uint16 y,uint16 size,uint16 d);  //画时钟表盘
void calendar_circle_clock_showtime(uint16 x,uint16 y,uint16 size,uint16 d,uint8 hour,uint8 min,uint8 sec); //显示时间
void oscilloscope_axis(uint16 x,uint16 y,uint16 size,uint16 d);		//画示波器坐标轴
void oscilloscope_sin();		//产生正弦波

#endif      //gui.c