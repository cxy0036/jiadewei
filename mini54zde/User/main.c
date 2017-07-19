/**********************************************************************************************************
AIOS(Advanced Input Output System) - An Embedded Real Time Operating System (RTOS)
Copyright (C) 2012~2017 SenseRate.Com All rights reserved.
http://www.aios.io -- Documentation, latest information, license and contact details.
http://www.SenseRate.com -- Commercial support, development, porting, licensing and training services.
--------------------------------------------------------------------------------------------------------
Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met: 
1. Redistributions of source code must retain the above copyright notice, this list of 
conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other materials 
provided with the distribution. 
3. Neither the name of the copyright holder nor the names of its contributors may be used 
to endorse or promote products derived from this software without specific prior written 
permission. 
--------------------------------------------------------------------------------------------------------
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
--------------------------------------------------------------------------------------------------------
 Notice of Export Control Law 
--------------------------------------------------------------------------------------------------------
 SenseRate AIOS may be subject to applicable export control laws and regulations, which might 
 include those applicable to SenseRate AIOS of U.S. and the country in which you are located. 
 Import, export and usage of SenseRate AIOS in any manner by you shall be in compliance with such 
 applicable export control laws and regulations. 
***********************************************************************************************************/

#include <stdio.h>
#include "Mini51Series.h"
#include "task.h"
#include "i2c_software_gpio.h"
#include "KEY_Scan.h"
//#include "Headset.h"
#include "Bluetooth.h"
//#include "Encoder.h"
#include "ir.h"
#include "tas5754.h"


#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000

//void Timer500ms( void *pvParameters );
//void timer1_init(void);
//void led_chang(uint32_t num);

void SYS_Init(void)
{
	/*---------------------------------------------------------------------------------------------------------*/
	/* Init System Clock                                                                                       */
	/*---------------------------------------------------------------------------------------------------------*/
    /* Set P5 multi-function pins for XTAL1 and XTAL2 */
    SYS->P5_MFP &= ~(SYS_MFP_P50_Msk | SYS_MFP_P51_Msk);
    SYS->P5_MFP |= (SYS_MFP_P50_XTAL1 | SYS_MFP_P51_XTAL2);

    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCON &= ~CLK_PWRCON_XTLCLK_EN_Msk;
    CLK->PWRCON |= (0x1 << CLK_PWRCON_XTLCLK_EN_Pos); // XTAL12M (HXT) Enabled

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady( CLK_CLKSTATUS_XTL_STB_Msk);

    /* Switch HCLK clock source to XTAL */
    CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLK_S_Msk;
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_XTAL;

    /* Enable IP clock */
    CLK->APBCLK |= CLK_APBCLK_UART_EN_Msk; // UART Clock Enable

    /* Select IP clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART_S_Msk;
    CLK->CLKSEL1 |= (0x0 << CLK_CLKSEL1_UART_S_Pos);// Clock source from external 12 MHz or 32 KHz crystal clock

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();//选择系统时钟源

}


static void SetupHardware(void)
{
	/* Unlock protected registers */
	SYS_UnlockReg();

	/* Init System, peripheral clock and multi-function I/O */
	SYS_Init();
	
	/* Init GPIO mode */
	GPIO_Init();
	
	/* Init IR mode */
	IR_init();
//	timer1_init();
	ADC_init();
	
	/* Lock protected registers */
	SYS_LockReg();
	
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{	
	SetupHardware();
	POWER_FLAG = 0;
	Channel_flag = 0;
	POWER_FLAG = 0xff;
	SYS_power_flag = 0;
	LED_Flag = 0;
//	POWER = 1;
//	POWER_OFF = 1;
//	BT_POWER = 1;
//	ST_BY = 1;
	I2C_SW_Open(500000);

	#if 1
	while(1)
	{
		if( POWER_FLAG && (SYS_power_flag == 0) )  		//power on 
		{
			Sys_power_on();
//			TIMER_Close(TIMER1);
			TAS_5754_Init(slave_addr);
			CLK_SysTickDelay(5000);	
			test_24c02();
//			timer1_init();
//			IR_init();
			Channel_select(Channel);
//			while(1)
//			{
//				LED_R = 0;LED_B = 0;LED_G = 0;
//			}
		}
		else if( (!POWER_FLAG) && (SYS_power_flag == 1) )//power off
		{
			_RST = 0;
			LED_Flag = 0;
			Sys_power_off();			
		}
//		if((disp>5)||(disp==0))
		IR_test_task();								//IR
//		Encoder_();
		if(Channel_flag)								//channel
		{
			Channel_flag = 0;
			Channel_select( Channel );	
			LED_Flag = 0;			
		}
		Bluetooth_Test_Task();							//Bluetooth
		// Trigger ADC conversion if it is idle
        if(!ADC_IS_BUSY(ADC)) 							//Voltage
		{
            ADC_START_CONV(ADC);
        }
		if(LED_Flag)
		{
			led_chang(0x2000);
		}
	}
	#endif
}

//void led_chang(uint32_t num)
//{
//	if(ledcount>num)
//	{
//		if(Channel[0]==1)
//		{
//			LED_G = ~LED_G;
//		}
//		else if((BT_DET)&&(Channel[0]==0))
//		{
//			LED_B = ~LED_B;
//		}
//		ledcount = 0;
//	}
//}
//void timer1_init(void)
//{
//	CLK_EnableModuleClock(TMR1_MODULE);        
//    // Select Timer 1 clock source from internal 22.1184MHz RC clock.
//    CLK_SetModuleClock(TMR1_MODULE,CLK_CLKSEL1_TMR1_S_IRC22M,1);
////	CLK_SetModuleClock(TMR1_MODULE,CLK_CLKSEL1_TMR1_S_XTAL,1);
//    // configure timer to operate in specified mode.
//    TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 7812);        //7.8125K = 0.128MS = 128US
//    // start Timer counting
//    TIMER_Start(TIMER1);
//    // enable the Timer time-out interrupt function.
//    TIMER_EnableInt(TIMER1);
//    // Enable timer interrupt
//    NVIC_EnableIRQ(TMR1_IRQn);
//}

//void Timer500ms( void *pvParameters )
//{
//	// 500ms软件定时器. 
////	Power_Meter_Detect();
//}

