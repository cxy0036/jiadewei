
#define KEY_GLOBALS
#include "KEY_Scan.h"


#define POWER_KEY   		P15
#define KEY_VALUE			1
#define KEY_NULL			0

//定义长按键的TICK数,以及连_发间隔的TICK数
#define KEY_LONG_PERIOD		100
#define KEY_CONTINUE_PERIOD	25
//定义按键返回值状态(按下,长按,连_发,释放)
#define KEY_DOWN		0x80
//#define KEY_short		0x40
#define KEY_SHORT		0x40
#define KEY_LONG		0x20
#define KEY_CONTINUE	0x20
#define KEY_UP			0x10
//#define KEY_UP			5
//定义按键状态
#define KEY_STATE_INIT		0	//初始状态
#define KEY_STATE_WOBBLE	1	//消抖状态
#define KEY_STATE_PRESS		2	//按下状态
#define KEY_STATE_LONG		3	//长按状态
#define KEY_STATE_CONTINUE	4	//连按状态
#define KEY_STATE_RELEASE	5	//释放状态

char n = 0,m = 0;
	static uint8_t s_u8LastKey = KEY_NULL,BOTH_EDGE = 0;

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
			}
			else
			{
				Channel++;
				if( Channel >= 0x04 )Channel = 0;				
			}
		}
    } 
	else 
	{
        /* Un-expected interrupt. Just clear all PORT0, PORT1 interrupts */
        P0->ISRC = P0->ISRC;
        P1->ISRC = P1->ISRC;
//        printf("Un-expected interrupts. \n");
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
    /* To check if P2.2 interrupt occurred */
    if (P2->ISRC & BIT2) 
	{
        P2->ISRC = BIT2;
//        printf("P2.2 INT occurred. \n");
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
//        printf("P2.2 INT occurred. \n");
		CLK_SysTickDelay(5000);
		if( VOL_ROTOB & BOTH_EDGE)
		{
			CLK_SysTickDelay(5000);
			BOTH_EDGE = 0;
			if(VOL_ROTOB)
				n++;		
		}
		else if(!( VOL_ROTOB | BOTH_EDGE))
		{
			CLK_SysTickDelay(5000);
			BOTH_EDGE = 1;
			if(!VOL_ROTOB)
				m++;
		}
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

