
#ifndef __KEY_SCAN_H__
#define __KEY_SCAN_H__

#include <stdio.h>
#include "Mini51Series.h"
#include "task.h"
#include "Encoder.h"

#ifdef KEY_GLOBALS
	#define KEY_EXT 
#else
	#define KEY_EXT extern
#endif
	
#define POWER_KEY   		P14

//KEY_EXT uint8_t key_status;
KEY_EXT uint16_t key_count;
KEY_EXT uint8_t	POWER;
//KEY_EXT uint8_t	POWER_OFF;	
KEY_EXT uint8_t	POWER_FLAG;
KEY_EXT uint8_t Channel[];
KEY_EXT uint8_t	SYS_power_flag;
KEY_EXT	uint8_t ADC_V;
	
void ADC_init(void);
void ADC_IRQHandler(void);		
void Sys_power_on( void );
void Sys_power_off( void );	
void Channel_select( uint8_t* Channel );

	
#endif
	
