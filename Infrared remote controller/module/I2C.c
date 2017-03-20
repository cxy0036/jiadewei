/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2016 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2016
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 I2C demo code, Slave Address of 24LC64 = 0xA0
//
//   ____________           ______________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |N76E003(M) |          |   24LC64(S) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
//  Microchip I2C EEPROM 24xx64 (64K Bit) is used as the slave device.  
//  The page size are 32Byte. Total are 256 page.
//  If verification passes, Port3 will show 0x78. If there is any failure
//  occured during the progress, Port3 will show 0x00.
//***********************************************************************************************************

#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include	"I2C.h"

//#define SYS_CLK_EN              0
//#define SYS_SEL                 2
//#define SYS_DIV_EN              0                   //0: Fsys=Fosc, 1: Fsys = Fosc/(2*CKDIV)
//#define SYS_DIV                 1
//#define I2C_CLOCK               159									//25kbps 

//#define EEPROM_SLA              0xe6
//#define EEPROM_WR               0
//#define EEPROM_RD               1

//#define LED                     P3
//#define PAGE_SIZE               32
//#define PAGE_NUMBER             4

//#define ERROR_CODE              0x78
//#define TEST_OK                 0x00

//定义端口
//sbit			SDA_I2C_FM1602LF				= P0^6; //RS为寄存器选择，高电平时选择数据寄存器、低电平时选择指令寄存器。
//sbit 			SCL_I2C_FM1602LF 				= P0^5; //R/W为读写信号线，高电平时进行读操作，低电平时进行写操作。
//sbit 			SCL_I2C_NPCA110P				= P0^4;
//sbit			SDA_I2C_NPCA110P				= P0^3;
sbit 			SCL_I2C									= P0^4;
sbit 			SDA_I2C									= P0^3;

//EX_extern	void	delay(void);
//EX_extern	void start_I2C(void);
//EX_extern	void respons_I2C(void);
//EX_extern	void stop_I2C(void);
//EX_extern	void writebyte_I2C(UINT8 data_I2C);
//EX_extern	UINT8 readbyte_I2C(void);
//EX_extern	void I2C_Error(void);

//EX_extern	void writebyte_I2C_add(UINT8 address,UINT8 data_I2C);
//EX_extern	UINT8 readbyte_I2C_add(UINT8 address);
//EX_extern	void One_Page_Read(UINT8 u8PageNumber,UINT8 u8DAT);
//EX_extern	void One_Page_Write(UINT8 u8PageNumber,UINT8 u8DAT);

//========================================================================================================
void	delay(void)
{
		UINT16 i = 0;
		for(i=0;i<50;i++);
//		Timer1_Delay10us(1);
}

//========================================================================================================
void I2C_Error(void)
{
//    P3 = I2STAT;
//    P3 = ERROR_CODE;
    while (1)P12 = 0;    
}

void Init_I2C(void)
{
		SCL_I2C = 1;                                //set SDA and SCL pins high
		delay();
    SDA_I2C = 1;
		delay();
}
//========================================================================================================
void start_I2C(void)
{
		SDA_I2C = 1;
		delay();
		SCL_I2C = 1; 
		delay();
		SDA_I2C = 0;
		delay();
}

//========================================================================================================
void respons_I2C(void)
{
		UINT16 i = 0;
		delay();
		delay();
		delay();
		delay();
		SCL_I2C = 1;
		delay();
		while((SDA_I2C == 1)&&(i<10))
		{
				delay();
				i++;
				if(i==10)
				{
						I2C_Error();
				}
		}
		SCL_I2C = 0;
		delay();
		delay();
		delay();
		delay();
		delay();
}

//========================================================================================================
void stop_I2C(void)
{
		SDA_I2C = 0;
		delay();
		SCL_I2C = 1;
		delay();
		SDA_I2C = 1;
		delay();
}

void writebyte_I2C(UINT8 data_I2C)
{
		UINT8 i,temp;
		temp = data_I2C;
		for(i = 0;i < 8;i++)
		{
				SCL_I2C = 0;
				delay();
				if(temp&0x80)
				{
						SDA_I2C = 1;
				}
				else
				{
						SDA_I2C = 0;
				}
				temp = temp << 1;
				delay();
				delay();
				delay();
				//delay();
				SCL_I2C = 1;
				delay();
		}
		SCL_I2C = 0;
		delay();
		SDA_I2C = 1;
		delay();
}

UINT8 readbyte_I2C(void)
{
		UINT8 i,k;
		SCL_I2C = 0;
		delay();
		SDA_I2C = 1;
		delay();
		for(i = 0;i < 8;i++)
		{
				SCL_I2C = 1;
				delay();
				k = (k << 1)| SDA_I2C;
				SCL_I2C = 0;
				delay();
		}
		delay();
		return k;
}


//========================================================================================================
//void Init_I2C1(void)
//{
//	#if 0
//    /* Set I2C clock rate */
////    I2CLK = I2C_CLOCK; 

////    /* Enable I2C */
////    set_I2CEN;     
//	#endif
////	  P13_Quasi_Mode;                         //set SCL (P13) is Quasi mode
////    P14_Quasi_Mode;                         //set SDA (P14) is Quasi mode
////    I2CPX = 0;
//		P03_OpenDrain_Mode;
//		P04_OpenDrain_Mode;
//    SCL_I2C = 1;                                //set SDA and SCL pins high
//		delay();
//    SDA_I2C = 1;
//		delay();
//    
////    set_P0SR_6;                             //set SCL (P06) is  Schmitt triggered input select.
////    
////    set_EI2C;                               //enable I2C interrupt by setting IE1 bit 0
////    set_EA;

////    I2ADDR = EEPROM_SLA;                    //define own slave address
////    set_I2CEN;                              //enable I2C circuit
////    set_AA;
//}


//void writebyte_I2C1_one(UINT8 data_I2C)
//{
//		start_I2C();
//		writebyte_I2C(EEPROM_SLA|EEPROM_WR);
//		respons_I2C();
//		writebyte_I2C(data_I2C);
//		respons_I2C();
//		stop_I2C();
//}

//void writebyte_I2C1_many(UINT8 number,UINT8 *data_I2C)
//{
//		UINT8 i=0;
//		start_I2C();
//		writebyte_I2C(EEPROM_SLA|EEPROM_WR);
//		respons_I2C();
//		for(i=0;i<number;i++)
//		{
//				writebyte_I2C(*data_I2C++);
//				respons_I2C();
//		}
//		stop_I2C();
//}
//void writebyte_I2C1_add(UINT8 address,UINT8 data_I2C)
//{
//		start_I2C();
//		writebyte_I2C(EEPROM_SLA|EEPROM_WR);
//		respons_I2C();
//		writebyte_I2C(address);
//		respons_I2C();
//		writebyte_I2C(data_I2C);
//		respons_I2C();
//		stop_I2C();
//}

//UINT8 readbyte_I2C1_add(UINT8 address)
//{
//		UINT8 data_I2C;
//		start_I2C();
//		writebyte_I2C(0xe7);
//		respons_I2C();
//		writebyte_I2C(address);
//		respons_I2C();
//		writebyte_I2C(0xe6);
//		respons_I2C();
//		data_I2C = readbyte_I2C();
//		stop_I2C();
//		return	data_I2C;
//}

//========================================================================================================
//void Init_I2C(void)
//{
////    /* Set I2C clock rate */
//		P13_OpenDrain_Mode;
//		P14_OpenDrain_Mode;
//		I2CPX = 0;
//    I2CLK = I2C_CLOCK; 
//    /* Enable I2C */
//    set_I2CEN;                                   
//}
//========================================================================================================

#if 0
//========================================================================================================
void One_Page_Read(UINT8 u8PageNumber,UINT8 u8DAT)
{
    UINT8  u8Count;
    UINT16 u16Address;

    u16Address = (UINT16)u8PageNumber*32;

    /* Step1 */
    set_STA;                                /* Send Start bit to I2C EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send STA' error");
        while (1);
    }

    /* Step2 */
    I2DAT = (EEPROM_SLA | EEPROM_WR);       /* Send (SLA+W) to EEPROM */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */    
    clr_SI;
    while (!SI);
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */              
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send SLA+W' error");
        while(1);
    }

    /* Step3 */
    I2DAT = HIBYTE(u16Address);             /* Send I2C EEPROM's High Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */              
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send I2C High Byte Address' error");
        while (1);
    }

    /* Step4 */
    I2DAT = LOBYTE(u16Address);             /* Send I2C EEPROM's Low Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */             
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send I2C Low Byte Address' error");
        while (1);
    }

    /* Step5 */
    set_STA;                                /* Repeated START */
    clr_SI; 
    while (!SI);
    if (I2STAT != 0x10)                     /* 0x10: A repeated START condition has been transmitted */
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send STA' error");
        while (1);
    }

    /* Step6 */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = (EEPROM_SLA | EEPROM_RD);       /* Send (SLA+R) to EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x40)                     /* 0x40:  SLA+R has been transmitted; ACK has been received */              
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send SLA+R' error");
        while (1);
    }

    /* Step7 */                             /* Verify I2C EEPROM data */
    for (u8Count = 0; u8Count <PAGE_SIZE; u8Count++)
    {
        set_AA;                             /* Set Assert Acknowledge Control Bit */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x50)                 /* 0x50:Data byte has been received; NOT ACK has been returned */              
        {
            LED = ERROR_CODE;
            printf("\nI2C 'No Ack' error");
            while (1);
        }
       
        if (I2DAT != u8DAT)                 /* Send the Data to EEPROM */    
        {
            LED = ERROR_CODE;
            printf("\nI2C 'Read data' error");
            while (1);
        }
        u8DAT = ~u8DAT; 
    }

    /* Step8 */
    clr_AA;                                 /* Send a NACK to disconnect 24xx64 */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x58)                     /* 0x58:Data byte has been received; ACK has been returned */
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Ack' error");
        while (1);
    }
    
    /* Step9 */    
    clr_SI;
    set_STO;
    while (STO);                            /* Check STOP signal */ 
}
//========================================================================================================
void One_Page_Write(UINT8 u8PageNumber,UINT8 u8DAT)
{
    UINT8  u8Count;
    UINT16 u16Address;

    u16Address = (UINT16)u8PageNumber*32;

    /* Step1 */
    set_STA;                                /* Send Start bit to I2C EEPROM */         
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send STA' error");
        while (1);
    }

    /* Step2 */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = EEPROM_SLA | EEPROM_WR;         /* Send (SLA+W) to EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */             
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send SLA+W' error");
        while (1);
    }

    /* Step3 */
    I2DAT = HIBYTE(u16Address);             /* Send EEPROM's High Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send High byte address' error");
        while (1);
    }

    /* Step4 */
    I2DAT = LOBYTE(u16Address);             /* Send EEPROM's Low Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        LED = ERROR_CODE;
        printf("\nI2C 'Send Low byte address' error");
        while (1);
    }

    /* Step5 */
                                            /* Write data to I2C EEPROM */
    for (u8Count = 0; u8Count < PAGE_SIZE; u8Count++)
    {
        I2DAT = u8DAT;                      /* Send data to EEPROM */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x28)                 /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
        {
            LED = ERROR_CODE;
            printf("\nI2C 'Write Data' error");
            while (1);
        }   
        u8DAT = ~u8DAT;        
    }
                                            //After STOP condition, a inner EEPROM timed-write-cycle 
                                            //will occure and EEPROM will not response to outside command
                                            /* 0x18: SLA+W has been transmitted; ACK has been received */
    /* Step6 */
    do
    {
        set_STO;                            /* Set I2C STOP Control Bit */
        clr_SI;
        while (STO);                        /* Check STOP signal */
        
        set_STA;                            /* Check if no ACK is returned by EEPROM, it is under timed-write cycle */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x08)                 /* 0x08:  A START condition has been transmitted*/
        {
            LED = ERROR_CODE;
            printf("\nI2C 'Wait Ready' error");
            while (1);
        }

        clr_STA;                            /* Clear STA and Keep SI value in I2CON */
        I2DAT = (EEPROM_SLA | EEPROM_WR);   /* Send (SLA+W) to EEPROM */
        clr_SI;
        while (!SI);
    }while(I2STAT != 0x18);

    /* Step7 */
    set_STO;                                /* Set STOP Bit to I2C EEPROM */
    clr_SI;
    while (STO);                            /* Check STOP signal */
}
#endif