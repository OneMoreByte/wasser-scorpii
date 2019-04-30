#include <stdlib.h>

/**

Motor notes:
  Driver is TMC2208
  Datasheet -> https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC220x_TMC222x_Datasheet.pdf
  Connected in UART MODE
  Driver is muxed (?)

  

**/

const int STEP_RESOLUTION = 256;

struct motor {
	int id;
	float pos;
	void *uart_port;
};
/**
  Over UART:
    Set microstep
    Set mode
	
**/
void init(struct motor *m) {
	// TODO
}


/**
  Reads the # of successful commands over UART
  This function is used for confirming command ACK
 **/
int read_trans_count(struct motor *m) {
	// TODO
	return 0;
}

/**
  Steps motor to a given degree
**/
void step_to_deg(float theta, struct motor *m) {
	int steps = 0;
	int dir = 0;
	
	if (m->pos > theta) {
		dir = 0;
		steps = ((m->pos) - theta) * STEP_RESOLUTION;
	} else if (m->pos < theta) {
		dir = 1;
		steps = (theta - (m->pos)) * STEP_RESOLUTION;
	}
	
	
	
	for (; steps > 0; steps--) {
		
		delay(100);
	
	}
}
