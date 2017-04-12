#include	"time1.h"

//#define	TH1_INIT_1ms	13290
//#define	TL1_INIT_1ms	13290
//#define	u8TH1_Tmp_1ms	(65536-TH1_INIT_1ms)/256
//#define	u8TL1_Tmp_1ms	(65536-TL1_INIT_1ms)%256

//UINT8	u8TH1_Tmp_1ms,u8TL1_Tmp_1ms;
bit		minute_1_flag = 0;
UINT16	count = 0;

void timer1_init(void)
{
//	set_T1M;		//ÏµÍ³Ê±ÖÓ
	clr_T1M;
//	u8TH1_Tmp_1ms = (65536-TH1_INIT_1ms)/256;
//	u8TL1_Tmp_1ms = (65536-TL1_INIT_1ms)%256;
	TIMER1_MODE1_ENABLE;
	TH1 = HIBYTE(TIMER_DIV12_VALUE_10ms);
    TL1 = LOBYTE(TIMER_DIV12_VALUE_10ms);
	set_ET1;
}

void Timer1_ISR (void) interrupt 3 
{
	clr_TR1;
	TH1 = HIBYTE(TIMER_DIV12_VALUE_10ms);
    TL1 = LOBYTE(TIMER_DIV12_VALUE_10ms);
	count++;
	if(count>6000)
	{
		minute_1_flag = 1;
		count = 0;
	}
	set_TR1;
}