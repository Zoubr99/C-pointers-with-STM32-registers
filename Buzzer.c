#include "Buzzer.h"
#include "Timers_nINTs.h"

void Buzzer_init (void){ // initiliazing the buzzer
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER &= ~(1<<(2*13));
	GPIOB->MODER |= (1<<(2*13));
	
}
void Sbuzzer (void){ // sound for buzzer as a dot
			GPIOB->BSRR = 1<<13;
			delay_mS(1000);
			GPIOB->BSRR = 1<<29;
	
}
void Sbuzzer2 (void){  // sound for buzzer as a dash
			GPIOB->BSRR = 1<<13;
			delay_mS(3000);
			GPIOB->BSRR = 1<<29;
	
}

// the function to make the buzzzer sound as a dot or dash was already defined inside the LEDs file