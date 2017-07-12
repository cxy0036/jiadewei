
#ifndef __IR_H__
#define __IR_H__

#include "task.h"
#include "Encoder.h"
#include "NTP8230.h"
#include "tas5754.h"
//#include "KEY_Scan.h"
#include "task.h"
#include "Bluetooth.h"

#ifdef IR_GLOBALS
	#define IR_EXT 
#else
	#define IR_EXT extern
#endif
	
	
void IR_init(void);
void IR_test_task(void);

#endif

