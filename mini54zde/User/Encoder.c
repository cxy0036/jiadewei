
#define Encoder_GLOBALS
#include "Encoder.h"

uint8_t	tone;
uint8_t	tone_flag;
uint8_t	tone_1=0,tone_2=0,tone_3=0,tone_4=0,tone_5=0,tone_6=0;

//void Encoder_(void)
//{
//	if( ( SYS_power_flag ) && (tone_flag) )
//	{
//		switch(tone)
//		{
//			case 0:
//				if(tone_1<5)
//				Amplifier_VOL_A();
//			break;
//			case 1:
//				if(tone_2<5)
//				Amplifier_VOL_B();
//			break;
//			case 2:
//				if(tone_3<5)
//				Amplifier_TREBLE_A();
//			break;
//			case 3:
//				if(tone_4<5)
//				Amplifier_TREBLE_B();
//			break;
//			case 4:
//				if(tone_5<5)
//				Amplifier_BASS_A();
//			break;
//			case 5:
//				if(tone_6<5)
//				Amplifier_BASS_B();
//			break;
//			default:
//				break;
//		}
//	}
//	tone_flag = 0;
//}
void Encoder_Task(void)
{
	LED_Flag = 0;
	tone_flag = 1;
	/*************	vol	*******************/
	if( VOL_A & Encoder_vol_flag )
	{
		Encoder_vol_flag = 0;
//		tone = 0;
//		tone_1++;tone_2=tone_3=tone_4=tone_5=tone_6=0;
			Amplifier_VOL_A();

	}
	else if( VOL_B && Encoder_vol_flag == 0 )
	{
		Encoder_vol_flag = 1;
//		tone = 1;
//		tone_2++;tone_1=tone_3=tone_4=tone_5=tone_6=0;
			Amplifier_VOL_B();
							
	}
	/*************	treble	*******************/
	else if ( TREBLE_A && Encoder_treble_flag )
	{
		Encoder_treble_flag = 0;
//		tone = 2;
//		tone_3++;tone_2=tone_1=tone_4=tone_5=tone_6=0;
		Amplifier_TREBLE_A();
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
	}
	else if  ( TREBLE_B && Encoder_treble_flag == 0 )
	{
		Encoder_treble_flag = 1;
//		tone = 3;
//		tone_4++;tone_2=tone_3=tone_1=tone_5=tone_6=0;
		Amplifier_TREBLE_B();
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
	}
	/*************	sub	*******************/
	else if  ( SUB_A && Encoder_sub_flag )
	{
		Encoder_sub_flag = 0;
//		tone = 4;
//		tone_5++;tone_2=tone_3=tone_4=tone_1=tone_6=0;
		Amplifier_BASS_A();
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
	}
	else if  ( SUB_B && Encoder_sub_flag == 0 )
	{
		Encoder_sub_flag = 1;
//		tone = 5;
//		tone_6++;tone_2=tone_3=tone_4=tone_5=tone_1=0;
		Amplifier_BASS_B();
//			if(LED_R == 0){LED_R = ~LED_R;CLK_SysTickDelay(40000);LED_R = ~LED_R;}
//			if(LED_G == 0){LED_G = ~LED_G;CLK_SysTickDelay(40000);LED_G = ~LED_G;}
//			if(LED_B == 0){LED_B = ~LED_B;CLK_SysTickDelay(40000);LED_B = ~LED_B;}
	}
}


