/******************************************************************************
* @file     ir.c
* @brief    The Driver code for VS1838A with MINI54FDE
* @version  1.0.0
* @date     22, August, 2014
*
* @note
* Copyright (C) 2000-2014 PM9GZY by yuanxihua@21cn.com. All rights reserved.
******************************************************************************/
#include "ir.h"

void IR_init(void)
{
	/*  Configure P1.0 as Quasi-bidirection mode and enable interrupt by falling edge trigger */
    GPIO_SetMode(P3, BIT0, GPIO_PMD_QUASI);
    GPIO_EnableInt(P3, 0, GPIO_INT_FALLING);
    NVIC_EnableIRQ(GPIO234_IRQn);
	// Enable IP clock
    CLK_EnableModuleClock(TMR1_MODULE);        
    // Select Timer 1 clock source from internal 22.1184MHz RC clock.
    CLK_SetModuleClock(TMR1_MODULE,CLK_CLKSEL1_TMR1_S_IRC22M,1);
    // configure timer to operate in specified mode.
    TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 7812);        //7.8125K = 0.128MS = 128US
    // start Timer counting
    TIMER_Start(TIMER1);
    // enable the Timer time-out interrupt function.
    TIMER_EnableInt(TIMER1);
    // Enable timer interrupt
    NVIC_EnableIRQ(TMR1_IRQn);
}

void IR_test_task(void)
{
				if(disp_flag)
                {
					switch(KEY_data)
					{
						case 0x01:							//BASS+
//							SUB_A_TASK();
							disp_flag=0;
						break;
							
						case 0x02:							//BASS-
//							SUB_B_TASK();
							disp_flag=0;
						break;
						
						case 0x03:							//TREBLE+
//							TREBLE_A_TASK();
							disp_flag=0;
						break;
						
						case 0x04:							//TREBLE-
//							TREBLE_B_TASK();
							disp_flag=0;
						break;
						
						case 0x0a:							//LINE IN
							P12 = 0;P13 = 1;P14 = 1;
							disp_flag=0;
						break;
						
						case 0x0b:							//AUX IN
							P12 = 0;P13 = 1;P14 = 0;
							disp_flag=0;
						break;
												
						case 0x0c:							//BLUETOOTH
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x0d:							//OPTICAL
							P12 = 0;P13 = 0;P14 = 0;
							disp_flag=0;
						break;
						
						case 0x0E:							//COAXIAL
							P12 = 0;P13 = 0;P14 = 0;
							disp_flag=0;
						break;

						case 0x12:							//VOL+
//							VOL_A_TASK();
							disp_flag=0;
						break;

						case 0x13:							//VOL-
//							VOL_B_TASK();
							disp_flag=0;
						break;

						case 0x14:							//ON-OFF
//							POWER_TASK();
							disp_flag=0;
						break;

						case 0x15:							//MUTE
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x18:							//HDMI
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

					}
				}
}
