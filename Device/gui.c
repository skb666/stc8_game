#include "gui.h"

//画圆形指针表盘
//x，y坐标中心点
//size:表盘大小
//d:表盘分割，秒钟的高度
void calendar_circle_clock_drawpanel(uint16 x,uint16 y,uint16 size,uint16 d)
{
	uint16 r=size/2;//得到半径
	uint16 sx=x-r;
	uint16 sy=y-r;
	uint16 px0,px1;
	uint16 py0,py1; 
	uint16 i;

	tft_lcd_draw_circle(x, y, r, TFT_LCD_WHITE, 1);
	tft_lcd_draw_circle(x, y, r-4, TFT_LCD_BLACK, 1);

	for(i=0;i<60;i++)   //画秒钟格
	{ 
		px0=sx+r+(r-4)*sin((app_pi/30)*i); 
		py0=sy+r-(r-4)*cos((app_pi/30)*i); 
		px1=sx+r+(r-d)*sin((app_pi/30)*i); 
		py1=sy+r-(r-d)*cos((app_pi/30)*i);  
		tft_lcd_draw_line1(px0,py0,px1,py1,0, TFT_LCD_WHITE);
	}
	for(i=0;i<12;i++)   //画小时格
	{ 
		px0=sx+r+(r-5)*sin((app_pi/6)*i); 
		py0=sy+r-(r-5)*cos((app_pi/6)*i); 
		px1=sx+r+(r-d)*sin((app_pi/6)*i); 
		py1=sy+r-(r-d)*cos((app_pi/6)*i);  
		tft_lcd_draw_line1(px0,py0,px1,py1,2, TFT_LCD_YELLOW);
	}
	for(i=0;i<4;i++)    //画3小时格
	{ 
		px0=sx+r+(r-5)*sin((app_pi/2)*i); 
		py0=sy+r-(r-5)*cos((app_pi/2)*i); 
		px1=sx+r+(r-d-3)*sin((app_pi/2)*i); 
		py1=sy+r-(r-d-3)*cos((app_pi/2)*i);  
		tft_lcd_draw_line1(px0,py0,px1,py1,2, TFT_LCD_YELLOW);
	}
	//gui_circle(x,y,d/2,WHITE);		//画中心圆
	tft_lcd_draw_circle(x, y, d/2, TFT_LCD_WHITE, 1);
}

//显示时间
//x,y:坐标中心点
//size: 表盘大小
//d:表盘分割，秒钟高度
//hour:时钟
//min:分钟
//sec:秒钟
void calendar_circle_clock_showtime(uint16 x,uint16 y,uint16 size,uint16 d,uint8 hour,uint8 min,uint8 sec)
{
	static uint8 oldhour=0;	//最近一次进入该函数的时分秒信息
	static uint8 oldmin=0;
	static uint8 oldsec=0;
	float temp;
	uint16 r=size/2;           //得到半径 
	uint16 sx=x-r;
	uint16 sy=y-r;
	uint16 px0,px1;
	uint16 py0,py1;  
	uint8 r1; 
	if(hour>11)hour-=12;
///////////////////////////////////////////////
	//清除小时
	r1=d/2+4;
	//清除上一次数据
	temp=(float)oldmin/60;
	temp+=oldhour;
	px0=sx+r+(r-3*d-7)*sin((app_pi/6)*temp); 
	py0=sy+r-(r-3*d-7)*cos((app_pi/6)*temp); 
	px1=sx+r+r1*sin((app_pi/6)*temp); 
	py1=sy+r-r1*cos((app_pi/6)*temp); 
	tft_lcd_draw_line1(px0,py0,px1,py1,2, TFT_LCD_BLACK);
	//清除分钟
	r1=d/2+3;
	temp=(float)oldsec/60;
	temp+=oldmin;
	//清除上一次数据
	px0=sx+r+(r-2*d-7)*sin((app_pi/30)*temp); 
	py0=sy+r-(r-2*d-7)*cos((app_pi/30)*temp); 
	px1=sx+r+r1*sin((app_pi/30)*temp); 
	py1=sy+r-r1*cos((app_pi/30)*temp); 
	tft_lcd_draw_line1(px0,py0,px1,py1,1, TFT_LCD_BLACK);
	//清除秒钟
	r1=d/2+3;
	//清除上一次数据
	px0=sx+r+(r-d-7)*sin((app_pi/30)*oldsec); 
	py0=sy+r-(r-d-7)*cos((app_pi/30)*oldsec); 
	px1=sx+r+r1*sin((app_pi/30)*oldsec); 
	py1=sy+r-r1*cos((app_pi/30)*oldsec); 
	tft_lcd_draw_line1(px0,py0,px1,py1,0, TFT_LCD_BLACK);
///////////////////////////////////////////////
	//显示小时
	r1=d/2+4; 
	//显示新的时钟
	temp=(float)min/60;
	temp+=hour;
	px0=sx+r+(r-3*d-7)*sin((app_pi/6)*temp); 
	py0=sy+r-(r-3*d-7)*cos((app_pi/6)*temp); 
	px1=sx+r+r1*sin((app_pi/6)*temp); 
	py1=sy+r-r1*cos((app_pi/6)*temp); 
	tft_lcd_draw_line1(px0,py0,px1,py1,2, TFT_LCD_YELLOW);
	//显示分钟
	r1=d/2+3; 
	temp=(float)sec/60;
	temp+=min;
	//显示新的分钟
	px0=sx+r+(r-2*d-7)*sin((app_pi/30)*temp); 
	py0=sy+r-(r-2*d-7)*cos((app_pi/30)*temp); 
	px1=sx+r+r1*sin((app_pi/30)*temp); 
	py1=sy+r-r1*cos((app_pi/30)*temp); 
	tft_lcd_draw_line1(px0,py0,px1,py1,1, TFT_LCD_GREEN);
	//显示秒钟
	r1=d/2+3;
	//显示新的秒钟
	px0=sx+r+(r-d-7)*sin((app_pi/30)*sec); 
	py0=sy+r-(r-d-7)*cos((app_pi/30)*sec); 
	px1=sx+r+r1*sin((app_pi/30)*sec); 
	py1=sy+r-r1*cos((app_pi/30)*sec); 
	tft_lcd_draw_line1(px0,py0,px1,py1,0, TFT_LCD_RED);
	oldhour=hour;	//保存时
	oldmin=min;		//保存分
	oldsec=sec;		//保存秒
}	    

//画坐标轴
//x,y中心点位置
//size:轴的间距
//d: 轴的大小
void oscilloscope_axis(uint16 x,uint16 y,uint16 size,uint16 d)
{
	uint16 px0,px1;
	uint16 py0,py1;
	uint16 c1 ,c2;

	//画X轴
	px0 = x;
	py0 = y + d/2;
	py1 = y - d/2;
	c1 = y;	c2 = y;
	tft_lcd_draw_line1(px0,py0,px0,py1,1, TFT_LCD_WHITE);	//画X轴中心点
	while(px0 <= (lcddev.width-size))
	{
		px0 = px0 +size;
		tft_lcd_draw_line1(px0,py0,px0,py1,1, TFT_LCD_WHITE);	//画正x半轴
		while(c1 <= lcddev.height-size*5)
		{
			c1 = c1 + size * 5;
			tft_lcd_draw_circle(px0, c1, 1, TFT_LCD_WHITE, 1);
		}
		while(c2 >= size*5)
		{
			c2 = c2 - size * 5;
			tft_lcd_draw_circle(px0, c2,1, TFT_LCD_WHITE,  1);
			
		}
		c1 = y;
		c2 = y;
	}

	while(px0 >= size){
		px0 = px0 - size;
		tft_lcd_draw_line1(px0,py0,px0,py1,1, TFT_LCD_WHITE);	//画负x半轴
		while(c1 <= lcddev.height-size*5)
		{
			c1 = c1 + size * 5;
			tft_lcd_draw_circle(px0, c1, 1, TFT_LCD_WHITE,  1);
			
		}
		while(c2 >= size*5)
		{
			c2 = c2 - size * 5;
			tft_lcd_draw_circle(px0, c2, 1, TFT_LCD_WHITE, 1);
			
		}
		c1 = y;
		c2 = y;
	}

	//画y轴
	py0 = y;
	px0 = x + d/2;
	px1 = x - d/2;
	c1 = x;	c2 = x;
	tft_lcd_draw_line1(px0,py0,px1,py0,1, TFT_LCD_WHITE);	//画Y轴中心点
	while(py0 <= lcddev.height-size)
	{
		py0 = py0 +size;
		tft_lcd_draw_line1(px0,py0,px1,py0,1, TFT_LCD_WHITE);	//画正Y半轴
		while(c1 <= lcddev.width-size*5)
		{
			c1 = c1 + size * 5;
			tft_lcd_draw_circle(c1, py0, 1, TFT_LCD_WHITE, 1);
			
		}
		while(c2 >= size*5)
		{	
			c2 = c2 - size * 5;
			tft_lcd_draw_circle(c2, py0, 1, TFT_LCD_WHITE, 1);
		}
		c1 = x;
		c2 = x;
	}

	while(py0 >= size){
		py0 = py0 - size;
		tft_lcd_draw_line1(px0,py0,px1,py0,1, TFT_LCD_WHITE);	//画负Y半轴
		while(c1 <= lcddev.width-size*5)
		{
			c1 = c1 + size * 5;
			tft_lcd_draw_circle(c1, py0, 1, TFT_LCD_WHITE, 1);
			
		}
		while(c2 >= size*5)
		{
			c2 = c2 - size*5;
			tft_lcd_draw_circle(c2, py0, 1, TFT_LCD_WHITE, 1);
		}
		c1 = x;
		c2 = x;
	}
}

//画正弦函数
void oscilloscope_sin()
{
	uint16 i,tem_color;
	int y;
	int k;
	tem_color = _tft_lcd_point_color;
	for(i=0; i<339;i++){
		y = 30*sin(i/20.0);
		_tft_lcd_point_color = TFT_LCD_YELLOW;
		tft_lcd_draw_point((u16)y+161,i);
		tft_lcd_draw_point((u16)y+160,i);
		tft_lcd_draw_point((u16)y+159,i);

		k = 30*cos(i/20.0);
		_tft_lcd_point_color = TFT_LCD_GBLUE;
		tft_lcd_draw_point((u16)k+41,i);
		tft_lcd_draw_point((u16)k+40,i);
		tft_lcd_draw_point((u16)k+39,i);
		delay(10);
	}
	_tft_lcd_point_color = tem_color;
}
