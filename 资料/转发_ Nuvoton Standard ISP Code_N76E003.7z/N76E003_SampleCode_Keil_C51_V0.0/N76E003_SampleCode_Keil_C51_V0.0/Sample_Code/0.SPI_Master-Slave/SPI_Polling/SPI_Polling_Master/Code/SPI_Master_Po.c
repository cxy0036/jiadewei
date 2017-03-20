/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2015 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2015
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E885 SPI in Master mode demo code
//***********************************************************************************************************

#include <stdio.h>
#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"

//***********************************************************************************************************
//  Application: SPI Function 
//  Master send 0x90 and recevie 0x4E
//  Master send 0x01 and recevie 0x55
//  Master send 0x02 and recevie 0x56
//  Master send 0x03 and recevie 0x4F
//  Master send 0x04 and recevie 0x54
//
//  Master recevie 0x4E and 0x4F form slave after transmitting
//***********************************************************************************************************

//------------------------- <<< Use Configuration Wizard in Context Menu >>> --------------------------------
////<e0> System Clock Source Configuration
// <o1> System Clock Source Selection
//      <0=> 2~25MHz    XTAL
//      <1=> 32.768KHz  XTAL
//      <2=> 22.1184MHz Internal
//      <3=> 10KHz      Internal
//      <4=> OSC-In     External
//</e>
//
//<e2> Clock Divider Configuration
//     <o3.0..7>  System Clock Source Devider <1-255>
//                     <i> Fsys = (System Clock Source) / (2 * Devider)
//</e>
//
// <o4> SPI Clock Divider Selection
//      <0=> Fsys/4
//      <1=> Fsys/8
//      <2=> Fsys/16
//      <3=> Fsys/32
//
//-------------------------------- <<< end of configuration section >>> -------------------------------------

#define SYS_CLK_EN              0
#define SYS_SEL                 2
#define SYS_DIV_EN              0               //0: Fsys=Fosc, 1: Fsys = Fosc/(2*CKDIV)
#define SYS_DIV                 1
#define SPI_DIV                 1
bit BIT_TMP;
//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
    printf ("\nSPI error.\n");
    while(1)                                    // SPI error and P0.7 flash/
    {
        P07 = 1;
        Timer0_Delay1ms(500);
        P07 = 0;
        Timer0_Delay1ms(500);
    }
}
//-----------------------------------------------------------------------------------------------------------
void SPI_Clock_Select(void)
{
    #if   SPI_DIV == 0
            clr_SPR0;                           // SPI clock = Fosc/4
            clr_SPR1;
    #elif SPI_DIV == 1
            set_SPR0;                           // SPI clock = Fosc/8
            clr_SPR1;
    #elif SPI_DIV == 2
            clr_SPR0;                           // SPI clock = Fosc/16
            set_SPR1; 
    #elif SPI_DIV == 3
            set_SPR0;                           // SPI clock = Fosc/32
            set_SPR1;
    #endif
}
//-----------------------------------------------------------------------------------------------------------
void SPI_Initial(void)
{      
    clr_P0M1_4;                                 //P04 (SS) Quasi mode
    clr_P0M2_4;
    
    clr_P0M1_5;                                 //P05 (SPCLK) Quasi mode
    clr_P0M2_5;
    
    clr_P2M1_1;                                 //P21 (MOSI) Quasi mode
    clr_P2M2_1;
    
    clr_P2M1_2;                                 //P22 (MISO) Quasi mode
    clr_P2M2_2;
    
    set_DISMODF;                                // SS General purpose I/O ( No Mode Fault ) 
    clr_SSOE;
   
    clr_LSBFE;                                  // MSB first         

    clr_CPOL;                                   // The SPI clock is low in idle mode
    set_CPHA;                                   // The data is sample on the second edge of SPI clock 
    
    set_MSTR;                                   // SPI in Master mode 
    SPI_Clock_Select();                         // Select SPI clock 
    set_SPIEN;                                  // Enable SPI function 
    clr_SPIF;
}
//-----------------------------------------------------------------------------------------------------------
void Start_Sending_SPI(UINT8 *pu8MID,UINT8 *pu8DID)
{
    SS = 0;
      
    SPDR = 0x90;
    Delay10us(1);                               // Send 0x90 to Slave 
    while(!(SPSR & SET_BIT7));
    clr_SPIF;
    if(SPDR != 0x4E)
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);
   
    SPDR = 0x01;                                // Send 0x01 to Slave 
    Delay10us(1); 
    while(!(SPSR & SET_BIT7));
    clr_SPIF;
    if(SPDR != 0x55)
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);
    
    SPDR = 0x02;                                // Send 0x02 to Slave 
    Delay10us(1);
    while(!(SPSR & SET_BIT7));    
    clr_SPIF;
    if(SPDR != 0x56)
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);

    SPDR = 0x03;                                // Send 0x03 to Slave 
    Delay10us(1);
    while(!(SPSR & SET_BIT7));
    clr_SPIF;
    if(SPDR != 0x4F)
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);

    SPDR = 0x04;                                // Send 0x04 to Slave 
    Delay10us(1);
    while(!(SPSR & SET_BIT7));
    clr_SPIF;
    if(SPDR != 0x54)
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);

    SPDR = 0xFF;                   
    Delay10us(1);
    while(!(SPSR & SET_BIT7));
    clr_SPIF;
    *pu8MID = SPDR;                             // Receive Slave 1st DATA from Slave 
    printf ("\nSlave Return %c!\n",SPDR);
        
    SPDR = 0xFF;                   
    Delay10us(1);
    while(!(SPSR & SET_BIT7));  
    clr_SPIF;           
    *pu8DID = SPDR;                             // Receive Slave 2nd DATA from Slave 
    printf ("\nSlave Return %c!\n",SPDR);
        
    SS = 1;    
}
//-----------------------------------------------------------------------------------------------------------
void main(void)
{      
    UINT8 u8MID,u8DID;

    /* Note
       MCU power on system clock is HIRC (22.1184MHz), so Fsys = 22.1184MHz
    */
    
    Set_All_GPIO_Quasi_Mode();
    InitialUART0_Timer1_Type1(9600);             /* 9600 Baud Rate*/

    Show_FW_Version_Number_To_PC();
    
    printf ("\n*===================================================================");
    printf ("\n*  Name: N76E885 SPI Master(Polling) Demo Code.");
    printf ("\n*===================================================================\n");
        
    /* Change system closk source */
    #if SYS_CLK_EN == 1
        #if   SYS_SEL == 0
            System_Clock_Select(E_HXTEN);   //Fosc = 2~25MHz XTAL
        #elif SYS_SEL == 1
            System_Clock_Select(E_LXTEN);   //Fosc = 32.768KHz XTAL
        #elif SYS_SEL == 2
            System_Clock_Select(E_HIRCEN);  //Fosc = 22.1184MHz Internal RC
        #elif SYS_SEL == 3
            System_Clock_Select(E_LIRCEN);  //Fosc = 10KHz Internal RC
        #elif SYS_SEL == 4
            System_Clock_Select(E_OSCEN);   //Fosc = OSC-In External OSC
        #endif
    #endif
    
    #if SYS_DIV_EN == 1
        CKDIV = SYS_DIV;                        //Fsys = Fosc / (2* CLKDIV) = Fcpu
    #endif

		SPI_Initial();

		Start_Sending_SPI(&u8MID,&u8DID);
        
    if((u8MID != 0x4F)&&(u8DID != 0x4E))
        SPI_Error();

    printf ("\nSPI Test OK!\n");
    while(1);                                    // SPI transmission finish and P0.6 flash
}
//-----------------------------------------------------------------------------------------------------------
