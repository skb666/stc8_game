#ifndef __EEPROM_H
#define __EEPROM_H

#include "sys.h"
#include <intrins.h>

sfr IAP_TPS = 0xf5;

#define     EEPROM_STANDBY()       IAP_CMD = 0     //IAP空闲命令（禁止）
#define     EEPROM_IAP_READ()      IAP_CMD = 1     //IAP读出命令
#define     EEPROM_IAP_WRITE()     IAP_CMD = 2     //IAP写入命令
#define     EEPROM_IAP_ERASE()     IAP_CMD = 3     //IAP擦除命令

#define     EEPROM_IAP_ENABLE()    IAP_CONTR = EEPROM_IAP_EN; IAP_TPS = sys_clk / 1000000
#define     EEPROM_IAP_DISABLE()   IAP_CONTR = 0; IAP_CMD = 0; IAP_TRIG = 0; IAP_ADDRH = 0xff; IAP_ADDRL = 0xff

#define     EEPROM_IAP_EN          (1<<7)
#define     EEPROM_IAP_SWBS        (1<<6)
#define     EEPROM_IAP_SWRST       (1<<5)
#define     EEPROM_IAP_CMD_FAIL    (1<<4)

void eeprom_sector_erase(uint16 EE_address);//EEPROM擦除指定扇区
void eeprom_read(uint16 EE_address,uint8 *DataAddress,uint8 length);//EEPROM读数据
uint8 eeprom_write(uint16 EE_address,uint8 *DataAddress,uint8 length);//EEPROM写数据
float eeprom_read_float(uint16 EE_address);
uint8 eeprom_write_float(uint16 EE_address, float dat);
int eeprom_read_int(uint16 EE_address);
uint8 eeprom_write_int(uint16 EE_address, int dat);

#endif