#ifndef	__BLUETOOTH_H
#define	__BLUETOOTH_H

#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#include	"time1.h"


/*************	本地常量声明	**************/
#define	GPIO1		P07
#define	GPIO2		P06
#define	GPIO3		P05
#define	PLAY		P11
#define	REV			P13
#define	FWD			P12
#define	VOL_UP		P00
#define	VOL_DOWN	P01
#define	PAIR		P10

#define	CMD_VOL_UP		(GPIO1==1) && (GPIO2==0) && (GPIO3==1)
#define	CMD_VOL_DOWN	(GPIO1==1) && (GPIO2==1) && (GPIO3==0)
#define	CMD_PLAY		(GPIO1==0) && (GPIO2==1) && (GPIO3==1)
#define	CMD_FWD			(GPIO1==0) && (GPIO2==1) && (GPIO3==0)
#define	CMD_REV			(GPIO1==0) && (GPIO2==0) && (GPIO3==1)
#define	CMD_PAIR		(GPIO1==1) && (GPIO2==0) && (GPIO3==0)

#define	__PLAY			1
#define	__REV			2
#define	__FWD			3
#define	__VOL_UP		4
#define	__VOL_DOWN		5
#define	__PAIR			6

/*************	本地函数声明	**************/
void	Bluetooth_process(void);
void	Bluetooth_CMD(UINT8	cmd);

/*************  外部函数和变量声明 *****************/

#endif