#ifndef __QMA7981_H
#define __QMA7981_H
	
#include "sys.h"
#include "delay.h"
#include "hardiic.h"

/***********************************
 * 中断功能配置宏定义
 * *********************************/
//使能抬手唤醒中断
//#define	QMA7981_HAND_UP_DOWN    
//使能任何运动检测中断
//#define QMA7981_ANY_MOTION
//使能无动作中断
//#define QMA7981_NO_MOTION
//使能步数检测中断
//#define QMA7981_STEP_INT
//使能重大中断（用户位置变化而产生的运动）
//#define QMA7981_SIGNIFICANT_MOTION

/***********************************
 * 配置中断使用锁存模式宏定义
 * *********************************/
#define	QMA7981_INT_LATCH	

/***********************************
 * 计步功能宏定义
 * *********************************/
#define QMA7981_STEPCOUNTER	//使能计步功能
#define QMA7981_BW_REG 		0xe1	//带宽设置
#define QMA7981_REG_0X12	0x94	//[7]计步使能,[6~0]设置用于动态阈值计算的样本计数
#define QMA7981_REG_0X13	0x00	//[7]步数清除,[6~0]两个连续样本的加速变化阈值
#define QMA7981_REG_0X14	0x24	//有效步数的短时间窗口
#define QMA7981_REG_0X15	0x20	//退出步数计数器的时间窗口
#define QMA7981_REG_0X1f	0x09	//

uint8 qma7981_init();//加速度初始化
void qma7981_set_range(uint8 range);//设置加速度范围 QMA7981_RANGE_2G/4G/8G/16G/32G.
void qma7981_read_acc(int32 *accData);//读加速度三轴值
uint32 qma7981_read_stepcounter();//获取步数
unsigned char qma7981_irq_hdlr();//读中断
void qma7981_raise_config(uint8 wake_sum, uint8 diff, uint16 period, uint16 timeout, uint8 hd_z, uint8 hd_x);	//抬手唤醒配置函数


#define QMA7981_I2C_SLAVE_ADDR		0x24	// AD0 GND 0x12, AD0 VDD 0x13
#define QMA7981_ERR_I2C				-1
#define QMA7981_SUCCESS				0

#define GRAVITY_EARTH_1000          9807	// about (9.80665f)*1000   mm/s2
#define QMA7981_ABS(X) 				((X) < 0 ? (-1 * (X)) : (X))
/*Register Map*/
#define QMA7981_CHIP_ID		    	0x00
#define QMA7981_XOUTL				0x01
#define QMA7981_XOUTH				0x02
#define QMA7981_YOUTL				0x03
#define QMA7981_YOUTH				0x04
#define QMA7981_ZOUTL				0x05
#define QMA7981_ZOUTH				0x06
#define QMA7981_STEP_CNT_L			0x07
#define QMA7981_INT_STAT0			0x0a
#define QMA7981_INT_STAT1			0x0b
#define QMA7981_INT_STAT2			0x0c
#define QMA7981_INT_STAT3			0x0d
#define QMA7981_FIFO_STATE			0x0e
#define QMA7981_STEP_CNT_M			0x0e
#define QMA7981_REG_RANGE			0x0f
#define QMA7981_REG_BW_ODR			0x10
#define QMA7981_REG_POWER_CTL		0x11
#define QMA7981_STEP_SAMPLE_CNT		0x12
#define QMA7981_STEP_PRECISION		0x13
#define QMA7981_STEP_TIME_LOW		0x14
#define QMA7981_STEP_TIME_UP		0x15
#define QMA7981_INTPIN_CFG			0x20
#define QMA7981_INT_CFG				0x21
#define QMA7981_OS_CUST_X		    0x27
#define QMA7981_OS_CUST_Y			0x28
#define QMA7981_OS_CUST_Z			0x29
#define QMA7981_RAISE_CFG			0x2B
#define QMA7981_STEP_TIME_UP		0x15
/*ODR SET @lower ODR*/
#define QMA6981_ODR_1000HZ			0x07
#define QMA6981_ODR_500HZ			0x06
#define QMA6981_ODR_250HZ			0x05
#define QMA6981_ODR_125HZ			0x04  
#define QMA6981_ODR_62HZ			0x03   
#define QMA6981_ODR_31HZ			0x02   
#define QMA6981_ODR_16HZ			0x01
#define QMA6981_ODR_HIGH			0x20

/* Accelerometer Sensor Full Scale */
#define QMA7981_RANGE_2G			0x01
#define QMA7981_RANGE_4G			0x02
#define QMA7981_RANGE_8G			0x04
#define QMA7981_RANGE_16G			0x08
#define QMA7981_RANGE_32G			0x0f

/* 0x11 Set the sleep time, when device is in power cycling power saving.*/
#define QMA6981_SLEEP_DUR0			0x00
#define QMA6981_SLEEP_DUR1			0x06
#define QMA6981_SLEEP_DUR2			0x07
#define QMA6981_SLEEP_DUR4			0x08
#define QMA6981_SLEEP_DUR6			0x09
#define QMA6981_SLEEP_DUR10			0x0a
#define QMA6981_SLEEP_DUR25			0x0b
#define QMA6981_SLEEP_DUR50			0x0c
#define QMA6981_SLEEP_DUR100		0x0d
#define QMA6981_SLEEP_DUR500		0x0e
#define QMA6981_SLEEP_DUR1000		0x0f

#if defined(QMA7981_DOUBLE_TRIPLE_CLICK)
typedef struct{
	unsigned char check_click;
	unsigned short click_num;
	unsigned short static_num;
	unsigned short t_msec_1;			// check_click timer
	unsigned short t_msec_2;			// check static timer
	unsigned short t_msec_out;			// timeout
}qst_click_check;
#endif

#if defined(QMA7981_ABNORMAL_SHAKE_CHECK)
typedef struct{
	unsigned char check_shake;
	unsigned short shake_num;
	unsigned short t_msec_1;
	unsigned short t_msec_out;			// timeout
}qst_shake_check;
#endif

typedef enum{	
	CHIP_TYPE_QMA6981 = 0,
	CHIP_TYPE_QMA7981,
	CHIP_TYPE_QMA6100,
	CHIP_TYPE_UNDEFINE,
	CHIP_TYPE_MAX
}QMA7981_type;

typedef struct{
    int16 sign[3];
    uint16 map[3];
}qst_convert;

typedef struct{
	uint8					chip_id;
	QMA7981_type			chip_type;
	int32					lsb_1g;
	uint8					layout;
	qst_convert				cvt;
	uint8					int32_level;
}QMA7981_data;

#endif