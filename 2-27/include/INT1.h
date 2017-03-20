#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Function_define.h"
//#include "Common.h"

//#define	boot_code_min	32000				//8ms
//#define boot_code_max	60000				//15ms
//#define data0_min			3200				//0.8ms
//#define data0_max			6000				//1.5ms
//#define data1_min			8000				//2ms
//#define data1_max			10000				//2.5ms
//#define	Num						33					//32code

//unsigned char 		time=0;
//UINT8 		CodeNum=0,Code[5]={0};
//uint32_t	time=0;
//BIT				First_INT=0,Start_Flag=0;

void INT1_ISR_init(void);
//void INT1_ISR(void)	interrupt 2