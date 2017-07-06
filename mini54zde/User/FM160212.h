#ifndef __FM160212_H__
#define __FM160212_H__

//#include "task.h"
//#include "Encoder.h"
//#include "NTP8230.h"
#include "i2c_software_gpio.h"

#ifdef FM160212_GLOBALS
	#define FM160212_EXT 
#else
	#define FM160212_EXT extern
#endif
	
#define	FM_slave_addr	0x78
	
FM160212_EXT	uint8_t	lcd_init[18];

	void init_lcd( void );

#endif

