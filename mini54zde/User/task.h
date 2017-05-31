#include <stdio.h>
//#include "AIOS.h"
#include "Mini51Series.h"
//#include "i2c_software_gpio_with_timer.h"

#ifdef TASK_GLOBALS
	#define TASK_EXT 
#else
	#define TASK_EXT extern
#endif

/**
  * IR Define
  */
#define IR_BT_REV			54
#define IR_BT_FWD			53
#define IR_BT_POWER			52
	
/** Define GPIO Pin. 
 *
 */
#define BT_REV				P04
#define BT_FWD				P05
#define BT_DET				P06
#define BT_POWER			P07
#define ICE_DAT				P47
#define ICE_CLK				P46
#define _4052_B				P26
#define _4052_A				P25
#define _RST				P24
#define _SDA				P23
#define _SCL				P22
#define EP_DET  			P52
#define ST_BY   			P36
#define SUB_ROTOB			P35
#define SUB_ROTOA			P34
#define TREBLE_ROTOB		P32
#define TREBLE_ROTOA		P31
#define VOL_ROTOB  			P54
#define VOL_ROTOA   		P30
#define IR					P10
#define LED_B				P12
#define LED_G				P13
#define LED_R				P14

#define VOL_ROTOA_1			1
#define VOL_ROTOB_2			2
#define TREBLE_ROTOA_3		3
#define	TREBLE_ROTOB_4		4
#define	SUB_ROTOA_5			5
#define SUB_ROTOB_6			6

//VOL	Addr 0x2D: Master Volume Fine Control

void _RST_8230( void );
void Sys_power_on( void );
void Sys_power_off( void );
void GPIO_Init( void );
void Channel_select( uint8_t Channel );

