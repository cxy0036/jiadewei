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
//  File Function: N76E885 INT1_ISR
//***********************************************************************************************************

#include "INT1.h"
/*
#define	boot_code_min	32000				//8ms
#define boot_code_max	60000				//15ms
#define data0_min			3200				//0.8ms
#define data0_max			6000				//1.5ms
#define data1_min			8000				//2ms
#define data1_max			10000				//2.5ms
#define	Num						33					//32code


UINT8 		CodeNum=0,Code[5]={0};
uint32_t	time=0;
BIT				First_INT=0,Start_Flag=0;
*/
//-------------------------------------------------------------------------
void INT1_ISR_init(void)
{
		set_EX1;							//开启外部中断1
		set_IT1;							//下降沿触发
}
#if 0
//-------------------------------------------------------------------------
void INT1_ISR(void)	interrupt 2
{
		if(!First_INT)
		{
				time = 0;
				set_TR2;
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
								clr_TR2;
								CodeNum = 0;
								Start_Flag = 0;
								First_INT = 0;
						}
				}
		}
}
#endif