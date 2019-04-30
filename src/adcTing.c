#include <MKL25Z4.H>
#include "user_defs.h"
#include "LEDs.h"

//This program is to light RGB LED according to range of the IR LED.

//the Threshold parameters are used to sweep through valid IR Levels of the IR_LED
//IR_LED
int Threshold[NUM_RANGE_STEPS] = {0, 20200, 25270, 25400, 28100, 73500};

const int Colors[NUM_RANGE_STEPS][3] = {{ 1, 0, 0}, // red
																				{ 1, 0, 1}, // magenta
																				{ 1, 1, 1}, // white
																				{ 1, 1, 0}, // yellow
																				{ 0, 1, 0}, // green
																				{ 0, 0, 1}};// blue
																	 

void Init_ADC(void) {
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT); 
	ADC0->CFG1 = 0x9C; //ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADIV(0) | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0); // 16 bit precision //CHANGED?
	ADC0->SC2 = 0;
}

//switch on and off IR_LED
void Control_IR_LED(unsigned int led_on) {
	if (led_on) {
			PTB->PCOR =  MASK(IR_LED_POS);
	} else {
			PTB->PSOR = MASK(IR_LED_POS); 
	}
}

//initilize IR_LED by using the PCR register; identify the pin number
//on the PORTB to connect it to PORTB 
void Init_IR_LED(void) {
	PORTB->PCR[IR_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[IR_LED_POS] |= PORT_PCR_MUX(1);          
	PTB->PDDR |= MASK(IR_LED_POS);
	
	// start off with IR LED turned off
	Control_IR_LED(0);
}

unsigned Measure_IR(void) {
	volatile unsigned res=0;
	
	ADC0->SC1[0] = IR_PHOTOTRANSISTOR_CHANNEL; // start conversion on channel 0
	
	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	res = ADC0->R[0];
	// complement result since voltage falls with increasing IR level
	// but we want result to rise with increasing IR level
	return 0xffff-res;
}


_Bool Display_Range(int b) {
	unsigned i;
	
	for (i=0; i<NUM_RANGE_STEPS-1; i++) {
		if (b < Threshold[i]&&i>=1)
			return 1;
	}
	return 0;
}

void Delay_us(volatile unsigned int time_del) {
	// This is a very imprecise and fragile implementation!
	time_del = 9*time_del + time_del/2; 
	while (time_del--) {
		;
	}
}
/*----------------------------------------------------------------------------
  MAIN function
//MODIFIED FROM IR LED CODE
 *----------------------------------------------------------------------------*/
_Bool isTriggered(void) {
	unsigned on_brightness=0, measured_voltage=0;
	static int avg_voltage;
	int sum;
	unsigned n;
	
	Init_ADC();
	Init_RGB_LEDs();
	Init_IR_LED();
	Control_RGB_LEDs(0, 0, 0);
	
	while (1) {
		sum = 0;
		for (n=0; n<NUM_SAMPLES_TO_AVG; n++) {
			// Measure the voltage level to see if tripped
			Delay_us(T_DELAY);
			measured_voltage = Measure_IR();

			// add the measured voltage
			sum += measured_voltage;
		}
		avg_voltage = sum/NUM_SAMPLES_TO_AVG;
		
		// light RGB LED according to range
		//Modify to this line to send a signal to the main.c process
		return Display_Range(avg_voltage);
	}
}
