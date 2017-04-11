//  File Function: N76E885 demo 
//***********************************************************************************************************
#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "GPIO.h"


/*************	本地常量声明	**************/


/*************	本地变量声明	**************/


/*************	本地函数声明	**************/
void	mcu_init(void);
void	GPIO_config(void);

/*************  外部函数和变量声明 *****************/

void	mcu_init(void)
{
	GPIO_config();
}


/******************** IO配置函数 **************************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
/*************	P0	**************/	
	GPIO_InitStructure.Pin  = GPIO_Pin_0;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_1;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_2;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_3;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_4;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_5;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_6;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_7;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	
//	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
//	GPIO_InitStructure.Mode = GPIO_HighZ;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//初始化


/*************	P1	**************/
	GPIO_InitStructure.Pin  = GPIO_Pin_0;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_1;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_2;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_3;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_4;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_5;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_6;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = GPIO_Pin_7;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	
	
/*************	P2	**************/	
	GPIO_InitStructure.Pin  = GPIO_Pin_0;
	GPIO_InitStructure.Mode = GPIO_HighZ;

	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);

	
/*************	P3	**************/
	GPIO_InitStructure.Pin  = GPIO_Pin_0;
	GPIO_InitStructure.Mode = GPIO_PullUp;
//	GPIO_InitStructure.Mode = GPIO_HighZ;
//	GPIO_InitStructure.Mode = GPIO_OUT_OD;
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);
	
	
}


/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
	mcu_init();
	while(1)
	{
		
	}
}