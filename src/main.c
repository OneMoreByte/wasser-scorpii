#include <MKL25Z4.H>
#include "motor.h"


//Global variables
int stepcount = 0;

int main(void) {
	int degree = stepcount%360;
	Motor base;
	
	/*
	While loop turns motor in a circle whilst calling isTriggered();
	*/
	while(1){
		//*run motor*
		if(isTriggered()){
			stopNfire();
		}
	}

}

void stopNfire(){
	//send power to a port
	//LED for test case, massive pump for real product
}


