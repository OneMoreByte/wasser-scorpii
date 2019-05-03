#include <MKL25Z4.H>
#include "motor.h"
#include "adcTing.h"
#include "user_defs.h"

//Global variables
int stepcount = 0;
const int Colors[NUM_RANGE_STEPS][3] = {{ 1, 0, 0}, // red
																				{ 1, 0, 1}, // magenta
																				{ 1, 1, 1}, // white
																				{ 1, 1, 0}, // yellow
																				{ 0, 1, 0}, // green
																				{ 0, 0, 1}};// blue


void initAll(Motor *m){
//	Init_ADC();
//	Init_IR_LED();
	m->step_pin = 4; // Use PORTA4
	m->dir_pin = 13;  // Use PORTA5
	m->id = 0;
	m->pos = 0;
	m->dir = 0;
	
	init(m);

	//Init_RGB_LEDs();
}

void stopNfire(){
	//pause the motor
	//Control_RGB_LEDs(1,0,0);
	Delay_us(5000000);
	//TODO
	//send power to a port
	//LED for test case, massive pump for real product
}

int main(void) {
	int degree = stepcount%360;
	Motor base;
	initAll(&base);


	/*
	While loop turns motor in a circle whilst calling isTriggered();
	*/
	while(1){
		//Control_RGB_LEDs(0,0,1);
		//*run motor*
		for (int x = 0; x < 200; x++) {
			step_to_pos(x*16, &base);
		//delay a bit then check with isTriggered()
		//	if(!isTriggered()){
		//		stopNfire();
		//	}
		}
		toggle_dir(&base);
	}
}
