#include	"LCD1602.h"
	
	
	void LCD_Delay(uint n)
	{
		while(--n);				// 8us一次
	}

	
	void LCD_BusyCheck(void)
	{
		uchar isBusy;
		LCD_RS = 0;
		LCD_RW = 1;
		LCD_E  = 1;
		LCD_Delay(10);
		isBusy = DataPin & 0x80;     
		LCD_E  = 0;

		if(isBusy == 0x80)
		{
			LCD_BusyCheck();
		}
	}

	void LCD_WriteByte(uchar var,bit RS )	   //参数 RS为 LCD数据/ 命令选择 ,高电平时选择数据寄存器
	{
		LCD_BusyCheck();
		LCD_RS = RS;
		LCD_RW = 0;
		DataPin = var;
		LCD_E = 0;
		LCD_Delay(70);					  //必须延时500us左右		
		LCD_E  = 1;
		LCD_Delay(5);
		LCD_E = 0;
	}

	void LCD_WriteString(uchar *str,uchar line)
	{
		uchar i = 0,addr;
		if(line == 1) { addr = 0x80;}
		if(line == 2) { addr = 0xC0;}
		while(1)		
		{			
			LCD_WriteByte(addr+i,0);	   //写入地址
			LCD_WriteByte(str[i],1);
			i++;
			if(i==16 || str[i] == '\0'){ break;}
		}			
	}

	void LCD_CGRAM_WriteByte(uchar *p,uchar num)		   //将自定义字符写入CGRAM中,最多64字节,uchar num为自定义字符存放位置 0-7
	{
		uchar i,place;
		place = 0x40 + 8*(num&0x07);					// num & 0x07 保证num取值范围为 0-7
		for(i=0;i<8;i++)
		{
			LCD_WriteByte(place+i,0);		
			LCD_WriteByte(p[i],1);
		}
	}


	void LCD_Init(void)
	{
		LCD_Delay(1875);			//延时15ms
		LCD_WriteByte(0x38,0);
		LCD_Delay(625);				//延时5ms
		LCD_WriteByte(0x38,0);  //配置LCD为4位数据总线,双行显示,5*7点阵字符
		LCD_WriteByte(0x08,0);  //配置LCD关闭显示,无光标,无闪烁
		LCD_WriteByte(0x01,0);  //LCD清屏
		LCD_WriteByte(0x06,0);  //LCD光标右移
		LCD_WriteByte(0x0C,0);  //打开LCD显示
	}