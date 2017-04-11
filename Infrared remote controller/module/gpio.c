#include	"gpio.h"


//void	gpio_init(void)
//{
////	Set_All_GPIO_Quasi_Mode;
//	P14_PushPull_Mode;
//	
//}

void gpio_init(void)
{
//	P00_PushPull_Mode;
//	P01_PushPull_Mode;
//	P03_PushPull_Mode;
//	P04_PushPull_Mode;
	P04_Input_Mode;
	P05_Input_Mode;
	P06_Input_Mode;
	P07_Input_Mode;
//	P10_PushPull_Mode;
//	P11_PushPull_Mode;
//	P12_PushPull_Mode;
//	P13_PushPull_Mode;
	P14_PushPull_Mode;
	P17_Input_Mode;
//	P30_PushPull_Mode;
	
	P01 = 0;
	P00 = 0;
	P10 = 0;
	P11 = 0;
//	while(1);
	P12 = 0;
	P13 = 0;
}