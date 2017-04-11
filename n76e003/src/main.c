
#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

void main (void) 
{
//	Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
//	InitialUART0_Timer1(115200);
	set_CLOEN;  
  	P12_PushPull_Mode;
	P00_PushPull_Mode;
	P01_PushPull_Mode;
  while(1)
  {
//        clr_GPIO1;												// Tiny board GPIO1 LED define in Common.h
//        Timer3_Delay1ms(300);
//		P00 = 1;
//		P01 = 1;      
	  set_GPIO1;
//				Timer3_Delay1ms(300);
//				Send_Data_To_UART0(0x44);
  }
}
