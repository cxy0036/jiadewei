
#define Headset_GLOBALS
#include "Headset.h"

extern 	uint8_t NTP_8230[];
uint8_t	Headset_flag = 1;

/************************************************************
 *@Headset file
 ************************************************************/
 /*
 *Headset test task function
 */
void Headset_Test_Task( void )
{
//	uint8_t xStatus;
	
	if(EP_DET & Headset_flag)//打开耳机
	{
		;
//			_RST_8230();
//			I2C_SW_Open(50000);
//			I2C_SW_Send( 0x54,NTP_8230,350);
//			Headset_flag = 0;
	}
	else if( ( EP_DET== 0 ) && ( Headset_flag == 0 ) )//关闭耳机
	{
		;
//			_RST_8230();
//			I2C_SW_Open(50000);
//			I2C_SW_Send( 0x54,NTP_8230,350);
//			Headset_flag = 1;
	}
}

