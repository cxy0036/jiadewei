
#ifndef __TAS5754_H__
#define __TAS5754_H__

#include <stdint.h>
#include <stdio.h>
#include "Mini51Series.h"
#include "i2c_software_gpio.h"
//#include "502.h"


#ifdef TAS5754_GLOBALS
	#define TAS5754_EXT 
#else
	#define TAS5754_EXT extern
#endif
	
//TAS5754_EXT uint8_t _TAS_5754_REG0[][2];
TAS5754_EXT uint8_t TAS_5754_REG0[][2];
TAS5754_EXT	const uint8_t IIC_REG_5754[][2];

#define slave_addr	0x98
	
void PA_5754_Init(uint8_t Adds);
void IICsetReg(uint8_t Adds,uint8_t* buff);
void Amplifier_Power_ON(void);
void Amplifier_Power_OFF(void);
void Amplifier_VOL_A(void);
void Amplifier_VOL_B(void);
void Amplifier_TREBLE_A(void);
void Amplifier_TREBLE_B(void);
void Amplifier_BASS_A(void);
void Amplifier_BASS_B(void);
void Amplifier_DELAY_A(void);
void Amplifier_DELAY_B(void);	
void Amplifier_BALANCE_A(void);
void Amplifier_BALANCE_B(void);	
void Amplifier_Auto_Mute(void);	
	
#endif
