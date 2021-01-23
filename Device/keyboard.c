#include "keyboard.h"

/*****************************************************
    ���м�ɨ�����
    ʹ��XY����4x4���ķ�����ֻ�ܵ������ٶȿ�

   Y     P74      P75      P76      P77
          |        |        |        |
X         |        |        |        |
P70 ---- K00 ---- K01 ---- K02 ---- K03 ----
          |        |        |        |
P71 ---- K04 ---- K05 ---- K06 ---- K07 ----
          |        |        |        |
P72 ---- K08 ---- K09 ---- K10 ---- K11 ----
          |        |        |        |
P73 ---- K12 ---- K13 ---- K14 ---- K15 ----
          |        |        |        |
******************************************************/
int8 KeyCode = -1;
uint8 IO_KeyState, IO_KeyState1, IO_KeyHoldCnt;
uint8 code T_KeyTable[16] = {0,1,2,0,3,0,0,0,4,0,0,0,0,0,0,0};
uint8 KEY_MAP[17] = {0, '+', 9, 8, 7, '-', 6, 5, 4, 'x', 3, 2, 1, '/', '#', 0, '*'};

void IO_KeyScan(void){    //50ms call
    uint8 i, j;

    j = IO_KeyState1;   //������һ��״̬

    P7 = 0xf0;  //X�ͣ���Y
    i = 60;
    while(--i);
    IO_KeyState1 = P7 & 0xf0;

    P7 = 0x0f;  //Y�ͣ���X
    i = 60;
    while(--i);
    IO_KeyState1 |= (P7 & 0x0f);
    
    IO_KeyState1 ^= 0xff;   //ȡ��
    
    if(j == IO_KeyState1){   //�������ζ����
        j = IO_KeyState;
        IO_KeyState = IO_KeyState1;
        if(IO_KeyState != 0){    //�м�����
            F0 = 0;
            if(j == 0)  F0 = 1; //��һ�ΰ���
            else if(j == IO_KeyState){
                if(++IO_KeyHoldCnt >= 20){   //1����ؼ�
                    IO_KeyHoldCnt = 18;
                    F0 = 1;
                }
            }
            if(F0){
                j = T_KeyTable[IO_KeyState >> 4];
                if((j != 0) && (T_KeyTable[IO_KeyState & 0x0f] != 0)) 
                    KeyCode = (j - 1) * 4 + T_KeyTable[IO_KeyState & 0x0f];    //������룬1~16
            }
        }else IO_KeyHoldCnt = 0;
    }
    P7 = 0xff;
}
