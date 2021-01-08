#ifndef __OLED_H
#define __OLED_H

#include "sys.h"
#include "delay.h"
#include "hardiic.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define OLED_ADDR   0x78 //写地址
#define OLED_CMD    0	//写命令
#define OLED_DATA   1	//写数据
#define OLED_MODE   0

#define OLED_MAX_COLUMN	    128
#define OLED_MAX_ROW		32

static uint8 xdata _oled_disbuffer[128][4];

void oled_init();	//初始化OLED
void oled_display_off();	//关闭OLED显示
void oled_display_on();     //开启OLED显示
void oled_display();		//缓存显示
void oled_clear();	//清屏
void oled_set_pixel(uint8 x, uint8 y,uint8 pixel);	//在指定位置显示一个点
//X 个像素点，y行
void oled_show_char(int8 x,int8 y,uint8 chr);	//在指定位置显示一个字符  字符高8，宽5
void oled_show_string(int8 x,int8 y,uint8 *chr); //在指定位置显示字符串 字符高8，间距8
void oled_show_num(int8 x,int8 y,int16 num);	//在指定位置显示字符串 字符高8，间距8
void oled_show_font12(uint8 lenth,const uint8* hz,int x,int y);	//在指定位置显示12x12汉字
void oled_show_font16(uint8 lenth,const uint8* hz,int x,int y);	//在指定位置显示16x16汉字
void oled_show_font24(uint8 lenth,const uint8* hz,int x,int y);	//在指定位置显示24x24汉字
void oled_show_font32(uint8 lenth, const uint8* hz, int x, int y);	//在指定位置显示32x32汉字
void oled_show_bmp(uint8 x0, uint8 y0,uint8 x1, uint8 y1,uint8* BMP);	//显示BMP图片

#endif  //oled.h
