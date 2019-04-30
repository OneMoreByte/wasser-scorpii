#include <MKL25Z4.H>

#define MASK(X) (1UL << (X))

#define RED_LED_POS (18)
#define GREEN_LED_POS (19)
#define BLUE_LED_POS (1)

void Delay(unsigned int tem_delay) {
	volatile int t;
	
	while(tem_delay--) {
		for(t=4800; t>0; t--);
	}
}
	
void red(void) {
	PTB->PDOR = ~MASK(RED_LED_POS);
	PTD->PDOR = 0xFFFFFFFF;
	Delay(100);
	PTB->PDOR = 0xFFFFFFFF;	
	PTD->PDOR = 0xFFFFFFFF;
	Delay(100);	
	PTB->PDOR = ~MASK(RED_LED_POS);
	PTD->PDOR = 0xFFFFFFFF;
	Delay(100);		
}

int main(void) {
	unsigned int counter = 0;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);
	
	PTB->PDDR |= MASK(RED_LED_POS);
	
	PTB->PSOR = MASK(RED_LED_POS);
	
	while(1) {
		red();
	}
	
}
