#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#include "sysInit.h"
#include "bluetooth.h"

void	mcu_init(void)
{
	Set_All_GPIO_Quasi_Mode;
}

void main(void)
{
//	bit sys_flag = 0;
	mcu_init();
	sys_init();
	__delay_10ms(20);
	set_EA;
	set_TR0;
	__delay_10ms(500);
	ST_BY = 1;
	BT_POWER = 1;
	while(1)
	{
//		if(ST_BY && BT_POWER)
//		{
//			sys_flag = 1;
//		}
//		else
//		{
//			sys_flag = 0;
//		}
//		while(BT_DET && sys_flag)
//		while(sys_flag)
		while(ST_BY && BT_POWER)
		{
			Bluetooth_process();
//			while(!BT_DET)
//			{
//				__delay_10ms(10);
//				N_1s++;
//				if(N_1s == 9000)//15*60s ±º‰
//				{
//					BT_POWER = 0;
//					__delay_10ms(50);
//					ST_BY = 0;
//					N_1s = 0;
//					clr_EA;
//					while(1)
//					{
//						set_PD;						
//					}
//				}
//			}
//			N_1s = 0;		
		}

	}
}
