#include "sys.h"
#include "hc595.h"
#include "led8.h"

uint32 sys_clk = 24000000;//����PWM����ʱ�������ڡ�EEPROMƵ�ʲ���

void InitMCU(){
	P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
    P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
    P2M1 = 0;   P2M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���

    RSTCFG = 0x50;          //��λ�Ĵ����������0x00����λ�ܽ�������ͨIO
    
	led8_disable();			//LED Power OFF
    hc595_init(); 
   	hc595_disable();
	
	P41 = 0;				//�ر�CMP��
}
