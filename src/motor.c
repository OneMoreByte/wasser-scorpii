#include "MKL25Z4.h"
#include "motor.h"
/**

Motor notes:
  Driver is TMC2208
  Datasheet -> https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC220x_TMC222x_Datasheet.pdf
  Connected in UART MODE
  Driver is muxed (?)
  RAW_STEPS * STEP_RESOLUTION per 360 deg (0.1125 deg per step)


**/

const int RAW_STEPS = 200;
const int STEP_RESOLUTION = 16 * RAW_STEPS; // Driver is in 1/16 mode

/**
    Over UART:
    Set microstep
    Set mode

**/

void delay(unsigned int tem_delay) {
	volatile int t;

	while(tem_delay--) {
		for(t=100; t>0; t--);
	}
}

void init(Motor *m) {
	// Init control pins
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[m->step_pin] = 1U << m->step_pin; /* make step_pin GPIO */
  PORTC->PCR[m->dir_pin] = 1U << m->dir_pin;  /* make dir_pin GPIO */
	PTC->PDDR |= 1U << m->step_pin;

  //Init UART
  //SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
}


/**
  Reads the # of successful commands over UART
  This function is used for confirming command receipt
 **/
int read_trans_count(Motor *m) {
	// TODO (Nah, no UART)
	return 0;
}

/**
  Steps Motor to a given position
**/
void step_to_pos(int pos, Motor *m) {
	int steps = pos - m->pos;

	if (pos > STEP_RESOLUTION)
		pos = pos - STEP_RESOLUTION;
	if (pos < 0)
		pos = pos + STEP_RESOLUTION;

	steps = steps * 2; // duplicates step count for on/off toggle
	for (; steps > 0; steps--) {
		GPIOC_PTOR |= 1U << m->step_pin;
		delay(1);
	}

	m->pos = pos; // Update position
}
