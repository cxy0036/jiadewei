//  File Function: N76E885 demo 
//***********************************************************************************************************
#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "gpio.h"
#include "adc.h"
#include "bluetooth.h"
#include	"time0.h"


/*************	本地常量声明	**************/
//#define	TH0_INIT_1ms	1340
//#define	TL0_INIT_1ms	1340


/*************	本地变量声明	**************/
//UINT8	u8TH0_Tmp_1ms,u8TL0_Tmp_1ms;

/*************	本地函数声明	**************/
void	sys_init(void);

/*************  外部函数和变量声明 *****************/

void	SetSysClock(void)
{
	CKSWT = 0x30;
	CKEN  = 0x30;
}
void	sys_init(void)
{
	SetSysClock();
	Set_All_GPIO_Quasi_Mode;
	TIMER0_MODE1_ENABLE;
}


/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
//	P12_PushPull_Mode;
//	P14_PushPull_Mode;
	UINT16	N_1s=0;
	bit sys_flag=0;
	sys_init();
	adc_init();
//	gpio_init();
	gpio_init();
	timer0_init();
//	set_T0M;		//系统时钟
//	u8TH0_Tmp_1ms = (65536-TH0_INIT_1ms)/256;
//	u8TL0_Tmp_1ms = (65536-TL0_INIT_1ms)%256;
//	TH0 = u8TH0_Tmp_1ms;
//    TL0 = u8TL0_Tmp_1ms;
//	set_ET0;
	set_EA;
	set_TR0;
	__delay_ms(5*100);//5s延时，等待有效电压的检测完成
	ST_BY = 1;
	BT_POWER = 1;
	while(1)
	{
//		Bluetooth_process();
		if(ST_BY && BT_POWER)
		{
			sys_flag = 1;
		}
		else
		{
			sys_flag = 0;
		}
		while(sys_flag)
//		while(BT_DET && sys_flag)
		{
			Bluetooth_process();
		}
//		while(!BT_DET)
//		{
//			__delay_ms(100);
//			N_1s++;
//			if(N_1s == 900)//15*60s时间
//			{
//				ST_BY = 0;
//				BT_POWER = 0;
//				N_1s = 0;
//			}
////	}
//		N_1s = 0;
	}
}