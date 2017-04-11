

#include	"adc.h"


//========================================================================
// 函数: void	ADC_Inilize(ADC_InitTypeDef *ADCx)
// 描述: ADC初始化程序.
// 参数: ADCx: 结构参数,请参考adc.h里的定义.
// 返回: none.
// 版本: V1.0, 2012-10-22
//========================================================================
void	ADC_Inilize(u8 GPIO, ADC_InitTypeDef *ADCx)
{
/******************ADC通道选择********************/	
	#if 1
/******************	IO配置	********************/
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = ADCx->ADC_Px;
	GPIO_InitStructure.Mode = GPIO_HighZ;		//浮空输入
	GPIO_Inilize(GPIO,&GPIO_InitStructure);
	#endif
	
	ADCCON0&=0xF0;
	//if(GPIO==1 && GPIO_InitStructure.Pin==1)
	AINDIDS=0x00;
	//Enable_ADC_AIN0;
	#if 0
	P1ASF = ADCx->ADC_Px;
	ADC_CONTR = (ADC_CONTR & ~ADC_90T) | ADCx->ADC_Speed;
	if(ADCx->ADC_Power == ENABLE)	ADC_CONTR |= 0x80;
	else							ADC_CONTR &= 0x7F;
	if(ADCx->ADC_AdjResult == ADC_RES_H2L8)	PCON2 |=  (1<<5);	//10位AD结果的高2位放ADC_RES的低2位，低8位在ADC_RESL。
	else									PCON2 &= ~(1<<5);	//10位AD结果的高8位放ADC_RES，低2位在ADC_RESL的低2位。
	if(ADCx->ADC_Interrupt == ENABLE)	EADC = 1;			//中断允许		ENABLE,DISABLE
	else								EADC = 0;
	if(ADCx->ADC_Polity == PolityHigh)	PADC = 1;		//优先级设置	PolityHigh,PolityLow
	else								PADC = 0;
	#endif
}


//========================================================================
// 函数: void	ADC_PowerControl(u8 pwr)
// 描述: ADC电源控制程序.
// 参数: pwr: 电源控制,ENABLE或DISABLE.
// 返回: none.
// 版本: V1.0, 2012-10-22
//========================================================================
void	ADC_PowerControl(u8 pwr)
{
	#if 0
	if(pwr == ENABLE)	ADC_CONTR |= 0x80;
	else				ADC_CONTR &= 0x7f;
	#endif
}

//========================================================================
// 函数: u16	Get_ADC10bitResult(u8 channel)
// 描述: 查询法读一次ADC结果.
// 参数: channel: 选择要转换的ADC.
// 返回: 10位ADC结果.
// 版本: V1.0, 2012-10-22
//========================================================================
u16	Get_ADC10bitResult(u8 channel)	//channel = 0~7
{
	if(channel > ADC_CH7)	return	1024;	//错误,返回1024,调用的程序判断	
	
	ADCCON0|=channel;
	switch(channel)
	{
		case	ADC_CH0:
			AINDIDS|=SET_BIT0;
			break;
		case	ADC_CH1:
			AINDIDS|=SET_BIT1;
			break;
		case	ADC_CH2:
			AINDIDS|=SET_BIT2;
			break;
		case	ADC_CH3:
			AINDIDS|=SET_BIT3;
			break;
		case	ADC_CH4:
			AINDIDS|=SET_BIT4;
			break;
		case	ADC_CH5:
			AINDIDS|=SET_BIT5;
			break;
		case	ADC_CH6:
			AINDIDS|=SET_BIT6;
			break;
		case	ADC_CH7:
			AINDIDS|=SET_BIT7;
			break;
		default:
			break;
	}
	ADCCON1|=SET_BIT0;
	
	#if 0
	u16	adc;
	u8	i;

	if(channel > ADC_CH7)	return	1024;	//错误,返回1024,调用的程序判断	
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | ADC_START | channel; 
	NOP(4);			//对ADC_CONTR操作后要4T之后才能访问

	for(i=0; i<250; i++)		//超时
	{
		if(ADC_CONTR & ADC_FLAG)
		{
			ADC_CONTR &= ~ADC_FLAG;
			if(PCON2 &  (1<<5))		//10位AD结果的高2位放ADC_RES的低2位，低8位在ADC_RESL。
			{
				adc = (u16)(ADC_RES & 3);
				adc = (adc << 8) | ADC_RESL;
			}
			else		//10位AD结果的高8位放ADC_RES，低2位在ADC_RESL的低2位。
			{
				adc = (u16)ADC_RES;
				adc = (adc << 2) | (ADC_RESL & 3);
			}
			return	adc;
		}
	}
	return	1024;	//错误,返回1024,调用的程序判断
	#endif
	return 1024;
}


//========================================================================
// 函数: void ADC_int(void) interrupt ADC_VECTOR
// 描述: ADC中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2012-10-22
//========================================================================
//void ADC_int (void) interrupt ADC_VECTOR
//{
//	#if 0
//	ADC_CONTR &= ~ADC_FLAG;
//	#endif
//}


