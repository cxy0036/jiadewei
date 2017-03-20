#ifndef __I2C_H__
#define __I2C_H__

#ifndef		_EX_I2C
	#define	_EX_I2C   
#else
	#define	_EX_I2C		extern
#endif

_EX_I2C	void	delay(void);
_EX_I2C	void Init_I2C(void);
_EX_I2C	void start_I2C(void);
_EX_I2C	void writebyte_I2C(UINT8 data_I2C);
_EX_I2C	UINT8 readbyte_I2C(void);
_EX_I2C	void respons_I2C(void);
_EX_I2C	void stop_I2C(void);
//EX_extern	void writebyte_I2C1_one(UINT8 data_I2C);
//EX_extern	void writebyte_I2C1_many(UINT8 number,UINT8 *data_I2C);

#endif