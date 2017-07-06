#ifndef __HEADSET_H__
#define __HEADSET_H__

#include <stdio.h>
#include "Mini51Series.h"
#include "task.h"
#include "i2c_software_gpio.h"

#ifdef Headset_GLOBALS
	#define Headset_EXT 
#else
	#define Headset_EXT extern
#endif


void Headset_Test_Task( void );
	
#endif
