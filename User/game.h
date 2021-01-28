#ifndef __GAME_H
#define __GAME_H

#include "sys.h"
#include "tftlcd.h"
#include <stdlib.h>
#include "eeprom.h"

typedef enum{
    S_FAIL = 0,
    S_WIN,
    S_NORMAL,
    S_QUIT
}gameStatus;

typedef struct{
    uint16 Data[4][4];
    int Score, Best;
    gameStatus Status;
}gameData_2048;

extern gameData_2048 gd_2048;

void readToBuf();
void updateBuf();

extern code const uint8 str_2048[];
void game_2048_init();                   // 2048初始化游戏界面
void game_2048_run();                    // 运行游戏
void game_2048_updateStatus(uint8 key);  // 处理输入

#endif
