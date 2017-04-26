#include	"bluetooth.h"

bit		sw_time1 = 0;
bit		minutes_15_flag = 0;
UINT8	minutes_num = 0;
extern 	bit		minute_1_flag;

void	Bluetooth_process(void)
{
	UINT8	i=0,count=0,CMD=0;
	__delay_10ms(1);
/***********Induction remote commands**************/
	if(CMD_PLAY)
	{
		do
		{
			__delay_10ms(1);
			count++;
		}while(CMD_PLAY);
		if(count>15)
		{
			CMD=__PLAY;	
			Bluetooth_CMD(CMD);
			count=0;
		}
	}
	if(CMD_REV)
	{
		do
		{
			__delay_10ms(1);
			count++;
		}while(CMD_REV);
		if(count>15)
		{
			CMD=__REV;
			Bluetooth_CMD(CMD);
			count=0;
		}
	}
	if(CMD_FWD)
	{
		do
		{
			__delay_10ms(1);
			count++;
		}while(CMD_FWD);
		if(count>15)
		{
			CMD=__FWD;
			Bluetooth_CMD(CMD);
			count=0;
		}
	}
	if(CMD_VOL_UP)
	{
		do
		{
			__delay_10ms(1);
			count++;
		}while(CMD_VOL_UP);
		if(count>2)
		{
			CMD=__VOL_UP;
			Bluetooth_CMD(CMD);
			count=0;
		}
	}
	if(CMD_VOL_DOWN)
	{
		do
		{
			__delay_10ms(1);
			count++;
		}while(CMD_VOL_DOWN);
		if(count>2)
		{
			CMD=__VOL_DOWN;
			Bluetooth_CMD(CMD);
			count=0;
		}
	}
	if(CMD_PAIR)
	{
		do
		{
			__delay_10ms(1);
			count++;
		}while(CMD_PAIR);
		if(count>15)
		{
			CMD=__PAIR;
			Bluetooth_CMD(CMD);
			count=0;
		}
	}	

/***********Detection of Bluetooth connection status**************/
	if(BT_DET)
	{
		sw_time1 = 0;
		minute_1_flag = 0;
		minutes_15_flag = 0;
	}
	else
	{
		if(!sw_time1)
		{
			set_TR1;	
			sw_time1 = 1;
		}
		if(minute_1_flag)
		{
			set_TR1;
			minutes_num++;
			minute_1_flag = 0;
			if(minutes_num>15)
			{
				minutes_15_flag = 1;
				minutes_num = 0;
			}
		}//if(minute_1_flag)
		if(minutes_15_flag)
		{
			minutes_15_flag = 0;
			BT_POWER = 0;
			__delay_10ms(10);
			LOW_BAT_NOTIFY = 0;
//			while(1);
			ST_BY = 0;
//			BT_POWER = 0;
//			__delay_10ms(50);
//			ST_BY = 0;
			clr_EA;
			while(1)
			{
				set_PD;						
			}
		}//if(minutes_15_flag)
	}//if(BT_DET)
}

void	Bluetooth_CMD(UINT8	cmd)
{
	switch(cmd)
	{
		case	__PLAY:
			PLAY = 1;
			__delay_10ms(15);
			PLAY = 0;
			break;
		case	__REV:
			REV = 1;
			__delay_10ms(15);
			REV = 0;
			break;
		case	__FWD:
			FWD = 1;
			__delay_10ms(15);
			FWD = 0;
			break;
		case	__VOL_UP:
			VOL_UP = 1;
//			P00 = 1;
			__delay_10ms(15);
			VOL_UP = 0;
//			P00 = 0;
//			while(1);
			break;
		case	__VOL_DOWN:
			VOL_DOWN = 1;
//			P01 = 1;
			__delay_10ms(15);
			VOL_DOWN = 0;
//			P01 = 0;
//			while(1);
			break;
		case	__PAIR:
			PAIR = 1;
			__delay_10ms(15);
			PAIR = 0;
			break;
		default:
			break;
	}
}