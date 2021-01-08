#include "pcf8563.h"

//========================================================================
// 描述: 写多个字节数据.
// 参数: addr:写入的寄存器地址; p:写入的数据; number:需要写的数据个数.
// 返回: none.
//========================================================================
void pcf8563_write_nbyte(uint8 addr, uint8 *p, uint8 number)
{
    hardiic_start();                        //开始信号
    hardiic_send_byte(PCF8563_ADDR_W);      //发送器件写地址
    hardiic_wait_ack();
    hardiic_send_byte(addr);                //发送寄存器地址
    hardiic_wait_ack();
    do
    {
        hardiic_send_byte(*p++);             //发送数据
        hardiic_wait_ack();
    }while(--number);
    hardiic_stop();                          //发送停止命令
}

//========================================================================
// 描述: 读取多个数据.
// 参数: addr:读取的寄存器地址; p:读回来的数据; number:需要读的数据个数.
// 返回: none.
//========================================================================
void pcf8563_read_nbyte(uint8 addr, uint8 *p, uint8 number)
{
    hardiic_start();                        //开始信号
    hardiic_send_byte(PCF8563_ADDR_W);      //发送器件写地址
    hardiic_wait_ack();
    hardiic_send_byte(addr);                //发送寄存器地址
    hardiic_wait_ack();

    hardiic_start();                        //重复开始信号
    hardiic_send_byte(PCF8563_ADDR_W | 0x01);      //发送器件读地址
    hardiic_wait_ack();	
    do
    {
        *p = hardiic_read_byte();
        p++;
        if(number != 1) hardiic_ack();     

    }while(--number);
    hardiic_nack(); 
    hardiic_stop();
}

//========================================================================
// 描述: 初始化.
// 参数: none.
// 返回: none.
//========================================================================
void pcf8563_init()
{
    uint8 vlaue = 0;
    hardiic_init();
    pcf8563_write_nbyte(0,&vlaue,1);
}

//========================================================================
// 描述: 根据年月日获取星期.
// 参数: 年月日.
// 返回: none.
//========================================================================
uint8 get_weekday(uint16 year,uint8 month, uint8 day)
{
    int c,y,w;
    uint8 dow;
  	int m = month;
    int d = day;  // 根据月份对年份和月份进行调整
    if(m <= 2)
    {
        year -= 1;
        m += 12;
    }
    c =year / 100; // 取得年份前两位
    y =year % 100; // 取得年份后两位
    w = (int)(c/4) - 2*c + y + (int)(y/4) + (int)(13*(m+1)/5) + d - 1;   // 根据泰勒公式计算星期
    if((w%7)==0){
       dow=7;
    }else{
      dow=w%7;
    }
    return dow;
}

//========================================================================
// 描述: 读取rtc数据.
// 参数: none.
// 返回: none.
//========================================================================
void pcf8563_read_rtc(pcf8563_Time *tim)
{
    uint8  tmp[7];

    pcf8563_read_nbyte(2, tmp, 7);

    tim->second = ((tmp[0] >> 4) & 0x07) * 10 + (tmp[0] & 0x0f);    //秒钟
    tim->minute = ((tmp[1] >> 4) & 0x07) * 10 + (tmp[1] & 0x0f);    //分钟
    tim->hour   = ((tmp[2] >> 4) & 0x03) * 10 + (tmp[2] & 0x0f);    //小时

    tim->day = ((tmp[3] >> 4) & 0x07) * 10 + (tmp[3] & 0x0f);                //日
    tim->weekday = tmp[4] + 1;                                          //星期
    tim->month = ((tmp[5] >> 4) & 0x07) * 10 + (tmp[5] & 0x0f);              //月
    tim->year = 2000 + ((tmp[6] >> 4) & 0x07) * 10 + (tmp[6] & 0x0f);        //年
}

//========================================================================
// 描述: 写rtc数据.
// 参数: 年，月，日，星期，时，分，秒.
// 返回: none.
//========================================================================
void pcf8563_write_rtc(pcf8563_Time *tim)
{
    uint8  tmp[7];
    tim->year = tim->year - 2000;

    tmp[0] = ((tim->second / 10) << 4) + (tim->second % 10);      //秒
    tmp[1] = ((tim->minute / 10) << 4) + (tim->minute % 10);      //分
    tmp[2] = ((tim->hour / 10) << 4) + (tim->hour % 10);          //小时

    tmp[3] = ((tim->day / 10) << 4) + (tim->day % 10);            //日
    tmp[4] = tim->weekday - 1;                                    //星期
    tmp[5] = ((tim->month / 10) << 4) + (tim->month % 10);        //月
    tmp[6] = ((tim->year / 10) << 4) + (tim->year % 10);          //年

    pcf8563_write_nbyte(2, tmp, 7);
}
