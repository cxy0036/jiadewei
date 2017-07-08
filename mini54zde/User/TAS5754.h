
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

TAS5754_EXT	uint8_t page_[5][2];	
TAS5754_EXT	uint8_t treble_level;
TAS5754_EXT uint8_t TAS_5754_vol[][2];
//TAS5754_EXT uint8_t TAS_5754_Treble[][2];
//TAS5754_EXT uint8_t TAS_5754_Bass[][2];	
//TAS5754_EXT uint8_t TAS_5754_REG0[][2];
TAS5754_EXT	const uint8_t IIC_REG_5754[][2];
TAS5754_EXT uint8_t sub_data1[17][8];
//typedef struct page
//{
//	uint8_t cmd;
//	uint8_t page_value;
//}page;

//typedef struct reg
//{
//	uint8_t cmd;
//	uint8_t *reg_data;
//}reg;
	
//typedef struct tas_5754
//{
//	uint8_t		cmd;
//	uint8_t		page_num;
//	uint8_t		reg;	
//	uint8_t		*data;
//}tas_5754;
//typedef struct TAS_5754_Tune
//{
//	tas_5754	*Tune;
//	uint8_t		*page0;
//}TAS_5754_Tune;

#define slave_addr	0x98
	

void tas_5758_init(void);
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
void tone_tuning(uint8_t tone);
	
#endif
