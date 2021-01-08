#ifndef __PCF8563_H
#define __PCF8563_H
	
#include "sys.h"
#include "delay.h"
#include "hardiic.h"

//设备地址
#define     PCF8563_ADDR_W       0xA2
#define     PCF8563_ADDR_R       0xA3
//寄存器地址
#define     PCF8563_CONTROL_STATUS_1     0x00
#define     PCF8563_CONTROL_STATUS_2     0x01
#define     PCF8563_VL_SECONDS           0x02
#define     PCF8563_MINUTES              0x03
#define     PCF8563_HOURS                0x04
#define     PCF8563_DAYS                 0x05
#define     PCF8563_WEEKDAYS             0x06
#define     PCF8563_CENTURY_MONTHS       0x07
#define     PCF8563_YEARS                0x08
#define     PCF8563_MINUTE_ALARM         0x09       //报警寄存器
#define     PCF8563_HOUR_ALARM           0x0A
#define     PCF8563_DAY_ALARM            0x0B
#define     PCF8563_WEEKDAY_ALARM        0x0C
#define     PCF8563_CLKOUT_CONTROL       0x0D
#define     PCF8563_TIMER_CONTROL        0x0E
#define     PCF8563_TIMER                0x0F

typedef struct{
    uint16 year;
    uint8 month;
    uint8 day;
    uint8 weekday;
    uint8 hour;
    uint8 minute;
    uint8 second;
}pcf8563_Time;

void pcf8563_init();                        // RTC初始化
void pcf8563_read_rtc(pcf8563_Time *tim);   // 读取时间
void pcf8563_write_rtc(pcf8563_Time *tim);  // 设置时间

#endif  //pcf8563.h