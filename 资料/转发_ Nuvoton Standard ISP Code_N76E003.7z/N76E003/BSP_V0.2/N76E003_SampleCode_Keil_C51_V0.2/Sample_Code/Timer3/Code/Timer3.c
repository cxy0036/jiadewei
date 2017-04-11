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
//  File Function: N76E885 Timer3 demo code
//***********************************************************************************************************

#include <stdio.h>
#include "N76E885.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
//
//<e0> System Clock Source Configuration
// <o1> System Clock Source Selection
//      <0=> 2~25MHz    XTAL
//      <1=> 32.768KHz  XTAL
//      <2=> 22.1184MHz Internal
//      <3=> 10KHz      Internal
//      <4=> OSC-In     External
//</e>
//
//<e2> Clock Divider Configuration
//     <o3.0..7>  System Clock Source Devider  <1-255>
//                     <i> Fsys = (System Clock Source) / (2 * Devider)
//</e>
//
// <o4> Pre-Scalar Divider
//      <0=> 1/1     
//      <1=> 1/2     
//      <2=> 1/3     
//      <3=> 1/8     
//      <4=> 1/16    
//      <5=> 1/32    
//      <6=> 1/64    
//      <7=> 1/128   
//
//-------- <<< end of configuration section >>> ------------------------------
*/

#define SYS_CLK_EN      0
#define SYS_SEL         2
#define SYS_DIV_EN      0                       //0: Fsys=Fosc, 1: Fsys = Fosc/(2*CKDIV)
#define SYS_DIV         1
#define PRE_SCALAR      0

#define RELOAD_VALUE_H  (65536-50)/256
#define RELOAD_VALUE_L  (65536-50)%256
bit BIT_TMP;
/************************************************************************************************************
*    TIMER 2 interrupt subroutine
************************************************************************************************************/
void Timer3_ISR (void) interrupt 16 
{
    clr_TF3;
    P02 = ~P02;                                 //P0.2 toggle when TF3 interrupt
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    /* Note
       MCU power on system clock is HIRC (22.1184MHz), so Fsys = 22.1184MHz
    */
    
    Set_All_GPIO_Quasi_Mode();

    
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

    #if   PRE_SCALAR == 0
        T3CON = 0;
    #elif PRE_SCALAR == 1
        T3CON = 1;
    #elif PRE_SCALAR == 2
        T3CON = 2;
    #elif PRE_SCALAR == 3
        T3CON = 3;
    #elif PRE_SCALAR == 4
        T3CON = 4;
    #elif PRE_SCALAR == 5
        T3CON = 5;
    #elif PRE_SCALAR == 6
        T3CON = 6;
    #elif PRE_SCALAR == 7
        T3CON = 7;
    #endif
    
    RH3 = RELOAD_VALUE_H;                       //initial counter values 
    RL3 = RELOAD_VALUE_L;    
    
    set_ET3;                                    //enable Timer3 interrupt
    set_EA;                                     //enable interrupts
    set_TR3;                                    //Timer3 run

    while(1);
}

