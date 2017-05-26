

/*******I2C Address  0x54*****
 ************AD = 0  0X54*****
 ************AD = 1  0X56*****/

//I2C Address  0x54(0x54+0)  is  write to NTP-8230
//I2C Address  0x55(0x54+1)  is  read from NTP-8230
/****Single Byte Write Mode Sequence****/
//@a	start + SlaveAddress + w + A + AIF + SubAddress + A + Data + A + stop
//@b	start + SlaveAddress + w + A + AIF + SubAddress#1 + A + Data#1 + A + AIF + SubAddress#2 + A + Data#2 + A +..... stop
//@c	start + SlaveAddress + w + A + AIF + SubAddress#1 + A + Data#1 + A + ..... Data#n + A + stop

/****Quad Byte Write Mode Sequence*****/
//@a	start + SlaveAddress + w + A + AIF + SubAddress + A + Data(Byte#4) + A + Data(Byte#3) + A +Data(Byte#2) + A +Data(Byte#1) + A + stop

//0x7e  PLL:0x02

//Addr 0x0D: 3D Delay Amount
//Addr 0x0E: 3D Effect Control Configuration
//Addr 0x0F : Equalizer (EQ) Configuration
//Addr 0x15: CH1&CH2 Prescaler Value Configuration
//Addr 0x16: CH3 Prescaler Value Configuration
//Addr 0x17~0x18: Post Biquad Filter (PBQ) Configuration0 for Ch 1 and Ch2, respectively
//Addr 0x26 : Soft Mute Control 0
