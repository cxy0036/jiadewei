#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "IR_recive.h"
#include "Codingformat_Define.h"


UINT8 dat[Data_count]={0},key_press=0,n=0;
bit Recive_flag=0,long_press_flag=0;

void INT1_ISR_init(void)
{
		set_EX1;							
		set_IT1;			//下降沿触发			
		P17 = 1;
}


void INT1_ISR(void)	interrupt 2
{
		UINT8 i=0,j=0;
		clr_EX1;
		clr_GPIO1;																//亮指示灯
		Timer1_Delay1ms(1);
		if(P17)																		//抖动无用中断
		{
				set_EX1;
				return;
		}
		
#if 0
	for(i=0;i<33;i++)
	{
		while(!P17);//low
		while(P17);//high
	}
	while(!P17);//low
	set_EX1;
#endif
	
		BootCode_OR_RepeatCode();
		if(!long_press_flag)
		{
				one_press();
		}
		else
		{
				long_press();
		}
		
		set_EX1;
	
	#if 0
		for(i=0;i<First_Boot_code-2;i++)						//9ms low
		{
				if(P17)
				{
						dat_clr();
						set_EX1;
						return;
				}
				Timer1_Delay1ms(1);
		}
		while(!P17);
	
		for(i=0;i<Second_Boot_code;i++)						//4ms	high
		{
				Timer1_Delay1ms(1);
				if(!P17)
				{
						dat_clr();
						set_EX1;
						return;
				}
		}
		while(P17);
	
		for(i=0;i<Data_count;i++)							//32bit数据码
		{
				for(j=0;j<8;j++)
				{
						while(!P17);									//0.56ms	low
					
						Timer1_Delay1ms(Data_0_1_code);
						if(P17)												//数据 1	high
						{
								dat[i] >>= 1;
								dat[i] |= 0x80;
								while(P17);
						}
						else													//数据 0	high
						{
								dat[i] >>= 1;
						}
				}
				
		}
			
		while(!P17);													//0.56ms	low
		
		for(i=0;i<Stop_code;i++)					//40ms		high
		{
				Timer1_Delay1ms(1);
				if(!P17)
				{
					dat_clr();
					set_EX1;
					return;
				}
		}
//		while(P17);	
		
		Data_Check();
		Timer1_Delay1ms(2);									//delay2ms
		
		for(i=0;i<First_Boot_code-2;i++)				
		{
				Timer1_Delay1ms(1);
				if(P17)
				{
						dat_clr();
						set_EX1;
						return;
				}
		}
		while(!P17);													//8ms		low

//		for(i=0;i<Second_Boot_code;i++)				
//		{
//				Timer1_Delay1ms(1);
//				if(!P17)
//				{
//						dat_clr();
//						set_EX1;
//						return;
//				}
//		}
		while(P17);														//2ms		high
		
		while(!P17);													//0.56ms	low
//		Timer1_Delay1ms(2000);									//delay2ms
//		while(P17);
		
		dat_clr();
		set_EX1;
		return;
		#endif
}


void Data_Check(void)
{
		if(dat[2] == ~dat[3])
		{
				key_press = dat[2];
				dat_clr();
				Recive_flag = 1;
		}
		else
		{
				key_press = 0;
				Recive_flag = 0;
		}
}

void dat_clr(void)
{
		UINT8	i;    
		for(i=0;i<Data_count;i++)
		{
				dat[i] = 0;
		}		
}

void one_press(void)
{
		UINT8	i=0,j=0;  
	
		for(i=0;i<Data_count;i++)							//32bit数据码
		{
				for(j=0;j<8;j++)
				{
						while(!P17);									//0.56ms	low
					
						Timer1_Delay1ms(Data_0_1_code);
						if(P17)												//数据 1	high
						{
								dat[i] >>= 1;
								dat[i] |= 0x80;
								while(P17);
						}
						else													//数据 0	high
						{
								dat[i] >>= 1;
						}
				}
				
		}
			
		while(!P17);													//0.56ms	low
		
		Timer1_Delay1ms(60);
		while(!P17);
		Data_Check();
		n = 1;
		
#if 0		
		for(i=0;i<Stop_code;i++)							//40ms		high
		{
				Timer1_Delay1ms(1);
				if(!P17)
				{
					dat_clr();
					set_EX1;
					return;
				}
		}
//		while(P17);	
		
		Data_Check();
		Timer1_Delay1ms(2);									//delay2ms
		
		for(i=0;i<First_Boot_code-2;i++)				
		{
				Timer1_Delay1ms(1);
				if(P17)
				{
						dat_clr();
						set_EX1;
						return;
				}
		}
		while(!P17);													//8ms		low

		while(P17);														//2ms		high
		
		while(!P17);													//0.56ms	low
#endif
	
}

void long_press(void)
{
//		UINT8	i;  
	
		while(!P17);
		Timer1_Delay1ms(80);
		n++;
}

void BootCode_OR_RepeatCode(void)
{
		UINT8	i=0;
		UINT32 k=0;
		for(i=0;i<First_Boot_code-2;i++)						//9-1ms low
		{
				Timer1_Delay1ms(1);
				if(P17)
				{
						dat_clr();
						set_EX1;
						return;
				}
		}
		while(!P17);
		
		do																				//4ms_OR_2ms	high
		{
				k++;
				if((k>200&&k<400)&&(!P17))
				{
						long_press_flag = 1;
						break;
				}
				else
				{
						long_press_flag = 0;
				}
		}while(P17);
		while(!P17);
		
#if 0		
		for(i=0;i<Second_Boot_code;i++)						//4ms_OR_2ms	high
		{
				Timer1_Delay1ms(1);
				if((!P17)&&(i>15))
				{
						long_press_flag = 1;
						break;
				}
				else
				{
						long_press_flag = 0;
				}
		}
		while(P17);	
#endif
}