#include "main.h"
#include "game.h"

void main(void){
    pcf8563_Time localtime;

    // ʱ�ӳ�ʼ��
	InitMCU();
    Timer0_init();
    Timer4_init();
    EA = 1;		        // �ж��ܿ���
    
    // Ӳ����ʼ��
    pcf8563_init();     // rtc
    ir_rx_init();       // ir
    tft_lcd_init();     // lcd
    
    // ��RTCʱ���ʼ�����������
    pcf8563_read_rtc(&localtime);
    srand(((long *)&localtime)[0]+((long *)&localtime)[1]);
    
    // gameԤ����
    mempool_init();
    readToBuf();
    
    // ��Ϸģʽѡ��
    game_mode = G_2048;
    
    // ��Ϸ��ʼ��
    switch(game_mode){
        case G_2048:
            game_2048_init();
            break;
        case G_SNAKE:
            game_snake_init();
            break;
    }
    
    // ��ѭ��
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
