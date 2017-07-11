
#ifndef __TAS5754_H__
#define __TAS5754_H__

#include <stdint.h>
#include <stdio.h>
#include "Mini51Series.h"
#include "i2c_software_gpio.h"
#include "task.h"

#define slave_addr	0x98
#define _24c02_addr	0xa0


#ifdef TAS5754_GLOBALS
	#define TAS5754_EXT 
#else
	#define TAS5754_EXT extern
#endif

typedef struct page
{
	uint8_t cmd;
	uint8_t page_value;
}page;

typedef struct reg_12
{
	uint8_t reg_value;
	uint8_t reg_data[12];
}reg_12;
typedef struct reg_8
{
	uint8_t reg_value;
	uint8_t reg_data[8];
}reg_8;
typedef struct reg
{
	uint8_t reg_value;
	uint8_t reg_data;
}reg;
typedef struct Treble
{
	page	page1_T;
	reg_8	reg1_t;
	page	page2_T;
	reg_12	reg2_t;
	page	page3_T;
	reg		reg3_t;
	page	page4_T;
	reg_8	reg4_t;
	page	page5_T;
	reg_12	reg5_t;
	page	page0_T;
}Treble;
typedef struct Bass
{
	page	page1_T;
	reg_8	reg1_t;
	page	page2_T;
	reg_12	reg2_t;
	page	page3_T;
	reg		reg3_t;
	page	page4_T;
	reg_8	reg4_t;
	page	page5_T;
	reg_12	reg5_t;
	page	page0_T;
}Bass;

void test_24c02(void);
void TAS_5754_Init(uint8_t Adds);
void Amplifier_Power_ON(void);
void Amplifier_Power_OFF(void);
void Amplifier_VOL_A(void);
void Amplifier_VOL_B(void);
void treble_adjust(void);
void Amplifier_TREBLE_A(void);
void Amplifier_TREBLE_B(void);
void bass_adjust(void);
void Amplifier_BASS_A(void);
void Amplifier_BASS_B(void);
void Amplifier_DELAY_A(void);
void Amplifier_DELAY_B(void);	
void Amplifier_BALANCE_A(void);
void Amplifier_BALANCE_B(void);	
void Amplifier_Auto_Mute(void);	
	
#endif
