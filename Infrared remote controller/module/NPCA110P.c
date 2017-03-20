#include	"NPCA110P.h"

//定义端口
//sbit 			SCL_I2C_NPCA110P				= P0^4;
//sbit			SDA_I2C_NPCA110P				= P0^3;

#define		NPCA110P_EEPROM_SLA			0xe6
#define 	EEPROM_WR               0
#define 	EEPROM_RD               1

/*------------------------------------------------
              I2C初始化函数
------------------------------------------------*/
void Init_NPCA110P_I2C(void)
{
		P03_OpenDrain_Mode;
		P04_OpenDrain_Mode;
    Init_I2C();                //set SDA and SCL pins high
}

void writeChar_NPCA110P(UINT8 data_I2C)
{
		start_I2C();
		writebyte_I2C(NPCA110P_EEPROM_SLA|EEPROM_WR);
		respons_I2C();
		writebyte_I2C(data_I2C);
		respons_I2C();
		stop_I2C();
}

void writeString_NPCA110P(UINT8 number,UINT8 *data_I2C)
{
		UINT8 i=0;
		start_I2C();
		writebyte_I2C(NPCA110P_EEPROM_SLA|EEPROM_WR);
		respons_I2C();
		for(i=0;i<number;i++)
		{
				writebyte_I2C(*data_I2C++);
				respons_I2C();
		}
		stop_I2C();		
}