/****************************************************************************
 * @file     Pin_config.c
 * @version  V1.09
 * @Date     2017/05/09-15:10:34 
 * @brief    NuMicro generated code file
 *
 * Copyright (C) 2013-2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU: MINI54ZDE(QFN33)
Pin Configuration:
Pin 1: AIN5
Pin 3: P3.0
Pin 4: P5.4
Pin 5: P3.1
Pin 6: P3.2
Pin 7: P3.4
Pin 8: P3.5
Pin 9: P3.6
Pin 10: XTAL2
Pin 11: XTAL1
Pin 13: INT1
Pin 14: P2.2
Pin 15: P2.3
Pin 17: P2.5
Pin 18: P2.6
Pin 19: ICE_CLK
Pin 20: ICE_DAT
Pin 21: P0.7
Pin 22: P0.6
Pin 23: P0.5
Pin 24: P0.4
Pin 29: AIN1
Pin 30: P1.2
Pin 31: P1.3
Pin 32: P1.4
********************/

#include "Mini51Series.h";
/*
 * @brief This function provides the configued MFP registers
 * @param None
 * @return None
 */
void SYS_Init(void)
{
    //SYS->P0_MFP = 0x00000000;
    //SYS->P1_MFP = 0x00000021;
    //SYS->P2_MFP = 0x00000000;
    //SYS->P3_MFP = 0x00000000;
    //SYS->P4_MFP = 0x000000C0;
    //SYS->P5_MFP = 0x00000007;

    //If the defines do not exist in your project, please refer to the related sys.h in the sys_h folder appended to the tool package.
    SYS->P0_MFP = 0x00000000;
    SYS->P1_MFP = SYS_MFP_P15_AIN5 | SYS_MFP_P10_AIN1;
    SYS->P2_MFP = 0x00000000;
    SYS->P3_MFP = 0x00000000;
    SYS->P4_MFP = SYS_MFP_P47_ICE_DAT | SYS_MFP_P46_ICE_CLK;
    SYS->P5_MFP = SYS_MFP_P52_INT1 | SYS_MFP_P51_XTAL2 | SYS_MFP_P50_XTAL1;

    return;
}

/*** (C) COPYRIGHT 2013-2017 Nuvoton Technology Corp. ***/