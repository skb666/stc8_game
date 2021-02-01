#ifndef __GAME_H
#define __GAME_H

#include "sys.h"
#include "tftlcd.h"
#include <stdlib.h>
#include <string.h>
#include "eeprom.h"

typedef enum{
    S_QUIT,
    S_NORMAL,
    S_PAUSE,
    S_FAIL,
    S_WIN
}gameStatus;

typedef enum{
    SPEED_SLOW,
    SPEED_MEDIUM,
    SPEED_FAST
}gameSpeed;

typedef enum{
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT
}Direction;

typedef struct{
    int16 x, y;
}Axis;

typedef struct Node{
    Axis axis;
    struct Node *next;
}Node, *Snake;

typedef struct{
    int Score, Best;
    gameStatus Status;
    uint16 Target;
    uint16 Data[4][4];
}gameData_2048;

typedef struct{
    int Score, Best;
    gameStatus Status;
    gameSpeed Speed;
    Direction direction;
    uint16 length;
    Axis food;
    Snake snake;
}gameData_snake;

extern gameData_2048 gd_2048;
extern gameData_snake gd_snake;

void game_init();
void readToBuf();
void updateFromBuf();

extern code const uint8 str_2048[];
void game_2048_init();                      // 2048初始化游戏界面
void game_2048_run();                       // 运行游戏
void game_2048_updateStatus(uint8 key);     // 处理输入

extern code const uint8 str_snake[];
void game_snake_init();                     // 贪吃蛇初始化游戏界面
void game_snake_run();                      // 运行游戏

#endif
