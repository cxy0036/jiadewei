#ifndef __NPCA110P_H__
#define __NPCA110P_H__

#include "N76E003.h"
#include "Common.h"
#include "Define.h"
#include "Function_define.h"
#include "I2C.h"

#ifndef		_EX_NPCA110P
	#define	_EX_NPCA110P   
#else
	#define	_EX_NPCA110P		extern	
#endif

_EX_NPCA110P	void Init_NPCA110P_I2C(void);
_EX_NPCA110P	void writeChar_NPCA110P(UINT8 data_I2C);
_EX_NPCA110P	void writeString_NPCA110P(UINT8 number,UINT8 *data_I2C);

#endif