#ifndef __LCD1602_H__
#define __LCD1602_H__
	
	
	#define uchar unsigned  char     // 宏定义uchar 为无符号字符
	#define uint  unsigned  int  

	#define DataPin	P0 

	sbit  LCD_RS = P0^4;	//	LCD	数据/ 命令选择 ,高电平时选择数据寄存器
	sbit  LCD_RW = P0^3;	//  LCD 读 / 写选择	   ,高电平时读操作
	sbit  LCD_E  = P0^2;	//  LCD 使能
	sbit  IR_DQ  = P0^1;	//	红外接收头数据线

	void  LCD_BusyCheck(void);
	void  LCD_WriteByte(uchar var,bit RS);
	void  LCD_Init(void);
	void  LCD_WriteString(uchar *str,uchar line);
	void  LCD_CGRAM_WriteByte(uchar *p,uchar num);
	void  LCD_Delay(uint n);
	
#endif