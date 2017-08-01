
#define KEY_GLOBALS
#include "KEY_Scan.h"


uint8_t	SYS_power_flag = 0;
uint16_t key_count = 0;
uint8_t Channel[1] = {0x00};


uint16_t ADC_V=0x4fe;


void led_chang(uint32_t num)
{
	if(ledcount>num)
	{
		if(Channel[0]==1)
		{
			LED_G = ~LED_G;
		}
		if((Channel[0]==0)&&(BT_DET&BT_POWER))
		{
			LED_B = ~LED_B;
		}
		ledcount = 0;
	}
}

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
	ADC_V = (uint32_t)ADC_GET_CONVERSION_DATA(ADC, 0);
    ADC_CLR_INT_FLAG(ADC, u32Flag);
}
void Sys_power_on( void )
{

	ST_BY = 1;
	CLK_SysTickDelay(200000);	
	SYS_power_flag = 1;
}

void Sys_power_off( void )
{
	BT_POWER = 0;
	ST_BY = 0;
	SYS_power_flag = 0;
	LED_R = 1;LED_B = 1;LED_G = 1;
}

void Channel_select( uint8_t* Channel )
{
	uint8_t p[2];
	p[0] = 31;
	_RST = 0;
	switch( *Channel )
	{
//		case 2:
//			_4052_A = 0;
//			_4052_B = 0;
//			if( SYS_power_flag )
//			{
//				LED_R = 0;LED_B = 1;LED_G = 1;		
//			}
//			p[1] = 0;
//			I2C_SW_Send(_24c02_addr,p,2);
//			*Channel = 0x00;
//			break;
		case 0:		//Bluetooth
			CLK_SysTickDelay(200000);
			_4052_A = 1;
			_4052_B = 0;
			if( SYS_power_flag )
			{
				BT_POWER = 1;
				LED_R = 1;LED_B = 0;LED_G = 1;		
			}
			p[1] = 0;
			I2C_SW_Send(_24c02_addr,p,2);
			*Channel = 0x00;
			break;
		case 1:			//aux
			_4052_A = 0;
			_4052_B = 1;
			if( SYS_power_flag )
			{
				BT_POWER = 0;
				LED_R = 1;LED_B = 1;LED_G = 0;		
			}
			p[1] = 1;
			I2C_SW_Send(_24c02_addr,p,2);
			*Channel = 0x01;
			break;
//		case 3:
//			_4052_A = 1;
//			_4052_B = 1;
//			if( SYS_power_flag )
//			{
//				LED_R = 0;LED_B = 0;LED_G = 0;		
//			}
//			p[1] = 3;
//			I2C_SW_Send(_24c02_addr,p,2);
//			*Channel = 0x03;
//			break;
		default:
			break;
	}
	CLK_SysTickDelay(100000);
	_RST = 1;
}
