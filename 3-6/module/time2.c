#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "time2.h"

UINT32	T2_count=0;


void time2_init(void)
{
		TIMER2_DIV_4;
		TIMER2_Auto_Reload_Delay_Mode;

		RCMP2L = TIMER_DIV4_VALUE_100us;
		RCMP2H = TIMER_DIV4_VALUE_100us>>8;
		TL2 = 0;
		TH2 = 0;
    set_ET2;                                    // Enable Timer2 interrupt		
}


/************************************************************************************************************
*    Timer2 interrupt subroutine
************************************************************************************************************/
void Timer2_ISR (void) interrupt 5
{
	  clr_TF2;                                //Clear Timer2 Interrupt Flag
		T2_count++;
}