#ifndef __HARDIIC_H
#define __HARDIIC_H

#include "sys.h"
#include "delay.h"

#define  HARDIIC_IICX         0x80                       //将IIC设置为P1_5,P1_4
#define  HARDIIC_SCL_OUT      {P1M1|=0x20;P1M0|=0x20;}   //开漏输出
#define  HARDIIC_SDA_OUT      {P1M1|=0x10;P1M0|=0x10;}   //开漏输出

void hardiic_start();
void hardiic_wait();
void hardiic_stop();
uint8 hardiic_wait_ack();
void hardiic_ack();
void hardiic_nack();
void hardiic_send_byte(uint8 iic_data);
uint8 hardiic_read_byte();

void hardiic_init();
void hardiic_read_nbyte(uint8 device_addr, uint8 reg_addr, uint8 *p, uint8 number);
void hardiic_write_nbyte(uint8 device_addr, uint8 reg_addr, uint8 *p, uint8 number);

#endif          //hardiic