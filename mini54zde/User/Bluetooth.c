#define Bluetooth_GLOBALS
#include "Bluetooth.h"


void Bluetooth_Test_Task(void)
{
	if( BT_POWER )
	{
		if(BT_DET)
		{
			if(LED_Flag==0)
			{
				LED_B = 0;				
			}
		}
		else
		{
			if(ledcount>0x1000)
			{
				LED_B = ~LED_B;
				ledcount = 0;
			}
		}
	}
}

void BT_patch(void)
{
	if(BT_DET)
	{
		BT_REV = 1;	BT_FWD = 1;
		CLK_SysTickDelay(600000);
		CLK_SysTickDelay(600000);
		CLK_SysTickDelay(600000);
		CLK_SysTickDelay(600000);
		CLK_SysTickDelay(600000);
		CLK_SysTickDelay(600000);
		BT_REV = 0;	BT_FWD = 0;
	}
}
void BT_Play_Pause(void)
{
	if(BT_DET)
	{
		BT_REV = 1;	BT_FWD = 1;
		CLK_SysTickDelay(300000);
		BT_REV = 0;	BT_FWD = 0;
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


