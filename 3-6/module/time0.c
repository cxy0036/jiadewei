#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "time0.h"

UINT32	T2_count=0;
#define TH0_INIT        133											//100us
#define TL0_INIT        133

UINT8 u8TH0_Tmp,u8TL0_Tmp;


void time0_init(void)
{
		TIMER0_MODE1_ENABLE;
		clr_T0M;																		//1/12Fsys
    
    u8TH0_Tmp = (65536-TH0_INIT)/256;
    u8TL0_Tmp = (65536-TL0_INIT)%256;    
    
    TH0 = u8TH0_Tmp;
    TL0 = u8TL0_Tmp;  
    
		set_ET0;                                    //enable Timer0 interrupt
}


/************************************************************************************************************
*    Timer2 interrupt subroutine
************************************************************************************************************/
void Timer0_ISR (void) interrupt 1
{
	  TH0 = u8TH0_Tmp;
    TL0 = u8TL0_Tmp;    
		T2_count++;
}