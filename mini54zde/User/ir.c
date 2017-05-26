/******************************************************************************
* @file     ir.c
* @brief    The Driver code for VS1838A with MINI54FDE
* @version  1.0.0
* @date     22, August, 2014
*
* @note
* Copyright (C) 2000-2014 PM9GZY by yuanxihua@21cn.com. All rights reserved.
******************************************************************************/
#include <stdio.h>
#include "Mini51Series.h"
/*
    �����߱��������ݴ���ͼ��õ���ң�س��õ�һ��ͨѶ������
��ʵ����һ��������ƵĴ���ͨѶ��
    �ҵ�ң���г��õĺ����߱����·�Ц�PD6121G��HT622�ͺ�7461�͵ȡ�
��PD6121Gң�����ĺ���ң��ϵͳ�ı����ʽ
    �����ơ�0����0.56ms�ļ����0.565ms�������ʾ��
    �����ơ�1����0.56ms�ļ����1.685ms�������ʾ��
ÿ�η��͵�32λ��������ɷֳ������֣�����
        ǰ16λ��ң������ʶ�룬��Ҫ��������ͬң������
        ��16λ�ǲ����롣���������ֵĺ�8λ����ǰ8λ�ķ��룬��������У�顣
ÿ֡������9ms�ļ����4.5ms��������Ϊ����ͷheader�źš�
    �����̰��³���108msʱ������˿�ʼ���������źţ��뵥�η���һ����
ֻ������ͷheader�ź�����9ms�ļ����2.5ms��������ɵġ�
*/
/*
_________________________________________________
|        MINI54FDE                                                LED                        |
|                                                                                                |
|        P25                                        <---                VS1838A                |
|        P24                                        --->                RED-LED                |
|_______________________________________________|
*/
#pragma anon_unions
#define TIME_INTERRUPT_PERIOD_US        128          //��ʱ�ж�ʱ�䣬���ڼ����½��ص��½���֮��ʱ�䣬Ҳ����һ������+��϶��ʱ��
#define TIME_INFRARED_HEAD_US           13500        //����ͷ��ʱ�䣺TH=9+4.5=13.5ms
#define TIME_INFRARED_REPEAT_US         11500        //�����̰��³���108msʱ�����������źŵ�����ͷ��ʱ�䣺TH=9+2.5=11.5ms
#define TIME_INFRARED_ZERO_US           1125         //���ݡ�0����ʱ�䣺T0=0.565+0.56=1.125ms
#define TIME_INFRARED_ONE_US            2245         //���ݡ�1����ʱ�䣺T1=1.685+0.56=2.245ms

typedef enum  {IDLE=1,HEAD,DATA} irstatus_t; 
typedef union {uint32_t data;struct {uint8_t data0;uint8_t data1;uint16_t address;};}irdata_t;
irdata_t ir;
uint32_t irticks=0,ircount=0,ledcount=0;
irstatus_t irwork=IDLE;
uint8_t disp_flag=0;
// The Timer1 default IRQ, declared in startup_Mini51.s.
void TMR1_IRQHandler(void)
{
        irticks++;ledcount++;
        TIMER_ClearIntFlag(TIMER1);
}
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
void IR_test(void)
{
    /*Configure P24 for LED control */
    GPIO_SetMode(P2, BIT4, GPIO_PMD_OUTPUT);
        
        /*  Configure P2.5 as Quasi-bidirection mode and enable interrupt by falling edge trigger */
    GPIO_SetMode(P2, BIT5, GPIO_PMD_QUASI);
    GPIO_EnableInt(P2, 5, GPIO_INT_FALLING);
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
        
        while(1)
        {
                if(disp_flag)
                {
                        printf("ir.data=0x%x, ADDR=%04x DATA1=%02x /DATA1=%02x DATA0=%02x \n\r",
                                        ir.data,ir.address,ir.data1,0xff-ir.data1,ir.data0);
                        if((0xff-ir.data0)==ir.data1){P24^=1;}
                        disp_flag=0;
                }
        }
}

