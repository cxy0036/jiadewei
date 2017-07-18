
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


uint8_t ADC_V=0;

//void AUDIO_TEST(void)
//{
//	if(SYS_power_flag)
//	{
//		if(AUDIO_DET)_RST = 0;
//	}
//}
void ADC_init(void)
{
	CLK_EnableModuleClock(ADC_MODULE);
	CLK_SetModuleClock(ADC_MODULE,CLK_CLKSEL1_ADC_S_XTAL,CLK_CLKDIV_ADC(6));
		/* Set P3.0 to ADC channel 6 input pin */
	SYS->P1_MFP = SYS_MFP_P14_AIN4;
	/* Analog pin OFFD to prevent leakage */
	P1->OFFD |= (1<<4) << GPIO_OFFD_OFFD_Pos;	
	// Enable channel 6
    ADC_Open(ADC, 0, 0, 0x01 << 4);
	// Power on ADC
    ADC_POWER_ON(ADC);
	// Enable ADC convert complete interrupt
    ADC_EnableInt(ADC, ADC_ADF_INT);
    NVIC_EnableIRQ(ADC_IRQn);	
}
void ADC_IRQHandler(void)
{
    uint32_t u32Flag;

    // Get ADC comparator interrupt flag
    u32Flag = ADC_GET_INT_FLAG(ADC, ADC_ADF_INT);

    // Get ADC convert result
//    printf("Convert result is %x\n", (uint32_t)ADC_GET_CONVERSION_DATA(ADC, 0));
	ADC_V = (uint32_t)ADC_GET_CONVERSION_DATA(ADC, 0);
    ADC_CLR_INT_FLAG(ADC, u32Flag);
}
void Sys_power_on( void )
{

	ST_BY = 1;
	CLK_SysTickDelay(200000);	
//	POWER = 0;
	SYS_power_flag = 1;
	LED_R = 0;LED_B = 0;LED_G = 0;	
}

void Sys_power_off( void )
{
	BT_POWER = 0;
	ST_BY = 0;
	SYS_power_flag = 0;
	LED_R = 1;LED_B = 1;LED_G = 1;
//	POWER = 1;
}

void Channel_select( uint8_t* Channel )
{
	uint8_t p[2];
	p[0] = 31;
	_RST = 0;
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
			p[1] = 0;
			I2C_SW_Send(_24c02_addr,p,2);
			*Channel = 0x00;
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
			p[1] = 1;
			I2C_SW_Send(_24c02_addr,p,2);
			*Channel = 0x01;
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
			p[1] = 2;
			I2C_SW_Send(_24c02_addr,p,2);
			*Channel = 0x02;
			break;
		case 3:
			_4052_A = 1;
			_4052_B = 1;
			if( SYS_power_flag )
			{
//				Power_Meter_Detect();
				LED_R = 0;LED_B = 0;LED_G = 0;		
			}
			p[1] = 3;
			I2C_SW_Send(_24c02_addr,p,2);
			*Channel = 0x03;
			break;
		default:
			break;
	}
	CLK_SysTickDelay(10000);
	_RST = 1;
}
