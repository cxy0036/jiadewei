#define TASK_GLOBALS
#include "task.h"
/************************************************************
 *@init file
 ************************************************************/
/*
 *Init GPIO mode 
 */
void GPIO_Init( void )
{
	/* Set P1.5 to ADC channel 0 input pin */
    SYS->P1_MFP = SYS_MFP_P15_AIN5;//SYS_MFP_P10_AIN1
	/* Analog pin OFFD to prevent leakage */
    P1->OFFD |= (1 << 5) << GPIO_OFFD_OFFD_Pos;
	
	/* Init P2.2 P2.3 P2.4 and P3.6 to be output mode */
	GPIO_SetMode(P0, BIT4, GPIO_PMD_OUTPUT);//BT_REV
	GPIO_SetMode(P0, BIT5, GPIO_PMD_OUTPUT);//BT_FWD
	GPIO_SetMode(P0, BIT7, GPIO_PMD_OUTPUT);//BT_POWER
	GPIO_SetMode(P1, BIT2, GPIO_PMD_OUTPUT);//LED_B
	GPIO_SetMode(P1, BIT3, GPIO_PMD_OUTPUT);//LED_G
	GPIO_SetMode(P1, BIT4, GPIO_PMD_OUTPUT);//LED_R
//	GPIO_SetMode(P2, BIT2, GPIO_PMD_OUTPUT);//_SCL
//	GPIO_SetMode(P2, BIT3, GPIO_PMD_OUTPUT);//_SDA
	GPIO_SetMode(P2, BIT4, GPIO_PMD_OUTPUT);//_RST
//	GPIO_SetMode(P2, BIT4, GPIO_PMD_QUASI);
	GPIO_SetMode(P2, BIT5, GPIO_PMD_OUTPUT);//_4052_A
	GPIO_SetMode(P2, BIT6, GPIO_PMD_OUTPUT);//_4052_B
	GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT);//ST_BY 
	/* Configure P2.2 and P2.3 as open-drain mode */
    GPIO_SetMode(P2, BIT2, GPIO_PMD_OPEN_DRAIN);
	GPIO_SetMode(P2, BIT3, GPIO_PMD_OPEN_DRAIN);
	
	/*****init gpio output******/
	ST_BY = 1;
	_4052_A = 0;
	_4052_B = 0;
	_RST = 0;
	P23 = 0;
	P22 = 0;
	P23 = 1;
	P22 = 1;
}


void Sys_power( void )
{
	ST_BY = 1;
}

void Channel_select( void )
{
	_4052_A = 1;
	_4052_B = 0;
}

void _RST_8230( void )
{
	_RST = 1;
	TIMER_Delay( TIMER0, 5000 );
	_RST = 0;
	TIMER_Delay( TIMER0, 5000 );
	_RST = 1;
}

#if 0

uOS8_t POWER_KEY_4052 = 0,IR_POWER_KEY;



/************************************************************
 *@Headset file
 ************************************************************/
 /*
 *Headset test task function
 */
void Headset_Test_Task(void *pvParameters)
{
	sOSBase_t xStatus;
	unsigned char	pdata[]={0x7e,0x01};
	for( ;; )
	{
		if(EP_DET)
		{
			I2C_SW_I_Send(0x56,pdata,2);      //关闭功放     
			I2C_SW_I_Send(0x56,pdata,2); 	  //打开耳机通道
		}
		else
		{
			I2C_SW_I_Send(0x56,pdata,2);      //打开功放   
			I2C_SW_I_Send(0x56,pdata,2); 	  //关闭耳机通道
		}
	}
}
 /*
 *Headset work task function
 */
//void Headset_task( void *pvParameters )
//{
//	unsigned char	pdata[]={0x7e,0x01};
//	for( ;; )
//	{
//		OSSemPend(Headset_SemHandle, OSPEND_FOREVER_VALUE);	
//		I2C_SW_I_Send(0x56,pdata,2);      //关闭功放     
//		I2C_SW_I_Send(0x56,pdata,2); 	  //打开耳机通道
//	}	
//}

/************************************************************
 *@Bluetooth file
 ************************************************************/
 /*
 *Bluetooth Test task function
 */
void Bluetooth_Test_Task(void *pvParameters)
{
	sOSBase_t xStatus;
	for( ;; )
	{
		if(BT_DET)
		{
			xStatus = OSSemPost(Bluetooth_SemHandle);			
			if( xStatus != OS_TRUE )
			{
				printf("Could not post semaphore.\r\n" );
			}		
			OSTaskSleep( OSM2T(200) );
		}
	}
}
 /*
 *Bluetooth work task function
 */
void Encoder_Task(void *pvParameters)
{
	for( ;; )
	{
		OSSemPend(Bluetooth_SemHandle, OSPEND_FOREVER_VALUE);
		if( IR_BT_REV )
		{
			BT_REV = 1;
		}
		if( IR_BT_FWD )
		{
			BT_FWD = 1;
		}
//		switch(Pin)
//		{
//			case VOL_ROTOA:
//				break;
//			case VOL_ROTOB:
//				break;
//		}
	}
}

/************************************************************
 *@KeyPress file
 ************************************************************/
 /*
 *KeyPress test task function
 */
void KeyPress_test_Task( void )
{
	for( ;; )
	{
		// Enable channel 5
		ADC_Open(ADC, 0, 0, 0x10);
		// Power on ADC
		ADC_POWER_ON(ADC);
		if( IR_POWER_KEY )
		{
			IR_POWER_KEY = 0;
			POWER_KEY_4052++;
			switch( POWER_KEY_4052 )
			{
				case 1:
					_4052_A = 0;
					_4052_B = 0;
					break;
				case 2:
					_4052_A = 0;
					_4052_B = 1;
					break;
				case 3:
					_4052_A = 1;
					_4052_B = 0;
					break;
				case 4:
					_4052_A = 1;
					_4052_B = 1;
					break;
				default:
					break;
			}
//			if( POWER_KEY_4052 == 1 )
//			{
//				_4052_A = 0;
//				_4052_B = 0;
//			}
		}
	}
}

/************************************************************
 *@Encoder file
 ************************************************************/
/*
 *Encoder test task function
 */
void Encoder_test_Task( void *pdata )
{
	unsigned char coder = 0;
	for( ;; )
	{
		if( VOL_ROTOA )
		{
			coder = VOL_ROTOA_1;
		}
		if( VOL_ROTOB )
		{
			coder = VOL_ROTOB_2;
		}
		if( TREBLE_ROTOA )
		{
			coder = TREBLE_ROTOA_3;
		}
		if( TREBLE_ROTOB )
		{
			coder = TREBLE_ROTOB_4;
		}
		if ( SUB_ROTOA )
		{
			coder = SUB_ROTOA_5;
		}
		if( SUB_ROTOB )
		{
			coder = SUB_ROTOB_6;
		}
		switch( coder )
		{
			case VOL_ROTOA_1:
				coder = 0;
				I2C_SW_I_Send(0x56,pdata,2); //Volume up
				break;
			case VOL_ROTOB_2:
				coder = 0;
				I2C_SW_I_Send(0x56,pdata,2); //Volume down
				break;
			case TREBLE_ROTOA_3:
				coder = 0;
				I2C_SW_I_Send(0x56,pdata,2); //Treble up
				break;
			case TREBLE_ROTOB_4:
				coder = 0;
				I2C_SW_I_Send(0x56,pdata,2); //Treble down
				break;
			case SUB_ROTOA_5:
				coder = 0;
				I2C_SW_I_Send(0x56,pdata,2); //Bass up
				break;
			case SUB_ROTOB_6:
				coder = 0;
				I2C_SW_I_Send(0x56,pdata,2); //Bass down
				break;
			default:
				break;
		}
	}	
}

/************************************************************
 *@IR file
 ************************************************************/

#endif

