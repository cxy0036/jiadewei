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
#include "Headset.h"
#include "Bluetooth.h"
#include "Encoder.h"
#include "ir.h"
#include "NTP8230.h"

#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000

void Timer500ms( void *pvParameters );

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
    SystemCoreClockUpdate();

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
	
	/* Lock protected registers */
	SYS_LockReg();
	
}
#if 0
uint8_t NTP_8230[]=
	{     
			  0x02,     0x00,
              0x00,     0x00,
              0x2E,     0xCF,
              0x2D,     0x00,
              0x2F,     0xCF,
              0x30,     0xCF,
              0x31,     0xCF,
              0x15,     0xE7,
              0x16,     0xB3,
              0x2C,     0x43,
              0x52,     0x90,
              0x62,     0x1A,
              0x01,     0x00,
              0x03,     0x4E,
              0x04,     0x00,
              0x05,     0x00,
              0x06,     0x4E,
              0x07,     0x36,
              0x08,     0x36,
              0x32,     0x00,
              0x0F,     0x00,
              0x10,     0x00,
              0x11,     0x00,
              0x12,     0x00,
              0x13,     0x00,
              0x14,     0x00,
              0x33,     0x00,
              0x34,     0x00,
              0x55,     0x0F,
              0x2B,     0x0B,
              0x35,     0x08,
              0x36,     0x1A,
              0x37,     0x2C,
              0x1C,     0x80,
              0x1D,     0x01,
              0x1E,     0x00,
              0x25,     0x00,
              0x22,     0x00,
              0x20,     0x00,
              0x7E,     0x03,
              0x00,     0x10,0x7F,0x66,0xFF,
              0x01,     0x11,0xFF,0x66,0xFF,
              0x02,     0x10,0x7F,0x66,0xFF,
              0x03,     0x11,0x7F,0x66,0xD2,
              0x04,     0x10,0xFE,0xCE,0x56,
              0x05,     0x11,0x00,0x00,0x00,
              0x06,     0x20,0x00,0x00,0x00,
              0x07,     0x20,0x00,0x00,0x00,
              0x08,     0x20,0x00,0x00,0x00,
              0x09,     0x20,0x00,0x00,0x00,
              0x14,     0x11,0x00,0x00,0x00,
              0x15,     0x20,0x00,0x00,0x00,
              0x16,     0x20,0x00,0x00,0x00,
              0x17,     0x20,0x00,0x00,0x00,
              0x18,     0x20,0x00,0x00,0x00,
              0x19,     0x11,0x00,0x00,0x00,
              0x1A,     0x20,0x00,0x00,0x00,
              0x1B,     0x20,0x00,0x00,0x00,
              0x1C,     0x20,0x00,0x00,0x00,
              0x1D,     0x20,0x00,0x00,0x00,
              0x1E,     0x11,0x00,0x00,0x00,
              0x1F,     0x20,0x00,0x00,0x00,
              0x20,     0x20,0x00,0x00,0x00,
              0x21,     0x20,0x00,0x00,0x00,
              0x22,     0x20,0x00,0x00,0x00,
              0x23,     0x11,0x00,0x00,0x00,
              0x24,     0x20,0x00,0x00,0x00,
              0x25,     0x20,0x00,0x00,0x00,
              0x26,     0x20,0x00,0x00,0x00,
              0x27,     0x20,0x00,0x00,0x00,
              0x28,     0x11,0x00,0x00,0x00,
              0x29,     0x20,0x00,0x00,0x00,
              0x2A,     0x20,0x00,0x00,0x00,
              0x2B,     0x20,0x00,0x00,0x00,
              0x2C,     0x20,0x00,0x00,0x00,
              0x2D,     0x11,0x00,0x00,0x00,
              0x2E,     0x20,0x00,0x00,0x00,
              0x2F,     0x20,0x00,0x00,0x00,
              0x30,     0x20,0x00,0x00,0x00,
              0x31,     0x20,0x00,0x00,0x00,
              0x32,     0x11,0x00,0x00,0x00,
              0x33,     0x20,0x00,0x00,0x00,
              0x34,     0x20,0x00,0x00,0x00,
              0x35,     0x20,0x00,0x00,0x00,
              0x36,     0x20,0x00,0x00,0x00,
              0x37,     0x11,0x00,0x00,0x00,
              0x38,     0x20,0x00,0x00,0x00,
              0x39,     0x20,0x00,0x00,0x00,
              0x3A,     0x20,0x00,0x00,0x00,
              0x3B,     0x20,0x00,0x00,0x00,
              0x7E,     0x00,
              0x0C,     0x3F,
              0x17,     0x1F,
              0x19,     0x15,
              0x18,     0x1F,
              0x1A,     0x15,
              0x1B,     0x15,
              0x28,     0x04,
              0x27,     0x00,
              0x26,     0x00
	};
#endif
/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{	
	SetupHardware();
	
	POWER_FLAG = 0;
	Channel = 0;
	POWER = 1;
	POWER_OFF = 1;
	I2C_SW_Open(50000);
//	Sys_power_on();
//	ST_BY = 1;
	BT_POWER = 1;
//	while(1);
	_RST_8230();
//		
    I2C_SW_Open(50000);
	I2C_SW_Send( 0x54,NTP_8230,350);
	#if 1
	while(1)
	{
		if( POWER_FLAG & POWER )
		{
			Sys_power_on();
			Power_Meter_Control();
		}
		else if( !(POWER_FLAG) & POWER_OFF )
		{
			Sys_power_off();
		}
		Channel_select( Channel );
		Headset_Test_Task();
		Bluetooth_Test_Task();
		IR_test_task();
//		if(ST_BY)
//		{
//			Power_Meter_Detect();
//		}
//		if(Power_Meter>0xff)
//		{
//			Sys_power_off();
//		}
	}
	#endif
}



void Timer500ms( void *pvParameters )
{
	// 500ms软件定时器. 
//	Power_Meter_Detect();
}

