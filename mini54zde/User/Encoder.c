
#define Encoder_GLOBALS
#include "Encoder.h"


void Encoder_Task(void)
{
	/*************	vol	*******************/
	if( VOL_A & Encoder_vol_flag )
	{
		Encoder_vol_flag = 0;
		if(TAS_5754_vol[1][1] == 0x00)
		{
			;
//			if(P12 == 0){P12 = P12;}
//			if(P13 == 0){P13 = P13;}
//			if(P14 == 0){P14 = P14;}
		}		
		else
		{
			Amplifier_VOL_A();
//			NTP_8230[5] += 1;
//			I2C_SW_Send(0x54,NTP_8230+4,2);	
//			I2C_SW_Send(0xa0,NTP_8230+4,2);
//			if(P12 == 0){P12 = ~P12;CLK_SysTickDelay(40000);P12 = ~P12;}
//			if(P13 == 0){P13 = ~P13;CLK_SysTickDelay(40000);P13 = ~P13;}
//			if(P14 == 0){P14 = ~P14;CLK_SysTickDelay(40000);P14 = ~P14;}
		}

	}
	else if( VOL_B && Encoder_vol_flag == 0 )
	{
		Encoder_vol_flag = 1;
		if(TAS_5754_vol[1][1] == 0xff)
		{
			;
		}
		else
		{
			Amplifier_VOL_B();
//			NTP_8230[5] -= 1;
//			I2C_SW_Send(0x54,NTP_8230+4,2);
//			I2C_SW_Send(0xa0,NTP_8230+4,2);
//			if(P12 == 0){P12 = ~P12;CLK_SysTickDelay(40000);P12 = ~P12;}
//			if(P13 == 0){P13 = ~P13;CLK_SysTickDelay(40000);P13 = ~P13;}
//			if(P14 == 0){P14 = ~P14;CLK_SysTickDelay(40000);P14 = ~P14;}			
		}
				
	}
	/*************	treble	*******************/
	else if ( TREBLE_A && Encoder_treble_flag )
	{
//		NTP_8230[15] += 1;
//		I2C_SW_Send(0x54,NTP_8230+14,2);
//		I2C_SW_Send(0xa0,NTP_8230+14,2);
		Encoder_treble_flag = 0;
		Amplifier_TREBLE_A();
//		if(P12 == 0){P12 = ~P12;CLK_SysTickDelay(40000);P12 = ~P12;}
//		if(P13 == 0){P13 = ~P13;CLK_SysTickDelay(40000);P13 = ~P13;}
//		if(P14 == 0){P14 = ~P14;CLK_SysTickDelay(40000);P14 = ~P14;}
	}
	else if  ( TREBLE_B && Encoder_treble_flag == 0 )
	{
//		NTP_8230[15] -= 1;
//		I2C_SW_Send(0x54,NTP_8230+14,2);
//		I2C_SW_Send(0xa0,NTP_8230+14,2);
		Encoder_treble_flag = 1;
		Amplifier_TREBLE_B();
//		if(P12 == 0){P12 = ~P12;CLK_SysTickDelay(40000);P12 = ~P12;}
//		if(P13 == 0){P13 = ~P13;CLK_SysTickDelay(40000);P13 = ~P13;}
//		if(P14 == 0){P14 = ~P14;CLK_SysTickDelay(40000);P14 = ~P14;}
	}
	/*************	sub	*******************/
	else if  ( SUB_A && Encoder_sub_flag )
	{
//		NTP_8230[21] += 1;
//		I2C_SW_Send(0x54,NTP_8230+20,2);
//		I2C_SW_Send(0xa0,NTP_8230+20,2);
		Encoder_sub_flag = 0;
		Amplifier_BASS_A();
//		if(P12 == 0){P12 = ~P12;CLK_SysTickDelay(40000);P12 = ~P12;}
//		if(P13 == 0){P13 = ~P13;CLK_SysTickDelay(40000);P13 = ~P13;}
//		if(P14 == 0){P14 = ~P14;CLK_SysTickDelay(40000);P14 = ~P14;}
	}
	else if  ( SUB_B && Encoder_sub_flag == 0 )
	{
//		NTP_8230[21] -= 1;
//		I2C_SW_Send(0x54,NTP_8230+20,2);
//		I2C_SW_Send(0xa0,NTP_8230+20,2);
		Encoder_sub_flag = 1;
		Amplifier_BASS_B();
//		if(P12 == 0){P12 = ~P12;CLK_SysTickDelay(40000);P12 = ~P12;}
//		if(P13 == 0){P13 = ~P13;CLK_SysTickDelay(40000);P13 = ~P13;}
//		if(P14 == 0){P14 = ~P14;CLK_SysTickDelay(40000);P14 = ~P14;}
	}
}


