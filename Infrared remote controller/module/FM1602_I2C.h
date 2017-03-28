#ifndef __FM1602_I2C_H__
#define __FM1602_I2C_H__

#ifndef		_EX_FM1602_I2C
	#define	_EX_FM1602_I2C   
#else
	#define	_EX_FM1602_I2C		extern
#endif

#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

sbit 			SCL_I2C									= P1^3;
sbit 			SDA_I2C									= P1^4;
//******************************************************************** 
// 文件名称：  I2C.h 
// 创建日期：  2017-3-21 
// 最新更改：  2017-3-21 
// 描述：      I2C初始化  
//********************************************************************                                     
// 

#define _XTAL_FREQ 2000000// 延时函数delay_us/ms使用此值 
#define Slave_Add   0x7E	// 从器件地址,PCF8574A,0x7E                                     
													// PCF8574,0x27,左移1位,0x4E,  
//#define I2C_BPS     0x18 	// I2C波特率Fclock = Fosc/((I2C_BPS+1)*4)                                     
													// 2MHz,20k,0x18  
//#define Idle !(SSP1STATbits.R_nW|(0x1F & SSP1CON2)) // 空闲   
#define I2C_CLOCK     159							//25kbps 
#define Idle					!(SCL_I2C&SDA_I2C)			// 空闲		
_EX_FM1602_I2C	void I2CInit  ( ); 
_EX_FM1602_I2C	void I2CError( );
_EX_FM1602_I2C	void I2CStart ( ); 
_EX_FM1602_I2C	void I2CStop  ( ); 
_EX_FM1602_I2C	void ReStart  ( );  
_EX_FM1602_I2C	void I2CSendByte(unsigned char I2CSnBy); 
_EX_FM1602_I2C	void WriteCommand(unsigned char Command); 
_EX_FM1602_I2C	void WriteData (unsigned char Data); 
_EX_FM1602_I2C	void LCD1602Init(void);  
_EX_FM1602_I2C	void Dip_Single_char(unsigned char col,unsigned char row,unsigned char sign);
_EX_FM1602_I2C	void DisDec(unsigned char col_D,unsigned char row_D,unsigned int Temp_k );   
/********************************************************************* 
**The End  
*********************************************************************/

#endif