#include "DAC.h"
#include "ADC.h"
#include "LEDs.h"
#include "Timers_nINTs.h"
#include "math.h"
#define pi 3.14
#define ch7 0x07
#define   SINE_RES          128
extern uint16_t samples[3];
float  dacr[1];
int PWM[2] = {0,4095};

////*******************************////
const uint16_t function[SINE_RES] = { 2048, 2145, 2242, 2339, 2435, 2530, 2624, 2717, 2808, 2897,
                                      2984, 3069, 3151, 3230, 3307, 3381, 3451, 3518, 3581, 3640,
                                      3696, 3748, 3795, 3838, 3877, 3911, 3941, 3966, 3986, 4002,
                                      4013, 4019, 4020, 4016, 4008, 3995, 3977, 3954, 3926, 3894,
                                      3858, 3817, 3772, 3722, 3669, 3611, 3550, 3485, 3416, 3344,
                                      3269, 3191, 3110, 3027, 2941, 2853, 2763, 2671, 2578, 2483,
                                      2387, 2291, 2194, 2096, 1999, 1901, 1804, 1708, 1612, 1517,
                                      1424, 1332, 1242, 1154, 1068, 985, 904, 826, 751, 679,
                                      610, 545, 484, 426, 373, 323, 278, 237, 201, 169,
                                      141, 118, 100, 87, 79, 75, 76, 82, 93, 109,
                                      129, 154, 184, 218, 257, 300, 347, 399, 455, 514,
                                      577, 644, 714, 788, 865, 944, 1026, 1111, 1198, 1287,
                                      1378, 1471, 1565, 1660, 1756, 1853, 1950, 2047 };
// array to be used to generate sine wave
////*******************************////
//const uint16_t function2[SINE_RES] = { 682, 751, 747, 779, 811, 843, 874, 905, 936, 965,
//															2984, 3069, 3151, 3230, 3307, 3381, 3451, 3518, 3581, 3640,
//															3696, 3748, 3795, 3838, 3877, 3911, 3941, 3966, 3986, 4002,
//															4013, 4019, 4020, 4016, 4008, 3995, 3977, 3954, 3926, 3894,
//															3858, 3817, 3772, 3722, 3669, 3611, 3550, 3485, 3416, 3344,
//															3269, 3191, 3110, 3027, 2941, 2853, 2763, 2671, 2578, 2483,
//															2387, 2291, 2194, 2096, 1999, 1901, 1804, 1708, 1612, 1517,
//															1424, 1332, 1242, 1154, 1068, 985, 904, 826, 751, 679,
//															610, 545, 484, 426, 373, 323, 278, 237, 201, 169,
//															141, 118, 100, 87, 79, 75, 76, 82, 93, 109,
//															129, 154, 184, 218, 257, 300, 347, 399, 455, 514,
//															577, 644, 714, 788, 865, 944, 1026, 1111, 1198, 1287,
//															1378, 1471, 1565, 1660, 1756, 1853, 1950, 2047 };														
																			
																			
																			
																			
																			
																			
																			
																																					
void init_DAC22(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
	DAC_port->MODER|=(3u<<(2*5));			//DAC output pin set as anaglogue
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable 
	DAC->CR |= (2<<19); // trigger selection TIM7 to start conversion ****************
	DAC->CR |= DAC_CR_TEN2;
	DAC->CR|=DAC_CR_EN2;									//DAC 1 enabled
}

int output_dac2(unsigned short l)
{
	DAC->DHR12R2=l;			//write data byte to DAC 1 output register
	return l;
}



void init_DAC2(uint16_t s[])
{
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN; // enabling port A	clock 
RCC->APB1ENR|=RCC_APB1ENR_DACEN; // enabling dac clock
RCC->APB1ENR|=RCC_APB1ENR_TIM6EN; // enabling timer 6 clock
RCC->AHB1ENR|=RCC_AHB1ENR_DMA1EN; // enabling DMA clock
GPIOA->MODER|=GPIO_MODER_MODE5_0|GPIO_MODER_MODE5_1; // clearring and ssetting pin 5
DMA1_Stream6->CR&=~DMA_SxCR_EN; // disabling DMA so it can be configured
while(((DMA1_Stream6->CR)&DMA_SxCR_EN)==1); // waiting for DMA to be disabled
DMA1_Stream6->CR|=(ch7<<25); // setting the DMA channel according to the refrence manual the DAC2 DMA is on DMA1 stream 6 channel 7 
DMA1_Stream6->CR|=DMA_SxCR_MSIZE_0|DMA_SxCR_PSIZE_0|DMA_SxCR_MINC|DMA_SxCR_CIRC|DMA_SxCR_DIR_0; // setting memmory and periph size ot 16 bit // memmory increament mode // circular mode/direction from memmory to periphral
DMA1_Stream6->NDTR=128; // NO of data to be transferred
DMA1_Stream6->PAR=(uint32_t)&(DAC->DHR12R2); // data transferred to the DHR of DAC2
DMA1_Stream6->M0AR=(uint32_t)s; // data collected from array function in memmory

DMA1_Stream6->FCR |= DMA_SxFCR_DMDIS;
DMA1_Stream6->FCR |= (DMA_SxFCR_FTH_0 | DMA_SxFCR_FTH_1); // setting FIFO(first input first out) threshold to full

TIM6->PSC=350; // setting timer 6 to give 1KHz sine wave
TIM6->ARR=1;
TIM6->CR2|=TIM_CR2_MMS_1; // setting tim 6 as an external trigger

DAC->CR|=DAC_CR_MAMP1_3|DAC_CR_MAMP1_1|DAC_CR_MAMP1_0|DAC_CR_MAMP1_2; // setting wave amplitude to max
DAC->CR&=~(DAC_CR_TSEL1_0|DAC_CR_TSEL1_1|DAC_CR_TSEL1_2); // setting TRGO timer 6 as the external trigger
DAC->CR|=DAC_CR_DMAEN2; //enabling DMA for DAC2
DAC->CR|=DAC_CR_TEN2; // enabling DAC2 trigger 
DAC->CR|=DAC_CR_EN2; // enabling DAC2
DMA1_Stream6->CR|=DMA_SxCR_EN; // enabling DMA1
TIM6->CR1|=TIM_CR1_CEN; // enabling tim 6

}


/************************************************************/


void init_DAC1(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
	DAC_port->MODER|=(3u<<(2*4));			//DAC output pin set as anaglogue
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable 
	DAC->CR |= (2<<3); // trigger selection TIM7 to start conversion ****************
	DAC->CR |= (1<<2);
	DAC->SWTRIGR |= 1<<0;
	DAC->CR|=(1<<0);										//DAC 1 enabled
}
char output_dac1(unsigned short k)
{
	DAC->DHR12R1=k;			
	return k;
}

void usartV (unsigned short u){
	float f = 3.3; 
 	float  t = 4096.0;
	float h = (t/f);  //max V 4096/ 3.3 = 1241.21212
	float l = u*h;
	dacr[0] = l;  // the ratio (1241.21212) times what the user inserts ex: input = 1.65, 1241.21212*1.65 = 2048 which is half 4096 and half 3.3V
	DAC->DHR12R1=(dacr[0]); // store the results obtained into the DHR 
}

void pwm1 (void){
			DAC->DHR12R1=PWM[1];
//			delay_uS(50);
			DAC->DHR12R1= PWM[0];
//			delay_uS(50);
}


/*************************************************************************/
