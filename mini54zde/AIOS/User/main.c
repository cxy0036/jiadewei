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
#include "AIOS.h"

#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000

OSTimerHandle_t			Timer500msHandle	= NULL;
OSTaskHandle_t 			CtrlTaskHandle		= NULL;
OSTaskHandle_t 			LedTaskHandle		= NULL;
OSSemHandle_t 			LedSemHandle		= NULL;

void CtrlTask( void *pvParameters );
void LedTask( void *pvParameters );
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
    SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
    SYS->P1_MFP |= (SYS_MFP_P12_RXD | SYS_MFP_P13_TXD);

    /* Set P0 multi-function pins for UART1 RTS and CTS */
    SYS->P0_MFP &= ~(SYS_MFP_P00_Msk | SYS_MFP_P01_Msk);
    SYS->P0_MFP |= (SYS_MFP_P00_CTS | SYS_MFP_P01_RTS);
}

void UART0_Init()
{
	/*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    UART_Open(UART, 115200);
	/*---------------------------------------------------------------------------------------------------------*/
	/* Init UART                                                                                               */
	/*---------------------------------------------------------------------------------------------------------*/
	/* Reset UART0 */
//	SYS->IPRSTC2 |=  SYS_IPRSTC2_UART0_RST_Msk;
//	SYS->IPRSTC2 &= ~SYS_IPRSTC2_UART0_RST_Msk;

	/* Configure UART0 and set UART0 Baudrate */
//	UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HXT, 115200);
//	UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
}

static void SetupHardware(void)
{
	/* Unlock protected registers */
	SYS_UnlockReg();

	/* Init System, peripheral clock and multi-function I/O */
	SYS_Init();

	/* Lock protected registers */
	SYS_LockReg();

	/* Init UART0 for printf */
	UART0_Init();

	printf("\n\nCPU @ %dHz\n", SystemCoreClock);

	/*
		This sample code will blinking LED on NuTiny EVB board of M058SSAN.
		The I/O for LED is P2.3 or P3.6
	*/

	printf("+---------------------------------------+\n");
	printf("|    NuTiny EVB LED Sample Code         |\n");
	printf("+---------------------------------------+\n");

	/* Init P2.3 and P3.6 to be output mode */
	GPIO_SetMode(P2, BIT3, GPIO_PMD_OUTPUT); 
	GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT); 
//	P2->PMD = (P2->PMD & ~(0x3 << 2*3)) | (1 << 2*3);
//	P3->PMD = (P3->PMD & ~(0x3 << 2*6)) | (1 << 2*6);  
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
	SetupHardware();

	//创建500ms的定时器，分配定时器服务函数为Timer500ms
	Timer500msHandle = OSTimerCreate(OSM2T(500), OS_TRUE, Timer500ms, NULL, "T500ms");
	//创建信号量
	LedSemHandle	= OSSemCreate(0);
	//创建任务，控制LED灯
	CtrlTaskHandle	= OSTaskCreate(CtrlTask, NULL, OSMINIMAL_STACK_SIZE, OSLOWEAST_PRIORITY+1, "Ctrl" );
	LedTaskHandle	= OSTaskCreate(LedTask, NULL, OSMINIMAL_STACK_SIZE, OSLOWEAST_PRIORITY+1, "Led" );

	OSTimerStart(Timer500msHandle);

	// Start the scheduler. 
	OSStart();
		
	//if everything is ok, can't reach here
	for( ;; );  
}

void CtrlTask( void *pvParameters )
{
	for( ;; )
	{
		OSSemPost(LedSemHandle);	

		OSTaskSleep( OSM2T(500) );        
	}
}

void LedTask( void *pvParameters )
{
	for( ;; )
	{
		OSSemPend(LedSemHandle, OSPEND_FOREVER_VALUE);	
		/* Toggle P2.3 */
		P23 ^= 1;

		/* Toggle P3.6 */
		P36 ^= 1;                
	}
}

void Timer500ms( void *pvParameters )
{
	// 500ms软件定时器. 
}
