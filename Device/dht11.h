#ifndef __DHT11_H
#define __DHT11_H

#include "sys.h"
#include "delay.h" 
#include <intrins.h>

#define DHT11_DQ       	P46
#define DHT11_DQ_MODE	{P4M1&=~0x40;P4M0&=~0x40;}	//设置P46双向IO口

uint8 dht11_init();			        //DHT11初始化
uint8 dht11_read_data(uint8 *dat);  //读数据
float dht11_read_temp();            //读温度
uint8 dht11_read_humidity();        //读湿度

#endif		//dht11.h