#ifndef __LCD1602_H
#define __LCD1602_H

#include <string.h>
#include <stdio.h>
#include "sys.h"
#include "delay.h"

#define LCD_BUSY        0x80    //用于检测LCD状态字中的LCD_BUSY标识

// IO引脚定义
#define LCD1602_RS 		    P13  
#define LCD1602_RS_OUT 	    {P1M1&=~0x08;P1M0|=0x08;}   //推挽输出
#define LCD1602_RW 		    P10
#define LCD1602_RW_OUT 	    {P1M1&=~0x01;P1M0|=0x01;}   //推挽输出
#define LCD1602_E 		    P11
#define LCD1602_E_OUT 	    {P1M1&=~0x02;P1M0|=0x02;}   //推挽输出
#define LCD1602_Data        P6
#define LCD1602_Data_OUT    {P6M1=0x00;P6M0=0xff;}      //推挽输出

void lcd1602_init();			//1602初始化							
void lcd1602_show_char(uint8 x, uint8 y, char c);	//1602显示一个字符
void lcd1602_show_string(uint8 x, uint8 y, uint8 *str);	//1602显示字符串
void lcd1602_show_num(uint8 x,uint8 y,int num);	//1602显示数字
void lcd1602_clear();//1602清屏

#endif      //LCD1602.h