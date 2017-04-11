#ifndef	__SYSINIT_H
#define	__SYSINIT_H

#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#include	"adc.h"
#include	"time0.h"
#include	"time1.h"

void 	gpio_init(void);
//void	time0_init(void);
//void	adc_init(void);
void	sys_init(void);
void	SetSysClock(void);


#endif