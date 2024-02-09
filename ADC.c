#include "ADC.h"
#include "PLL_Config.c"
#include "Timers_nINTs.h"
 
uint16_t samples[3];


void ADCone(void)
{

	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;	//GPIOA clock enable
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;	//GPIOC clock enable
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		//ADC clock enable

	GPIOA->MODER&=~(3u<<(2*0));
	GPIOA->MODER&=~(3u<<(2*3));
	GPIOC->MODER&=~(3u<<(2*0));	
	GPIOA->MODER|=(3u<<(2*0));	//ADC input pin0 is PORT A analogue mode
	GPIOA->MODER|=(3u<<(2*3));	//ADC input pin2 is PORT A analogue mode
	GPIOC->MODER|=(3u<<(2*0));	//ADC input pin0 PORTC is analogue mode

	ADC1->SQR1 |= (2<<20);						//set number of conversions per sequence to 3
	
	// CLEARING SEQ CHANNELS
	ADC1->SQR3&=~(0u<<0); // first conversion in sequence  
	ADC1->SQR3&=~(3u<<5);  // second conversion in sequence 
	ADC1->SQR3&=~(10u<<10);  // third conversion in sequence 
	
	ADC1->SQR3 |= (0<<0);	//set channel 0 pot
	ADC1->SQR3 |= (3<<5); // set channel 3 MIC
	ADC1->SQR3 |= (10<<10);  // set channel 10 LDR
	
	ADC1->CR1 |= ADC_CR1_SCAN; // SETTING THE ADC ON SCAN MODE
	
	ADC1->CR2 |= ADC_CR2_DMA;  
	
	ADC1->CR2|=ADC_CR2_DDS|ADC_CR2_CONT;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; // enabling DMA clock
	
	DMA2_Stream0->CR &=~DMA_SxCR_EN; // disabling DMA as configuring DMA while its on is not possible
	
	while(DMA2_Stream0->CR == DMA_SxCR_EN){} // a loop to stop at untill DMA is off
		
	DMA2_Stream0->CR|=DMA_SxCR_CIRC|DMA_SxCR_MSIZE_0|DMA_SxCR_PSIZE_0|DMA_SxCR_MINC; // setting DMA to be on CIRCULAR mode/ memmory and periph size as 16 bit / memmory increment
		// direction on default is form periph to memmory therefore :
	DMA2_Stream0->PAR = (uint32_t)(&(ADC1->DR));  // taking data from the ADC connected to pin
	DMA2_Stream0->M0AR = (uint32_t)(&samples); // handing data from adc to the arraya inside memmory
		
	DMA2_Stream0->NDTR = sizeof(samples); // total number of data items to be transferred 
		
	DMA2_Stream0->CR		|=DMA_SxCR_EN; // enable DMA
	ADC1->CR2|=1;
	
	DMA2_Stream0->CR |= (1<<0);
	ADC1->CR2 |= (ADC_CR2_EXTSEL_3);  // EXTERNAL EVENT TRIGGER TIMER3 TRGO
	ADC1->CR2 |= ADC_CR2_EXTEN_0;   // EXTERNAL EVENT TRIGGER DETECTION ON RISING EDGE
		
	ADC1->CR2|=ADC_CR2_SWSTART;				//start ADC conversion
		
	}
	

