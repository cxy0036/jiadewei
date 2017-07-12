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
//    CLK_EnableModuleClock(TMR0_MODULE);        
//    // Select Timer 1 clock source from internal 22.1184MHz RC clock.
//    CLK_SetModuleClock(TMR0_MODULE,CLK_CLKSEL1_TMR0_S_IRC22M,1);
//    // configure timer to operate in specified mode.
//    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 7812);        //7.8125K = 0.128MS = 128US
//    // start Timer counting
//    TIMER_Start(TIMER0);
//    // enable the Timer time-out interrupt function.
//    TIMER_EnableInt(TIMER0);
//    // Enable timer interrupt
//    NVIC_EnableIRQ(TMR0_IRQn);
}

void IR_test_task(void)
{
				if(disp_flag)
                {
					switch(KEY_data)
					{
						case 0x01:							//BASS+
							if( SYS_power_flag )
							{
								Amplifier_BASS_A();
								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}								
							}
							disp_flag=0;
						break;
							
						case 0x02:							//BASS-
							if( SYS_power_flag )
							{
								Amplifier_BASS_B();
								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}	
							}
							disp_flag=0;
						break;
						
						case 0x03:							//TREBLE+
							if( SYS_power_flag )
							{
								Amplifier_TREBLE_A();
								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}						
							}	
							disp_flag=0;
						break;
						
						case 0x04:							//TREBLE-
							if( SYS_power_flag )
							{
								Amplifier_TREBLE_B();
								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}	
							}
							disp_flag=0;
						break;
						
						case 0x0a:							//ÔÝÊ±BLUETOOTHÌæ´úLINE IN
							if( SYS_power_flag )
							{
								_4052_A = 1;_4052_B = 0;
								BT_POWER = 1;
								LED_R = 1;LED_B = 0;LED_G = 1;
							}	
							disp_flag=0;
						break;
						
						case 0x0b:							//AUX IN
							if(SYS_power_flag)
							{
								_4052_A = 0;_4052_B = 1;
								BT_POWER = 0;
								LED_R = 1;LED_B = 1;LED_G = 0;		
								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
							}
							disp_flag=0;
						break;
												
						case 0x0c:							//BLUETOOTH
//							_4052_A = 1;_4052_B = 0;
							if( SYS_power_flag )
							{
								if(disp_flag>1)
								{
									BT_patch();
								}
								else
								{
									BT_Play_Pause();
								}
							}
							disp_flag=0;
						break;

						case 0x0d:							//OPTICAL
							disp_flag=0;
						break;
						
						case 0x0E:							//COAXIAL
							disp_flag=0;
						break;

						case 0x12:							//VOL+
							if( SYS_power_flag )
							{
								Amplifier_VOL_A();
								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}			
							}
							disp_flag=0;
						break;

						case 0x13:							//VOL-
							if( SYS_power_flag )
							{
								Amplifier_VOL_B();
								if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
								if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
								if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
							}
							disp_flag=0;
						break;

						case 0x14:							//ON-OFF
							POWER_KEY = 0;
							CLK_SysTickDelay(25*1000*1000);
							POWER_KEY = 1;
							disp_flag=0;
						break;

						case 0x15:							//MUTE
							if( SYS_power_flag )
							{
								//Amplifier_Auto_Mute();
							}
							disp_flag=0;
						break;

						case 0x18:							//HDMI
							disp_flag=0;
						break;
						default:
							break;
					}
				}
	
}
