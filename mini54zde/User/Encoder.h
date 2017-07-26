#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "task.h"
#include "i2c_software_gpio.h"
//#include "NTP8230.h"
#include "tas5754.h"

#ifdef Encoder_GLOBALS
	#define Encoder_EXT 
#else
	#define Encoder_EXT extern
#endif


//#define EP_DET  			P52
//#define	VOL_A		( ( VOL_ROTOA == 0 ) && ( VOL_ROTOB == 0 ) )
#define	VOL_B		( ( VOL_ROTOA == 0 ) && ( VOL_ROTOB == 1 ) )
#define	VOL_A		( ( VOL_ROTOA == 1 ) && ( VOL_ROTOB == 0 ) )
#define	VOL_D		( ( VOL_ROTOA == 1 ) && ( VOL_ROTOB == 1 ) )	
//#define TREBLE_A	( ( TREBLE_ROTOA == 0 ) && ( TREBLE_ROTOB == 0 ) )
#define TREBLE_B	( ( TREBLE_ROTOA == 0 ) && ( TREBLE_ROTOB == 1 ) )
#define TREBLE_A	( ( TREBLE_ROTOA == 1 ) && ( TREBLE_ROTOB == 0 ) )
#define TREBLE_D	( ( TREBLE_ROTOA == 1 ) && ( TREBLE_ROTOB == 1 ) )
//#define SUB_A	( ( SUB_ROTOA == 0 ) && ( SUB_ROTOB == 0 ) )
#define SUB_B	( ( SUB_ROTOA == 0 ) && ( SUB_ROTOB == 1 ) )
#define SUB_A	( ( SUB_ROTOA == 1 ) && ( SUB_ROTOB == 0 ) )
#define SUB_D	( ( SUB_ROTOA == 1 ) && ( SUB_ROTOB == 1 ) )
	
	
Encoder_EXT uint8_t	Encoder_vol_flag;
Encoder_EXT uint8_t	Encoder_treble_flag;
Encoder_EXT uint8_t	Encoder_sub_flag;
	
	
void Encoder_(void);
void Encoder_Task(void);
	
#endif
