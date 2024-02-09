#include "EXTI.h"
#include "DAC.h"
#include "ADC.h"
#include "USART.h"
#include "Timers_nINTs.h"
#include "LEDs.h"


// external interrupts and switches


// these are settings for the blue button as external interrupt ive set the setting, However i didnt know where to use it

//void init_ext (void){
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
//				GPIOC->MODER &= ~(1u<<(2*13));
//				GPIOC->PUPDR &= ~(3u<<(2*13));
//				GPIOC->PUPDR  |= (2u<<(2*13));
//	NVIC_EnableIRQ(EXTI15_10_IRQn);
//				GPIOC->ODR |= (1<<13);
//	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//		SYSCFG->EXTICR[3] &= ~(2u<<(4*1));
//		SYSCFG->EXTICR[3]  |= (2u<<(4*1));
//			EXTI->IMR |= (1<<13);
//			EXTI->RTSR |= (1<<13);
//			EXTI->FTSR &= ~(1u<<13);
//	NVIC_SetPriority(EXTI15_10_IRQn, 1);
//}


/*
void init_extC (void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
				GPIOG->MODER &= ~(1u<<(2*2));
				GPIOG->PUPDR &= ~(3u<<(2*2));
				GPIOG->PUPDR  |= (2u<<(2*2));
	NVIC_EnableIRQ(EXTI2_IRQn);
				GPIOG->ODR |= (1<<2);
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
		SYSCFG->EXTICR[0] &= ~(6u<<(2*4));
		SYSCFG->EXTICR[0]  |= (6u<<(2*4));
			EXTI->IMR |= (1<<2);
			EXTI->RTSR |= (1<<2);
			EXTI->FTSR &= ~(1u<<2);
	NVIC_SetPriority(EXTI2_IRQn, 2);
}

*/



/////************************needs adjusments *************************************************8/
void inputUser (void) {
	GPIOC->MODER &= ~(1<<(2*13)); // setting pin C13 as input
}
	
// buttons A and B in port G are pull down resistor buttons hence 
void inputpinA (void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
				GPIOG->MODER &= ~(1u<<(2*0)); // clearing pin mode bits to input mode for PG0
				GPIOG->PUPDR &= ~(3u<<(2*0)); // clearing pull up/down bits
				GPIOG->PUPDR  |= (2u<<(2*0)); // setting pin PG0 as pull down
}
// now button B
void inputpinB (void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
				GPIOG->MODER &= ~(1u<<(2*1)); // clearing pin mode bits to input mode for PG0
				GPIOG->PUPDR &= ~(3u<<(2*1)); // clearing pull up/down bits
				GPIOG->PUPDR  |= (2u<<(2*1)); // setting pin PG0 as pull down

}

// as for buttons C and D they are  pull down open drain, so they should be set as following:
void inputpinC (void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
				GPIOG->MODER &= ~(1u<<(2*2)); // clearing pin mode bits to input mode for PG2
				//GPIOG->PUPDR &= ~(3u<<(2*2)); // clearing pull up/down bits
				GPIOG->PUPDR  |= (2u<<(2*2)); // setting pin PG0 as pull down
				//GPIOG->OTYPER &= ~(1u<<(2*2));
				GPIOG->OTYPER |= (1u<<(2)); // setting as open drain
}
// same for button D
void inputpinD (void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
				GPIOG->MODER &= ~(1u<<(2*3)); // clearing pin mode bits to input mode for PG2
				//GPIOG->PUPDR &= ~(3u<<(2*3)); // clearing pull up/down bits
				GPIOG->PUPDR  |= (2u<<(2*3)); // setting pin PG0 as pull down
				//GPIO->OTYPER &= ~(1u<<(2*3));
				GPIOG->OTYPER |= (1u<<(2*3)); //  setting as open drain

}