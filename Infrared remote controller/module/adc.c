#include "adc.h"

/*************	本地变量声明	**************/
UINT8	adc_count = 0;
//UINT8	adc_data = 0;
//UINT8	adc_V = 0;
//bit		adc_V_flag = 0;

//void Timer0_ISR_adc (void) interrupt 1 
//{
//	adc_data += adc_start();
//	if(adc_count == times)
//	{
//		adc_V =	adc_data/100;
//		adc_count = 0;
//		adc_V_flag = 1;
//	}
//	if(adc_V_flag)
//	{
//		if(adc_V < V_3_3)
//		{
//			ST_BY = 0;
//			BT_POWER = 0;
//		}
//		else if(adc_V < V_3_5)
//		{
//			LOW_BAT_NOTIFY = 0;
//		}
//		else
//		{
//			LOW_BAT_NOTIFY = 1;
//		}
//	}
//}
UINT8	adc_start(void)
{
	UINT8	adc_dat = 0;
	clr_ADCF;
	set_ADCS;
	while(ADCF == 0);
	adc_dat = ADCRH;
	adc_count++;
	return	adc_dat;
}

void	adc_init(void)
{
	ADCCON0&=0xc0;		//AD转换启动AD标志完成
	AINDIDS=0x00;		
	AIN(AINx);			//通道选择并配置
	ADCCON1|=SET_BIT0;	//ADC使能
}

void	AIN	(UINT8	adc_AINx)
{
	switch(adc_AINx)
	{
		case	AIN0:
			ADCCON0 |= 0x00;
			P17_Input_Mode;
			AINDIDS|=SET_BIT0;
			break;
		
		case	AIN1:
			ADCCON0 |= 0x01;
			P30_Input_Mode;
			AINDIDS|=SET_BIT1;
			break;
		
		case	AIN2:
			ADCCON0 |= 0x02;
			P07_Input_Mode;
			AINDIDS|=SET_BIT2;
			break;
			
		case	AIN3:
			ADCCON0 |= 0x03;
			P06_Input_Mode;
			AINDIDS|=SET_BIT3;
			break;
			
		case	AIN4:
			ADCCON0 |= 0x04;
			P05_Input_Mode;
			AINDIDS|=SET_BIT4;
			break;
			
		case	AIN5:
			ADCCON0 |= 0x05;
			P04_Input_Mode;
			AINDIDS|=SET_BIT5;
			break;
			;
		case	AIN6:
			ADCCON0 |= 0x06;
			P03_Input_Mode;
			AINDIDS|=SET_BIT6;
			break;
			
		case	AIN7:
			ADCCON0 |= 0x07;
			P11_Input_Mode;
			AINDIDS|=SET_BIT7;
			break;
			
		default:
			break;
	}
}