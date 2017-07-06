#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include <stdio.h>
#include "Mini51Series.h"
#include "task.h"
//#include "i2c_software_gpio.h"
#include "KEY_Scan.h"

#ifdef Bluetooth_GLOBALS
	#define Bluetooth_EXT 
#else
	#define Bluetooth_EXT extern
#endif


//#define EP_DET  			P52
	
	
void Bluetooth_Test_Task(void);
void BT_REV_TASK(void);	
void BT_FWD_TASK(void);	
	

#endif
