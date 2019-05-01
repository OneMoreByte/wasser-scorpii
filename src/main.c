#include <MKL25Z4.H>
#include "motor.h"


//Global variables
int stepcount = 0;


	
void initAll(){
	Init_ADC();
	Init_IR_LED();
}

int main(void) {
	initAll();
	int degree = stepcount%360;
	Motor base;
	
	/*
	While loop turns motor in a circle whilst calling isTriggered();
	*/
	while(1){
		//*run motor*
		//delay a bit then check with isTriggered()
		if(!isTriggered()){
			stopNfire();
		}
	}

}

void stopNfire(){
	//pause the motor
	
	//TODO
	//send power to a port
	//LED for test case, massive pump for real product
}


