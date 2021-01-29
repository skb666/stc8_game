#include "qma7981.h"

code qst_convert qst_map[] = 
{
    { { 1, 1, 1}, {0, 1, 2} },
    { {-1, 1, 1}, {1, 0, 2} },
    { {-1,-1, 1}, {0, 1, 2} },
    { { 1,-1, 1}, {1, 0, 2} },

    { {-1, 1, -1}, {0, 1, 2} },
    { { 1, 1, -1}, {1, 0, 2} },
    { { 1,-1, -1}, {0, 1, 2} },
    { {-1,-1, -1}, {1, 0, 2} }
};

static QMA7981_data g_QMA7981;
#if defined(QMA7981_DOUBLE_TRIPLE_CLICK)
static unsigned int acc_data_curr[3];
static unsigned int acc_data[3];
static qst_click_check g_click;
#endif
#if defined(QMA7981_ABNORMAL_SHAKE_CHECK)
static qst_shake_check g_shake;
#endif
//========================================================================
// 描述: QMA7981写寄存器.
// 参数: none.
// 返回: none.
//========================================================================
void qma7981_write_reg(uint8 reg,uint8 _data)
{
    hardiic_write_nbyte(QMA7981_I2C_SLAVE_ADDR,reg,&_data,1);
}

//========================================================================
// 描述: QMA7981读寄存器.
// 参数: none.
// 返回: none.
//========================================================================
void qma7981_read_reg(uint8 reg,uint8 *buf, uint8 len)
{
    hardiic_read_nbyte(QMA7981_I2C_SLAVE_ADDR,reg,buf,len);
}

/*	
qma7981 odr setting
0x10<2:0>		ODR(Hz)				Time(ms)	|	RANGE 0x0f<3:0>
000				43.3125				23.088		|	0001	2g  		244ug/LSB
001				86.4453				11.568		|	0010	4g  		488ug/LSB
002				172.1763			5.808		|	0100	8g  		977ug/LSB
003				341.5300			2.928		|	1000	16g  	1.95mg/LSB
004				672.0430			1.488		|	1111	32g  	3.91mg/LSB
005				32.5013				30.768		|	Others	2g  		244ug/LSB
006				129.3995			7.728		|
007				257.2016			3.888		|
*/

const uint8 qma7981_init_tbl[][2] = 
{
	{0x11, 0x80},		//将设备设置为活动模式
	{0x36, 0xb6},
	{0xff, 5},
	{0x36, 0x00},
	{0x0f, QMA7981_RANGE_8G},
	{0x10, 0xe1},		// ODR 130hz	
	//{0x4a, 0x08},		//Force I2C I2C uint32erface.SPI is disabled,SENB can be used as ATB
	{0x20, 0x04},		//将int1设置为活动电平为逻辑低
	{0x11, 0x80},
	{0x5f, 0x80},		//enable test mode,take control the FSM
	{0x5f, 0x00},		//normal mode
	{0xff, 1},
};

//========================================================================
// 描述: QMA7981延时函数.
// 参数: none.
// 返回: none.
//========================================================================
void qma7981_delay(uint32 delay)
{
	uint32 i,j;
	for(i=0;i<delay;i++)
	{
		for(j=0;j<1000;j++)
		{
			;
		}
	}
}

//========================================================================
// 描述: QMA7981抬手唤醒配置函数.
// 参数: wake_sum:手部动作强度(0~31); diff:两次动作的微分值(0~15); period:唤醒时间(0~2047).
//		 timeout:唤醒超时时间(0~4095);	hd_z:放下时的z阈值(0~7); hd_x:放下时的x阈值(0~7);
// 返回: none.
//========================================================================
void qma7981_raise_config(uint8 wake_sum, uint8 diff, uint16 period, uint16 timeout, uint8 hd_z, uint8 hd_x)
{
	qma7981_write_reg(0x2a, ((diff&0x03)<<6)|(wake_sum&0x1f));

	qma7981_write_reg(0x2b, ((hd_z&0x07)<<5)|((hd_x&0x07)<<2)|((diff&0x0c)>>2));

	qma7981_write_reg(0x35, period&0x00ff);

	qma7981_write_reg(0x3e, timeout&0x00ff);

	qma7981_write_reg(0x3f, ((period&0x0700)>>4)|((timeout&0x0f00)>>8));
}

//========================================================================
// 描述: QMA7981初始化寄存器.
// 参数: none.
// 返回: none.
//========================================================================
uint8 qma7981_initialize()
{
    uint32 ret = 0;
	uint32 index, total;
	uint8 _data[2] = {0};
	uint8 reg_0x10 = 0;
	uint8 reg_0x16 = 0;
	uint8 reg_0x18 = 0;
	uint8 reg_0x19 = 0;
	uint8 reg_0x1a = 0;
#if defined(QMA7981_ANY_MOTION)||defined(QMA7981_NO_MOTION)
	uint8 reg_0x2c = 0;
#endif

	total = sizeof(qma7981_init_tbl)/sizeof(qma7981_init_tbl[0]);
	for(index=0; index<total; index++)
	{	
		_data[0] = qma7981_init_tbl[index][0];
		_data[1] = qma7981_init_tbl[index][1];
		if(_data[0] == 0xff)
		{
			qma7981_delay(_data[1]);
		}
		else
		{
			if(_data[0] == QMA7981_REG_RANGE)
			{
				if(_data[1] == QMA7981_RANGE_4G)
					g_QMA7981.lsb_1g = 2048;
				else if(_data[1] == QMA7981_RANGE_8G)
					g_QMA7981.lsb_1g = 1024;
				else if(_data[1] == QMA7981_RANGE_16G)
					g_QMA7981.lsb_1g = 512;
				else if(_data[1] == QMA7981_RANGE_32G)
					g_QMA7981.lsb_1g = 256;
				else
					g_QMA7981.lsb_1g = 4096;
			}
			qma7981_write_reg(_data[0],_data[1]);
			
			qma7981_delay(2);
		}
	}

	// read reg
	qma7981_read_reg(0x16, &reg_0x16, 1);
	qma7981_read_reg(0x18, &reg_0x18, 1);
	qma7981_read_reg(0x19, &reg_0x19, 1);
	qma7981_read_reg(0x1a, &reg_0x1a, 1);
#if defined(QMA7981_ANY_MOTION)||defined(QMA7981_NO_MOTION)
	qma7981_read_reg(0x2c, &reg_0x2c, 1);
#endif
	// read reg
	reg_0x10 = QMA7981_BW_REG;		
	qma7981_write_reg(0x10, reg_0x10);	//带宽设置
#if defined(QMA7981_STEPCOUNTER)
	#if (QMA7981_BW_REG == 0xe0)
	{
		// ODR: 65hz 15.48 ms
		qma7981_write_reg(0x12, QMA7981_REG_0X12);
		qma7981_write_reg(0x13, 0x80);		// clear step
		qma7981_write_reg(0x13, QMA7981_REG_0X13);		// 
		qma7981_write_reg(0x14, QMA7981_REG_0X14);		// STEP_TIME_LOW<7:0>*(1/ODR) 
		qma7981_write_reg(0x15, QMA7981_REG_0X15);		// STEP_TIME_UP<7:0>*8*(1/ODR) 
	}
	#elif (QMA7981_BW_REG == 0xe1)
	{
		// ODR: 130hz 7.74 ms
		qma7981_write_reg(0x12, QMA7981_REG_0X12);
		qma7981_write_reg(0x13, 0x80);		// clear step
		qma7981_write_reg(0x13, QMA7981_REG_0X13);		// 
		qma7981_write_reg(0x14, QMA7981_REG_0X14);		// STEP_TIME_LOW<7:0>*(1/ODR) 
		qma7981_write_reg(0x15, QMA7981_REG_0X15);		// STEP_TIME_UP<7:0>*8*(1/ODR) 
	}
	#elif (QMA7981_BW_REG == 0xe2)
	{
		// ODR: 258Hz 3.87 ms
		qma7981_write_reg(0x12, QMA7981_REG_0X12);
		qma7981_write_reg(0x13, 0x80);		// clear step
		qma7981_write_reg(0x13, QMA7981_REG_0X13);		// 
		qma7981_write_reg(0x14, QMA7981_REG_0X14);		// STEP_TIME_LOW<7:0>*(1/ODR) 
		qma7981_write_reg(0x15, QMA7981_REG_0X15);		// STEP_TIME_UP<7:0>*8*(1/ODR) 
	}
	#endif
	qma7981_write_reg(0x1f, QMA7981_REG_0X1f);

	// step int
	#if defined(QMA7981_STEP_INT)
	reg_0x16 |= 0x08;
	reg_0x19 |= 0x08;
	qma7981_write_reg(0x16, reg_0x16);
	qma7981_write_reg(0x19, reg_0x19);
	#endif
	#if defined(QMA7981_SIGNIFICANT_STEP)
	qma7981_write_reg(0x1d, 0x26);		//every 30 step
	reg_0x16 |= 0x40;
	reg_0x19 |= 0x40;
	qma7981_write_reg(0x16, reg_0x16);
	qma7981_write_reg(0x19, reg_0x19);
	#endif
#endif

//RANGE<3:0> Acceleration range Resolution
//0001 2g 244ug/LSB
//0010 4g 488ug/LSB
//0100 8g 977ug/LSB
//1000 16g 1.95mg/LSB
//1111 32g 3.91mg/LSB
//Others 2g 244ug/LSB

//0x2c
//Duration = (NO_MOT_DUR<3:0> + 1) * 1s, if NO_MOT_DUR<5:4> =b00 
//Duration = (NO_MOT_DUR<3:0> + 4) * 5s, if NO_MOT_DUR<5:4> =b01 
//Duration = (NO_MOT_DUR<3:0> + 10) * 10s, if NO_MOT_DUR<5:4> =b1x 
//ANY_MOT_DUR<1:0>: any motion interrupt will be triggered when slope > ANY_MOT_TH for (ANY_MOT_DUR<1:0> + 1) samples 

//0x2e ANY MOTION MOT_CONF2
//TH= ANY_MOT_TH<7:0> * 16 * LSB 

#if defined(QMA7981_ANY_MOTION)
	reg_0x18 |= 0x07;
	reg_0x1a |= 0x01;
	reg_0x2c |= 0x00;	//BIT[0-1]	 (ANY_MOT_DUR<1:0> + 1) samples 
	
	qma7981_write_reg(0x18, reg_0x18);
	qma7981_write_reg(0x1a, reg_0x1a);
	qma7981_write_reg(0x2c, reg_0x2c);
	//qma7981_write_reg(0x2e, 0x14);		// 0.488*16*20 = 156mg
	//qma7981_write_reg(0x2e, 0x80);		// 0.488*16*128 = 1g
	//qma7981_write_reg(0x2e, 0xa0);		// 0.488*16*160 = 1.25g
	//qma7981_write_reg(0x2e, 0x60);		// 0.488*16*96 = 750mg
	//qma7981_write_reg(0x2e, 0x40);		// 0.488*16*64 = 500mg
	//qma7981_write_reg(0x2e, 0x20);		// 0.488*16*32 = 250mg
	qma7981_write_reg(0x2e, 0x40);		// 0.488*16*64 = 500mg

#if defined(QMA7981_ABNORMAL_SHAKE_CHECK)
	reg_0x10 = 0xe0;		// ODR: 65hz 15.48 ms
	qma7981_write_reg(0x10, reg_0x10);
	QMA7981_set_range(QMA7981_RANGE_8G);
	qma7981_write_reg(0x2e, 0x60);		// 0.977*16*96 = 1500mg
#endif
	
#if defined(QMA7981_SIGNIFICANT_MOTION)
	//SIG_MOT_TPROOF [BIT4-5]<1:0>: 00: T_PROOF=0.25s,  01: T_PROOF=0.5s,  10: T_PROOF=1s,  11: T_PROOF=2s 
	//SIG_MOT_TSKIP[BIT2-3]<1:0>: 00: T_SKIP=1.5s,  01: T_SKIP=3s,  10: T_SKIP=6s,  11: T_SKIP=12s 
	//SIG_MOT_SEL: 1: select significant motion interrupt ,  0: select any motion interrupt

	//qma7981_write_reg(0x2f, 0x0c|0x01);
	qma7981_write_reg(0x2f, 0x01);		// bit0   1 significant motion, 0: any motion.

	reg_0x19 |= 0x01;
	qma7981_write_reg(0x19, reg_0x19);
#endif
#endif
#if defined(QMA7981_NO_MOTION)
	reg_0x18 |= 0xe0;
	reg_0x1a |= 0x80;
	reg_0x2c |= 0x00;	//1s 	//0x24;

	qma7981_write_reg(0x18, reg_0x18);
	qma7981_write_reg(0x1a, reg_0x1a);
	qma7981_write_reg(0x2c, reg_0x2c);
	qma7981_write_reg(0x2d, 0x14);	//无运动中断阈值
#endif

#if defined(QMA7981_HAND_UP_DOWN)

	reg_0x16 |= 0x06;   //启用中断
	reg_0x19 |= 0x06;	//将中断映射到INT1

	qma7981_write_reg(0x16, reg_0x16);
	qma7981_write_reg(0x19, reg_0x19);
	// hand down	
#if 0	// swap xy
	read_reg(0x42, &reg_0x42, 1);
	reg_0x42 |= 0x80;		// 0x42 bit 7 swap x and y
	qma7981_write_reg(0x42, reg_0x42);
#endif
#endif

#if defined(QMA7981_DATA_READY)
	reg_0x1a |= 0x10;
	qma7981_write_reg(0x17, 0x10);
	qma7981_write_reg(0x1a, reg_0x1a);
#endif

#if defined(QMA7981_INT_LATCH)
	qma7981_write_reg(0x21, 0x1f);	// default 0x1c, step latch mode
#endif

#if defined(QMA7981_DOUBLE_TRIPLE_CLICK)
	//memset(&g_click, 0, sizeof(g_click));
	g_click.check_click = 1;
	g_click.click_num = 0;
	g_click.static_num = 0;
	g_click.t_msec_1 = 200;
	g_click.t_msec_2 = 8;
	g_click.t_msec_out = 350;
#endif
#if defined(QMA7981_ABNORMAL_SHAKE_CHECK)
	g_shake.check_shake = 1;
	g_shake.shake_num = 0;
	g_shake.t_msec_1 = 200;
	g_shake.t_msec_out = 500;
#endif

   	return ret;
}
//========================================================================
// 描述: QMA7981初始化.
// 参数: none.
// 返回: 1：正常；0：错误.
//========================================================================
uint8 qma7981_init()
{
	uint8 ret = 0;
    uint8 chip_id = 0;

    hardiic_init();

	delay(100);

    qma7981_write_reg(QMA7981_REG_POWER_CTL, 0x80);
    qma7981_read_reg(QMA7981_CHIP_ID,&chip_id,1);
    if((chip_id>=0xe0) && (chip_id<=0xe7))	
	{
        ret = 1;
		qma7981_initialize();
    }

	#if defined(QMA7981_HAND_UP_DOWN)
  	// 参数: wake_sum:手部动作强度(0~31); diff:两次动作的微分值(0~15); period:唤醒时间(0~2047).
 	//		   timeout:唤醒超时时间(0~4095);	hd_z:放下时的z阈值(0~7); hd_x:放下时的x阈值(0~7);
	qma7981_raise_config(20 , 0, 20, 4095,7,3);	//中断唤醒配置
	#endif

	return ret;
}

//========================================================================
// 描述: QMA7981设置范围.
// 参数: QMA7981_RANGE_2/4/8/16/32G.
// 返回: none.
//========================================================================
void qma7981_set_range(uint8 range)
{
	if(range == QMA7981_RANGE_4G)
		g_QMA7981.lsb_1g = 2048;
	else if(range == QMA7981_RANGE_8G)
		g_QMA7981.lsb_1g = 1024;
	else if(range == QMA7981_RANGE_16G)
		g_QMA7981.lsb_1g = 512;
	else if(range == QMA7981_RANGE_32G)
		g_QMA7981.lsb_1g = 256;
	else
		g_QMA7981.lsb_1g = 4096;
	
	qma7981_write_reg(QMA7981_REG_RANGE, range);	
}

//========================================================================
// 描述: QMA7981读三轴加速度原始数据.
// 参数: 数据地址.
// 返回: none.
//========================================================================
void qma7981_read_raw_xyz(int32 *_data)
{
	uint8 databuf[6] = {0}; 	

	qma7981_read_reg(QMA7981_XOUTL, databuf, 6);
	
	_data[0] = (short)((databuf[1]<<8)|(databuf[0]));
	_data[1] = (short)((databuf[3]<<8)|(databuf[2]));
	_data[2] = (short)((databuf[5]<<8)|(databuf[4]));
	_data[0] = _data[0]>>2;
	_data[1] = _data[1]>>2;
	_data[2] = _data[2]>>2;
}

//========================================================================
// 描述: QMA7981读三轴加速度加速度值.
// 参数: 数据地址.
// 返回: none.
//========================================================================
void qma7981_read_acc(int32 *accData)
{
	int32 rawData[3];

	qma7981_read_raw_xyz(rawData);
	// accData[g_QMA7981.cvt.map[0]] = g_QMA7981.cvt.sign[0]*rawData[0];
	// accData[g_QMA7981.cvt.map[1]] = g_QMA7981.cvt.sign[1]*rawData[1];
	// accData[g_QMA7981.cvt.map[2]] = g_QMA7981.cvt.sign[2]*rawData[2];

	accData[0] = (rawData[0]*GRAVITY_EARTH_1000)/(g_QMA7981.lsb_1g);
	accData[1] = (rawData[1]*GRAVITY_EARTH_1000)/(g_QMA7981.lsb_1g);
	accData[2] = (rawData[2]*GRAVITY_EARTH_1000)/(g_QMA7981.lsb_1g);
}

//========================================================================
// 描述: QMA7981读步数.
// 参数: none.
// 返回: 步数.
//========================================================================
#if defined(QMA7981_STEPCOUNTER)
uint32 qma7981_read_stepcounter()
{
	uint8 _data[3];
	uint32 step_num;

    qma7981_read_reg(QMA7981_STEP_CNT_L, _data, 2);
	qma7981_read_reg(QMA7981_STEP_CNT_M, &_data[2], 1);
	step_num = (uint32)(((uint32)_data[2]<<16)|((uint32)_data[1]<<8)|_data[0]);
	
#if defined(QMA7981_CHECK_ABNORMAL_DATA)
	QMA7981_check_abnormal_data(step_num, &step_num);

#endif
#if defined(QMA7981_STEP_DEBOUNCE_IN_INT)
	step_num = QMA7981_step_debounce_read_data(step_num);
#endif

	return step_num;
}
#endif

//========================================================================
// 描述: QMA7981中断配置.
// 参数: none.
// 返回: 中断类型.
//========================================================================
unsigned char qma7981_irq_hdlr()
{
	unsigned char r_data[3];
	//unsigned char reg_0x18 = 0;
	unsigned char reg_0x1a = 0;
	unsigned char int_type = 0;

	qma7981_read_reg(0x09,r_data,3);
	if(r_data[0] & 0xF)		//产生ANY_MOT中断
	{
#if defined(QMA7981_DOUBLE_TRIPLE_CLICK)
		if(g_click.check_click)
		{
#if defined(QMA7981_NO_MOTION)
			qma7981_read_reg(0x1a,&reg_0x1a,1);
			reg_0x1a |= 0x80;			// enable nomotion
			//reg_0x1a &= 0xfe;			// disable anymotion
			qma7981_write_reg(0x1a, reg_0x1a);
#endif
			//bsp_stop_timer(0);
			g_click.check_click = 0;
			g_click.static_num = 0;			
			g_click.click_num++;
			//bsp_start_timer(0, g_click.t_msec_1, click_timer_cbk_1);
		}		
#endif

#if defined(QMA7981_ABNORMAL_SHAKE_CHECK)
		if(g_shake.check_shake)
		{
			//bsp_stop_timer(0);
			g_shake.check_shake = 0;		
			g_shake.shake_num++;
			//bsp_start_timer(0, g_shake.t_msec_1, shake_timer_cbk_1);
		}
#endif
		int_type = 1;
	}
	else if(r_data[0] & 0x80)		//产生no_motion中断
	{	
		//bsp_stop_timer(0);
		qma7981_read_reg(0x1a,&reg_0x1a,1);
		//reg_0x1a &= 0x7f;
		reg_0x1a |= 0x80;
		qma7981_write_reg(0x1a, reg_0x1a);		// disable nomotion
		int_type = 2;
	}
	else if(r_data[1] & 0x01)		//significant interrupt
	{	
		int_type = 3;
		
		qma7981_read_reg(0x1a,&reg_0x1a,1);
		reg_0x1a |= 0x80;			// enable nomotion
		//reg_0x1a &= 0xfe;			// disable anymotion
		qma7981_write_reg(0x1a, reg_0x1a);
	}
	else if(r_data[1] & 0x40)
	{	
		int_type = 4;
	}
	else if(r_data[1] & 0x08)		//计步中断
	{
		int_type = 5;
	}
#if defined(QMA7981_HAND_UP_DOWN)
	else if(r_data[1] & 0x02)		//举手中断
	{
		int_type = 6;
	}
	else if(r_data[1] & 0x04)		//手放下中断
	{
		int_type = 7;
	}
#endif
	return int_type;
}
