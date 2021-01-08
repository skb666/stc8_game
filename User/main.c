#include "main.h"
#include "game_2048.h"

uint8 B_100us = 0;
uint16 tim0_ms = 50;
uint8 sign_ir = 0;

void main(void){
    pcf8563_Time localtime;
    
    // 时钟初始化
	InitMCU();
    Timer0_init();
    Timer4_init();
    EA = 1;		// 中断总开关
    
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
            //ir_send_nec(1, KEY_MAP[KeyCode]);
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
        if(sign_ir){
            game2048_updateStatus(sign_ir);
            sign_ir = 0;
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