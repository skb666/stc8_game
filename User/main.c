#include "main.h"
#include "game.h"

uint8 B_100us = 0;
uint8 B_1ms = 0;
uint8 B_50ms = 0;

void main(void){
    pcf8563_Time localtime;
    uint8 sign_ir = 0;
    int8 sign_key = -1;
    uint8 cnt = 0;

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
    
    // test_code
    game_snake_init();
    while(1){
        // 红外输入
        if(B_100us){
            B_100us = 0;
            if(ir_rx_available()){
                // 红外接收
                sign_ir = ir_rx_ircode();
            }
        }
        if(sign_ir){
            switch(sign_ir){
                case 17:
                    game_snake_updateStatus('w');
                    break;
                case 25:
                    game_snake_updateStatus('s');
                    break;
                case 20:
                    game_snake_updateStatus('a');
                    break;
                case 22:
                    game_snake_updateStatus('d');
                    break;
                case 12:
                    game_snake_updateStatus('q');
                    break;
                case 14:
                    game_snake_updateStatus('r');
                    break;
                case 21:
                    game_snake_updateStatus('c');
                    break;
                case 4:
                    game_snake_updateStatus(SPEED_SLOW);
                    break;
                case 5:
                    game_snake_updateStatus(SPEED_MEDIUM);
                    break;
                case 6:
                    game_snake_updateStatus(SPEED_FAST);
                    break;
            }
            sign_ir = 0;
        }
        if(B_50ms){
            B_50ms = 0;
            switch(gd_snake.Speed){
                case SPEED_SLOW:
                    if(++cnt >= 10){
                        cnt = 0;
                        game_snake_run();
                    }
                    break;
                case SPEED_MEDIUM:
                    if(++cnt >= 6){
                        cnt = 0;
                        game_snake_run();
                    }
                    break;
                case SPEED_FAST:
                    if(++cnt >= 3){
                        cnt = 0;
                        game_snake_run();
                    }
                    break;
            }
        }
    }
    
    // 游戏初始化
    game_2048_init();
    
    while(1){
        // 矩阵键盘输入
        if(KeyCode>=0){
            sign_key = KEY_MAP[KeyCode];
            KeyCode = -1;
        }
        
        // 红外输入
        if(B_100us){
            B_100us = 0;
            if(ir_rx_available()){
                // 红外接收
                sign_ir = ir_rx_ircode();
            }
        }
        
        // 字符：0   1   2   3   4   5   6   7   8   9   #   *   w(+) s(/) a(-) d(x) ok
        // IR  ：13  0   1   2   4   5   6   8   9   10  14  12  17   25   20   22   21
        // 按键：0   1   2   3   4   5   6   7   8   9   35  42  43   47   45   120  -
        if(sign_ir){
            switch(sign_ir){
                case 17:
                    game_2048_updateStatus('w');
                    break;
                case 25:
                    game_2048_updateStatus('s');
                    break;
                case 20:
                    game_2048_updateStatus('a');
                    break;
                case 22:
                    game_2048_updateStatus('d');
                    break;
                case 12:
                    game_2048_updateStatus('q');
                    break;
                case 14:
                    game_2048_updateStatus('r');
                    break;
                case 21:
                    game_2048_updateStatus('c');
                    break;
            }
            sign_ir = 0;
        }else if(sign_key != -1){
            switch(sign_key){
                case '+':
                    game_2048_updateStatus('w');
                    break;
                case '/':
                    game_2048_updateStatus('s');
                    break;
                case '-':
                    game_2048_updateStatus('a');
                    break;
                case 'x':
                    game_2048_updateStatus('d');
                    break;
                case '*':
                    game_2048_updateStatus('q');
                    break;
                case '#':
                    game_2048_updateStatus('r');
                    break;
                case 0:
                    game_2048_updateStatus('c');
                    break;
            }
            sign_key = -1;
        }
    }
}

// 1ms
void Timer0_interrupt(void) interrupt 1{
    static int cnt = 0;
    cnt = (cnt + 1) % 50;
    if(cnt == 49){
        B_50ms = 1;
        IO_KeyScan();
    }
    B_1ms = 1;
}

// 0.1ms
void Timer4_interrupt(void) interrupt 20{
    ir_rec_callback();      //红外接收回调函数
    B_100us = 1;
}
