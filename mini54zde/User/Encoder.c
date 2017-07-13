
#define Encoder_GLOBALS
#include "Encoder.h"



void Encoder_Task(void)
{
	/*************	vol	*******************/
	if( VOL_A & Encoder_vol_flag )
	{
		Encoder_vol_flag = 0;
			Amplifier_VOL_A();

	}
	else if( VOL_B && Encoder_vol_flag == 0 )
	{
		Encoder_vol_flag = 1;
			Amplifier_VOL_B();
							
	}
	/*************	treble	*******************/
	else if ( TREBLE_A && Encoder_treble_flag )
	{
		Encoder_treble_flag = 0;
		Amplifier_TREBLE_A();
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
	}
	else if  ( TREBLE_B && Encoder_treble_flag == 0 )
	{
		Encoder_treble_flag = 1;
		Amplifier_TREBLE_B();
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
	}
	/*************	sub	*******************/
	else if  ( SUB_A && Encoder_sub_flag )
	{
		Encoder_sub_flag = 0;
		Amplifier_BASS_A();
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
	}
	else if  ( SUB_B && Encoder_sub_flag == 0 )
	{
		Encoder_sub_flag = 1;
		Amplifier_BASS_B();
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
	}
}


