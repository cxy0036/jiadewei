#ifndef __FM1602LF_H__
#define __FM1602LF_H__

#include "N76E003.h"
#include "Common.h"
#include "Define.h"
#include "Function_define.h"
#include "I2C.h"

#ifndef		_EX_FM1602LF
	#define	_EX_FM1602LF   
#else
	#define	_EX_FM1602LF		extern	
#endif

_EX_FM1602LF	void Init_FM1602LF_I2C(void);
_EX_FM1602LF	void writeChar_FM1602LF(UINT8 data_I2C);
_EX_FM1602LF	void LCD_Init(void);
_EX_FM1602LF	void LCD_Write_Com(unsigned char com);
_EX_FM1602LF	void DelayMs(unsigned char t);

#endif