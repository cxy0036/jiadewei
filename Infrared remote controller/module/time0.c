#include	"time0.h"

extern	UINT8	adc_count;

UINT8	adc_data = 0;
UINT8	adc_V = 0;
bit		adc_V_flag = 0;
UINT8	u8TH0_Tmp_1ms,u8TL0_Tmp_1ms;
UINT16	adc_flag=0;

#define	TH0_INIT_1ms	13290
#define	TL0_INIT_1ms	13290



void timer0_init(void)
{
	set_T0M;		//ÏµÍ³Ê±ÖÓ
	u8TH0_Tmp_1ms = (65536-TH0_INIT_1ms)/256;
	u8TL0_Tmp_1ms = (65536-TL0_INIT_1ms)%256;
	TH0 = u8TH0_Tmp_1ms;
    TL0 = u8TL0_Tmp_1ms;
	set_ET0;
}

void Timer0_ISR (void) interrupt 1 
{
	TH0 = u8TH0_Tmp_1ms;
    TL0 = u8TL0_Tmp_1ms;
	adc_flag++;
	if(adc_flag>=5000)
	{
//		P12=~P12;
		adc_data += adc_start();
		if(adc_count == times)
		{
			adc_V =	adc_data/100;
			adc_count = 0;
			adc_V_flag = 1;
		}
//		if(adc_V_flag)
//		{
//			if(adc_V < V_3_3)
//			{
//				//ST_BY = 1;
//				BT_POWER = 0;
//				__delay_ms(50);
//				ST_BY = 0;
//			}
//			else if(adc_V < V_3_5)
//			{
//				LOW_BAT_NOTIFY = 0;
//			}
//			else
//			{
//				LOW_BAT_NOTIFY = 1;
//			}
//		}
		adc_flag = 0;
	}
}