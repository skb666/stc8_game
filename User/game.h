#ifndef __GAME_H
#define __GAME_H

#include "sys.h"
#include "tftlcd.h"
#include <stdlib.h>
#include "eeprom.h"

extern int32 eeprom_buf[10];
void readToBuf();
void updateBuf();

extern code const uint8 str_2048[];
void game2048_init();                   // 2048��ʼ����Ϸ����
void game2048_run();                    // ������Ϸ
void game2048_updateStatus(uint8 key);  // ��������

#endif
