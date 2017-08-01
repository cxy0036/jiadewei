#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include <stdio.h>
#include "Mini51Series.h"
#include "task.h"
#include "KEY_Scan.h"

#ifdef Bluetooth_GLOBALS
	#define Bluetooth_EXT 
#else
	#define Bluetooth_EXT extern
#endif


//#define EP_DET  			P52
	

void Bluetooth_Test_Task(void);
void BT_patch(void);
void BT_Play_Pause(void);	
//void BT_REV_TASK(void);	
//void BT_FWD_TASK(void);	
	

#endif
