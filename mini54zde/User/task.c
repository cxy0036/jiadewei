#define TASK_GLOBALS
#include "task.h"

#pragma anon_unions
#define TIME_INTERRUPT_PERIOD_US        128          //定时中断时间，用于计算下降沿到下降沿之间时间，也就是一个脉冲+间隙的时间
#define TIME_INFRARED_HEAD_US           13500        //数据头的时间：TH=9+4.5=13.5ms
#define TIME_INFRARED_REPEAT_US         11500        //当键盘按下长达108ms时，发送连续信号的数据头的时间：TH=9+2.5=11.5ms
#define TIME_INFRARED_ZERO_US           1125         //数据“0”的时间：T0=0.565+0.56=1.125ms
#define TIME_INFRARED_ONE_US            2245         //数据“1”的时间：T1=1.685+0.56=2.245ms
#define TIME_INFRARED_STOP_US			40560		 //数据结束的时间：TH=40+0.56=40.56ms
typedef union {uint32_t data;struct {uint8_t address0;uint8_t address1;uint8_t data0;uint8_t data1;};}irdata_t;
irdata_t ir;
uint16_t irticks=0;
uint32_t ledcount=0,audio_adc=0;
uint8_t ircount=0;
irstatus_t irwork=IDLE;
uint8_t disp_flag=0,disp=0;
uint8_t KEY_data = 0;
uint8_t	power_change=0;
uint8_t	VOL_F=0,TREBLE_F=0,SUB_F=0;

/************************************************************
 *@init file
 ************************************************************/
/**
 *Init GPIO mode 
 */
void GPIO_Init( void )
{
	/* Init P2.2 P2.3 P2.4 and P3.6 to be output mode */
	GPIO_SetMode(P0, BIT0, GPIO_PMD_OUTPUT);//BT_REV
	GPIO_SetMode(P0, BIT1, GPIO_PMD_OUTPUT);//BT_FWD
	GPIO_SetMode(P1, BIT0, GPIO_PMD_OUTPUT);//BT_POWER
	GPIO_SetMode(P5, BIT4, GPIO_PMD_OUTPUT);//BT_DET
	
//	GPIO_SetMode(P3, BIT0, GPIO_PMD_QUASI);	//IR
	GPIO_SetMode(P1, BIT5, GPIO_PMD_INPUT);//AUDIO_DET
	
	GPIO_SetMode(P3, BIT2, GPIO_PMD_OUTPUT);//LED_B
	GPIO_SetMode(P3, BIT1, GPIO_PMD_OUTPUT);//LED_G
	GPIO_SetMode(P5, BIT4, GPIO_PMD_OUTPUT);//LED_R
	
	GPIO_SetMode(P1, BIT4, GPIO_PMD_QUASI);	//POWER_KEY
	
    GPIO_SetMode(P2, BIT2, GPIO_PMD_OPEN_DRAIN);//_SCL
	GPIO_SetMode(P2, BIT3, GPIO_PMD_OPEN_DRAIN);//_SDA
	
//	GPIO_SetMode(P2, BIT4, GPIO_PMD_OUTPUT);//_RST AMP_MUTE
	
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

	GPIO_EnableInt(P0, 4, GPIO_INT_BOTH_EDGE);
	GPIO_EnableInt(P0, 6, GPIO_INT_BOTH_EDGE);
    NVIC_EnableIRQ(GPIO01_IRQn);
	GPIO_EnableInt(P2, 6, GPIO_INT_BOTH_EDGE);
    NVIC_EnableIRQ(GPIO234_IRQn);
	GPIO_SET_DEBOUNCE_TIME(GPIO_DBNCECON_DBCLKSRC_HCLK, GPIO_DBNCECON_DBCLKSEL_1024);
	GPIO_ENABLE_DEBOUNCE(P0,BIT4);
	GPIO_ENABLE_DEBOUNCE(P0,BIT6);
	GPIO_ENABLE_DEBOUNCE(P2,BIT6);
	
	/*****init gpio output******/
	_RST = 0;
	ST_BY = 0;
	BT_REV = 0;
	BT_FWD = 0;
}


/**
 * @brief       Timer1 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Timer1 default IRQ, declared in startup_Mini51.s.
 */
void TMR1_IRQHandler(void)
{
	if(ADC_V>0x3f0)
	{
		if((key_count>0x100)&&(key_count<0x2000))
		{
			Channel[0]++;
			if(Channel[0] >= 0x02 )Channel[0] = 0;//2 channel
			Channel_flag = 1;
		}
		key_count = 0;
		power_change = 0;
	}
	if((ADC_V>0xf0)&&(ADC_V<0x3f0))
	{
		if((key_count>0x100)&&(key_count<0x2000))
		{
			Channel[0]++;
			if(Channel[0] >= 0x02 )Channel[0] = 0;//2 channel
			Channel_flag = 1;
		}
		key_count = 0;
		power_change = 0;
		if(AUDIO_DET)
		{
			audio_adc++;
			if((audio_adc >= 0x1ad2748)&&(_RST == 1))	//2 hours  0x35a4e90
//			if((audio_2 >= 0x1692000)&&(_RST == 1))	//1 hours  0x1ad2748
//			if((audio_2 >= 0xb49000)&&(_RST == 1))	//半 hours  0xd693a4	
//			if((audio_2 >= 0x3c3000)&&(_RST == 1))	//10 minis	0x47868c
//			if((audio_2 >= 0x78600)&&(_RST == 1))	//1 minis	0x7270e			
			{
				_RST = 0;
				power_change = 1;
				POWER_FLAG = ~POWER_FLAG;
			}
		}
		else
		{
			audio_adc = 0;
		}
	}
	if(ADC_V<0x0f)
	{
		key_count++;
		if(key_count > 0xfff0)key_count = 0xfff0;
		if((key_count > 0x2000)&&(power_change ==0))
		{
			power_change = 1;
			POWER_FLAG = ~POWER_FLAG;
		}
	}
	irticks++;ledcount++;//audio_1++;Power_Meter++;
	if(irticks>0xfffd)irticks = 0xfffd;
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
	if(P0->ISRC & BIT4)
	{
		P0->ISRC = BIT4;
		if( VOL_A )
		{
			Encoder_vol_flag = 1;
			VOL_F = 1;
		}
		else if(VOL_B)
		{
			Encoder_vol_flag = 0;
			VOL_F = 1;
		}
	}
	else if(P0->ISRC & BIT6)
	{
		P0->ISRC = BIT6;
		if( TREBLE_A )
		{
			Encoder_treble_flag = 1;
			TREBLE_F = 1;
		}
		else if( TREBLE_B )
		{
			Encoder_treble_flag = 0;
			TREBLE_F = 1;
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
	if(P2->ISRC & BIT6)
	{
		P2->ISRC = BIT6;
		if( SUB_A )
		{
			Encoder_sub_flag = 1;
			SUB_F = 1;
		}
		else if( SUB_B )
		{
			Encoder_sub_flag = 0;
			SUB_F = 1;
		}
	}
	else if(P3->ISRC & BIT0)
	{
		if(irticks > 0xf0)irwork=IDLE;
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

