#include "main.h"
#include "game_2048.h"

uint8 B_100us = 0;
uint16 tim0_ms = 50;

void main(void){
    pcf8563_Time localtime;
    uint8 sign_ir = 0;
    int8 sign_key = -1;
    
    // 时钟初始化
	InitMCU();
    Timer0_init();
    Timer4_init();
    EA = 1;		        // 中断总开关
    
    // 硬件初始化
    pcf8563_init();
    ir_rx_init();
    tft_lcd_init();
    
    // 用RTC时间初始化随机数种子
    pcf8563_read_rtc(&localtime);
    srand(((long *)&localtime)[0]+((long *)&localtime)[1]);
    
    // 游戏初始化
    game2048_init();
    
    while(1){
        // 矩阵键盘输入
        if(IO_KeyState){
            // 红外发送
            sign_key = KEY_MAP[KeyCode];
            while(IO_KeyState);
        }
        
        // 红外输入
        if(B_100us){
            B_100us = 0;
            if(ir_rx_available()){
                // 红外接收
                sign_ir = ir_rx_ircode();
            }
        }
        
        // 运行2048
        game2048_run();
        
        // 字符：0   1   2   3   4   5   6   7   8   9   #   *   w(+) s(/) a(-) d(x) ok
        // IR  ：13  0   1   2   4   5   6   8   9   10  14  12  17   25   20   22   21
        // 按键：0   1   2   3   4   5   6   7   8   9   35  42  43   47   45   120  -
        if(sign_ir){
            switch(sign_ir){
                case 17:
                    game2048_updateStatus('w');
                    break;
                case 25:
                    game2048_updateStatus('s');
                    break;
                case 20:
                    game2048_updateStatus('a');
                    break;
                case 22:
                    game2048_updateStatus('d');
                    break;
                case 12:
                    game2048_updateStatus('q');
                    break;
                case 14:
                    game2048_updateStatus('r');
                    break;
            }
            sign_ir = 0;
        }else if(sign_key != -1){
            switch(sign_key){
                case '+':
                    game2048_updateStatus('w');
                    break;
                case '/':
                    game2048_updateStatus('s');
                    break;
                case '-':
                    game2048_updateStatus('a');
                    break;
                case 'x':
                    game2048_updateStatus('d');
                    break;
                case '*':
                    game2048_updateStatus('q');
                    break;
                case '#':
                    game2048_updateStatus('r');
                    break;
            }
            sign_key = -1;
        }
    }
}

// 1ms
void Timer0_interrupt(void) interrupt 1{
    static int cnt = 0;
    cnt = (cnt + 1) % tim0_ms;
    if(cnt == tim0_ms - 1){
        IO_KeyScan();
    }
}

// 0.1ms
void Timer4_interrupt(void) interrupt 20{
    ir_rec_callback();      //红外接收回调函数
    B_100us = 1;
}