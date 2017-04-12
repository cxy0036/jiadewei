#include "sysInit.h"

void	sys_init(void)
{
	SetSysClock();
	gpio_init();
	timer0_init();
	timer1_init();
	adc_init();
//	Enable_ADC_AIN0;
}

void	SetSysClock(void)
{
	CKSWT = 0x30;
	CKEN  = 0x30;
//	CKDIV = 0x02;
	__delay_10ms(2);
}

void gpio_init(void)
{
	P00_PushPull_Mode;
	P01_PushPull_Mode;
	P03_PushPull_Mode;
//	P04_PushPull_Mode;
	P04_Input_Mode;
	P05_Input_Mode;
	P06_Input_Mode;
	P07_Input_Mode;
	P10_PushPull_Mode;
	P11_PushPull_Mode;
	P12_PushPull_Mode;
	P13_PushPull_Mode;
	P14_PushPull_Mode;
	P17_Input_Mode;
	P30_PushPull_Mode;
	
//	BAT_DET		

	LOW_BAT_NOTIFY	= 0;
	ST_BY = 0;			
	BT_POWER = 0;		
//	BT_DET			

//	GPIO1		
//	GPIO2		
//	GPIO3		

	PLAY = 0;	
	REV = 0;			
	FWD = 0;			
	VOL_UP = 0;		
	VOL_DOWN = 0;	
	PAIR = 0;		
}

//void	time0_init(void)
//{
//	TIMER0_MODE1_ENABLE;
//	u8TH0_Tmp = (65536-TH0_INIT)/256;
//    u8TL0_Tmp = (65536-TL0_INIT)%256;
//	TH0 = u8TH0_Tmp;
//    TL0 = u8TL0_Tmp;
//	set_ET0;
//}

//void	adc_init(void)
//{
//	Enable_ADC_AIN0;
//}