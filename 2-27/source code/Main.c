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
//  File Function: N76E885 ADC demo code
//***********************************************************************************************************

#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "INT1.h"
#include "Time2.h"



//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
#if 0
#define Enable_ADC_AIN0			ADCCON0&=0xF0;P17_Input_Mode;AINDIDS=0x00;AINDIDS|=SET_BIT0;ADCCON1|=SET_BIT0									//P17
#define Enable_ADC_AIN1			ADCCON0&=0xF0;ADCCON0|=0x01;P30_Input_Mode;AINDIDS=0x00;AINDIDS|=SET_BIT1;ADCCON1|=SET_BIT0		//P30
#define Enable_ADC_AIN2			ADCCON0&=0xF0;ADCCON0|=0x02;P07_Input_Mode;AINDIDS=0x00;AINDIDS|=SET_BIT2;ADCCON1|=SET_BIT0		//P07
#define Enable_ADC_AIN3			ADCCON0&=0xF0;ADCCON0|=0x03;P06_Input_Mode;AINDIDS=0x00;AINDIDS|=SET_BIT3;ADCCON1|=SET_BIT0		//P06
#define Enable_ADC_AIN4			ADCCON0&=0xF0;ADCCON0|=0x04;P05_Input_Mode;AINDIDS=0x00;AINDIDS|=SET_BIT4;ADCCON1|=SET_BIT0		//P05
#define Enable_ADC_AIN5			ADCCON0&=0xF0;ADCCON0|=0x05;P04_Input_Mode;AINDIDS=0x00;AINDIDS|=SET_BIT5;ADCCON1|=SET_BIT0		//P04
#define Enable_ADC_AIN6			ADCCON0&=0xF0;ADCCON0|=0x06;P03_Input_Mode;AINDIDS=0x00;AINDIDS|=SET_BIT6;ADCCON1|=SET_BIT0		//P03
#define Enable_ADC_AIN7			ADCCON0&=0xF0;ADCCON0|=0x07;P11_Input_Mode;AINDIDS=0x00;AINDIDS|=SET_BIT7;ADCCON1|=SET_BIT0		//P11
#define Enable_ADC_BandGap	ADCCON0|=0x0F;ADCCON1|=SET_BIT0																																//Band-gap 1.22V

#define PWM0_FALLINGEDGE_TRIG_ADC		ADCCON0&=~SET_BIT5;ADCCON0&=~SET_BIT4;ADCCON1&=~SET_BIT3;ADCCON1&=~SET_BIT2;ADCCON1|=SET_BIT1
#define PWM2_FALLINGEDGE_TRIG_ADC		ADCCON0&=~SET_BIT5;ADCCON0|=SET_BIT4;ADCCON1&=~SET_BIT3;ADCCON1&=~SET_BIT2;ADCCON1|=SET_BIT1
#define PWM4_FALLINGEDGE_TRIG_ADC		ADCCON0|=SET_BIT5;ADCCON0&=~SET_BIT4;ADCCON1&=~SET_BIT3;ADCCON1&=~SET_BIT2;ADCCON1|=SET_BIT1
#define PWM0_RISINGEDGE_TRIG_ADC		ADCCON0&=~SET_BIT5;ADCCON0&=~SET_BIT4;ADCCON1&=~SET_BIT3;ADCCON1|=SET_BIT2;ADCCON1|=SET_BIT1
#define PWM2_RISINGEDGE_TRIG_ADC		ADCCON0&=~SET_BIT5;ADCCON0|=SET_BIT4;ADCCON1&=~SET_BIT3;ADCCON1|=SET_BIT2;ADCCON1|=SET_BIT1
#define PWM4_RISINGEDGE_TRIG_ADC		ADCCON0|=SET_BIT5;ADCCON0&=~SET_BIT4;ADCCON1&=~SET_BIT3;ADCCON1|=SET_BIT2;ADCCON1|=SET_BIT1

#define P04_FALLINGEDGE_TRIG_ADC		ADCCON0|=0x30;ADCCON1&=0xF3;ADCCON1|=SET_BIT1;ADCCON1&=~SET_BIT6
#define P13_FALLINGEDGE_TRIG_ADC		ADCCON0|=0x30;ADCCON1&=0xF3;ADCCON1|=SET_BIT1;ADCCON1|=SET_BIT6
#define P04_RISINGEDGE_TRIG_ADC			ADCCON0|=0x30;ADCCON1&=~SET_BIT3;ADCCON1|=SET_BIT2;ADCCON1|=SET_BIT1;ADCCON1&=~SET_BIT6
#define P13_RISINGEDGE_TRIG_ADC			ADCCON0|=0x30;ADCCON1&=~SET_BIT3;ADCCON1|=SET_BIT2;ADCCON1|=SET_BIT1;ADCCON1|=SET_BIT6
#endif


#if 1
#define	boot_code_min	0x30//800//32000				//8ms
#define boot_code_max	0x37//1500//60000				//15ms
#define data0_min			80//3200				//0.8ms
#define data0_max			150//6000				//1.5ms
#define data1_min			200//8000				//2ms
#define data1_max			250//10000				//2.5ms
#define	Num						33					//32code


UINT8 		CodeNum=0,Code[5]={0};
UINT8			time=0,n=0;
BIT				First_INT=0,Start_Flag=0;
//-------------------------------------------------------------------------
void INT1_ISR()	interrupt 2
{
	n++;
	#if 1
		clr_TR0;
	time=TH0;
	TH0=0;
	TL0=0;
				set_TR0;
		clr_EX1;
		if(!First_INT)
		{
				time = 0;
				First_INT = 1;
		}
		else
		{
				if((time>boot_code_min)&&(time<boot_code_max))
				{
						Start_Flag = 1;
						CodeNum = 0;
						time = 0;
				}
				else if(!Start_Flag)
				{
						First_INT = 1;
						time = 0;
				}
				if(Start_Flag&&time!=0)
				{
						if((time>data0_min)&&(time<data0_max))					//code: 0
						{
								Code[CodeNum/8] = Code[CodeNum/8] & 0xfe;
						}
						else if((time>data1_min)&&(time<data1_max))			//code: 1
						{
								Code[CodeNum/8] = Code[CodeNum/8] | 0x01;
						}
						time = 0;
						CodeNum++;
						if(CodeNum>=Num)
						{
								clr_TR0;
								CodeNum = 0;
								Start_Flag = 0;
								First_INT = 0;
						}
				}
		}
		set_EX1;
		#endif
}
#endif

#if 0
/******************************************************************************
 * FUNCTION_PURPOSE: I/O Pin interrupt Service Routine
 ******************************************************************************/
void PinInterrupt_ISR (void) interrupt 7
{
		clr_TR2;																										// Timer2 stop
		th = TH2;
		TL2 = 0;TH2 = 0;set_TR2;                										// Timer2 run
    PIF = 0x00;                             										//clear interrupt flag
		if((count==1)&&(th>boot_code_min>>256)&&(th<boot_code_max))	//?boot_code	
		{
				boot_code_flag = 1;
		}
		if(boot_code_flag)
		{
				if((count>1)&&(count<34))
				{
						if((th>data0_min)&&(th<data0_max))									//0
						{
								data_code[(count-2)/8] = data_code[(count-2)/8] & 0xfe;
						}
						if((th>data1_min)&&(th<data1_max))									//1
						{
								data_code[(count-2)/8] = data_code[(count-2)/8] | 0x01;
						}
				}
				count++;
				if(count>=34)
				{
						count = 0;
						boot_code_flag = 0;
						clr_TR2;
						TL2 = 0;TH2 = 0;
				}
		}
}
#endif

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    Set_All_GPIO_Quasi_Mode;

		INT1_ISR_init();
		Time0_ISR_init();
		set_EA;								//¿ª×ÜÖÐ¶Ï
		//set_TR2;
   // Timer1_Delay1ms(100);
		//set_EX1;
    while(1)
    {
       // set_PD;						//Enter Power Down wait 
    }
}


