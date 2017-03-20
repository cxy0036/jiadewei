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
//  File Function: N76E885 SPI in Salave mode demo code
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
//  Slave receive 0x90 and return 0x4E
//  Slave receive 0x01 and return 0x55
//  Slave receive 0x02 and return 0x56
//  Slave receive 0x03 and return 0x4F
//  Slave receive 0x04 and return 0x54
//
//  Slave send 0x4F and 0x4E to Master after receiving
//  
//  Output : P1.4 & P2.1 flash when SPI pass.
//           P0.7 flash when SPI error 
//***********************************************************************************************************

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------
//
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
//-------- <<< end of configuration section >>> ------------------------------
*/

#define SYS_CLK_EN              0
#define SYS_SEL                 2
#define SYS_DIV_EN              0                   //0: Fsys=Fosc, 1: Fsys = Fosc/(2*CKDIV)
#define SYS_DIV                 1
bit BIT_TMP;
//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
    while(1)                                    // SPI error and P0.7 flash/
    {
        P07 = 1;
        Timer0_Delay1ms(500);
        P07 = 0;
        Timer0_Delay1ms(500);
    }
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
    
    set_P0S_5;                                  //Schmitt triggered input select.
    
    clr_MSTR;                                   // SPI in Slave mode 
    clr_LSBFE;                                  // MSB first 

    clr_CPOL;                                   // The SPI clock is low in idle mode
    set_CPHA;                                   // The data is sample on the second edge of SPI clock     
       
    set_SPIEN;                                  // Enable SPI function
    clr_SPIF; 
}
//-----------------------------------------------------------------------------------------------------------
void Slave_Receive_Data(void)
{
    SPDR = 0x4E;                                // Receive Master 1st DATA 
    while(!(SPSR & SET_BIT7));          
    clr_SPIF;
    if(SPDR != 0x90)                      
       SPI_Error(); 
                                                
    SPDR = 0x55;                                // Receive Master 2nd DATA 
    while(!(SPSR & SET_BIT7));          
    clr_SPIF;
    if(SPDR != 0x01)
       SPI_Error();
                                                 
    SPDR = 0x56;                                // Receive Master 3rd DATA
    while(!(SPSR & SET_BIT7));                  
    clr_SPIF;
    if(SPDR != 0x02)
        SPI_Error();
    
    SPDR = 0x4F;                                // Receive Master 4th DATA 
    while(!(SPSR & SET_BIT7));                  
    clr_SPIF;
    if(SPDR != 0x03)
        SPI_Error();
                                                
    SPDR = 0x54;                                // Receive Master 5th DATA
    while(!(SPSR & SET_BIT7));                   
    clr_SPIF;
    if(SPDR != 0x04)
        SPI_Error();
}
//-----------------------------------------------------------------------------------------------------------
void Slave_tranmit_Data(void)
{
    SPDR = 0x4F;                                // Send 1st data (0x4F) to Master 
    while(!(SPSR & SET_BIT7));      
    clr_SPIF;
    if(SPDR != 0xFF)
        SPI_Error();
    
    SPDR = 0x4E;                                // Send 2nd data (0x4E) to Master 
    while(!(SPSR & SET_BIT7));      
    clr_SPIF;
    if(SPDR != 0xFF)
        SPI_Error();
}
//-----------------------------------------------------------------------------------------------------------
void main(void)
{   
    /* Note
       MCU power on system clock is HIRC (22.1184MHz), so Fsys = 22.1184MHz
    */
    
    Set_All_GPIO_Quasi_Mode();
    InitialUART0_Timer1_Type1(9600);             /* 9600 Baud Rate*/

    Show_FW_Version_Number_To_PC();
    
    printf ("\n*===================================================================");
    printf ("\n*  Name: N76E885 SPI Slave(Polling) Demo Code.");
    printf ("\n*===================================================================");  
        
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

    printf ("\nSPI Start Receive...\n");    
         
    Slave_Receive_Data();                       // Slave receive data from master
    Slave_tranmit_Data();                       // Slave transmit data to master
    while(1)                                    
    {
        P21 = 1;
        Timer0_Delay1ms(500);
        P21 = 0;
        Timer0_Delay1ms(500);
    }
}
//-----------------------------------------------------------------------------------------------------------
