
#define KEY_GLOBALS
#include "KEY_Scan.h"

//#define POWER_KEY   		P15
#define KEY_VALUE			1
#define KEY_NULL			0

//定义长按键的TICK数,以及连_发间隔的TICK数
#define KEY_LONG_PERIOD		100
#define KEY_CONTINUE_PERIOD	25
//定义按键返回值状态(按下,长按,连_发,释放)
#define KEY_DOWN		0x80
//#define KEY_short		0x40
#define KEY_SHORT		0x40
#define KEY_LONG		0x20
#define KEY_CONTINUE	0x20
#define KEY_UP			0x10
//#define KEY_UP			5
//定义按键状态
#define KEY_STATE_INIT		0	//初始状态
#define KEY_STATE_WOBBLE	1	//消抖状态
#define KEY_STATE_PRESS		2	//按下状态
#define KEY_STATE_LONG		3	//长按状态
#define KEY_STATE_CONTINUE	4	//连按状态
#define KEY_STATE_RELEASE	5	//释放状态

//char n = 0,m = 0,k=0,j=0,flag = 0;
uint8_t	SYS_power_flag = 0;
uint16_t key_count = 0;
uint8_t Channel[1] = {0x00};
//	static uint8_t s_u8LastKey = KEY_NULL,BOTH_EDGE_ROTOB = 1,BOTH_EDGE_ROTOA = 1;

void Sys_power_on( void )
{
//	ST_BY = 1;
//	CLK_SysTickDelay(1000);
//	ST_BY = 0;
//	CLK_SysTickDelay(1000);
	ST_BY = 1;
	CLK_SysTickDelay(200000);	
	POWER = 0;
	SYS_power_flag = 1;
//	_RST = 1;
//	BT_DET = 1;
//	NTP_8230_INIT();
//	_RST_8230();

	
//	I2C_SW_Open(50000);
//	I2C_SW_Send( 0x54,NTP_8230,350);
	LED_R = 0;LED_B = 0;LED_G = 0;	
}

void Sys_power_off( void )
{
//	Soft_Mute_flag = 1;
//	Soft_Mute();
//	BT_DET = 0;
//	_RST = 0;
//	PWM_Switching_flag = 1;
//	PWM_Switching();
//	PWM_MASK();
//	Driver_Control();
//	CLK_SysTickDelay(20000);
	BT_POWER = 0;
	ST_BY = 0;
	SYS_power_flag = 0;
	LED_R = 1;LED_B = 1;LED_G = 1;
	POWER_OFF = 0;
}

void Channel_select( uint8_t* Channel )
{
	switch( *Channel )
	{
		case 0:
			_4052_A = 0;
			_4052_B = 0;
			if( SYS_power_flag )
			{
//				Power_Meter_Detect();
				LED_R = 0;LED_B = 1;LED_G = 1;		
			}
			*Channel = 0xff;
			break;
		case 1:
			_4052_A = 1;
			_4052_B = 0;
			if( SYS_power_flag )
			{
				BT_POWER = 1;
//				Power_Meter_Detect();
				LED_R = 1;LED_B = 0;LED_G = 1;		
			}
			*Channel = 0xff;
			break;
		case 2:
			_4052_A = 0;
			_4052_B = 1;
			if( SYS_power_flag )
			{
				BT_POWER = 0;
//				Power_Meter_Detect();
				LED_R = 1;LED_B = 1;LED_G = 0;		
			}
			*Channel = 0xff;
			break;
		case 3:
			_4052_A = 1;
			_4052_B = 1;
			if( SYS_power_flag )
			{
//				Power_Meter_Detect();
				LED_R = 0;LED_B = 0;LED_G = 0;		
			}
			*Channel = 0xff;
			break;
		default:
			break;
	}
}
