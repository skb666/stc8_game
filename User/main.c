#include "main.h"
#include "game.h"

void main(void){
    pcf8563_Time localtime;

    // 时钟初始化
	InitMCU();
    Timer0_init();
    Timer4_init();
    EA = 1;		        // 中断总开关
    
    // 硬件初始化
    pcf8563_init();     // rtc
    ir_rx_init();       // ir
    tft_lcd_init();     // lcd
    
    // 用RTC时间初始化随机数种子
    pcf8563_read_rtc(&localtime);
    srand(((long *)&localtime)[0]+((long *)&localtime)[1]);
    
    // game预处理
    mempool_init();
    readToBuf();
    
    // 游戏模式选择
    game_mode = G_2048;
    
    // 游戏初始化
    switch(game_mode){
        case G_2048:
            game_2048_init();
            break;
        case G_SNAKE:
            game_snake_init();
            break;
    }
    
    // 主循环
    while(1){
        check_key();
        
        switch(game_mode){
            case G_2048:
                game_2048_run();
                break;
            case G_SNAKE:
                game_snake_run();
                break;
        }
    }
}
