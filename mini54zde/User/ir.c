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
	uint8_t p[2];
	p[0] = 31;
	if(KEY_data!=0x15)
		LED_Flag = 0;
				if(disp_flag == 1)
                {
					switch(KEY_data)
					{
						case 0x01:							//BASS+
							if( SYS_power_flag )
							{
								Amplifier_BASS_A();							
							}
						break;
							
						case 0x02:							//BASS-
							if( SYS_power_flag )
							{
								Amplifier_BASS_B();	
							}
						break;
						
						case 0x03:							//TREBLE+
							if( SYS_power_flag )
							{
								Amplifier_TREBLE_A();						
							}	
						break;
						
						case 0x04:							//TREBLE-
							if( SYS_power_flag )
							{
								Amplifier_TREBLE_B();	
							}
						break;
						
						case 0x0a:							//ÔÝÊ±BLUETOOTHÌæ´úLINE IN
							if(disp==0)
							{
								p[1] = Channel[0] = 0;
								Channel_select(Channel);
								I2C_SW_Send(_24c02_addr,p,2);
							}
						break;
						
						case 0x0b:							//AUX IN
							if(disp==0)
							{
								p[1] = Channel[0] = 1;
								Channel_select(Channel);
								I2C_SW_Send(_24c02_addr,p,2);
							}
						break;
												
						case 0x0c:							//BLUETOOTH
							if(( SYS_power_flag )&&(Channel[0]==0))
							{
								if(disp>2)
								{
									BT_patch();
								}
								else 
								{
									BT_Play_Pause();
								}
//								LED_R = 1;LED_G = 1;
								CLK_SysTickDelay(40000);LED_B = 1;
								CLK_SysTickDelay(40000);LED_B = 0;
							}
						break;

						case 0x0d:							//OPTICAL
						break;
						
						case 0x0E:							//COAXIAL
						break;

						case 0x12:							//VOL+
							disp_flag=0;
							if( SYS_power_flag )
							{
								Amplifier_VOL_A();			
							}
						break;

						case 0x13:							//VOL-
							disp_flag=0;
							if( SYS_power_flag )
							{
								Amplifier_VOL_B();
							}
						break;

						case 0x14:							//ON-OFF
							if(disp==0)
							POWER_FLAG = ~POWER_FLAG;
							
						break;

						case 0x15:							//MUTE
							if( SYS_power_flag && (disp==0) )
							{
								_RST = ~_RST;
								LED_Flag = ~LED_Flag;
								if(LED_Flag==0)
								{
									if(Channel[0])
										LED_G = 0;
									else if((BT_DET)&&(Channel[0]==0))
										LED_B = 0;
								}
							}
							if( SYS_power_flag && (disp>=0x15) )
							{
								treble_level = 0;
								bass_level = 0;
								LED_Flag = 0;
								bass_adjust(bass_level);
								treble_adjust(treble_level);
							}
						break;

						case 0x18:							//HDMI
						break;
						default:
							irwork = IDLE;
							break;
					}
				}
		disp_flag=0;
}
