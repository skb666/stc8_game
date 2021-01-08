#include "ir.h"

bit _b_ir_press;               //红外接收标志
xdata uint8  _ir_code;           //红外键码
xdata uint16 _user_code;          //用户码

//========================================================================
// 描述: 红外延时函数(内部调用)
// 参数: time:延时的时间（不精确）.
// 返回: none.
//========================================================================
static void ir_delayus(uint16 time)
{
    uint8 i;
    do{
        i = 6;
        while (--i);
    }while(time--);
}

//========================================================================
// 描述: 红外发射使能(内部调用)
// 参数: fre:红外发射频率（kHz）.
// 返回: none.
//========================================================================
static void enable_ir_out(uint8 fre)
{  
    IR_SEND_PIN_OUT;
    pwm_init(IR_SEND_PWM, (fre*1000L), 0);
}

//========================================================================
// 描述: 红外发射禁止(内部调用)
// 参数: none.
// 返回: none.
//========================================================================
static void disable_ir_out()
{
    IR_SEND_PIN_INIT;
}

//========================================================================
// 描述: 红外发射载波信号(内部调用)
// 参数: time:发射的时间.
// 返回: none.
//========================================================================
static void ir_tx_mark(uint16 time)
{
    // 占空比 1/3
    pwm_duty(IR_SEND_PWM, PWM_DUTY_MAX/3*2);
    ir_delayus(time);
}

//========================================================================
// 描述: 红外发射空闲信号(内部调用)
// 参数: time:发射的时间.
// 返回: none.
//========================================================================
static void ir_tx_space(uint16 time)
{
    pwm_duty(IR_SEND_PWM, PWM_DUTY_MAX);
    ir_delayus(time);
}

//========================================================================
// 描述: 红外发射NEC码
// 参数: address:发送的地址 ;command: 发送的命令.
// 返回: none.
//========================================================================
void ir_send_nec(uint8 address, uint8 command)
{
    uint8 i;
    uint8 inverse_address = ~address;
    uint8 inverse_command = ~command;

    // 1. 载波配置
    enable_ir_out(38);
    // 2. 发送引导码
    ir_tx_mark(NEC_HDR_MARK);
    ir_tx_space(NEC_HDR_SPACE);
    // 3. 发送地址
    for (i=0;i<8;i++)
    {
        if (address & 0x01) 
        {
            ir_tx_mark(NEC_BIT_MARK);
            ir_tx_space(NEC_ONE_SPACE);
        } 
        else 
        {
            ir_tx_mark(NEC_BIT_MARK);
            ir_tx_space(NEC_ZERO_SPACE);
        }
        address >>= 1;
    }
    // 4. 发送地址反码
    
    for (i=0;i<8;i++)
    {
        if (inverse_address & 0x01) 
        {
            ir_tx_mark(NEC_BIT_MARK);
            ir_tx_space(NEC_ONE_SPACE);
        } 
        else 
        {
            ir_tx_mark(NEC_BIT_MARK);
            ir_tx_space(NEC_ZERO_SPACE);
        }
        inverse_address >>= 1;
    }

    // 5. 发送命令
    for (i=0;i<8;i++)
    {
        if (command & 0x01) 
        {
            ir_tx_mark(NEC_BIT_MARK);
            ir_tx_space(NEC_ONE_SPACE);
        } 
        else 
        {
            ir_tx_mark(NEC_BIT_MARK);
            ir_tx_space(NEC_ZERO_SPACE);
        }
        command >>= 1;
    }

    // 6. 发送命令反码
    for (i=0;i<8;i++)
    {
        if ((inverse_command) & 0x01) 
        {
            ir_tx_mark(NEC_BIT_MARK);
            ir_tx_space(NEC_ONE_SPACE);
        } 
        else 
        {
            ir_tx_mark(NEC_BIT_MARK);
            ir_tx_space(NEC_ZERO_SPACE);
        }
        inverse_command >>= 1;
    }
    ir_tx_mark(NEC_BIT_MARK);
    ir_tx_space(1);// 为0，进入死循环
    disable_ir_out();
}

//========================================================================
// 描述: 红外接收回调函数（调用周期100uS）
// 参数: none.
// 返回: none.
//========================================================================
void ir_rec_callback()
{
    static xdata uint8  IR_SampleCnt;       //采样计数
    static xdata uint8  IR_BitCnt;          //编码位数
    static xdata uint8  IR_UserH;           //用户码(地址)高字节
    static xdata uint8  IR_UserL;           //用户码(地址)低字节
    static xdata uint8  IR_data;            //数据原码
    static xdata uint8  IR_DataShift;        //数据移位

    static bit P_IR_RX_temp;             //Last sample
    static bit B_IR_Sync;                //已收到同步标志

    uint8  SampleTime;
    uint8  IR_TemShit;

    IR_SampleCnt++;                         //Sample + 1

    F0 = P_IR_RX_temp;                      //Save Last sample status
    P_IR_RX_temp = IR_REC_PIN;                 //Read current status
    if(F0 && !P_IR_RX_temp)                 //Pre-sample is high，and current sample is low, so is fall edge
    {
        SampleTime = IR_SampleCnt;          //get the sample time
        IR_SampleCnt = 0;                   //Clear the sample counter

        if(SampleTime > D_IR_SYNC_MAX)     B_IR_Sync = 0;  //large the Maxim SYNC time, then error
        else if(SampleTime >= D_IR_SYNC_MIN)                    //SYNC
        {
            if(SampleTime >= D_IR_SYNC_DIVIDE)
            {
                B_IR_Sync = 1;                  //has received SYNC
                IR_BitCnt = D_IR_BIT_NUMBER;    //Load bit number
            }
        }
        else if(B_IR_Sync)                      //has received SYNC
        {
            if(SampleTime > D_IR_DATA_MAX)      B_IR_Sync=0;    //data samlpe time too large
            else
            {
                IR_DataShift >>= 1;                  //data shift right 1 bit
                if(SampleTime >= D_IR_DATA_DIVIDE)  IR_DataShift |= 0x80;    //devide data 0 or 1
                if(--IR_BitCnt == 0)                //bit number is over?
                {
                    B_IR_Sync = 0;                  //Clear SYNC

                    // if(~IR_DataShift == IR_data)     //判断数据正反码
                    IR_TemShit = ~IR_DataShift;
                    if(IR_TemShit == IR_data);
                    {
                        _user_code = ((uint16)IR_UserH << 8) + IR_UserL;
                        _ir_code      = IR_data;
                        _b_ir_press   = 1;           //数据有效
                    }
                }
                else if((IR_BitCnt & 7)== 0)        //one byte receive
                {
                    IR_UserL = IR_UserH;            //Save the User code high byte
                    IR_UserH = IR_data;             //Save the User code low byte
                    IR_data  = IR_DataShift;         //Save the IR data byte
                }
            }
        }
    }
}

//========================================================================
// 描述: 红外接收初始化
// 参数: none.
// 返回: none.
//========================================================================
void ir_rx_init()
{
    IR_REC_PIN_MODE;
}

//========================================================================
// 描述: 接收到红外信号
// 参数: none.
// 返回: 1,接收到红外信号;0,没有接收到红外数据.
//========================================================================
uint8 ir_rx_available()
{
    if(_b_ir_press)
    {
        _b_ir_press = 0;
        return 1;
    }
    return 0;
}

//========================================================================
// 描述: 接收到用户码
// 参数: none.
// 返回:  接收到的用户码.
//========================================================================
uint8 ir_rx_user_code()
{
    return _user_code;
}

//========================================================================
// 描述: 接收键码
// 参数: none.
// 返回: 接收到的键码.
//========================================================================
uint8 ir_rx_ircode()
{
     return _ir_code;
}
