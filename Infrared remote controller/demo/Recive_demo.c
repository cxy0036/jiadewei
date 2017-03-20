//  File Function: N76E885 demo 
//***********************************************************************************************************
//#define		_EX_
#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "IR_recive.h"
//#include	"Key_Check.h"
#include "I2C.h"
#include	"NPCA110P.h"

extern	UINT8  code	g_abMaxxDSPCommands[];
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
		UINT16 i=0,j=0;
		UINT8 *p = g_abMaxxDSPCommands;
	
/* init mcu */	
    Set_All_GPIO_Quasi_Mode;
		INT1_ISR_init();
		//set_EA;
		Init_NPCA110P_I2C();

/* transmit bytes to I2C */		
		for(i=0;i<306;i++)	
		{
			writeString_NPCA110P(3,p);                         /* I2C Master will send 0x55,0xAA,.... to slave */
			p += 3; 
			for(j=0;j<1340;j++);															/* every time delay 1ms */
		}

		
    while(1)
    {
				set_GPIO1;												// Tiny board GPIO1 LED define in Common.h
				if(Recive_flag)
				{
						//key_check(key_press);
						Recive_flag = 0;
				}
    }
}


