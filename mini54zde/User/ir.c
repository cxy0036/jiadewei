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
/*
    红外线编码是数据传输和家用电器遥控常用的一种通讯方法，
其实质是一种脉宽调制的串行通讯。
    家电遥控中常用的红外线编码电路有μPD6121G型HT622型和7461型等。
μPD6121G遥控器的红外遥控系统的编码格式
    二进制“0”由0.56ms的间隔加0.565ms的脉冲表示；
    二进制“1”由0.56ms的间隔加1.685ms的脉冲表示。
每次发送的32位二进制码可分成两部分，其中
        前16位是遥控器辨识码，主要用于区别不同遥控器，
        后16位是操作码。这两个部分的后8位都是前8位的反码，用作数据校验。
每帧数据以9ms的间隔加4.5ms的脉冲作为数据头header信号。
    当键盘按下长达108ms时，发射端开始发送连续信号，与单次发送一样，
只是数据头header信号是由9ms的间隔加2.5ms的脉冲组成的。
*/
uint8_t d=0;
/*
_________________________________________________
|        MINI54FDE                                                LED                        |
|                                                                                                |
|        P25                                        <---                VS1838A                |
|        P24                                        --->                RED-LED                |
|_______________________________________________|
*/
#pragma anon_unions
#define TIME_INTERRUPT_PERIOD_US        128          //定时中断时间，用于计算下降沿到下降沿之间时间，也就是一个脉冲+间隙的时间
#define TIME_INFRARED_HEAD_US           13500        //数据头的时间：TH=9+4.5=13.5ms
#define TIME_INFRARED_REPEAT_US         11500        //当键盘按下长达108ms时，发送连续信号的数据头的时间：TH=9+2.5=11.5ms
#define TIME_INFRARED_ZERO_US           1125         //数据“0”的时间：T0=0.565+0.56=1.125ms
#define TIME_INFRARED_ONE_US            2245         //数据“1”的时间：T1=1.685+0.56=2.245ms
#define TIME_INFRARED_STOP_US			40560		 //数据结束的时间：TH=40+0.56=40.56ms

typedef enum  {IDLE=1,HEAD,DATA} irstatus_t; 
typedef union {uint32_t data;struct {uint8_t address0;uint8_t address1;uint8_t data0;uint8_t data1;};}irdata_t;
irdata_t ir;
uint32_t irticks=0,ircount=0,ledcount=0;
irstatus_t irwork=IDLE;
uint8_t disp_flag=0,disp=0;
uint8_t KEY_data = 0;
// The Timer1 default IRQ, declared in startup_Mini51.s.
void TMR1_IRQHandler(void)
{
        irticks++;ledcount++;
        TIMER_ClearIntFlag(TIMER1);
}

/**
 * @brief       Port0/Port1 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Port0/Port1 default IRQ, declared in startup_Mini51.s.
 */
void GPIO01_IRQHandler(void)
{
	 uint8_t irdata;
    /* To check if P1.5 interrupt occurred */
    if (P1->ISRC & BIT5) 
	{
       P1->ISRC = BIT5;
//        printf("P1.5 INT occurred. \n");
		CLK_SysTickDelay(150000);		//150ms
		if(POWER_KEY == 0)				//The only correct interruption
		{
			CLK_SysTickDelay(150000);	//150ms
			if(POWER_KEY == 0)			//PressLong	or PressShort
			{
				POWER_FLAG = ~POWER_FLAG;
				POWER = 1;
			}
			else
			{
				Channel++;
				if( Channel >= 0x04 )Channel = 0;				
			}
		}
    } 
	else if(P1->ISRC & BIT0)
	{
		d++;
		        switch(irwork)
                {
                        case IDLE: 
							irwork=HEAD;
                        break;
						
                        case HEAD: 
							irwork=(irticks>((TIME_INFRARED_HEAD_US+TIME_INFRARED_REPEAT_US)/2)/TIME_INTERRUPT_PERIOD_US)?DATA:IDLE;
							if( irwork == DATA)			//BOOT_code
							{
								ir.data = 0;
								ircount = 0;
								disp_flag = 0;
							}
                            else// if( disp_flag == 1)	//REPEAT_code
							{
								disp++;
								disp_flag = 1;
							}								
                        break;
						

                        case DATA: 
							irdata=(irticks>((TIME_INFRARED_ZERO_US+TIME_INFRARED_ONE_US )/2)/TIME_INTERRUPT_PERIOD_US)?1:0;
								if( ircount < 8 )
								{
									ir.address0 >>= 1;
									ir.address0 |= ( irdata << 7 );
									disp_flag = 0;
								}
								else if( ircount < 16 )
								{
									ir.address1 >>= 1;
									ir.address1 |= ( irdata << 7 );
									disp_flag = 0;
								}
								else if( ircount < 24 )
								{
									ir.data0 >>= 1;
									ir.data0 |= ( irdata << 7 );
									disp_flag = 0;
								}
								else if( ircount < 32 )
								{
									ir.data1 >>= 1;
									ir.data1 |= ( irdata << 7 );
									disp_flag = 0;
								}
								ircount++;
								if( ircount >= 32 )	
								{
									irwork = IDLE;
									disp_flag=1;
									disp = 0;
									KEY_data = ir.data0;
								}
						break;
                }  
		irticks=0; 
		P1->ISRC = BIT0;
	}
	else 
	{
        /* Un-expected interrupt. Just clear all PORT0, PORT1 interrupts */
        P0->ISRC = P0->ISRC;
        P1->ISRC = P1->ISRC;
//        printf("Un-expected interrupts. \n");
    }
}

#if 0
// The Port2/Port3/Port4 default IRQ, declared in startup_Mini51.s.
void GPIO234_IRQHandler(void)
{
        uint8_t irdata;

    if (P2->ISRC & BIT5)
    {    /* To check if P2.5 interrupt occurred */
                switch(irwork)
                {
                        case IDLE: irwork=HEAD;
                                break;
                        case HEAD: irwork=(irticks>((TIME_INFRARED_HEAD_US+TIME_INFRARED_REPEAT_US)/2)/TIME_INTERRUPT_PERIOD_US)?DATA:IDLE;
                                ir.data=0;ircount=0;
                                break;
                        case DATA: irdata=(irticks>((TIME_INFRARED_ZERO_US+TIME_INFRARED_ONE_US   )/2)/TIME_INTERRUPT_PERIOD_US)?1:0;
                                ir.data<<=1;ir.data|=irdata;ircount++;
                                if(ircount>=32){irwork=IDLE;disp_flag=1;}
                                break;
                }        
                irticks=0;        P2->ISRC = BIT5;
    }else
    {   /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->ISRC = P2->ISRC;        P3->ISRC = P3->ISRC;        P4->ISRC = P4->ISRC;
        printf("Un-expected interrupts. \n\r");
    }
}
#endif

void IR_init(void)
{
	/*  Configure P2.5 as Quasi-bidirection mode and enable interrupt by falling edge trigger */
    GPIO_SetMode(P1, BIT0, GPIO_PMD_QUASI);
    GPIO_EnableInt(P1, 0, GPIO_INT_FALLING);
    NVIC_EnableIRQ(GPIO01_IRQn);
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
						case 0x01:
							P12 = 1;P13 = 1;P14 = 1;
							if(disp)
							{
								P12 = 0;P13 = 0;P14 = 0;
							}
							disp_flag=0;
						break;
							
						case 0x02:
							P12 = 1;P13 = 1;P14 = 0;
							disp_flag=0;
						break;
						
						case 0x03:
							P12 = 1;P13 = 0;P14 = 1;
							disp_flag=0;
						break;
						
						case 0x04:
							P12 = 1;P13 = 0;P14 = 0;
							disp_flag=0;
						break;
						
						case 0x0a:
							P12 = 0;P13 = 1;P14 = 1;
							disp_flag=0;
						break;
						
						case 0x0b:
							P12 = 0;P13 = 1;P14 = 0;
							disp_flag=0;
						break;
												
						case 0x0c:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x0d:
							P12 = 0;P13 = 0;P14 = 0;
							disp_flag=0;
						break;

						case 0x12:
							P12 = 1;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x13:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x14:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x15:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x18:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

					}
				}
}

#if 0
void IR_test(void)
{
	static uint8_t irdata;
    /*Configure P24 for LED control */
 //   GPIO_SetMode(P1, BIT4, GPIO_PMD_OUTPUT);
        
    /*  Configure P2.5 as Quasi-bidirection mode and enable interrupt by falling edge trigger */
    GPIO_SetMode(P1, BIT0, GPIO_PMD_QUASI);
    GPIO_EnableInt(P1, 0, GPIO_INT_FALLING);
    NVIC_EnableIRQ(GPIO01_IRQn);
        
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
        
        while(1)
        {
                if(disp_flag)
                {
//					irdata = ir.data0;
					switch(KEY_data)
					{
						case 0x01:
							P12 = 1;P13 = 1;P14 = 1;
							if(disp)
							{
								P12 = 0;P13 = 0;P14 = 0;
							}
							disp_flag=0;
						break;
							
						case 0x02:
							P12 = 1;P13 = 1;P14 = 0;
							disp_flag=0;
						break;
						
						case 0x03:
							P12 = 1;P13 = 0;P14 = 1;
							disp_flag=0;
						break;
						
						case 0x04:
							P12 = 1;P13 = 0;P14 = 0;
							disp_flag=0;
						break;
						
						case 0x0a:
							P12 = 0;P13 = 1;P14 = 1;
							disp_flag=0;
						break;
						
						case 0x0b:
							P12 = 0;P13 = 1;P14 = 0;
							disp_flag=0;
						break;
												
						case 0x0c:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x0d:
							P12 = 0;P13 = 0;P14 = 0;
							disp_flag=0;
						break;

						case 0x12:
							P12 = 1;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x13:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x14:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x15:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

						case 0x18:
							P12 = 0;P13 = 0;P14 = 1;
							disp_flag=0;
						break;

					}
 //                       printf("ir.data=0x%x, ADDR=%04x DATA1=%02x /DATA1=%02x DATA0=%02x \n\r",
//                                        ir.data,ir.address,ir.data1,0xff-ir.data1,ir.data0);
//                        if((0xff-ir.data0)==ir.data1){P14^=1;}
//                        disp_flag=0;
//					if( ir.data0 ==0x14 ){P14^=1;}
//					disp_flag=0;
                }
//				else
//				{
//					ir.data0 = 0;
//					irwork = IDLE;
//				}
        }
}
#endif


