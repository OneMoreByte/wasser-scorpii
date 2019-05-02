#ifndef ADCTING_H
#define ADCTING_H


void Init_ADC(void);

//switch on and off IR_LED
void Control_IR_LED(unsigned int led_on);
void Init_IR_LED(void);

unsigned Measure_IR(void);
_Bool Display_Range(int b);
void Delay_us();
_Bool isTriggered(void);

#endif
