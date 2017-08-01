
#define Encoder_GLOBALS
#include "Encoder.h"

uint8_t	tone;
uint8_t	tone_flag;
uint8_t	tone_1=0,tone_2=0,tone_3=0,tone_4=0,tone_5=0,tone_6=0;

#if 0
void Encoder_Task(void)
{
	if(vol_n>0xf0)
	{
		Amplifier_VOL_A();
		vol_n = 0xf0;
	}
	if(vol_n<0xf0)
	{
		Amplifier_VOL_B();
		vol_n = 0xf0;
	}
	if(treble_n>0xf0)
	{
		Amplifier_TREBLE_A();
		treble_n = 0xf0;
	}
	if(treble_n<0xf0)
	{
		Amplifier_TREBLE_B();
		treble_n = 0xf0;
	}
	if(sub_n>0xf0)
	{
		Amplifier_BASS_A();
		sub_n = 0xf0;
	}
	if(sub_n<0xf0)
	{
		Amplifier_BASS_B();
		sub_n = 0xf0;
	}
}
#endif 

void Encoder_Task(void)
{
	LED_Flag = 0;
	tone_flag = 1;
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
	}
	else if  ( TREBLE_B && Encoder_treble_flag == 0 )
	{
		Encoder_treble_flag = 1;
		Amplifier_TREBLE_B();
	}
	/*************	sub	*******************/
	else if  ( SUB_A && Encoder_sub_flag )
	{
		Encoder_sub_flag = 0;
		Amplifier_BASS_A();
	}
	else if  ( SUB_B && Encoder_sub_flag == 0 )
	{
		Encoder_sub_flag = 1;
		Amplifier_BASS_B();
	}
	
	VOL_F=0,TREBLE_F=0,SUB_F=0;
}


