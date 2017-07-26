
#ifndef __NTP8230_H__
#define __NTP8230_H__

#include "i2c_software_gpio.h"

#ifdef NTP8230_GLOBALS
	#define NTP8230_EXT 
#else
	#define NTP8230_EXT extern
#endif

NTP8230_EXT uint8_t Soft_Mute_flag;	
NTP8230_EXT uint8_t PWM_Switching_flag;	
NTP8230_EXT	uint32_t Power_Meter;
NTP8230_EXT	unsigned char NTP_8230[];
	
//#define VOL_A_TASK()	NTP_8230[5] += 1;I2C_SW_Send(0x54,NTP_8230+4,2)
//#define VOL_B_TASK()	NTP_8230[5] -= 1;I2C_SW_Send(0x54,NTP_8230+4,2)
//#define TREBLE_A_TASK()	NTP_8230[5] += 1;I2C_SW_Send(0x54,NTP_8230+4,2)
//#define TREBLE_B_TASK()	NTP_8230[5] += 1;I2C_SW_Send(0x54,NTP_8230+4,2)
//#define SUB_A_TASK()	NTP_8230[5] += 1;I2C_SW_Send(0x54,NTP_8230+4,2)	
//#define SUB_B_TASK()	NTP_8230[5] += 1;I2C_SW_Send(0x54,NTP_8230+4,2)
	
	
void NTP_8230_INIT(void);	
void Soft_Mute(void);	
void PWM_Switching(void);
void PWM_MASK(void);
void Driver_Control(void);
void Power_Meter_Control(void);
void Power_Meter_Detect(void);
void VOL_A_TASK(void);
void VOL_B_TASK(void);
void TREBLE_A_TASK(void);
void TREBLE_B_TASK(void);
void SUB_A_TASK(void);	
void SUB_B_TASK(void);	
void POWER_TASK(void);	

NTP8230_EXT uint8_t NTP_8230_REG[];

#endif


