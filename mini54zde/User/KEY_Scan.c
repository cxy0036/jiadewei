
#define KEY_GLOBALS
#include "KEY_Scan.h"

//#define POWER_KEY   		P15
#define KEY_VALUE			1
#define KEY_NULL			0

//���峤������TICK��,�Լ���_�������TICK��
#define KEY_LONG_PERIOD		100
#define KEY_CONTINUE_PERIOD	25
//���尴������ֵ״̬(����,����,��_��,�ͷ�)
#define KEY_DOWN		0x80
//#define KEY_short		0x40
#define KEY_SHORT		0x40
#define KEY_LONG		0x20
#define KEY_CONTINUE	0x20
#define KEY_UP			0x10
//#define KEY_UP			5
//���尴��״̬
#define KEY_STATE_INIT		0	//��ʼ״̬
#define KEY_STATE_WOBBLE	1	//����״̬
#define KEY_STATE_PRESS		2	//����״̬
#define KEY_STATE_LONG		3	//����״̬
#define KEY_STATE_CONTINUE	4	//����״̬
#define KEY_STATE_RELEASE	5	//�ͷ�״̬

char n = 0,m = 0,k=0,j=0,flag = 0;
//	static uint8_t s_u8LastKey = KEY_NULL,BOTH_EDGE_ROTOB = 1,BOTH_EDGE_ROTOA = 1;

void Sys_power_on( void )
{
	ST_BY = 1;
}

void Sys_power_off( void )
{
	ST_BY = 0;
}

void Channel_select( uint8_t Channel )
{
	switch( Channel )
	{
		case 0:
			_4052_A = 0;
			_4052_B = 0;
			P12 = 0;P13 = 1;P14 = 1;
			break;
		case 1:
			_4052_A = 1;
			_4052_B = 0;
			P12 = 1;P13 = 0;P14 = 1;
			break;
		case 2:
			_4052_A = 0;
			_4052_B = 1;
			P12 = 1;P13 = 1;P14 = 0;
			break;
		case 3:
			_4052_A = 1;
			_4052_B = 1;
			P12 = 0;P13 = 0;P14 = 0;
			break;
		default:
			break;
	}
}
