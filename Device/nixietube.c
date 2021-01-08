#include "hc595.h"
#include "nixietube.h"
#include "delay.h"
#include "math.h"

//段码
//0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,-,NONE
uint8 nix_seg[18]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xBF,0xFF};

//========================================================================
// 描述: 数码管显示初始化.
// 参数: none.
// 返回: none.
//========================================================================
void nix_init(){
    hc595_enable_nix();
    NIXIETUBE_PORT_MODE();//推挽输出
    NIXIETUBE_PORT=0xff;

    //左侧数码管冒号
    LEFT_COLON_PIN_MODE();//推挽输出
    LEFT_COLON_PIN = 1;

    //右侧数码管冒号
    RIGHT_COLON_PIN_MODE();//推挽输出
    RIGHT_COLON_PIN = 1;
}

void nix_display_num(int32 num){
    int8 n = 6;
    uint8 buf[8];
    if(num>=0){
        buf[7] = 17;
    }else{
        buf[7] = 16;
        num = -num; 
    }
    buf[0] = num%10;
    buf[1] = num/10%10;
    buf[2] = num/100%10;
    buf[3] = num/1000%10;
    buf[4] = num/10000%10;
    buf[5] = num/100000%10;
    buf[6] = num/1000000%10;
    while(buf[n] == 0)
        buf[n--] = 17;
    if(num==0) buf[0] = 0;
    for(n=7; n>=0; n--){
        hc595_bit_select(n);
        NIXIETUBE_PORT = nix_seg[buf[n]];
        delay(2);
        hc595_bit_disable();
    }
}

void nix_display_buf(uint8 begin, nix_content *buf, uint8 n){
    int8 i;
    if(begin<8 && n<=(8-begin)){
        i = 8 - begin - n;
        while(n--){
            hc595_bit_select(i);
            NIXIETUBE_PORT = nix_seg[buf[n]];
            delay(2);
            hc595_bit_disable();
            i++;
        }   
    }
}
