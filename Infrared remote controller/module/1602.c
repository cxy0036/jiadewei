/***************************************************************************
模    块:LCD1602.c  
说    明:LCD1602驱动程序
版    本:Version2.0.0		
2016/01/06 12:08(OK)
编译环境:Keil 8051 C complier V9.01
主控芯片:STC12C5A60S2  		
@11.0592MHZ
作    者:杨瑞
联系方式:【QQ】279729201		 
【Email】279729201@qq.com            		          
yangrui90s@163.com		 
修改记录:
=================	
2017/01/6 12:08
	记录:		
1.增加中文注释。		
2.修改函数名称模式，首写字母改为大写，例如lcd1602ReadStatus修改为Lcd1602ReadStatus。		
3.修改延时函数，将Delay1msForLcd1602函数修改为Delay80usForLcd1602函数。注意，这两个函数都是		  
由STC-ISP生成，Delay80usForLcd1602函数由STC-ISP V6.85Q的“软件延时计算器”针对STC-Y3指令集		  
@11.0592MHZ自动生成。经过测试，延时59us可能会出现只书写部分内容的情况，延时60us正好可以。		  
为了安全，也可以将此延时修改的更长。
=================

=================	
2014/04/31 20:09	
记录:	
1.解决大工程中，因未安装LCD1602而导致的工程卡死在函数	
lcd1602CheckBusy()的问题，将		
do
{
	;		
}
while( (lcd1602ReadStatus()) & 0x80));		
修改为		
do
{			
	i++;		
}while( ((lcd1602ReadStatus()) & 0x80)  && (i<10));		
因为在未安装LCD1602时，通过"读状态"函数lcd1602ReadStatus()读回来的永远是0xff,		
如果采用第一种算法，会导致程序"卡死"。
=================

=================	
2014/02/24 23:44
记录:	
1.增加函数lcd1602AddressWriteString(...)
=================

=================
2014/02/24 15:00记录:
1.增加函数delay1msForLcd1602()	  
STC12C5A60S2单片机操作速度快比传统8051快，某些操作延时必须足够。
=================
***************************************************************************/

#include <intrins.h>
#include <string.h>
#include "1602.h"
/*外部接口函数在lcd1602.h中声明*/
/*****************内部函数******************/
static void Delay80usForLcd1602(void) ;
static UB8 Lcd1602ReadStatus(void) ;
static void Lcd1602CheckBusy(void) ;
/**********************************************/

/******************************************************************
- 函数名称：Delay80usForLcd1602
- 功能描述：延时函数
- 隶属模块：LCD1602模块
- 函数属性：内部函数
- 参数说明：无
- 返回说明：无
- 注：此函数由STC-ISP V6.85Q的“软件延时计算器”针对STC-Y3指令集 @11.0592MHZ自动生成，若    
指令集或晶振不同，需稍作修改。
******************************************************************/
static void Delay80usForLcd1602(void)
{
	unsigned char i, j;
	_nop_();
	_nop_();
	_nop_();
	i = 1;
	j = 216;
	do
	{
		while (--j);
	} while (--i);
}

/******************************************************************
- 函数名称：Lcd1602ReadStatus
- 功能描述：读取LCD1602状态值
- 隶属模块：LCD1602模块
- 函数属性：内部函数
- 参数说明：无
- 返回说明：LCD1602的状态值
******************************************************************/
static UB8 Lcd1602ReadStatus(void)
{
	UB8 statusCode ;
	lcd1602_en_bit = LCD1602_DISABLE ;			/*禁止操作LCD1602*/
	lcd1602_rs_bit = LCD1602_COMMAND_OPERATION ;/*命令模式*/
	lcd1602_rw_bit = LCD1602_READ_OPERATION ;	/*读操作*/
	LCD1602_DATA_PORT = 0xff ;
	Delay80usForLcd1602() ;
	lcd1602_en_bit = LCD1602_ENABLE ;			/*允许操作LCD1602*/
	Delay80usForLcd1602() ;
	statusCode = LCD1602_DATA_PORT ;			/*读取状态值*/
	lcd1602_en_bit = LCD1602_DISABLE ;			/*禁止操作LCD1602*/
	return statusCode ;
}

/******************************************************************
- 函数名称：Lcd1602CheckBusy
- 功能描述：判断LCD1602是否忙碌：若忙碌则等待；若空闲则执行任务
- 隶属模块：LCD1602模块
- 函数属性：内部函数 
- 参数说明：无 
- 返回说明：无
- 注：当LCD1602_DATA_PORT[7]等于1，表示LCD1602忙碌，则需要等待一会儿   
当LCD1602_DATA_PORT[7]等于0，表示LCD1602空闲，则需要继续执行后面的任务				  
LCD1602_DATA_PORT[7]==0,lcd1602 is free.
- 补充：这里的“10”是经过测试的，测试中，利用串口打印
的i的值为1，这里写10已经足够大了。
******************************************************************/
static void Lcd1602CheckBusy(void)
{
	UW16 i=0;
	do
	{
		i++;
	}while( ((Lcd1602ReadStatus()) & 0x80) && (i<10));
}

/******************************************************************
- 函数名称：Lcd1602WriteCommand
- 功能描述：LCD1602写命令
- 隶属模块：LCD1602模块
- 函数属性：外部函数，供用户调用
- 参数说明：需要发送给LCD1602的指令值
- 返回说明：无
******************************************************************/

void Lcd1602WriteCommand(UB8 commandCode)
{
	Lcd1602CheckBusy();
	lcd1602_en_bit = LCD1602_DISABLE ;			/*禁止操作LCD1602*/
	lcd1602_rs_bit = LCD1602_COMMAND_OPERATION ;/*命令模式*/
	lcd1602_rw_bit = LCD1602_WRITE_OPERATION ;	/*写操作*/
	LCD1602_DATA_PORT = commandCode ;			/*发送指令值*/
	Delay80usForLcd1602();
	lcd1602_en_bit = LCD1602_ENABLE ;			/*允许操作LCD1602*/
	Delay80usForLcd1602();
	lcd1602_en_bit = LCD1602_DISABLE ;			/*禁止操作LCD1602*/
}

/******************************************************************
- 函数名称：Lcd1602WriteData
- 功能描述：LCD1602写数据
- 隶属模块：LCD1602模块
- 函数属性：外部函数，供用户调用
- 参数说明：需要发送给LCD1602的数据
- 返回说明：无
******************************************************************/

void Lcd1602WriteData(UB8 dataCode)
{	
	Lcd1602CheckBusy() ;
	lcd1602_en_bit = LCD1602_DISABLE ;			/*禁止操作LCD1602*/
	lcd1602_rs_bit = LCD1602_DATA_OPERATION ;	/*数据模式*/
	lcd1602_rw_bit = LCD1602_WRITE_OPERATION ;	/*写操作*/
	LCD1602_DATA_PORT = dataCode;				/*发送数据*/
	Delay80usForLcd1602();
	lcd1602_en_bit = LCD1602_ENABLE ;			/*允许操作LCD1602*/
	Delay80usForLcd1602();
	lcd1602_en_bit = LCD1602_DISABLE ;	 		/*禁止操作LCD1602*/ 
}


/******************************************************************
- 函数名称：Lcd1602CleanAll
- 功能描述：清除屏幕显示
- 隶属模块：LCD1602模块
- 函数属性：外部函数，供用户调用
- 参数说明：无
- 返回说明：无
- 注：清除屏幕显示，光标归位(左上角)，地址计数器AC设为0
******************************************************************/

void Lcd1602CleanAll(void)
{
	Lcd1602WriteCommand(LCD1602_CLEAN_ALL_DISPALY);
}


/******************************************************************
- 函数名称：Lcd1602CursorHoming
- 功能描述：光标归位
- 隶属模块：LCD1602模块
- 函数属性：外部函数，供用户调用
- 参数说明：无
- 返回说明：无
- 注：光标归为，当屏幕移动显示时，lcd1602显示所有数据后，
	   调用此函数，屏幕显示的所有东西都会归位。光标在第一
	   个位置(0x80)。
******************************************************************/

void Lcd1602CursorHoming(void)
{
	Lcd1602WriteCommand(LCD1602_CURSOR_RETURN_TO_ORIGIN);
}


/******************************************************************
 
- 函数名称：Lcd1602Init
- 功能描述：LCD1602初始化 
- 隶属模块：LCD1602模块
- 函数属性：外部函数，供用户调用
- 参数说明：无
- 返回说明：无
- 注：设置
（1）显示模式
（2）液晶显示允许或禁止、光标显示允许或禁止、光标闪烁允许或禁止
（3）地址指针加一或减一、光标指针加一或减一、屏幕左移或右移
可通过修改LCD1602.H中的LCD1602_DEFAULT_DISPALY_MODE、LCD1602_DEFAULT_DISPLAY_AND_CURSOR_MODE、
 LCD1602_DEFAULT_POINT_AND_POINT_ADDRESS_MODE达到不同的显示效果。
******************************************************************/

void Lcd1602Init(void)
{
		lcd1602_en_bit = LCD1602_DISABLE ;
		Lcd1602CleanAll();
		Lcd1602WriteCommand(LCD1602_DEFAULT_DISPALY_MODE);
		Lcd1602WriteCommand(LCD1602_DEFAULT_DISPLAY_AND_CURSOR_MODE);
		Lcd1602WriteCommand(LCD1602_DEFAULT_POINT_AND_POINT_ADDRESS_MODE);
		/*可忽略，在Lcd1602CleanAll()中隐含了该功能*/
		//Lcd1602CursorHoming(); 
		lcd1602_en_bit = LCD1602_DISABLE ;
}


/******************************************************************
- 函数名称：Lcd1602AddressWriteByte
- 功能描述：在LCD1602的row行column列写入数据dataCode
- 隶属模块：LCD1602模块
- 函数属性：外部函数，供用户调用
- 参数说明：row-->行地址，有效值为LCD1602_ROW0或LCD1602_ROW1
column-->列地址，有效值为0~39之间的整数
dataCode-->需要写入的数据。
- 返回说明：0（成功）或者-1（失败）
- 注：行地址和列地址都是从0开始的。
想在LCD1602的第0行第2列显示阿里伯数字5，调用方式为
 Lcd1602AddressWriteByte(LCD1602_ROW0,2,‘5’）；
在DEBUG模式下，会对入参进行有效性判断，协助分析。调试后期可通过
屏蔽common.h中的"#define DEBUG  1"减小目标文件的大小。   
******************************************************************/

SB8 Lcd1602AddressWriteByte(UB8 row,UB8 column,UB8 dataCode)
{
	#ifdef   DEBUG
	if(column< LCD1602_MIN_COLUMN|| column > LCD1602_MAX_COLUMN|| \
	( (row != LCD1602_ROW0) &&(row != LCD1602_ROW1)))
	{
			return LCD1602_ROW_OR_COLUMN_OVERFLOW ;
	}
	#endif /*DEBUG*/
	if(row == LCD1602_ROW0)
	{
		Lcd1602WriteCommand(LCD1602_ROW0_ADDRESS_START+column) ;
	}
	else if(row == LCD1602_ROW1)
	{
		Lcd1602WriteCommand(LCD1602_ROW1_ADDRESS_START+column) ;
	}
	Lcd1602WriteData(dataCode);
	return 0;
}

/******************************************************************
- 函数名称：Lcd1602AddressWriteString
- 功能描述：从LCD1602的row行column列开始写入字符串stringCode
- 隶属模块：LCD1602模块
- 函数属性：外部函数，供用户调用
- 参数说明：row-->行地址，有效值为LCD1602_ROW0或LCD1602_ROW1
						column-->列地址，有效值为0~39之间的整数
						stringCode-->字符串
- 返回说明：0（成功）或者-1（失败）
- 注：行地址和列地址都是从0开始的。
			想在LCD1602的第0行第2列显示"test"，调用方式为
			Lcd1602AddressWriteString(LCD1602_ROW0,2,"test"）；
			这里使用的是strlen，而不是sizeof。
			在DEBUG模式下，会对入参进行有效性判断，协助分析。调试后期可通过
			屏蔽common.h中的"#define DEBUG  1"减小目标文件的大小。
******************************************************************/

SB8 Lcd1602AddressWriteString(UB8 row,UB8 column,UB8 *stringCode)
{
		UB8 length = strlen(stringCode) ; 
		#ifdef DEBUG
		if(column< LCD1602_MIN_COLUMN|| (column+strlen(stringCode)-1) > LCD1602_MAX_COLUMN|| \
		( (row != LCD1602_ROW0) &&(row != LCD1602_ROW1)))
		{
					return LCD1602_ROW_OR_COLUMN_OVERFLOW ;
		}
		#endif	/*DEBUG*/
		if(row == LCD1602_ROW0)
		{
			Lcd1602WriteCommand(LCD1602_ROW0_ADDRESS_START+column) ;
		}
		else if(row == LCD1602_ROW1)
		{
			Lcd1602WriteCommand(LCD1602_ROW1_ADDRESS_START+column) ;
		}
		while(length--)
		{
			Lcd1602WriteData(*stringCode);
			stringCode++;
		}
		return 0;
}