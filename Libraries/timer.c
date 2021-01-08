#include "timer.h"

//========================================================================
// 函数: void   Timer0_init(void)
// 描述: timer0初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer0_init(void)
{
        TR0 = 0;    //停止计数

    #if (Timer0_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer0设置的中断过快!"

    #elif ((Timer0_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
        ET0 = 1;    //允许中断
    //  PT0 = 1;    //高优先级中断
        TMOD &= ~0x03;
        TMOD |= 0;  //工作模式, 0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
    //  TMOD |=  0x04;  //对外计数或分频
        TMOD &= ~0x04;  //定时
    //  INT_CLKO |=  0x01;  //输出时钟
        INTCLKO &= ~0x01;  //不输出时钟

        #if (Timer0_Reload < 65536UL)
            AUXR |=  0x80;  //1T mode
            TH0 = (uint8)((65536UL - Timer0_Reload) / 256);
            TL0 = (uint8)((65536UL - Timer0_Reload) % 256);
        #else
            AUXR &= ~0x80;  //12T mode
            TH0 = (uint8)((65536UL - Timer0_Reload/12) / 256);
            TL0 = (uint8)((65536UL - Timer0_Reload/12) % 256);
        #endif

        TR0 = 1;    //开始运行

    #else
        #error "Timer0设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void   Timer1_init(void)
// 描述: timer1初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer1_init(void)
{
        TR1 = 0;    //停止计数

    #if (Timer1_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer1设置的中断过快!"

    #elif ((Timer1_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
        ET1 = 1;    //允许中断
    //  PT1 = 1;    //高优先级中断
        TMOD &= ~0x30;
        TMOD |= (0 << 4);   //工作模式, 0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
    //  TMOD |=  0x40;  //对外计数或分频
        TMOD &= ~0x40;  //定时
    //  INT_CLKO |=  0x02;  //输出时钟
        INTCLKO &= ~0x02;  //不输出时钟

        #if (Timer1_Reload < 65536UL)
            AUXR |=  0x40;  //1T mode
            TH1 = (uint8)((65536UL - Timer1_Reload) / 256);
            TL1 = (uint8)((65536UL - Timer1_Reload) % 256);
        #else
            AUXR &= ~0x40;  //12T mode
            TH1 = (uint8)((65536UL - Timer1_Reload/12) / 256);
            TL1 = (uint8)((65536UL - Timer1_Reload/12) % 256);
        #endif

        TR1 = 1;    //开始运行

    #else
        #error "Timer1设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void   Timer2_init(void)
// 描述: timer2初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer2_init(void)
{
        AUXR &= ~0x1c;      //停止计数, 定时模式, 12T模式

    #if (Timer2_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer2设置的中断过快!"

    #elif ((Timer2_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
    //  IE2  &= ~ET2;       //禁止中断
        IE2  |=  ET2;       //允许中断
    //  INT_CLKO |=  0x04;  //输出时钟
        INTCLKO &= ~0x04;  //不输出时钟

        #if (Timer2_Reload < 65536UL)
            AUXR |=  (1<<2);    //1T mode
            T2H = (uint8)((65536UL - Timer2_Reload) / 256);
            T2L = (uint8)((65536UL - Timer2_Reload) % 256);
        #else
            T2H = (uint8)((65536UL - Timer2_Reload/12) / 256);
            T2L = (uint8)((65536UL - Timer2_Reload/12) % 256);
        #endif

            AUXR |=  (1<<4);    //开始运行

    #else
        #error "Timer2设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void   Timer3_init(void)
// 描述: timer3初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer3_init(void)
{
        T4T3M &= ~0x0f;     //停止计数, 定时模式, 12T模式, 不输出时钟

    #if (Timer3_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer3设置的中断过快!"

    #elif ((Timer3_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
    //  IE2  &= ~ET3;       //禁止中断
        IE2  |=  ET3;       //允许中断
    //  T4T3M |=  0x01;     //输出时钟
    //  T4T3M &= ~0x01;     //不输出时钟

        #if (Timer3_Reload < 65536UL)
            T4T3M |=  (1<<1);    //1T mode
            T3H = (uint8)((65536UL - Timer3_Reload) / 256);
            T3L = (uint8)((65536UL - Timer3_Reload) % 256);
        #else
            T3H = (uint8)((65536UL - Timer3_Reload/12) / 256);
            T3L = (uint8)((65536UL - Timer3_Reload/12) % 256);
        #endif

            T4T3M |=  (1<<3);    //开始运行

    #else
        #error "Timer3设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void   Timer4_init(void)
// 描述: timer4初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer4_init(void)
{
        T4T3M &= ~0xf0;     //停止计数, 定时模式, 12T模式, 不输出时钟

    #if (Timer4_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer4设置的中断过快!"

    #elif ((Timer4_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
    //  IE2  &= ~ET4;       //禁止中断
        IE2  |=  ET4;       //允许中断
    //  T4T3M |=  0x10;     //输出时钟
    //  T4T3M &= ~0x10;     //不输出时钟

        #if (Timer4_Reload < 65536UL)
            T4T3M |=  (1<<5);    //1T mode
            T4H = (uint8)((65536UL - Timer4_Reload) / 256);
            T4L = (uint8)((65536UL - Timer4_Reload) % 256);
        #else
            T4H = (uint8)((65536UL - Timer4_Reload/12) / 256);
            T4L = (uint8)((65536UL - Timer4_Reload/12) % 256);
        #endif

            T4T3M |=  (1<<7);    //开始运行

    #else
        #error "Timer4设置的中断过慢!"
    #endif
}

