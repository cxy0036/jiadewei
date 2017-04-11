#include	"bluetooth.h"

void	Bluetooth_process(void)
{
	UINT8	i=0,count=0,CMD=0;
	__delay_ms(1);
	if(CMD_PLAY)
	{
		do
		{
			__delay_ms(1);
			count++;
		}while(CMD_PLAY);
		if(count>20)
		{
			CMD=__PLAY;	
			count=0;
			Bluetooth_CMD(CMD);
		}
	}
	if(CMD_REV)
	{
		do
		{
			__delay_ms(1);
			count++;
		}while(CMD_REV);
		if(count>20)
		{
			CMD=__REV;
			count=0;
			Bluetooth_CMD(CMD);
		}
	}
	if(CMD_FWD)
	{
		do
		{
			__delay_ms(1);
			count++;
		}while(CMD_FWD);
		if(count>20)
		{
			CMD=__FWD;
			count=0;
			Bluetooth_CMD(CMD);
		}
	}
	if(CMD_VOL_UP)
	{
		do
		{
			__delay_ms(1);
			count++;
		}while(CMD_VOL_UP);
		if(count>20)
		{
			CMD=__VOL_UP;
			count=0;
			Bluetooth_CMD(CMD);
		}
	}
	if(CMD_VOL_DOWN)
	{
		do
		{
			__delay_ms(1);
			count++;
		}while(CMD_VOL_DOWN);
		if(count>20)
		{
			CMD=__VOL_DOWN;
			count=0;
			Bluetooth_CMD(CMD);
		}
	}
	if(CMD_PAIR)
	{
		do
		{
			__delay_ms(1);
			count++;
		}while(CMD_PAIR);
		if(count>20)
		{
			CMD=__PAIR;
			count=0;
			Bluetooth_CMD(CMD);
		}
	}	

}

void	Bluetooth_CMD(UINT8	cmd)
{
	switch(cmd)
	{
		case	__PLAY:
			PLAY = 1;
			__delay_ms(25);
			PLAY = 0;
			break;
		case	__REV:
			REV = 1;
			__delay_ms(25);
			REV = 0;
			break;
		case	__FWD:
			FWD = 1;
			__delay_ms(25);
			FWD = 0;
			break;
		case	__VOL_UP:
			VOL_UP = 1;
			P00 = 1;
			__delay_ms(25);
			P00 = 0;
			//while(1);
			break;
		case	__VOL_DOWN:
			VOL_DOWN = 1;
			P01 = 1;
			__delay_ms(25);
			P01 = 0;
			//while(1);
			break;
		case	__PAIR:
			PAIR = 1;
			__delay_ms(25);
			PAIR = 0;
			break;
		default:
			break;
	}
}