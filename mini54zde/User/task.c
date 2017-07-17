#define TASK_GLOBALS
#include "task.h"

#pragma anon_unions
#define TIME_INTERRUPT_PERIOD_US        128          //定时中断时间，用于计算下降沿到下降沿之间时间，也就是一个脉冲+间隙的时间
#define TIME_INFRARED_HEAD_US           13500        //数据头的时间：TH=9+4.5=13.5ms
#define TIME_INFRARED_REPEAT_US         11500        //当键盘按下长达108ms时，发送连续信号的数据头的时间：TH=9+2.5=11.5ms
#define TIME_INFRARED_ZERO_US           1125         //数据“0”的时间：T0=0.565+0.56=1.125ms
#define TIME_INFRARED_ONE_US            2245         //数据“1”的时间：T1=1.685+0.56=2.245ms
#define TIME_INFRARED_STOP_US			40560		 //数据结束的时间：TH=40+0.56=40.56ms
//typedef enum  {IDLE=1,HEAD,DATA} irstatus_t; 
typedef union {uint32_t data;struct {uint8_t address0;uint8_t address1;uint8_t data0;uint8_t data1;};}irdata_t;
irdata_t ir;
uint16_t irticks=0;//,ircount=0;//ledcount=0;
uint8_t ircount=0;
irstatus_t irwork=IDLE;
uint8_t disp_flag=0,disp=0;
uint8_t KEY_data = 0;
//uint8_t d=0;
uint8_t	power_change=0;

/************************************************************
 *@init file
 ************************************************************/
/*
 *Init GPIO mode 
 */
void GPIO_Init( void )
{
	/* Init P2.2 P2.3 P2.4 and P3.6 to be output mode */
	GPIO_SetMode(P0, BIT0, GPIO_PMD_OUTPUT);//BT_REV
	GPIO_SetMode(P0, BIT1, GPIO_PMD_OUTPUT);//BT_FWD
	GPIO_SetMode(P1, BIT0, GPIO_PMD_OUTPUT);//BT_POWER
	GPIO_SetMode(P5, BIT4, GPIO_PMD_OUTPUT);//BT_DET
//	
//	GPIO_SetMode(P3, BIT0, GPIO_PMD_QUASI);	//IR
	GPIO_SetMode(P1, BIT5, GPIO_PMD_QUASI);//AUDIO_DET
	
	GPIO_SetMode(P3, BIT2, GPIO_PMD_OUTPUT);//LED_B
	GPIO_SetMode(P3, BIT1, GPIO_PMD_OUTPUT);//LED_G
	GPIO_SetMode(P5, BIT4, GPIO_PMD_OUTPUT);//LED_R
	
	GPIO_SetMode(P1, BIT4, GPIO_PMD_QUASI);	//POWER_KEY
	
    GPIO_SetMode(P2, BIT2, GPIO_PMD_OPEN_DRAIN);//_SCL
	GPIO_SetMode(P2, BIT3, GPIO_PMD_OPEN_DRAIN);//_SDA
	
//	GPIO_SetMode(P2, BIT4, GPIO_PMD_OUTPUT);//_RST
	
	GPIO_SetMode(P2, BIT4, GPIO_PMD_QUASI);//AMP_MUTE
	
	GPIO_SetMode(P1, BIT2, GPIO_PMD_OUTPUT);//_4052_A
	GPIO_SetMode(P1, BIT3, GPIO_PMD_OUTPUT);//_4052_B
	
	GPIO_SetMode(P0, BIT4, GPIO_PMD_QUASI);	//VOL_ROTOA
	GPIO_SetMode(P0, BIT5, GPIO_PMD_QUASI);	//VOL_ROTOB
	GPIO_SetMode(P0, BIT6, GPIO_PMD_QUASI);	//TREBLE_ROTOA
	GPIO_SetMode(P0, BIT7, GPIO_PMD_QUASI);	//TREBLE_ROTOB
	GPIO_SetMode(P2, BIT6, GPIO_PMD_QUASI);	//SUB_ROTOA
	GPIO_SetMode(P2, BIT5, GPIO_PMD_QUASI);	//SUB_ROTOB
	
	GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT);//ST_BY 
	
//	/* Configure P2.2 and P2.3 as open-drain mode */
//    GPIO_SetMode(P2, BIT2, GPIO_PMD_OPEN_DRAIN);
//	GPIO_SetMode(P2, BIT3, GPIO_PMD_OPEN_DRAIN);

//    GPIO_EnableInt(P1, 4, GPIO_INT_FALLING);//GPIO_INT_LOW);
	GPIO_EnableInt(P0, 4, GPIO_INT_FALLING);
	GPIO_EnableInt(P0, 5, GPIO_INT_FALLING);
	GPIO_EnableInt(P0, 6, GPIO_INT_FALLING);
	GPIO_EnableInt(P0, 7, GPIO_INT_FALLING);
    NVIC_EnableIRQ(GPIO01_IRQn);
//	GPIO_EnableInt(P3, 0, GPIO_INT_RISING);
//    GPIO_EnableInt(P3, 0, GPIO_INT_FALLING);
//	GPIO_EnableInt(P3, 1, GPIO_INT_FALLING);
//	GPIO_EnableInt(P3, 2, GPIO_INT_FALLING);
//	GPIO_EnableEINT0(P3, 2, GPIO_INT_FALLING);
//	NVIC_EnableIRQ(EINT0_IRQn);
//	GPIO_EnableInt(P3, 4, GPIO_INT_FALLING);
//	GPIO_EnableInt(P3, 5, GPIO_INT_FALLING);
	GPIO_EnableInt(P2, 5, GPIO_INT_FALLING);
	GPIO_EnableInt(P2, 6, GPIO_INT_FALLING);
    NVIC_EnableIRQ(GPIO234_IRQn);
//	GPIO_EnableInt(P5, 4, GPIO_INT_BOTH_EDGE);
//	NVIC_EnableIRQ(GPIO5_IRQn);
	
	/*****init gpio output******/
	ST_BY = 0;
	BT_REV = 0;
	BT_FWD = 0;
}


// The Timer1 default IRQ, declared in startup_Mini51.s.
//void TMR0_IRQHandler(void)
//{
//        irticks++;//ledcount++;
//        TIMER_ClearIntFlag(TIMER0);
//}
// The Timer1 default IRQ, declared in startup_Mini51.s.
void TMR1_IRQHandler(void)
{
	if(ADC_V>0xf0)
	{
		if((key_count>0x100)&&(key_count<0x2000))
		{
			Channel[0]++;
			if(Channel[0] >= 0x04 )Channel[0] = 0;
			Channel_flag = 1;
		}
		key_count = 0;
		power_change = 0;
	}
	if(ADC_V<0x0f)
	{
		key_count++;
		if(key_count > 0xfff0)key_count = 0xfff0;
		if((key_count > 0x2000)&&(power_change ==0))
		{
			power_change = 1;
			POWER_FLAG = ~POWER_FLAG;
//			POWER = ~POWER;
		}
	}
	irticks++;//ledcount++;//Power_Meter++;
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
	#if 0
    /* To check if P1.4 interrupt occurred */
    if (P1->ISRC & BIT4) 
	{
       P1->ISRC = BIT4;
				ledcount++;
		CLK_SysTickDelay(70000);		//70ms
		if(POWER_KEY == 0)				//The only correct interruption
		{
//			CLK_SysTickDelay(2850000);	//2850ms
			CLK_SysTickDelay(1500000);	//1500ms
			if(POWER_KEY == 0)			//PressLong	or PressShort
			{
				POWER_FLAG = ~POWER_FLAG;
				POWER = 1;
				POWER_OFF = 1;
				Channel[0] = d;
			}
			else
			{
				d++;
				if(d >= 0x04 )d = 0;
				Channel[0] = d;
//				if( Channel[0] >= 0x04 )Channel[0] = 0;				
			}
		}
    } 
	#endif
	if(P0->ISRC & BIT4)
	{
		P0->ISRC = BIT4;
		CLK_SysTickDelay(1000);
		if( VOL_A )
		{
			Encoder_vol_flag = 1;
			Encoder_Task();
		}		
	}
	else if(P0->ISRC & BIT5)
	{
		P0->ISRC = BIT5;
		CLK_SysTickDelay(1000);
		if( VOL_B )
		{
			Encoder_vol_flag = 0;
			Encoder_Task();
		}		
	}
	else if(P0->ISRC & BIT6)
	{
		P0->ISRC = BIT6;
		CLK_SysTickDelay(1000);
		if( TREBLE_A )
		{
			Encoder_treble_flag = 1;
			Encoder_Task();
		}		
	}
	else if(P0->ISRC & BIT7)
	{
		P0->ISRC = BIT7;
		CLK_SysTickDelay(1000);
		if( TREBLE_B )
		{
			Encoder_treble_flag = 0;
			Encoder_Task();
		}		
	}	
	else 
	{
        /* Un-expected interrupt. Just clear all PORT0, PORT1 interrupts */
        P0->ISRC = P0->ISRC;
        P1->ISRC = P1->ISRC;
    }
}


/**
 * @brief       Port2/Port3/Port4 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Port2/Port3/Port4 default IRQ, declared in startup_Mini51.s.
 */
void GPIO234_IRQHandler(void)
{
	uint8_t irdata;
    /* To check if P3.0 interrupt occurred */
    if (P2->ISRC & BIT5) 
	{
        P2->ISRC = BIT5;
		CLK_SysTickDelay(1000);
		if( SUB_B )
		{
			Encoder_sub_flag = 1;
			Encoder_Task();
		}

    } 
	else if(P2->ISRC & BIT6)
	{
		P2->ISRC = BIT6;
		CLK_SysTickDelay(1000);
		if( SUB_A )
		{
			Encoder_sub_flag = 0;
			Encoder_Task();
		}
	}
	else if(P3->ISRC & BIT0)
	{
//		d++;
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
		P3->ISRC = BIT0;
	}
	else 
	{
        /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->ISRC = P2->ISRC;
        P3->ISRC = P3->ISRC;
        P4->ISRC = P4->ISRC;
    }
}


#if 0

/**
 * @brief       Port5 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Port5 default IRQ, declared in startup_Mini51.s.
 */
void GPIO5_IRQHandler(void)
{
    /* To check if P5.4 interrupt occurred */
    if (P5->ISRC & BIT4) 
	{
        P5->ISRC = BIT4;
		CLK_SysTickDelay(1000);
		if( VOL_B )
		{
			Encoder_vol_flag = 0;
			Encoder_Task();
		}

    } 
	else 
	{
        /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->ISRC = P2->ISRC;
        P3->ISRC = P3->ISRC;
        P4->ISRC = P4->ISRC;
    }
}


/**
 * @brief       External INT0 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The External INT0(P3.2) default IRQ, declared in startup_Mini51.s.
 */
void EINT0_IRQHandler(void)
{
    /* For P3.2, clear the INT flag */
    P3->ISRC = BIT2;
		CLK_SysTickDelay(1000);
		if( TREBLE_B )
		{
			Encoder_treble_flag = 0;
			Encoder_Task();
		}
}
#endif


