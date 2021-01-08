#include "touch.h"

//========================================================================
// 描述: 读取X坐标.
// 参数: none.
// 返回: 读到的坐标.
//========================================================================
uint16 touch_read_raw_x()
{
	uint16 i, j;
	uint16 buf[TOUCH_READ_TIMES];
	uint16 sum=0;
	uint16 temp;
	if(lcddev.id == 0x9341)
	{
		LCD9341_SET_XM_OUT;
		LCD9341_SET_XP_OUT;
		LCD9341_SET_YP_IN;   
		LCD9341_SET_YM_IN;
		LCD9341_TOUCH_XP_PIN = 1;
		LCD9341_TOUCH_YP_PIN = 0;
		LCD9341_TOUCH_YM_PIN = 0;
		LCD9341_TOUCH_XM_PIN = 0;
		adc_init(LCD9341_YP_ADC_PIN, ADC_SYSclk_DIV_2, ADC_12BIT);
		for(i=0;i<TOUCH_READ_TIMES;i++)buf[i]=adc_read(LCD9341_YP_ADC_PIN); 		    
		for(i=0;i<TOUCH_READ_TIMES-1; i++)//排序
		{
			for(j=i+1;j<TOUCH_READ_TIMES;j++)
			{
				if(buf[i]>buf[j])//升序排列
				{
					temp=buf[i];
					buf[i]=buf[j];
					buf[j]=temp;
				}
			}
		}	 
		sum=0;
		for(i=TOUCH_LOST_VAL;i<TOUCH_READ_TIMES-TOUCH_LOST_VAL;i++)sum+=buf[i];
		temp=sum/(TOUCH_READ_TIMES-2*TOUCH_LOST_VAL);
		LCD9341_SET_YP_OUT;
		LCD9341_SET_YM_OUT;
		return temp;
	}
	else
	{
		SM245_SET_XM_OUT;
		SM245_SET_XP_OUT;
		SM245_SET_YP_IN;   
		SM245_SET_YM_IN;
		SM245_TOUCH_XP_PIN = 1;
		SM245_TOUCH_YP_PIN = 0;
		SM245_TOUCH_YM_PIN = 0;
		SM245_TOUCH_XM_PIN = 0;
		adc_init(SM245_YP_ADC_PIN, ADC_SYSclk_DIV_2, ADC_12BIT);
		for(i=0;i<TOUCH_READ_TIMES;i++)buf[i]=adc_read(SM245_YP_ADC_PIN); 		    
		for(i=0;i<TOUCH_READ_TIMES-1; i++)//排序
		{
			for(j=i+1;j<TOUCH_READ_TIMES;j++)
			{
				if(buf[i]>buf[j])//升序排列
				{
					temp=buf[i];
					buf[i]=buf[j];
					buf[j]=temp;
				}
			}
		}	 
		sum=0;
		for(i=TOUCH_LOST_VAL;i<TOUCH_READ_TIMES-TOUCH_LOST_VAL;i++)sum+=buf[i];
		temp=sum/(TOUCH_READ_TIMES-2*TOUCH_LOST_VAL);
		SM245_SET_YP_OUT;
		SM245_SET_YM_OUT;
		return temp;
	}
}

//========================================================================
// 描述: 读取Y坐标.
// 参数: none.
// 返回: 读到的坐标.
//========================================================================
uint16 touch_read_raw_y()
{
	uint16 i, j;
	uint16 buf[TOUCH_READ_TIMES];
	uint16 sum=0;
	uint16 temp;
	if(lcddev.id == 0x9341)
	{
		LCD9341_SET_YP_OUT;
		LCD9341_SET_YM_OUT;
		LCD9341_SET_XP_IN;   
		LCD9341_SET_XM_IN;
		LCD9341_TOUCH_YP_PIN = 1;
		LCD9341_TOUCH_YM_PIN = 0;
		LCD9341_TOUCH_XP_PIN = 0;
		LCD9341_TOUCH_XM_PIN = 0;
	
		adc_init(LCD9341_XM_ADC_PIN, ADC_SYSclk_DIV_2, ADC_12BIT);

		for(i=0;i<TOUCH_READ_TIMES;i++)buf[i]=adc_read(LCD9341_XM_ADC_PIN); 		    
		for(i=0;i<TOUCH_READ_TIMES-1; i++)//排序
		{
			for(j=i+1;j<TOUCH_READ_TIMES;j++)
			{
				if(buf[i]>buf[j])//升序排列
				{
					temp=buf[i];
					buf[i]=buf[j];
					buf[j]=temp;
				}
			}
		}	 
		sum=0;
		for(i=TOUCH_LOST_VAL;i<TOUCH_READ_TIMES-TOUCH_LOST_VAL;i++)sum+=buf[i];
		temp=sum/(TOUCH_READ_TIMES-2*TOUCH_LOST_VAL);
		LCD9341_SET_XM_OUT;
		LCD9341_SET_XP_OUT;
		return temp;
	}
	else
	{
		SM245_SET_YP_OUT;
		SM245_SET_YM_OUT;
		SM245_SET_XP_IN;   
		SM245_SET_XM_IN;
		SM245_TOUCH_YP_PIN = 1;
		SM245_TOUCH_YM_PIN = 0;
		SM245_TOUCH_XP_PIN = 0;
		SM245_TOUCH_XM_PIN = 0;
	
		adc_init(SM245_XM_ADC_PIN, ADC_SYSclk_DIV_2, ADC_12BIT);

		for(i=0;i<TOUCH_READ_TIMES;i++)buf[i]=adc_read(SM245_XM_ADC_PIN); 		    
		for(i=0;i<TOUCH_READ_TIMES-1; i++)//排序
		{
			for(j=i+1;j<TOUCH_READ_TIMES;j++)
			{
				if(buf[i]>buf[j])//升序排列
				{
					temp=buf[i];
					buf[i]=buf[j];
					buf[j]=temp;
				}
			}
		}	 
		sum=0;
		for(i=TOUCH_LOST_VAL;i<TOUCH_READ_TIMES-TOUCH_LOST_VAL;i++)sum+=buf[i];
		temp=sum/(TOUCH_READ_TIMES-2*TOUCH_LOST_VAL);
		SM245_SET_XM_OUT;
		SM245_SET_XP_OUT;
		return temp;
	}
}

//========================================================================
// 描述: 读取触摸的压力值.
// 参数: none.
// 返回: 读到的压力值.
//========================================================================
uint16 touch_read_pressure()
{
    int z1,z2;
	if(lcddev.id == 0x9341)
	{
		LCD9341_SET_XP_OUT;
		LCD9341_SET_YM_OUT;
		LCD9341_SET_XM_IN;
		LCD9341_SET_YP_IN;
		LCD9341_TOUCH_XP_PIN = 0;
		LCD9341_TOUCH_YM_PIN = 1; 
		LCD9341_TOUCH_XM_PIN = 0;
		LCD9341_TOUCH_YP_PIN = 0;

		adc_init(LCD9341_XM_ADC_PIN, ADC_SYSclk_DIV_2, ADC_12BIT);
		adc_init(LCD9341_YP_ADC_PIN, ADC_SYSclk_DIV_2, ADC_12BIT);

		z1 = adc_read(LCD9341_XM_ADC_PIN); 
		z2 = adc_read(LCD9341_YP_ADC_PIN);

		LCD9341_SET_XM_OUT;
		LCD9341_SET_YP_OUT;
		LCD9341_TOUCH_YP_PIN = 1;
		LCD9341_TOUCH_XM_PIN = 1;
		return (4095 - (z2-z1));
	}
	else
	{
		SM245_SET_XP_OUT;
		SM245_SET_YM_OUT;
		SM245_SET_XM_IN;
		SM245_SET_YP_IN;
		SM245_TOUCH_XP_PIN = 0;
		SM245_TOUCH_YM_PIN = 1; 
		SM245_TOUCH_XM_PIN = 0;
		SM245_TOUCH_YP_PIN = 0;

		adc_init(SM245_XM_ADC_PIN, ADC_SYSclk_DIV_2, ADC_12BIT);
		adc_init(SM245_YP_ADC_PIN, ADC_SYSclk_DIV_2, ADC_12BIT);

		z1 = adc_read(SM245_XM_ADC_PIN); 
		z2 = adc_read(SM245_YP_ADC_PIN);

		SM245_SET_XM_OUT;
		SM245_SET_YP_OUT;
		SM245_TOUCH_YP_PIN = 1;
		SM245_TOUCH_XM_PIN = 1;
		return (4095 - (z2-z1));
	}
}

//========================================================================
// 描述: 通过2次采样误差得到更准确的坐标值.
// 参数: x,y:采样得到的物理坐标.
// 返回: 误差在50以内返回1，否则返回0.
//========================================================================
#define ERR_RANGE 	50      //误差范围 
uint8 tp_read_xy2(uint16 *x,uint16 *y) 
{
	uint16 x1,y1;
 	uint16 x2,y2;

	x1 = touch_read_raw_x();
	y1 = touch_read_raw_y();
	x2 = touch_read_raw_x();
	y2 = touch_read_raw_y();

    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后2次采样误差在50以内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
} 

//========================================================================
// 描述: 画一个触摸点.
// 参数: x,y:坐标; color:颜色值.
// 返回: none.
//========================================================================
void tp_drow_touch_point(uint16 x,uint16 y,uint16 color)
{
	_tft_lcd_point_color = color;
	tft_lcd_draw_line(x-12,y,x+13,y,color);    //横线
	tft_lcd_draw_line(x,y-12,x,y+13,color);    //竖线
	tft_lcd_draw_point(x+1,y+1);
	tft_lcd_draw_point(x-1,y+1);
	tft_lcd_draw_point(x+1,y-1);
	tft_lcd_draw_point(x-1,y-1);
	tft_lcd_draw_circle(x,y,6,color,0);         //画中心圈
}

//触摸屏控制器
typedef struct
{		
	uint16 x;      	
	uint16 y;		
	uint8  sta;	              		
    /////////////////////触摸屏校准参数//////////////////////								
	float xfac;					
	float yfac;
	int xoff;
	int yoff;	   

	uint8 touchtype;	//屏幕方向
}_m_tp_dev;

_m_tp_dev tp_dev=
{
	0,
	0, 
	0,
	0,
	0,
	0,	  	 		
	0,
	0	  	 		
};

//========================================================================
// 描述: 触摸校准程序.
// 参数: none.
// 返回: none.
//========================================================================
void touch_adjust()
{
	uint16 pos_temp[4][2];//坐标缓冲值
	uint8  cnt=0;	
	uint16 d1,d2;
	uint32 tem1,tem2;
	float fac; 	
	uint16 outtime=0;
 	cnt=0;				
	_tft_lcd_point_color=TFT_LCD_BLUE;
	_tft_lcd_back_color =TFT_LCD_WHITE;
	tft_lcd_clear(TFT_LCD_WHITE);   //清屏 
	_tft_lcd_point_color=TFT_LCD_RED;    //红色
	tft_lcd_clear(TFT_LCD_WHITE);   //清屏   
	_tft_lcd_point_color=TFT_LCD_BLACK;
	tft_lcd_show_string(70,40,"touch adjust",TFT_LCD_RED,TFT_LCD_WHITE,16,1);//显示提示信息
	tp_drow_touch_point(20,20,TFT_LCD_RED);     //画点1
	tp_dev.sta=0;       //消除触发信号 
	tp_dev.xfac=0;      //xfac清除校准标志	
    while(1)            //如果连续10s没有按下，则自动退出
    {
        if( tp_read_xy2(&tp_dev.x,&tp_dev.y) && touch_read_pressure() > 100)     //代表有按键按下
        {
            outtime = 0;
          	tp_dev.sta=1;       //标记按键已经被处理过了

			if(lcddev.id == 0x9341)
			{
				pos_temp[cnt][0] = tp_dev.y;
				pos_temp[cnt][1] = tp_dev.x; 		
			}
			else if(lcddev.id == 0x9340)
			{
				pos_temp[cnt][0] = tp_dev.y;
				pos_temp[cnt][1] = tp_dev.x; 
			}
			else if(tp_dev.touchtype == 0)
			{
				pos_temp[cnt][0] = 4095 - tp_dev.y;
				pos_temp[cnt][1] = 4095 - tp_dev.x; 
			}
			else if(tp_dev.touchtype == 1)
			{
				pos_temp[cnt][0] = tp_dev.y;
				pos_temp[cnt][1] = tp_dev.x; 
			}
            cnt++;
            switch(cnt)
			{			   
				case 1:						 
					tp_drow_touch_point(20,20,TFT_LCD_WHITE);				//清除点1
					tp_drow_touch_point(lcddev.width-20,20,TFT_LCD_RED);	//画点2
					break;
				case 2:
 					tp_drow_touch_point(lcddev.width-20,20,TFT_LCD_WHITE);	//清除点2
					tp_drow_touch_point(20,lcddev.height-20,TFT_LCD_RED);	//画点3
					break;
				case 3:
 					tp_drow_touch_point(20,lcddev.height-20,TFT_LCD_WHITE);			//清除点3
 					tp_drow_touch_point(lcddev.width-20,lcddev.height-20,TFT_LCD_RED);	//画点4
					break;
				case 4:	 //全部4个点已经得到
	    		    //对边相等
					tem1=fabs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
					tem2=fabs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);     //得到1，2的距离
					
					tem1=fabs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
					tem2=fabs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到3，4的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05||d1==0||d2==0)//不合格
					{
						cnt=0;
 				    	tp_drow_touch_point(lcddev.width-20,lcddev.height-20,TFT_LCD_WHITE);	//清除点4
   	 					tp_drow_touch_point(20,20,TFT_LCD_RED);								//画点一 
 						continue;
					}
					tem1=fabs(pos_temp[0][0]-pos_temp[2][0]);    //x1-x3
					tem2=fabs(pos_temp[0][1]-pos_temp[2][1]);    //y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1，3的距离
					
					tem1=fabs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
					tem2=fabs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到2，4的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
 				    	tp_drow_touch_point(lcddev.width-20,lcddev.height-20,TFT_LCD_WHITE);	//清除点4
   	 					tp_drow_touch_point(20,20,TFT_LCD_RED);								//画点1
						continue;
					}//正确了
								   
					//对角线相等
					tem1=fabs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
					tem2=fabs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);    //得到1，4的距离
	
					tem1=fabs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
					tem2=fabs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到2，3的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
 				    	tp_drow_touch_point(lcddev.width-20,lcddev.height-20,TFT_LCD_WHITE);	//清除点4
   	 					tp_drow_touch_point(20,20,TFT_LCD_RED);								//画点1
						continue;
					}//正确了
					//计算结果
					tp_dev.xfac=(float)(lcddev.width-40)/(pos_temp[1][0]-pos_temp[0][0]);//得到xfac		 
					tp_dev.xoff=(lcddev.width-tp_dev.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//得到xoff
						  
					tp_dev.yfac=(float)(lcddev.height-40)/(pos_temp[2][1]-pos_temp[0][1]);//得到yfac
					tp_dev.yoff=(lcddev.height-tp_dev.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//得到yoff  
					if(fabs(tp_dev.xfac)>2||fabs(tp_dev.yfac)>2)//触屏和预设的相反了
					{
						cnt=0;
 				    	tp_drow_touch_point(lcddev.width-20,lcddev.height-20,TFT_LCD_WHITE);	//清除点4
   	 					tp_drow_touch_point(20,20,TFT_LCD_RED);								//画点1
						tft_lcd_show_string(40,26,"TP Need readjust!",TFT_LCD_RED,TFT_LCD_WHITE,16,1);
						if(lcddev.id == 0x9340)
						{
							lcddev.id = 0;
							tp_dev.touchtype = 0;
						}
						//tp_dev.touchtype=!tp_dev.touchtype;//修改触屏类型		    
						continue;
					}		
					_tft_lcd_point_color=TFT_LCD_BLUE;
					tft_lcd_clear(TFT_LCD_WHITE);//清屏
					tft_lcd_show_string(35,110,"Touch Screen Adjust OK!",TFT_LCD_RED,TFT_LCD_WHITE,16,1);//校正完成
					delay(200);
					//把校准数据写入触摸屏
                    eeprom_sector_erase(TOUCH_EEPROM_ADDR);
    				eeprom_write_float(TOUCH_EEPROM_ADDR,tp_dev.xfac);
					eeprom_write_float(TOUCH_EEPROM_ADDR+sizeof(float),tp_dev.yfac);
					eeprom_write_int(TOUCH_EEPROM_ADDR+2*sizeof(float),tp_dev.xoff);
					eeprom_write_int(TOUCH_EEPROM_ADDR+2*sizeof(float)+sizeof(int),tp_dev.yoff);

 					tft_lcd_clear(TFT_LCD_WHITE);//清屏  
					return;//校正完成				 
			}
            while(touch_read_pressure() > 100);
		}
		delay(10);
		outtime++;
		if(outtime>1000)
		{
            tft_lcd_clear(TFT_LCD_WHITE);
			//从存储器中得到校准数据
            tp_dev.xfac = eeprom_read_float(TOUCH_EEPROM_ADDR);
			tp_dev.yfac = eeprom_read_float(TOUCH_EEPROM_ADDR+sizeof(float));
			tp_dev.xoff = eeprom_read_int(TOUCH_EEPROM_ADDR+2*sizeof(float));
			tp_dev.yoff = eeprom_read_int(TOUCH_EEPROM_ADDR+2*sizeof(float)+sizeof(int));
			return;
	 	} 
 	}            
}

//========================================================================
// 描述: 触摸的初始化函数.
// 参数: t:0,不进入校准程序;其他值:进入校准程序.
// 返回: none.
//========================================================================
void touch_init(uint8 t)
{
	if(t == 0)	//直接从eeprom中获取校准数据
	{
		tp_dev.xfac = eeprom_read_float(TOUCH_EEPROM_ADDR);
		tp_dev.yfac = eeprom_read_float(TOUCH_EEPROM_ADDR+sizeof(float));
		tp_dev.xoff = eeprom_read_int(TOUCH_EEPROM_ADDR+2*sizeof(float));
		tp_dev.yoff = eeprom_read_int(TOUCH_EEPROM_ADDR+2*sizeof(float)+sizeof(int));		
	}else{
		touch_adjust();	//进入校准程序
	}
}

//========================================================================
// 描述: 读取触摸的坐标以及压力值.
// 参数: none.
// 返回: 读到的坐标.
//========================================================================
void touch_get_point(uint16 *tspoint)
{
 	uint16 x,y;
	tp_read_xy2(&x,&y);
	if(lcddev.id == 0x9341)
	{
		//读取X坐标
		tspoint[0] = tp_dev.xfac*(y)+tp_dev.xoff;	
		//读取Y坐标
		tspoint[1] = tp_dev.yfac*(x)+tp_dev.yoff;	
	}
	else if(lcddev.id == 0x9340)
	{
		//读取X坐标
		tspoint[0] = tp_dev.xfac*(y)+tp_dev.xoff;	
		//读取Y坐标
		tspoint[1] = tp_dev.yfac*(x)+tp_dev.yoff;	
	}

	else if(tp_dev.touchtype == 0)
	{
		//读取X坐标
		tspoint[0] = tp_dev.xfac*(4095 - y)+tp_dev.xoff;	
		//读取Y坐标
		tspoint[1] = tp_dev.yfac*(4095 - x)+tp_dev.yoff;
	}
	else if(tp_dev.touchtype == 1)
	{
		//读取X坐标
		tspoint[0] = tp_dev.xfac*(4095 - x)+tp_dev.xoff;	
		//读取Y坐标
		tspoint[1] = tp_dev.yfac*(4095 - y)+tp_dev.yoff;	
	}

    //读取压力
    tspoint[2] = touch_read_pressure();
}

//========================================================================
// 描述: 读取触摸的x坐标.
// 参数: none.
// 返回: 读到的坐标.
//========================================================================
uint16 touch_read_x()	//读取X的坐标
{
	uint16 x,y;
	tp_read_xy2(&x,&y);
	if(lcddev.id == 0x9341)
	{
		//读取X坐标
		return (tp_dev.xfac*(y)+tp_dev.xoff);	
	}
	else if(tp_dev.touchtype == 0)
	{
		//读取X坐标
		return (tp_dev.xfac*(4095 - y)+tp_dev.xoff);	
	}
	else if(tp_dev.touchtype == 1)
	{
		//读取X坐标
		return (tp_dev.xfac*(4095 - x)+tp_dev.xoff);		
	}
	return 0;
}

//========================================================================
// 描述: 读取触摸的y坐标.
// 参数: none.
// 返回: 读到的坐标.
//========================================================================
uint16 touch_read_y()	//读取Y的坐标
{
	uint16 x,y;
	tp_read_xy2(&x,&y);
	if(lcddev.id == 0x9341)
	{
		//读取Y坐标
		return (tp_dev.yfac*(x)+tp_dev.yoff);	
	}
	else if(tp_dev.touchtype == 0)
	{	
		//读取Y坐标
		return (tp_dev.yfac*(4095 - x)+tp_dev.yoff);
	}
	else if(tp_dev.touchtype == 1)
	{
		//读取Y坐标
		return (tp_dev.yfac*(4095 - y)+tp_dev.yoff);		
	}
	return 0;
}
