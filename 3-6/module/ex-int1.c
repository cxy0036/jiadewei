#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "ex-int1.h"
//#include "time2.h"

extern UINT32	T2_count;

UINT8 dat[4]={0};
long m=0;

void INT1_ISR_init(void)
{
		set_EX1;							
		set_IT1;			//下降沿触发				
}

void INT1_ISR(void)	interrupt 2
{
	
	UINT8 i=0,j=0;
	
	clr_EX1;
	clr_GPIO1;									//亮指示灯
	for(i=0;i<8;i++)						//8ms
	{
		Timer1_Delay1ms(1);
		if(P17)
		{
			set_EX1;
			return;
		}
	}
	while(!P17);
	
	for(i=0;i<4;i++)				//4ms
	{
		Timer1_Delay1ms(1);
		if(!P17)
		{
			set_EX1;
			return;
		}
	}
	while(P17);
	
		for(i=0;i<4;i++)						//32bit数据码
		{
				for(j=0;j<8;j++)
				{
						while(!P17);				//0.56ms
					
						Timer1_Delay1ms(1);
						if(P17)							//数据 1
						{
								dat[i] >>= 1;
								dat[i] |= 0x80;
								while(P17);
						}
						else								//数据 0
						{
								dat[i] >>= 1;
						}
				}
				
		}
			
		while(!P17);								//0.56ms
		
		for(i=0,j=0;i<40;i++)
		{
				Timer1_Delay1ms(1);
				if(!P17)
				{
					set_EX1;
					return;
				}
				j++;
		}
		while(P17);									//40ms
		
		set_EX1;
		return;
}