#ifndef __DELAY_H__
#define __DELAY_H__

void Delay10us(UINT16 u16CNT);
void Timer0_Delay1ms (UINT32 u32CNT);
void Timer1_Delay10us(UINT32 u32CNT);
void Timer1_Delay1ms (UINT32 u32CNT);
void Timer2_Delay1ms (UINT32 u32CNT);
void Timer3_Delay1ms (UINT32 u32CNT);
void WakeUp_Timer_Delay25ms(UINT32 u32CNT);

#endif