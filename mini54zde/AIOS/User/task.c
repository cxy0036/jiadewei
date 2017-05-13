#include "task.h"

//void CtrlTask( void *pvParameters )
//{
//	for( ;; )
//	{
//		OSSemPost(LedSemHandle);	

//		OSTaskSleep( OSM2T(500) );        
//	}
//}


//void LedTask( void *pvParameters )
//{
//	for( ;; )
//	{
//		OSSemPend(LedSemHandle, OSPEND_FOREVER_VALUE);	
//		/* Toggle P2.3 */
//		P23 ^= 1;

//		/* Toggle P3.6 */
//		P36 ^= 1;                
//	}
//}

void Headset_Test_Task(void *pvParameters)
{
	sOSBase_t xStatus;
	for( ;; )
	{
		if(EP_DET)
		{
			xStatus = OSSemPost(Headset_SemHandle);			
			if( xStatus != OS_TRUE )
			{
				printf("Could not post semaphore.\r\n" );
			}		
			OSTaskSleep( OSM2T(200) );
		}
	}
}


//void Bluetooth_Test_Task(void *pvParameters)
//{
//	sOSBase_t xStatus;
//	for( ;; )
//	{
//		if(BT_DET)
//		{
//			xStatus = OSSemPost(SemHandle);			
//			if( xStatus != OS_TRUE )
//			{
//				printf("Could not post semaphore.\r\n" );
//			}		
//			OSTaskSleep( OSM2T(200) );
//		}
//	}
//}

//void Encoder_Task(void *pvParameters)
//{
//	for( ;; )
//	{
//		switch(Pin)
//		{
//			case VOL_ROTOA:
//				break;
//			case VOL_ROTOB:
//				break;
//		}
//	}
//}
