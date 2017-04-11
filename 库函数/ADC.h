
#ifndef	__ADC_H
#define	__ADC_H

#include	"config.h"
#include 	"Define.h"
#include 	"Function_define.h"
#include 	"GPIO.h"

/*************	本地常量声明	**************/

//#define	ADC_P11		0x02	//IO引脚 P11
//#define	ADC_P03		0x08	//IO引脚 P03
//#define	ADC_P04		0x10	//IO引脚 P04
//#define	ADC_P05		0x20	//IO引脚 P05
//#define	ADC_P06		0x40	//IO引脚 P06
//#define	ADC_P07		0x80	//IO引脚 P07
//#define	ADC_P30		0x01	//IO引脚 P30
//#define	ADC_P17		0x80	//IO引脚 P17
//#define GPIO_Px		1		//0.1.3

#define ADC_90T		(3<<5)
#define ADC_180T	(2<<5)
#define ADC_360T	(1<<5)
#define ADC_540T	0
#define ADC_FLAG	(1<<4)	//软件清0
#define ADC_START	(1<<3)	//自动清0
#define ADC_CH0		0
#define ADC_CH1		1
#define ADC_CH2		2
#define ADC_CH3		3
#define ADC_CH4		4
#define ADC_CH5		5
#define ADC_CH6		6
#define ADC_CH7		7

#define ADC_RES_H2L8	1
#define ADC_RES_H8L2	0


/*************	本地变量声明	**************/


/*************	本地函数声明	**************/
typedef struct
{
	u8	ADC_Px;			//设置要做ADC的IO,	ADC_P10 ~ ADC_P17,ADC_P1_All
	u8	ADC_Speed;		//ADC速度			ADC_90T,ADC_180T,ADC_360T,ADC_540T
	u8	ADC_Power;		//ADC功率允许/关闭	ENABLE,DISABLE
	u8	ADC_AdjResult;	//ADC结果调整,	ADC_RES_H2L8,ADC_RES_H8L2
	u8	ADC_Polity;		//优先级设置	PolityHigh,PolityLow
	u8	ADC_Interrupt;	//中断允许		ENABLE,DISABLE
} ADC_InitTypeDef;

void	ADC_Inilize(u8 GPIO, ADC_InitTypeDef *ADCx);
void	ADC_PowerControl(u8 pwr);
u16		Get_ADC10bitResult(u8 channel);	//channel = 0~7

/*************  外部函数和变量声明 *****************/

#endif
