#include "Timers_nINTs.h"


void init_timer5 (void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	TIM5->DIER |= TIM_DIER_UIE;
	TIM5->PSC = 	0; // 
	TIM5->ARR = 0xffffffff;  // setting it to max val as this timer will be usaed for counting how long a button was pressed 
	TIM5->CNT = 0;	
}

// timer 7 to be used for triggering DAC1
void init_timer7 (void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	TIM7->DIER |= TIM_DIER_UIE;
	TIM7->PSC = 	90-1; 
	TIM7->ARR = 1;  
	TIM7->CNT = 0;
	TIM7->CR2 &= ~TIM_CR2_MMS;
	TIM7->CR2 |= TIM_CR2_MMS_1;
	NVIC->ISER[1] |= (1u<<23);
	
	TIM7->CR1 |= TIM_CR1_CEN;
	
}
// timer to be used for uS delays
void init_timer9 (void){
	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
	TIM10->DIER |= TIM_DIER_UIE;
	TIM10->PSC = 	90; 
	TIM10->ARR = 0xffff-1;  
	TIM10->CNT = 0;
	NVIC->ISER[0] |= (1u<<25);
	TIM10->CR1 |= TIM_CR1_CEN;
}



void init_timer8 (void){
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	TIM8->DIER |= TIM_DIER_UIE;
	TIM8->PSC = 	0xffff-1; 
	TIM8->ARR = 0xffff-1;  
	TIM8->CNT = 0;
}

void init_timer4 (void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->DIER |= TIM_DIER_UIE;
	TIM4->PSC = 	9000-1; // clock dividion = 9MHz  //900-1
	TIM4->ARR = 100;  //100-1/ 250/1000000 is the same as 1/40000 // hence the sine wave freq should be 1000/128 = 7.8 HZ
	TIM4->CNT = 0;
//	TIM4->CR2 &= ~TIM_CR2_MMS;
//	TIM4->CR2 |= TIM_CR2_MMS_1;	
	NVIC_SetPriority(TIM4_IRQn, 2);
	NVIC->ISER[0] |= (1u<<30);
	TIM4->CR1 |= TIM_CR1_CEN;
	
}
// timer to be used for mS delays where a value of 10000 to be inserted in the delay function will give a 1 SEC delay 
void init_timer2 (void){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->PSC = 	9000-1;
	TIM2->ARR = 0xffff;  
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM_CR1_CEN;
	
}



void init_timer3 (void){
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->PSC = 	90-1; // clock dividion = 9MHz
	TIM3->ARR = 250;  // 250/1000000 is the same as 1/40000 40 KHz timer for ADC
	TIM3->CNT = 0;
	TIM3->CR2 &= ~TIM_CR2_MMS;
	TIM3->CR2 |= TIM_CR2_MMS_1;
	NVIC->ISER[0] |= (1u<<29);
	TIM3->CR1 |= TIM_CR1_CEN;
}



// function to be used for a mS delay
void delay_mS (int k){
	
	int start;
	start = TIM2->CNT;
	while( ((TIM2->CNT - start)&0xffff) < k);
}
 // function to be used for uS delay
//void delay_uS (int k){
//	
//	int start;
//	start = TIM9->CNT;
//	while( ((TIM9->CNT - start)&0xffff) < k);
//}

