#define Bluetooth_GLOBALS
#include "Bluetooth.h"

//uint8_t	BT_Flag = 0;

void Bluetooth_Test_Task(void)
{
	if( BT_POWER )
	{
		if(BT_DET)
		{
			LED_B = 0;
		}
		else
		{
			if(ledcount>0x1000)
			{
//				BT_Flag = 0;
				LED_B = ~LED_B;
				ledcount = 0;
			}
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}	
		}
	}
}

void BT_patch(void)
{
	if(BT_DET)
	{
		BT_REV = 0;	BT_FWD = 0;
		CLK_SysTickDelay(1000);
		BT_REV = 1;	BT_FWD = 1;
		CLK_SysTickDelay(7000*1000);
		BT_REV = 0;	BT_FWD = 0;
		CLK_SysTickDelay(1000);
	}
}
void BT_Play_Pause(void)
{
	if(BT_DET)
	{
		BT_REV = 0;	BT_FWD = 0;
		CLK_SysTickDelay(1000);
		BT_REV = 1;	BT_FWD = 1;
		CLK_SysTickDelay(300*1000);
		BT_REV = 0;	BT_FWD = 0;
		CLK_SysTickDelay(1000);
	}
}
//void BT_REV_TASK(void)
//{
//	;
//}
//void BT_FWD_TASK(void)
//{
//	;
//}


