#ifndef __TFTLCD_H
#define __TFTLCD_H	

#include "sys.h"
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include <stdlib.h>
#include <intrins.h>

/////////////////////////////////////用户配置区///////////////////////////////////	 
//支持横竖屏快速定义切换
#define TFT_LCD_USE_HORIZONTAL	    0   //定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转
#define TFT_LCD_USE_8BIT_MODEL   	1 	//定义数据总线是否使用8位模式 0,使用16位模式.1,使用8位模式
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////	  
//定义LCD的尺寸
#define TFT_LCD_LCD_W 240
#define TFT_LCD_LCD_H 320

//IO连接
#define TFT_LCD_DATAPORTH 			P6     //高8位数据口,8位模式下只使用高8位 
#define TFT_LCD_DATAPORTH_IN	 	{ P6M1=0xff;P6M0=0x00;}		//P6口高阻输入
#define TFT_LCD_DATAPORTH_OUT	 	{ P6M1=0x00;P6M0=0xff;}		//P6口推挽输出
#define TFT_LCD_DATAPORTL 			P2     //低8位数据口,8位模式下只使用高8位
#define TFT_LCD_RESET 				P15
#define TFT_LCD_RESET_OUT			{P1M1&=~0x20;P1M0|=0x20;}	//推挽输出
#define TFT_LCD_CS 					P13
#define TFT_LCD_CS_OUT			    {P1M1&=~0x08;P1M0|=0x08;}	//推挽输出
#define TFT_LCD_RS 					P03
#define TFT_LCD_RS_OUT			    {P0M1&=~0x08;P0M0|=0x08;}	//推挽输出
#define TFT_LCD_WR 					P11
#define TFT_LCD_WR_OUT  			{P1M1&=~0x02;P1M0|=0x02;}	//推挽输出
#define TFT_LCD_RD 					P10
#define TFT_LCD_RD_OUT   			{P1M1&=~0x01;P1M0|=0x01;}	//推挽输出

//LCD的画笔颜色和背景色	   
extern uint16  _tft_lcd_point_color;//默认红色    
extern uint16  _tft_lcd_back_color; //背景颜色.默认为白色
//LCD重要参数集
typedef struct
{
	uint16 width;			//LCD 宽度
	uint16 height;			//LCD 高度
	uint16 id;				//LCD ID
	uint8  dir;				//横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16	wramcmd;		//开始写gram指令
	uint16  rramcmd;   		//开始读gram指令
	uint16  setxcmd;		//设置x坐标指令
	uint16  setycmd;		//设置y坐标指令	 
}_lcd_dev;
extern _lcd_dev lcddev;

void tft_lcd_init();	//初始化
void tft_lcd_clear(uint16 color);	//清屏
void tft_lcd_set_cursor(uint16 x, uint16 y);	//设置光标位置
void tft_lcd_set_windows(uint16 x0, uint16 y0, uint16 x1, uint16 y1);	//设置显示窗口
void tft_lcd_draw_point(uint16 x, uint16 y);	//画点
uint16 tft_lcd_read_point(uint16 x, uint16 y);	//读点
void tft_lcd_direction(uint8 direction);  //屏幕旋转
uint16 tft_lcd_read_id();	//读取ID号
void tft_lcd_fill(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint16 color);	//填充
void tft_lcd_draw_line(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint16 color);	//画线
void tft_lcd_draw_line1(uint16 x0,uint16 y0,uint16 x1,uint16 y1,uint8 size,uint16 color); //画粗线
void tft_lcd_draw_rectangle(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint16 color);	//绘制矩形框
void tft_lcd_fill_rectangle(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint16 color);	//填充矩形
void tft_lcd_draw_circle(int xc, int yc, int r, uint16 color, uint8 fill);	//画圆
void tft_lcd_draw_triangel(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color);	//绘制三角形
void tft_lcd_fill_triangel(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color);	//填充三角形
void tft_lcd_show_char(int16 x,int16 y, uint8 chr, uint16 font_color, uint16 background_color, uint8 msize,uint8 mode);	//显示一个字符
void tft_lcd_show_string(int16 x,int16 y,uint8 *p,uint16 font_color, uint16 background_color,uint8 msize,uint8 mode);	//显示字符串
void tft_lcd_show_num(int16 x,int16 y,int num,uint16 font_color, uint16 background_color,uint8 msize, uint8 mode);	//显示数字
void tft_lcd_show_font12(uint8 lenth, uint8 *hz, int16 x, int16 y,uint16 font_color, uint16 background_color, uint8 mode);	//显示12x12汉字
void tft_lcd_show_font16(uint8 lenth, uint8 *hz, int16 x, int16 y,uint16 font_color, uint16 background_color, uint8 mode);	//显示16x16汉字
void tft_lcd_show_font24(uint8 lenth, uint8 *hz, int16 x, int16 y,uint16 font_color, uint16 background_color, uint8 mode);	//显示24x24汉字
void tft_lcd_show_font32(uint8 lenth, uint8 *hz, int16 x, int16 y,uint16 font_color, uint16 background_color, uint8 mode);	//显示32x32汉字
void tft_lcd_draw_bmp16(uint16 x0,uint16 y0,uint16 w,uint16 h,const uint8 *p);	//显示bmp图像

//颜色
#define TFT_LCD_WHITE         	 0xFFFF //白色
#define TFT_LCD_BLACK         	 0x0000 //黑色
#define TFT_LCD_BLUE             0x001F //蓝色
#define TFT_LCD_BRED             0XF81F //紫色
#define TFT_LCD_GBLUE            0X07FF //蓝绿色
#define TFT_LCD_RED           	 0xF800 //红色
#define TFT_LCD_MAGENTA       	 0xF81F //粉色
#define TFT_LCD_GREEN         	 0x07E0 //绿色
#define TFT_LCD_CYAN          	 0x7FFF //青色
#define TFT_LCD_YELLOW        	 0xFFE0 //黄色
#define TFT_LCD_BROWN            0XBC40 //棕色
#define TFT_LCD_BRRED            0XFC07 //棕红色
#define TFT_LCD_GRAY             0X8430 //灰色
#define TFT_LCD_DARKBLUE      	 0X01CF	//深蓝色
#define TFT_LCD_LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define TFT_LCD_GRAYBLUE       	 0X5458 //灰蓝色
#define TFT_LCD_LIGHTGREEN     	 0X841F //浅绿色
#define TFT_LCD_LGRAY            0XC618 //浅灰色(PANNEL),窗体背景色
#define TFT_LCD_LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define TFT_LCD_LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#endif  //tftlcd.h

