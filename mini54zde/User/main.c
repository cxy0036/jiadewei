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
//AIOS
//#include "AIOS.h"
#include "task.h"
#include "i2c_software_gpio.h"
#include "KEY_Scan.h"
#include "Headset.h"
#include "Bluetooth.h"
#include "Encoder.h"
#include "ir.h"

#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000

void Timer500ms( void *pvParameters );

#if 0
/************************************************************
 *@init file
 ************************************************************/
/*
 *Init GPIO mode 
 */
void GPIO_Init( void )
{
	/* Set P1.5 to ADC channel 0 input pin */
    SYS->P1_MFP = SYS_MFP_P15_AIN5;
	/* Analog pin OFFD to prevent leakage */
    P1->OFFD |= (1 << 5) << GPIO_OFFD_OFFD_Pos;
	
	/* Init P2.2 P2.3 P2.4 and P3.6 to be output mode */
	GPIO_SetMode(P0, BIT4, GPIO_PMD_OUTPUT);//BT_REV
	GPIO_SetMode(P0, BIT5, GPIO_PMD_OUTPUT);//BT_FWD
	GPIO_SetMode(P0, BIT7, GPIO_PMD_OUTPUT);//BT_POWER
	GPIO_SetMode(P1, BIT2, GPIO_PMD_OUTPUT);//LED_B
	GPIO_SetMode(P1, BIT3, GPIO_PMD_OUTPUT);//LED_G
	GPIO_SetMode(P1, BIT4, GPIO_PMD_OUTPUT);//LED_R
	GPIO_SetMode(P2, BIT2, GPIO_PMD_OUTPUT);//_SCL
	GPIO_SetMode(P2, BIT3, GPIO_PMD_OUTPUT);//_SDA
	GPIO_SetMode(P2, BIT4, GPIO_PMD_OUTPUT);//_RST
	GPIO_SetMode(P2, BIT5, GPIO_PMD_OUTPUT);//_4052_A
	GPIO_SetMode(P2, BIT6, GPIO_PMD_OUTPUT);//_4052_B
	GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT);//ST_BY 
}
#endif

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

//	/* Enable Internal RC 22.1184MHz clock */
//	CLK->PWRCON |= CLK_PWRCON_OSC22M_EN_Msk;

//	/* Waiting for Internal RC clock ready */
//	while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_OSC22M_STB_Msk));

//	/* Switch HCLK clock source to Internal RC and and HCLK source divide 1 */
//	CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLK_S_Msk;
//	CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_HIRC;
//	CLK->CLKDIV &= ~CLK_CLKDIV_HCLK_N_Msk;
//	CLK->CLKDIV |= CLK_CLKDIV_HCLK(1);

//	/* Enable external XTAL 12MHz clock */
//	CLK->PWRCON |= CLK_PWRCON_XTLCLK_EN_Msk;

//	/* Waiting for external XTAL clock ready */
//	while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_XTLCLK_STB_Msk ));

//	/* Set core clock as PLL_CLOCK from PLL */
//	CLK->PLLCON = PLLCON_SETTING;
//	while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_PLL_STB_Msk));
//	CLK->CLKSEL0 &= (~CLK_CLKSEL0_HCLK_S_Msk);
//	CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_PLL;

//	/* Update System Core Clock */
//	/* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
//	//SystemCoreClockUpdate();
//	PllClock        = PLL_CLOCK;            // PLL
//	SystemCoreClock = PLL_CLOCK / 1;        // HCLK
//	CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

//	/* Enable UART module clock */
//	CLK->APBCLK |= CLK_APBCLK_UART0_EN_Msk;

//	/* Select UART module clock source */
//	CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART_S_Msk;
//	CLK->CLKSEL1 |= CLK_CLKSEL1_UART_S_HXT;

	/*---------------------------------------------------------------------------------------------------------*/
	/* Init I/O Multi-function                                                                                 */
	/*---------------------------------------------------------------------------------------------------------*/

    /* Set P1 multi-function pins for UART1 RXD and TXD  */
//    SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
//    SYS->P1_MFP |= (SYS_MFP_P12_RXD | SYS_MFP_P13_TXD);

    /* Set P0 multi-function pins for UART1 RTS and CTS */
//    SYS->P0_MFP &= ~(SYS_MFP_P00_Msk | SYS_MFP_P01_Msk);
//    SYS->P0_MFP |= (SYS_MFP_P00_CTS | SYS_MFP_P01_RTS);
}

//void UART0_Init()
//{
//	/*---------------------------------------------------------------------------------------------------------*/
//    /* Init UART                                                                                               */
//    /*---------------------------------------------------------------------------------------------------------*/
//    UART_Open(UART, 115200);
//	/*---------------------------------------------------------------------------------------------------------*/
//	/* Init UART                                                                                               */
//	/*---------------------------------------------------------------------------------------------------------*/
//	/* Reset UART0 */
////	SYS->IPRSTC2 |=  SYS_IPRSTC2_UART0_RST_Msk;
////	SYS->IPRSTC2 &= ~SYS_IPRSTC2_UART0_RST_Msk;

//	/* Configure UART0 and set UART0 Baudrate */
////	UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HXT, 115200);
////	UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
//}

static void SetupHardware(void)
{
	/* Unlock protected registers */
	SYS_UnlockReg();

	/* Init System, peripheral clock and multi-function I/O */
	SYS_Init();
	
	/* Init GPIO mode */
	GPIO_Init();
	
	/* Lock protected registers */
	SYS_LockReg();

	/* Init UART0 for printf */
//	UART0_Init();
	

//	printf("\n\nCPU @ %dHz\n", SystemCoreClock);

	/*
		This sample code will blinking LED on NuTiny EVB board of M058SSAN.
		The I/O for LED is P2.3 or P3.6
	*/

//	printf("+---------------------------------------+\n");
//	printf("|    NuTiny EVB LED Sample Code         |\n");
//	printf("+---------------------------------------+\n");


//	P2->PMD = (P2->PMD & ~(0x3 << 2*3)) | (1 << 2*3);
//	P3->PMD = (P3->PMD & ~(0x3 << 2*6)) | (1 << 2*6);  
}

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

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
//	uint8_t power = 1;
	
	SetupHardware();
	
	POWER_FLAG = 0;
	Channel = 0;
	POWER = 1;
	Sys_power_on();
	
	_RST_8230();
		
//    printf("Initiate software I2C for Master\n");
    I2C_SW_Open(50000);
	I2C_SW_Send( 0x54,NTP_8230,350);
	
	while(1)
	{
		if( POWER_FLAG & POWER )
		{
			Sys_power_on();
			CLK_SysTickDelay(100000);
			_RST_8230();
			I2C_SW_Open(50000);
			I2C_SW_Send( 0x54,NTP_8230,350);
			POWER = 0;
		}
		else if( !(POWER_FLAG) )
		{
			Sys_power_off();
//			POWER = 1;
		}
		Channel_select( Channel );
		Headset_Test_Task();
		Bluetooth_Test_Task();
		IR_test();
		//if()
//		I2C_SW_Send(0x54,Tx_Data,6);
//		CLK_SysTickDelay(5000);
	}
		
	//if everything is ok, can't reach here
}




void Timer500ms( void *pvParameters )
{
	// 500ms软件定时器. 
}
