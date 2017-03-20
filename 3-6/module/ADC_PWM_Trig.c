



void INT1_ISR_init(void)
{
/*-------------------------------------------------
	ADC trig initial setting
	Please modify #if value to open diffent type
--------------------------------------------------*/
#if 1
// By PWM falling edge
		PWM0_P12_OUTPUT_ENABLE;				
		Enable_ADC_AIN0;														// Enable AIN0 P1.7 as ADC input
		PWM0_FALLINGEDGE_TRIG_ADC;	
#endif		
#if 0
// By PWM rising edge
		PWM0_P12_OUTPUT_ENABLE;				
		Enable_ADC_AIN0;														// Enable AIN0 P1.7 as ADC input
		PWM0_RISINGEDGE_TRIG_ADC;
#endif		
#if 0
// By PWM central point
		PWM0_P12_OUTPUT_ENABLE;				
		Enable_ADC_AIN0;														// Enable AIN0 P1.7 as ADC input
		PWM_CENTER_TYPE;
		PWM0_CENTRAL_TRIG_ADC;	
#endif	
#if 0
// By PWM end point
		PWM0_P12_OUTPUT_ENABLE;				
		Enable_ADC_AIN0;														// Enable AIN0 P1.7 as ADC input
		PWM_CENTER_TYPE;
		PWM0_END_TRIG_ADC;
#endif	
	
// Setting PWM value
		PWMPH = 0x07;																//Setting PWM value          
    PWMPL = 0xFF;
    PWM0H = 0x02;
    PWM0L = 0xFF;
	  set_LOAD;																		// PWM run
    set_PWMRUN;
// Setting ADC
	  set_EADC;																		// Enable ADC interrupt (if use interrupt)	
}

/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) interrupt 11
{
    clr_ADCF;                               // Clear ADC interrupt flag
		printf ("\n Value = 0x%bx",ADCRH);		// printf display will cause delay in ADC interrupt
		P30 ^= 1;																// Check the P3.0 toggle at falling edge of PWM
}