/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2016 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2016
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 UART-0 Mode3 demo code
//***********************************************************************************************************

#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_define.h"

#define BUFFER_SIZE		16

UINT8  UART_BUFFER[BUFFER_SIZE],temp;
UINT16 u16CNT=0,u16CNT1=0;
bit riflag;

/**
 * FUNCTION_PURPOSE: serial interrupt, echo received data.
 * FUNCTION_INPUTS: P3.0(RXD) serial input
 * FUNCTION_OUTPUTS: P3.1(TXD) serial output
 */
void serial_IT(void) interrupt 4 
{
    if (RI) 
    {                                       /* if reception occur */
        clr_RI;                             /* clear reception flag for next reception */
        UART_BUFFER[u16CNT] = SBUF;
        u16CNT ++;
				riflag =1;
    }
    if(TI)
    {
        clr_TI;                             /* if emission occur */
    }
}
/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{

   
    P06_Quasi_Mode;               					//Set UART GPIO are Quasi Mode
		P07_Quasi_Mode;
    InitialUART0_Timer1(115200);            /* 115200 Baud Rate */
	
    SCON = 0xD2;														// Special setting the mode 3 
    
    set_ES;                                 //enable UART interrupt
    set_EA;                                 //enable global interrupt
    clr_TB8;
    Send_Data_To_UART0(0x53);								//Send "start" ascii code show reset initial status
	  Send_Data_To_UART0(0x74);
	  Send_Data_To_UART0(0x61);
	  Send_Data_To_UART0(0x72);
	  Send_Data_To_UART0(0x74);
	
    while(1)
		{
			if (riflag)
			{
				temp = SBUF;												//This part send the receive data from RXD to TXD 
				Send_Data_To_UART0(temp);
				riflag = 0;
			}
		}
	
}

