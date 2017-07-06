
#ifndef __IR_H__
#define __IR_H__

#include "task.h"
#include "Encoder.h"
#include "NTP8230.h"
//#include "KEY_Scan.h"
#include "task.h"

#ifdef IR_GLOBALS
	#define IR_EXT 
#else
	#define IR_EXT extern
#endif
	
	
void IR_init(void);
void GPIO01_IRQHandler(void);
void TMR1_IRQHandler(void);
void IR_test_task(void);

#endif

