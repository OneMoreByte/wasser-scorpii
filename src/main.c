#include <MKL25Z4.H>
#include "motor.h"
#include "adcTing.h"

//Global variables
int stepcount = 0;


	
void initAll(Motor *m){
	Init_ADC();
	Init_IR_LED();
	m->step_pin = 4; // Use PORTA4
	m->dir_pin = 5;  // Use PORTA5
	m->id = 0;
	m->pos = 0;
	
	init(m);
}

void stopNfire(){
	//pause the motor
	
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
	//while(1){
		//*run motor*
		for (int x = 0; x < 200; x++) {
			step_to_pos(x, &base);
		//delay a bit then check with isTriggered()
			if(!isTriggered()){
				stopNfire();
			}
		}
		toggle_dir(&base);
	//}
}
