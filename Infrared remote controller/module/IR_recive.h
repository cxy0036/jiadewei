#ifndef __IR_RECIVE_H__
#define __IR_RECIVE_H__

extern UINT8	key_press;
extern bit Recive_flag;

void INT1_ISR_init(void);
void INT1_ISR(void);
void Data_Check(void);
void dat_clr(void);
void one_press(void);
void long_press(void);
void BootCode_OR_RepeatCode(void);

#endif