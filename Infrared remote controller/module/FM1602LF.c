#include	"FM1602LF.h"


//定义端口
sbit SDA_I2C_FM1602LF = P0^6; //RS为寄存器选择，高电平时选择数据寄存器、低电平时选择指令寄存器。
sbit SCL_I2C_FM1602LF = P0^5; //R/W为读写信号线，高电平时进行读操作，低电平时进行写操作。
sbit EN = P0^7; //E端为使能端，当E端由高电平跳变成低电平时，液晶模块执行命令。

#define		FM1602LF_EEPROM_SLA			0xe6
#define 	EEPROM_WR               0
#define 	EEPROM_RD               1

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1


//EX_extern	void Init_FM1602LF_I2C(void);
//EX_extern	void writeChar_FM1602LF(UINT8 data_I2C);
//EX_extern	void LCD_Init(void);
//EX_extern	void LCD_Write_Com(unsigned char com) ;
//EX_extern	void DelayMs(unsigned char t);

/*------------------------------------------------------
 mS延时函数
 含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振16M，精确延时请使用汇编
------------------------------------------------------*/
void DelayMs(unsigned char t)
{
		uint8_t	i=1334;
    while(t--)
    {
        //大致延时1mS
        while(i--);
    }
}

/*------------------------------------------------
              I2C初始化函数
------------------------------------------------*/
void Init_FM1602LF_I2C(void)
{
		P05_OpenDrain_Mode;
		P06_OpenDrain_Mode;
    Init_I2C();                                 //set SDA and SCL pins high
}

/*------------------------------------------------
             Send one byte
------------------------------------------------*/
void writeChar_FM1602LF(UINT8 data_I2C)
{
		start_I2C();
		writebyte_I2C(FM1602LF_EEPROM_SLA|EEPROM_WR);
		respons_I2C();
		writebyte_I2C(data_I2C);
		respons_I2C();
		stop_I2C();
}

/*------------------------------------------------
              LCD初始化函数
------------------------------------------------*/
void LCD_Init(void) 
{
		LCD_Write_Com(0x38);    /*显示模式设置*/ 
    DelayMs(5); 
    LCD_Write_Com(0x38); 
    DelayMs(5); 
    LCD_Write_Com(0x38); 
    DelayMs(5); 
    LCD_Write_Com(0x38);  
    LCD_Write_Com(0x08);    /*显示关闭*/ 
    LCD_Write_Com(0x01);    /*显示清屏*/ 
    LCD_Write_Com(0x06);    /*显示光标移动设置*/ 
    DelayMs(5); 
    LCD_Write_Com(0x0C);    /*显示开及光标设置*/
}

/*------------------------------------------------------
                    写入命令函数
------------------------------------------------------*/
void LCD_Write_Com(unsigned char com) 
{  
//    while(LCD_Check_Busy()); //忙则等待

}

/*------------------------------------------------------
                    写入数据函数
------------------------------------------------------*/
void LCD_Write_Data(unsigned char Data) 
{ 
//    while(LCD_Check_Busy()); //忙则等待

}


/*------------------------------------------------------
                    清屏函数
------------------------------------------------------*/
void LCD_Clear(void) 
{ 
    LCD_Write_Com(0x01); 
    DelayMs(5);
}


/*------------------------------------------------------
                    写入字符串函数
------------------------------------------------------*/
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
{     
    if (y == 0) 
    {     
        LCD_Write_Com(0x80 + x);     //表示第一行
    }
    else 
    {      
        LCD_Write_Com(0xC0 + x);      //表示第二行
    } 

    while (*s) 
    {     
        LCD_Write_Data( *s);     
        s ++;     
    }
}

/*------------------------------------------------------
                    写入字符函数
------------------------------------------------------*/
void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
{     
    if (y == 0) 
    {     
        LCD_Write_Com(0x80 + x);     
    }    
    else 
    {     
        LCD_Write_Com(0xC0 + x);     
    }
    
    LCD_Write_Data( Data);  
}