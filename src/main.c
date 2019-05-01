#include <MKL25Z4.H>
#include "motor.h"
#include "adcTing.c"

//Global variables
int stepcount = 0;


	
void initAll(){
	Init_ADC();
	Init_IR_LED();
}

void stopNfire(){
	//pause the motor
	
	//TODO
	//send power to a port
	//LED for test case, massive pump for real product
}

int main(void) {
	initAll();
	int degree = stepcount%360;
	Motor base;
	
	base.step_pin = 4; // Use PORTA4
	base.dir_pin = 5;  // Use PORTA5
	base.id = 0;
	base.pos = 0;
	
	init(&base);
	
	/*
	While loop turns motor in a circle whilst calling isTriggered();
	*/
	while(1){
		//*run motor*
		for (int x = 0; x < 200; x++) {
			step_to_pos(x*16, &base);
		//delay a bit then check with isTriggered()
			if(!isTriggered()){
				stopNfire();
			}
			base.pos = x * 16;
		}
		toggle_dir(&base);
	}
}
