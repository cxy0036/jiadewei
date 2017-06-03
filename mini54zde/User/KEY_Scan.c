
#define KEY_GLOBALS
#include "KEY_Scan.h"


//#define POWER_KEY   		P15
#define KEY_VALUE			1
#define KEY_NULL			0

//���峤������TICK��,�Լ���_�������TICK��
#define KEY_LONG_PERIOD		100
#define KEY_CONTINUE_PERIOD	25
//���尴������ֵ״̬(����,����,��_��,�ͷ�)
#define KEY_DOWN		0x80
//#define KEY_short		0x40
#define KEY_SHORT		0x40
#define KEY_LONG		0x20
#define KEY_CONTINUE	0x20
#define KEY_UP			0x10
//#define KEY_UP			5
//���尴��״̬
#define KEY_STATE_INIT		0	//��ʼ״̬
#define KEY_STATE_WOBBLE	1	//����״̬
#define KEY_STATE_PRESS		2	//����״̬
#define KEY_STATE_LONG		3	//����״̬
#define KEY_STATE_CONTINUE	4	//����״̬
#define KEY_STATE_RELEASE	5	//�ͷ�״̬

char n = 0,m = 0,k=0,j=0,flag = 0;
//	static uint8_t s_u8LastKey = KEY_NULL,BOTH_EDGE_ROTOB = 1,BOTH_EDGE_ROTOA = 1;

#if 0
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
#endif

#if 0
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
#endif

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
//		NVIC_DisableIRQ(GPIO234_IRQn);
//        printf("P2.2 INT occurred. \n");
		CLK_SysTickDelay(1000);
		if( VOL_B )
		{
			Encoder_vol_flag = 0;
			Encoder_Task();
		}

//		NVIC_EnableIRQ(GPIO234_IRQn);
    } 
	else 
	{
        /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->ISRC = P2->ISRC;
        P3->ISRC = P3->ISRC;
        P4->ISRC = P4->ISRC;
 //       printf("Un-expected interrupts. \n");
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
//			Encoder_treble_flag = 1;
			Encoder_Task();
		}
 //   printf("P3.2 EINT0 occurred. \n");
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
    /* To check if P3.0 interrupt occurred */
    if (P3->ISRC & BIT0) 
	{
        P3->ISRC = BIT0;
//        printf("P3.0 INT occurred. \n");
		CLK_SysTickDelay(1000);
		if( VOL_A )
		{
			Encoder_vol_flag = 1;
			Encoder_Task();
		}

    } 
	else if(P3->ISRC & BIT1)
	{
		P3->ISRC = BIT1;
		CLK_SysTickDelay(1000);
		if( TREBLE_A )
		{
			Encoder_treble_flag = 1;
			Encoder_Task();
		}
	}
//	else if(P3->ISRC & BIT2)
//	{
//		P3->ISRC = BIT2;
//		CLK_SysTickDelay(1000);
//		if( TREBLE_B )
//		{
//						m++;
//			Encoder_treble_flag = 0;
//			Encoder_Task();
//		}
//	}
	else if(P3->ISRC & BIT4)
	{
		P3->ISRC = BIT4;
		CLK_SysTickDelay(1000);
		if( SUB_A )
		{
			Encoder_sub_flag = 1;
			Encoder_Task();
		}
	}
	else if(P3->ISRC & BIT5)
	{
		P3->ISRC = BIT5;
		CLK_SysTickDelay(1000);
		if( SUB_B )
		{
			Encoder_sub_flag = 0;
			Encoder_Task();
		}
	}
	else 
	{
        /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->ISRC = P2->ISRC;
        P3->ISRC = P3->ISRC;
        P4->ISRC = P4->ISRC;
//        printf("Un-expected interrupts. \n");
    }
}


#if 0

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
		NVIC_DisableIRQ(GPIO5_IRQn);
    /* To check if P3.0 interrupt occurred */
    if (P3->ISRC & BIT0) 
	{
        P3->ISRC = BIT0;
//        printf("P3.0 INT occurred. \n");
		m++;

			CLK_SysTickDelay(500);
			if( VOL_ROTOA & BOTH_EDGE_ROTOA )
			{
				CLK_SysTickDelay(500);
				BOTH_EDGE_ROTOA = 0;
				if(VOL_ROTOA)k++;
//				{
//					flag++;
//					if( flag == 1)
//					{
//						k++;
//					}
//					else
//					{
//						flag = 0;
//					}						
//				}
			}
			else if( !( VOL_ROTOA | BOTH_EDGE_ROTOA) )
			{
				CLK_SysTickDelay(500);
				BOTH_EDGE_ROTOA = 1;
				if(!VOL_ROTOA)k++;
//				{
//					flag++;
//					if( flag == 1)
//					{
//						k++;
//					}
//					else
//					{
//						flag = 0;
//					}	
//				}
			}			
	
//		NVIC_EnableIRQ(GPIO5_IRQn);
    } 
	else 
	{
        /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->ISRC = P2->ISRC;
        P3->ISRC = P3->ISRC;
        P4->ISRC = P4->ISRC;
//        printf("Un-expected interrupts. \n");
    }
}

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
		NVIC_DisableIRQ(GPIO234_IRQn);
//        printf("P2.2 INT occurred. \n");

			CLK_SysTickDelay(15000);
			if( VOL_ROTOB & BOTH_EDGE_ROTOB)
			{
				CLK_SysTickDelay(15000);
				BOTH_EDGE_ROTOB = 0;
				if(VOL_ROTOB)
				{
					flag++;
					if( flag == 1)
					{
						n++;
					}
					else
					{
						flag = 0;
					}	
				}
			}
			else if( !( VOL_ROTOB | BOTH_EDGE_ROTOB) )
			{
				CLK_SysTickDelay(15000);
				BOTH_EDGE_ROTOB = 1;
				if(!VOL_ROTOB)
				{
					flag++;
					if( flag == 1)
					{
						n++;
					}
					else
					{
						flag = 0;
					}	
				}
			}			


		NVIC_EnableIRQ(GPIO234_IRQn);
    } 
	else 
	{
        /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->ISRC = P2->ISRC;
        P3->ISRC = P3->ISRC;
        P4->ISRC = P4->ISRC;
 //       printf("Un-expected interrupts. \n");
    }
}
#endif


#if 0
void KeyInit(void) 
{
	POWER_KEY = 1;
}
static uint8_t KeyScan(void) 
{ 
	if(POWER_KEY == 0)return KEY_VALUE;
	return KEY_NULL;
}
//void GetKey( uint8_t *pKeyValue )
uint8_t GetKey(  )
{
	static uint8_t s_u8KeyState = KEY_STATE_PRESS;
	static uint8_t s_u8KeyTimeCount = 0;
//	static uint8_t s_u8LastKey = KEY_NULL;
	uint8_t KeyTemp = KEY_NULL;
	
	KeyTemp |= KeyScan();
//	KeyTemp = KEY_VALUE;
	switch(s_u8KeyState)
	{
//		case	KEY_STATE_INIT:
//			if( KEY_NULL != KeyTemp )
//			{
//				s_u8KeyState = KEY_STATE_WOBBLE;
//			}
//			break;
//			
//		case	KEY_STATE_WOBBLE:
//			s_u8KeyState = KEY_STATE_PRESS;
//			break;
		
		case	KEY_STATE_PRESS:
			if( KEY_NULL != KeyTemp )
			{
				s_u8LastKey |= KEY_DOWN;
//				s_u8LastKey |= KeyTemp;
				s_u8KeyState = KEY_STATE_LONG;
			}
			else
			{
//				s_u8KeyState = KEY_STATE_INIT;
				s_u8KeyState = KEY_STATE_PRESS;
			}
			break;
			
		case	KEY_STATE_LONG:
			if( KEY_NULL != KeyTemp )
			{
				if( ++s_u8KeyTimeCount > KEY_LONG_PERIOD )
				{
					s_u8KeyTimeCount = 0;
					s_u8LastKey |= KEY_LONG;
//					s_u8LastKey |= KeyTemp;
					s_u8KeyState = KEY_STATE_CONTINUE;
				}
//				else
//				{
//					KeyTemp |= KEY_SHORT;
//				}
			}
			else
			{
//				KeyTemp |= KEY_SHORT;
				s_u8KeyState = KEY_STATE_RELEASE;
			}
			break;
			
		case	KEY_STATE_CONTINUE:
			if( KEY_NULL != KeyTemp )
			{
				if( ++s_u8KeyTimeCount > KEY_CONTINUE_PERIOD )
				{
					s_u8KeyTimeCount = 0;
					s_u8LastKey |= KEY_CONTINUE;
//					s_u8LastKey |= KeyTemp;
				}
			}
			else
			{
				s_u8KeyState = KEY_STATE_RELEASE;
			}
			break;
		
		case	KEY_STATE_RELEASE:
			s_u8LastKey |= KEY_UP;

			KeyTemp |= s_u8LastKey;
			s_u8LastKey = 0;
			s_u8KeyState = KEY_STATE_PRESS;
			break;
		
		default:
			break;
	}
	return KeyTemp;
	
//	*pKeyValue = KeyTemp;
}
#endif

