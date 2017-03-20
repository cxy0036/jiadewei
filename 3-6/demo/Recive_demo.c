//  File Function: N76E885 demo 
//***********************************************************************************************************

#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "ex-int1.h"
#include "time0.h"

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    Set_All_GPIO_Quasi_Mode;
	
		time0_init();
		INT1_ISR_init();
		set_EA;

	//set_TR0;
	//Timer1_Delay1ms(1);
	
    while(1)
    {
				set_GPIO1;												// Tiny board GPIO1 LED define in Common.h
    }
}


