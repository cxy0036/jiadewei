#define Bluetooth_GLOBALS
#include "Bluetooth.h"

uint32_t	BT_Flag = 0;

void Bluetooth_Test_Task(void)
{
	if( SYS_power_flag )
	{
		if(BT_DET)
		{
			BT_Flag = 1;
		}
		else
		{
			BT_Flag = 0;
		}
	}
}

void BT_patch(void)
{
	BT_REV = 0;	BT_FWD = 0;
	CLK_SysTickDelay(1000);
	BT_REV = 1;	BT_FWD = 1;
	CLK_SysTickDelay(3000*1000);
	BT_REV = 0;	BT_FWD = 0;
	CLK_SysTickDelay(1000);
}
void BT_Play_Pause(void)
{
	BT_REV = 0;	BT_FWD = 0;
	CLK_SysTickDelay(1000);
	BT_REV = 1;	BT_FWD = 1;
	CLK_SysTickDelay(300*1000);
	BT_REV = 0;	BT_FWD = 0;
	CLK_SysTickDelay(1000);
}
void BT_REV_TASK(void)
{
	;
}
void BT_FWD_TASK(void)
{
	;
}


