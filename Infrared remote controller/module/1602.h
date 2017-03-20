#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "common.h"

sbit lcd1602_rs_bit = P0^6;/*【根据实际需要修改】*/
sbit lcd1602_rw_bit = P0^5;/*【根据实际需要修改】*/
sbit lcd1602_en_bit = P0^7;/*【根据实际需要修改】*/

#define LCD1602_DATA_PORT	P0/*【根据实际需要修改】*/

/*default type:  
px^0---DB0(LSB)  
px^1---DB1  
px^2---DB2  	   
px^3---DB3  
px^4---DB4  
px^5---DB5  
px^6---DB6  
px^7---DB7(MSB)  
*/

/*  
RS          Rw      
0           0   ---->写命令    
0           1   ---->读状态    
1           0   ---->写数据   
1           1   ---->读数据        
*/ 

/*LCD1602 RW 引脚选择*/
#define LCD1602_READ_OPERATION		1/*读操作*/
#define LCD1602_WRITE_OPERATION		0/*写操作*/

/*LCD1602 RS 引脚选择*/
#define LCD1602_DATA_OPERATION		1/*数据模式*/
#define LCD1602_COMMAND_OPERATION	0/*命令模式*/

/*LCD1602 EN 引脚选择*/
#define LCD1602_ENABLE				1/*允许操作LCD1602*/
#define LCD1602_DISABLE				0/*禁止操作LCD1602*/

/*显示模式：16X2个字符， 5X7点阵，8位数据口*/
#define LCD1602_DEFAULT_DISPALY_MODE	0x38

/*
====================================================
LCD1602设置：显示允许或禁止、光标显示或禁止、光标闪烁或禁止  
====================================================
/*  
0   0   0   0   1   D   C   B            
										|   |   |------光标闪烁  : 1-->允许 ; 0-->禁止                      			
										|   |----------光标显示	 : 1-->允许 ; 0-->禁止                     			
										|-------------液晶屏显示 : 1-->允许 ; 0-->禁止   
*/

#define LCD1602_DISPLAY_ENABLE			0X04				 								/*允许液晶显示*/
#define LCD1602_CURSOR_DISPLAY_ENABLE	0X02				 							/*允许光标显示*/
#define LCD1602_CURSOR_BLINK_ENABLE 	0X01				 							/*允许光标闪烁*/
#define LCD1602_DISPLAY_DISABLE			(0X04 & (~(0x01<<2)))				/*禁止液晶显示*/
#define LCD1602_CURSOR_DISPLAY_DISABLE	(0X02 & (~(0x01<<1)))		/*禁止光标显示*/
#define LCD1602_CURSOR_BLINK_DISABLE 	(0X01 & (~(0x01<<0)))			/*禁止光标闪烁*/

/*默认设置:lcd显示，光标显示，光标闪烁*/					 
/*【根据实际需要修改】*/
#define LCD1602_DEFAULT_DISPLAY_AND_CURSOR_MODE 0x08 			|\
														LCD1602_DISPLAY_ENABLE				|\
														LCD1602_CURSOR_DISPLAY_ENABLE	|\
														LCD1602_CURSOR_BLINK_ENABLE

/*
====================================================
LCD1602设置：指针加一或减一、光标位置加一或减一
==================================================== 
0   0   0   0   0   1   N   S  
												|   |-----  屏幕移动:1-->允许 ; 0-->禁止                         
												|---------  
												N=1:读或者写一个字符后地址指针加1，且光标加1                                    
												N=0:度或者写一个字符后地址指针减1，且光标减1                        
												当S=1时 ：                            
												若N=1，整屏幕左移                                
												N=0，整屏幕右移                              
												以达到光标不移动，而整个屏幕移动的效果  
*/   	 									

#define LCD1602_POINT_AND_CURSOR_PLUS		0X02				 						/*指针加一、光标加一*/
#define LCD1602_SCREEN_MOVE_ENABLE			0x01				 						/*允许屏幕移动*/
#define LCD1602_POINT_AND_CURSOR_MINUS		(0X02 & (~(0X01<<1)))	/*指针减一、光标减一*/
#define LCD1602_SCREEN_MOVE_DISABLE			(0x01 & (~(0X01<<0)))		/*禁止屏幕移动*/

/*默认设置:光标和指针加一，屏幕不移动*/						     
/*【根据实际需要修改】*/
#define LCD1602_DEFAULT_POINT_AND_POINT_ADDRESS_MODE 0X04				|\
																LCD1602_POINT_AND_CURSOR_PLUS		|\
																LCD1602_SCREEN_MOVE_DISABLE

/*行位置参数，注意行地址从0开始*/											
#define LCD1602_ROW0	0										/*第0行*/		
#define LCD1602_ROW1	1										/*第1行*/		
#define LCD1602_MIN_ROW	LCD1602_ROW0			/*行数的最小值，为LCD1602_ROW0，即0*/
#define LCD1602_MAX_ROW	LCD1602_ROW1			/*行数的最大值，为LCD1602_ROW1，即1*/

/*列位置参数，注意列地址从0开始*/
#define LCD1602_ROW_LENGHT	0x28 					/*每一行的长度为0x28,即40*/
#define LCD1602_MIN_COLUMN	0							/*列数的最小值，为0*/
#define LCD1602_MAX_COLUMN	(LCD1602_ROW_LENGHT-1)			/*列数的最大值，为39*/
/*每一行的起始地址*/
#define LCD1602_ROW0_ADDRESS_START	0X80								/*第0行起始地址*/
#define LCD1602_ROW1_ADDRESS_START	(0X80+0X40)					/*第1行起始地址*/

/*每一行的结束地址*/
#define LCD1602_ROW0_ADDRESS_END (LCD1602_ROW0_ADDRESS_START+LCD1602_ROW_LENGHT)/*第0行结束地址*/
#define LCD1602_ROW1_ADDRESS_END (LCD1602_ROW1_ADDRESS_START+LCD1602_ROW_LENGHT)/*第1行结束地址*/

/*命令集指令*/
#define LCD1602_CLEAN_ALL_DISPALY					0x01				/*清屏指令*/
#define LCD1602_CURSOR_RETURN_TO_ORIGIN		0x02				/*光标归位指令*/

/*错误返回值*/
#define LCD1602_ROW_OR_COLUMN_OVERFLOW 		-1

/*****************外部接口函数******************/
//写命令
extern void Lcd1602WriteCommand(UB8 commandCode);
//写数据
extern void Lcd1602WriteData(UB8 dataCode);
//清屏
extern void Lcd1602CleanAll(void) ;
//光标归位
extern void Lcd1602CursorHoming(void);
//LCD1602初始化
extern void Lcd1602Init(void) ;
//LCD1602地址写字节
extern SB8 Lcd1602AddressWriteByte(UB8 row,UB8 column,UB8 dataCode);
//LCD1602地址写字符串
extern SB8 Lcd1602AddressWriteString(UB8 row,UB8 column,UB8 *stringCode);
/**********************************************/
#endif	/*__LCD1602_H__*/