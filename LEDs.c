#include "LEDs.h"
#include "Timers_nINTs.h"
#include "Buzzer.h"

extern uint16_t samples[3];

void init_led3(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER &= ~(1<<(2*0));
	GPIOB->MODER |= (1<<(2*0));
}

void TL3 (void){
	GPIOB->ODR^=(1u<<0);	
}






void init_led1(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER &= ~(1<<(2*7));
	GPIOB->MODER |= (1<<(2*7));
}

void TL1 (void){
	GPIOB->ODR^=(1u<<7);	
}

void dot (void){
	GPIOB->BSRR = 1<<13;
	GPIOB->BSRR =(1u<<7);	
	delay_mS(1000);
	GPIOB->BSRR =(1u<<23);
	GPIOB->BSRR = 1<<29;
	delay_mS(1000);
}

void dash (void){
	GPIOB->BSRR = 1<<13;
	GPIOB->BSRR =(1u<<7);	
	delay_mS(3000);
	GPIOB->BSRR =(1u<<23);
	GPIOB->BSRR = 1<<29;
	delay_mS(3000);
}
	
///***************************TOGGLING LEDS FOR CHECKING*******************************/
	
void init_led2(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER &= ~(1u<<(2*14));
	GPIOB->MODER |= (1<<(2*14));
}

void TL2 (void){
	GPIOB->ODR^=(1u<<14);
}
/**************************************7 Seg leds*******************************************/
void seg_init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	GPIOE->MODER &= ~(1u<<(2*15)); // OE for the digitsso if active low it is 1
	GPIOE->MODER |= (1<<(2*15));
	//GPIOE->PUPDR |= (2<<15);
	
	GPIOE->MODER &= ~(1u<<(2*10)); // setting PE10 latch as output
	GPIOE->MODER |= (1<<(2*10));
	//GPIOE->OTYPER &= ~(1u<<(2*10));
  //GPIOE->OTYPER |= (1u<<(2*10));
	
	GPIOE->MODER &= ~(1u<<(2*11));  // setting PE11 latch as output
	GPIOE->MODER |= (1<<(2*11));
	
					GPIOE->MODER &= ~(1u<<(2*2));
					GPIOE->MODER |= (1<<(2*2));
					//GPIOE->OTYPER &= ~(1u<<(2*2));
					//GPIOE->OTYPER |= (1u<<(2*2));
					
					GPIOE->MODER &= ~(1u<<(2*3));
					GPIOE->MODER |= (1<<(2*3));
					//GPIOE->OTYPER &= ~(1u<<(2*3));
					//GPIOE->OTYPER |= (1u<<(2*3));
					
					GPIOE->MODER &= ~(1u<<(2*4));
					GPIOE->MODER |= (1<<(2*4));
					//GPIOE->OTYPER &= ~(1u<<(2*4));
					//GPIOE->OTYPER |= (1u<<(2*4));
					
					GPIOE->MODER &= ~(1u<<(2*5));
					GPIOE->MODER |= (1<<(2*5));
					//GPIOE->OTYPER &= ~(1u<<(2*5));
					//GPIOE->OTYPER |= (1u<<(2*5));
					
					GPIOE->MODER &= ~(1u<<(2*6));
					GPIOE->MODER |= (1<<(2*6));
					//GPIOE->OTYPER &= ~(1u<<(2*6));
					//GPIOE->OTYPER |= (1u<<(2*6));
					
					GPIOE->MODER &= ~(1u<<(2*7));
					GPIOE->MODER |= (1<<(2*7));
					//GPIOE->OTYPER &= ~(1u<<(2*8));
					//GPIOE->OTYPER |= (1u<<(2*8));
					
					GPIOE->MODER &= ~(1u<<(2*8));
					GPIOE->MODER |= (1<<(2*8));
					//GPIOE->OTYPER &= ~(1u<<(2*8));
					//GPIOE->OTYPER |= (1u<<(2*8));
					
					GPIOE->MODER &= ~(1u<<(2*9));
					GPIOE->MODER |= (1<<(2*9));
					//GPIOE->OTYPER &= ~(1u<<(2*9));
					//GPIOE->OTYPER |= (1u<<(2*9));
					
					GPIOE->BSRR = 1<<10;
					GPIOE->BSRR = 1<<11;
}








/*****************************************************numbers*******************************************************************/
int one (void){
	
	GPIOE->BSRR = 1<<7;	
	GPIOE->BSRR = 1<<8;
	return 0;
}
int two (void){
	GPIOE->BSRR = 1<<3;	
	GPIOE->BSRR = 1<<4;	
	GPIOE->BSRR = 1<<5;
	GPIOE->BSRR = 1<<6;	
	GPIOE->BSRR = 1<<7;
	return 0;
}

int three (void){
	
	GPIOE->BSRR = 1<<4;	
	GPIOE->BSRR = 1<<5;
	GPIOE->BSRR = 1<<6;	
	GPIOE->BSRR = 1<<7;
	GPIOE->BSRR = 1<<8; 
	return 0;
}

int four (void){
	
	GPIOE->BSRR = 1<<2;	
	GPIOE->BSRR = 1<<4;
	GPIOE->BSRR = 1<<7;	
	GPIOE->BSRR = 1<<8;
	return 0;
}

int five (void){
	GPIOE->BSRR = 1<<2;
	GPIOE->BSRR = 1<<4;
	GPIOE->BSRR = 1<<5;
	GPIOE->BSRR = 1<<6;
	GPIOE->BSRR = 1<<8;
	return 0;
	
}

int six (void){
	GPIOE->BSRR = 1<<2;
	GPIOE->BSRR = 1<<3;
	GPIOE->BSRR = 1<<4;
	GPIOE->BSRR = 1<<5;
	GPIOE->BSRR = 1<<6;
	GPIOE->BSRR = 1<<8;
	return 0;
	
}


int seven (void){
	GPIOE->BSRR = 1<<6;
	GPIOE->BSRR = 1<<7;
	GPIOE->BSRR = 1<<8;
	return 0;
}


int eight (void){
	GPIOE->BSRR = 1<<2;
	GPIOE->BSRR = 1<<3;
	GPIOE->BSRR = 1<<4;
	GPIOE->BSRR = 1<<5;
	GPIOE->BSRR = 1<<6;
	GPIOE->BSRR = 1<<7;
	GPIOE->BSRR = 1<<8;
	return 0;
	
}

int nine (void){
	GPIOE->BSRR = 1<<2;
	GPIOE->BSRR = 1<<4;
	GPIOE->BSRR = 1<<5;
	GPIOE->BSRR = 1<<6;
	GPIOE->BSRR = 1<<7;
	GPIOE->BSRR = 1<<8;
	return 0;
}

int zero (void){
	GPIOE->BSRR = 1<<2;
	GPIOE->BSRR = 1<<5;
	GPIOE->BSRR = 1<<6;
	GPIOE->BSRR = 1<<7;
	GPIOE->BSRR = 1<<8;
	return 0;
}

void offseg (void){
	GPIOE->BSRR = 1<<18; // this function sets the bits to zero 
	GPIOE->BSRR = 1<<19;  //so they do not overwrite the next operation after setting the latch to zero and setting the needed bits to 1 
	GPIOE->BSRR = 1<<20;
	GPIOE->BSRR = 1<<21;
	GPIOE->BSRR = 1<<22;
	GPIOE->BSRR = 1<<23;
	GPIOE->BSRR = 1<<24;
	GPIOE->BSRR = 1<<25;
}


void left_seg (int n){
for(;;)	{
					GPIOE->BSRR = 1<<26;
					GPIOE->BSRR = 1<<27;// clearing latch 11,12,13,14 so it cant be mosified while working on latch 10
					GPIOE->BSRR = 1<<28;
					GPIOE->BSRR = 1<<29;
					GPIOE->BSRR = 1<<30;
delay_mS(1);
GPIOE->BSRR = 1<<10; // setting latch 10 to do the operations needed
int display;
display = n;
delay_mS(1);
					GPIOE->BSRR = 1<<26;
					GPIOE->BSRR = 1<<27;
					GPIOE->BSRR = 1<<28;
					GPIOE->BSRR = 1<<29;
					GPIOE->BSRR = 1<<30;
	break;
}
}
void right_seg (int n){
for(;;){
					GPIOE->BSRR = 1<<26;// clearing latch 10,12,13,14 so it cant be mosified while working on latch 10
					GPIOE->BSRR = 1<<27;
					GPIOE->BSRR = 1<<28;
					GPIOE->BSRR = 1<<29;
					GPIOE->BSRR = 1<<30;
	delay_mS(1);
	GPIOE->BSRR = 1<<11;  // setting latch 11 to do the operations needed
	int display2;
	display2 = n;
	delay_mS(1);
					GPIOE->BSRR = 1<<26;
					GPIOE->BSRR = 1<<27;
					GPIOE->BSRR = 1<<28;
					GPIOE->BSRR = 1<<29;
					GPIOE->BSRR = 1<<30;
	break;
}
}

int L_segment_display (int n){  // this is the function to call for the left sided segment
			left_seg(n); // this function adjusts setting to the right segment of the digit display so the user can input any value
			delay_mS(1);
			offseg();    // this has the setting which contains setting latches and clearing other latches
			delay_mS(1); //10 mS delay
return 0;	
}


int R_segment_display (int n){ // this is the function to call for the right sided segment
			right_seg(n); // this function adjusts setting to the right segment of the digit display so the user can input any value
			delay_mS(1);
			offseg();  // this has the setting which contains setting latches and clearing other latches
			delay_mS(1); //10 mS delay
return 0;	
}


/*********************************************END OF 7 SEG DISPLAY TASK**************************************************************************/



/****************************************RGB LEDs*************************************************/
void RGB_init (void){
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; // ENABLING CLOCK
					GPIOE->MODER &= ~(1u<<(2*0));  // ENABLING THE OE LATCH FOR THE RGB LEDS
					GPIOE->MODER |= (1<<(2*0));
					//GPIOE->OTYPER &= ~(1u<<(2*0));
					//GPIOE->OTYPER |= (1u<<(2*0));

					GPIOE->MODER &= ~(1u<<(2*12)); // ENABLING  THE RED LATCH
					GPIOE->MODER |= (1<<(2*12));
		
					GPIOE->MODER &= ~(1u<<(2*13));  // ENABLING THE GREEN LATCH 
					GPIOE->MODER |= (1<<(2*13));
		
					GPIOE->MODER &= ~(1u<<(2*14)); // EANBLING THE BLUE LATCH
					GPIOE->MODER |= (1<<(2*14));
		
/*************************** SETTING PINS FOR THE RGB BANK*********************************************/		
					GPIOE->MODER &= ~(1u<<(2*2));
					GPIOE->MODER |= (1<<(2*2));
					//GPIOE->OTYPER &= ~(1u<<(2*2));
					//GPIOE->OTYPER |= (1u<<(2*2));
					
					GPIOE->MODER &= ~(1u<<(2*3));
					GPIOE->MODER |= (1<<(2*3));
					//GPIOE->OTYPER &= ~(1u<<(2*3));
					//GPIOE->OTYPER |= (1u<<(2*3));
					
					GPIOE->MODER &= ~(1u<<(2*4));
					GPIOE->MODER |= (1<<(2*4));
					//GPIOE->OTYPER &= ~(1u<<(2*4));
					//GPIOE->OTYPER |= (1u<<(2*4));
					
					GPIOE->MODER &= ~(1u<<(2*5));
					GPIOE->MODER |= (1<<(2*5));
					//GPIOE->OTYPER &= ~(1u<<(2*5));
					//GPIOE->OTYPER |= (1u<<(2*5));
					
					GPIOE->MODER &= ~(1u<<(2*6));
					GPIOE->MODER |= (1<<(2*6));
					//GPIOE->OTYPER &= ~(1u<<(2*6));
					//GPIOE->OTYPER |= (1u<<(2*6));
					
					GPIOE->MODER &= ~(1u<<(2*7));
					GPIOE->MODER |= (1<<(2*7));
					//GPIOE->OTYPER &= ~(1u<<(2*7));
					//GPIOE->OTYPER |= (1u<<(2*7));
					
					GPIOE->MODER &= ~(1u<<(2*8));
					GPIOE->MODER |= (1<<(2*8));
					///GPIOE->OTYPER &= ~(1u<<(2*8));
					//GPIOE->OTYPER |= (1u<<(2*8));
					
					GPIOE->MODER &= ~(1u<<(2*9));
					GPIOE->MODER |= (1<<(2*9));
					//GPIOE->OTYPER &= ~(1u<<(2*9));
					//GPIOE->OTYPER |= (1u<<(2*9));
					
					GPIOE->BSRR = 1<<12;
					GPIOE->BSRR = 1<<13;
					GPIOE->BSRR = 1<<14;



}






/********************************************************************************************/

// samples0 are the data collected from the potentiometer
// so if the POT function was called first all latches connected to port E will go low
// except for the latch connected to pin 12 which controls the red Led's hence if POT value goes max RED leds will all light
// and vise versa
// in steps of 512 so if the POT value goes below 512 only 1 led will blink and so on untill its max
// and as soon as the MCU finishes the task it immeadiatlly breaks out the loop and function heading straight to the next task 
	long long samples0 (void){
		
					GPIOE->BSRR = 1<<26; 
					GPIOE->BSRR = 1<<27;
					GPIOE->BSRR = 1<<28;
					GPIOE->BSRR = 1<<29;
					GPIOE->BSRR = 1<<30;
					delay_mS(1);
					GPIOE->BSRR = 1<<12;  
			while(0 < samples[0] &&  samples[0]< 512){		
			(GPIOE->BSRR = 1<<2);
				break;				
			}
			
			while(512 < samples[1] &&  samples[1]< 1024){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
				break;
			}
			
			while(1024 < samples[1] &&  samples[1]< 1536){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
				break;
			}
			
			while(1536 < samples[1] &&  samples[1]< 2048){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
				break;
			}
			
			while(2048 < samples[1] &&  samples[1]< 2560){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
				break;
			}
			
			while(2560 < samples[1] &&  samples[1]< 3072){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
				break;
			}
			
			while(3072 < samples[1] &&  samples[1]< 3584){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
			(GPIOE->BSRR = 1<<8);
				break;
			}
			
			while(3584 < samples[1] &&  samples[1]< 4096){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
			(GPIOE->BSRR = 1<<8);
			(GPIOE->BSRR = 1<<9);
				break;
			}
			
		return 0;
		
	}

	/*****************************************************************************************/
// same concept implies here 
// samples1 are the data collected from the MIC
// so if the MIC function was called first all latches connected to port E will go low
// except for the latch connected to pin 13 which controls the GREEN Led's hence if MIC values goes high GREEN leds will indicate the value obtained by lighting
// green leds and vise versa if no sound has been catched trough MIC
// the LEDs will ligh in steps of 512 so if the POT value goes below 512 only 1 led will and when over 512 2 will blink and so on untill its max
// as soon as the MCU finishes the task it immeadiatlly breaks out the loop and function heading straight to the next task 
		long long samples1 (void){
			
					GPIOE->BSRR = 1<<26;
					GPIOE->BSRR = 1<<27;
					GPIOE->BSRR = 1<<28;
					GPIOE->BSRR = 1<<29;
					GPIOE->BSRR = 1<<30;
					delay_mS(1);
					GPIOE->BSRR = 1<<13;
	
			while(0 < samples[0] &&  samples[0]< 512){		
			(GPIOE->BSRR = 1<<2);
				break;
			}
			
			while(512 < samples[0] &&  samples[0]< 1024){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
				break;
			}
			
			while(1024 < samples[0] &&  samples[0]< 1536){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
				break;
			}
			
			while(1536 < samples[0] &&  samples[0]< 2048){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
				break;
			}
			
			while(2048 < samples[0] &&  samples[0]< 2560){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
				break;
			}
			
			while(2560 < samples[0] &&  samples[0]< 3072){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
				break;
			}
			
			while(3072 < samples[0] &&  samples[0]< 3584){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
			(GPIOE->BSRR = 1<<8);
				break;
			}
			
			while(3584 < samples[0] &&  samples[0]< 4096){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
			(GPIOE->BSRR = 1<<8);
			(GPIOE->BSRR = 1<<9);
				break;
			}
			
	return 0;
		
	}

/******************************************************************************************************************/
	
// and lastly 
// samples2 are the data collected from the LDR
// THEREFORE if the LDR function was called first all latches connected to port E will go low
// except for the latch connected to pin 14 which controls the BLUE Led's hence if LDR values GO high BLUE leds will indicate the values obtained by lighting
// BLUE leds and vise versa if LIGHT WAS TARGETED ONTO THE LDR
// the LEDs will light in steps of 512 so if the LDR value goes below 512 only 1 led will and when over 512 2 will blink and so on untill its max
// as soon as the MCU finishes the task it immeadiatlly breaks out the loop and function heading straight to the next task 
	
			long long samples2 (void){
				
					GPIOE->BSRR = 1<<26;
					GPIOE->BSRR = 1<<27;
					GPIOE->BSRR = 1<<28;
					GPIOE->BSRR = 1<<29;
					GPIOE->BSRR = 1<<30;
					delay_mS(1);
					GPIOE->BSRR = 1<<14;
				
	
			while(0 < samples[2] &&  samples[2]< 512){		
			(GPIOE->BSRR = 1<<2);
				break;
			}
			
			while(512 < samples[2] &&  samples[2]< 1024){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
				break;
			}
			
			while(1024 < samples[2] &&  samples[2]< 1536){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
				break;
			}
			
			while(1536 < samples[2] &&  samples[2]< 2048){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
				break;
			}
			
			while(2048 < samples[2] &&  samples[2]< 2560){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
				break;
			}
			
			while(2560 < samples[2] &&  samples[2]< 3072){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
				break;
			}
			
			while(3072 < samples[2] &&  samples[2]< 3584){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
			(GPIOE->BSRR = 1<<8);
				break;
			}
			
			while(3584 < samples[2] &&  samples[2]< 4096){
			(GPIOE->BSRR = 1<<2);
			(GPIOE->BSRR = 1<<3);
			(GPIOE->BSRR = 1<<4);
			(GPIOE->BSRR = 1<<5);
			(GPIOE->BSRR = 1<<6);
			(GPIOE->BSRR = 1<<7);
			(GPIOE->BSRR = 1<<8);
			(GPIOE->BSRR = 1<<9);
				break;
			}
			

		return 0;
		
	}
			
	
	
void LDR_RGB (void){
	long long LDRRGB;
	offseg(); // sets all pins low before it goes into the routine
	delay_mS(5);
	LDRRGB = samples2(); // goes through LDR function routine 
	delay_mS(5);
	offseg(); // sets all pins low after setting the aimed leds on
	}

	
void MIC_RGB (void){
	long long MICRGB;
	offseg();  // sets all pins low before it goes into the routine
	delay_mS(5);
	MICRGB = samples0(); // goes through MIC function routine 
	delay_mS(5);
	offseg();  // sets all pins low after setting the aimed leds on
	}

void POT_RGB (void){
	long long POTRGB;
	offseg();  // sets all pins low before it goes into the routine
	delay_mS(5);
	POTRGB = samples1();  // goes through POT function routine 
	delay_mS(5);
	offseg();   // sets all pins low after setting the aimed leds on
}


	
/****************************************************END OF RGB BANK TASK**********************************************************************/
	


/****************************************************TRAFFIC LIGHTS LEDs*************************************************************/

void pin2_int (void){
	/*initialising PC2*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; /*enabling clock for port C */
	GPIOC->MODER &= ~(1u<<(2*2));  /* clearing the pin */
	GPIOC->MODER |= (1<<(2*2));		/* setting the pin as 1 [output] */
	GPIOC->OTYPER &= ~(1u<<2);   /* setting the pin as a push-pull */
	//GPIOC->OTYPER |= (1u<<2); this line should set it as an open drain ie: connecting it to ground


	
}
void pin3_int (void){
		/*initialising PC3*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &= ~(1u<<(2*3));
	GPIOC->MODER |= (1<<(2*3));
	GPIOC->OTYPER &= ~(1u<<3);
	//GPIOC->OTYPER |= (1u<<3); this line should set it as an open drain ie: connecting it to ground


	
}
void pin6_int (void){
		/*initialising PC6*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &= ~(1u<<(2*6));
	GPIOC->MODER |= (1<<(2*6));
	GPIOC->OTYPER &= ~(1u<<6);
	//GPIOC->OTYPER |= (1u<<6); this line should set it as an open drain ie: connecting it to ground


	
}

void pin7_int (void){
		/*initialising P76*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &= ~(1u<<(2*7));
	GPIOC->MODER |= (1<<(2*7));
	//GPIOC->OTYPER &= ~(1u<<7); /*this line should set it as an push-pull ie: connecting it to VDD*/
	GPIOC->OTYPER |= (1u<<7); /*this line should set it as an open drain ie: connecting it to ground*/


	
}
void pin8_int (void){
		/*initialising PC8*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &= ~(1u<<(2*8));
	GPIOC->MODER |= (1<<(2*8));
	//GPIOC->OTYPER &= ~(1u<<8); /*this line should set it as an push-pull ie: connecting it to VDD*/
	GPIOC->OTYPER |= (1u<<8); /*this line should set it as an open drain ie: connecting it to ground*/


	
}
void pin9_int (void){
		/*initialising PC9*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &= ~(1u<<(2*9));
	GPIOC->MODER |= (1<<(2*9));
	//GPIOC->OTYPER &= ~(1u<<9); /*this line should set it as an push-pull ie: connecting it to VDD*/
	GPIOC->OTYPER |= (1u<<9); /*this line should set it as an open drain ie: connecting it to ground*/


	
}
void pin10_int (void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
	GPIOF->MODER &= ~(1u<<(2*10));
	GPIOF->MODER |= (1u<<(2*10));
	GPIOF->OTYPER |= (1u<<10);
}
	
void RED (void){
		/*toggling the led 2 (Red)*/
	GPIOC->BSRR = (1<<2);

	
	
}
void offRED (void){
		/*toggling the led 2 (Red)*/
	GPIOC->BSRR = (1<<18);

	
	
}
void YELLOW (void){
		/*toggling the led 3 (Yellow)*/
	GPIOC->BSRR = (1<<3);

	
}
void offYELLOW (void){
		/*toggling the led 3 (Yellow)*/
	GPIOC->BSRR = (1<<19);

	
}

void GREEN (void){
		/*toggling the led6 (Green)*/
	GPIOC->BSRR = (1<<6);
}
void offGREEN (void){
		/*toggling the led6 (Green)*/
	GPIOC->BSRR = (1<<22);
}


void p7led (void){
		//toggling the led7 (red)
	GPIOC->BSRR = (1<<23);
}

void offp7led (void){
		//toggling the led7 (red)
	GPIOC->BSRR = (1<<7);
}


void p8led (void){
		//toggling the led8 (yellow)//
	GPIOC->BSRR = (1<<24);
}
void offp8led (void){
		//toggling the led9 (Green)
	GPIOC->BSRR = (1<<8);
}

void p9led (void){
		//toggling the led9 (Green)
	GPIOC->BSRR = (1<<25);
}
void offp9led (void){
		
	GPIOC->BSRR = (1<<9);
}

void white (void){
	GPIOF->BSRR = (1<<26);
}
void offwhite (void){
	GPIOF->BSRR = (1<<10);
}
	
void offALL (void){
	offp9led();
	offRED();
	offYELLOW();
	offGREEN();
	offp8led();
	offp7led();
	offwhite();
}

void onREDS (void){
	RED();
	p7led();
}

void transmission_start (void){
offALL();   // traffic lights sequence
RED();
delay_mS(30000);
offRED();
YELLOW();
delay_mS(20000);
offYELLOW();
GREEN();
delay_mS(5000);
offGREEN();
	
}

void transmission_end (void){
offALL();
p9led();
delay_mS(2000);
offp9led();
p8led();
delay_mS(2000);
offp8led();
p7led();	
delay_mS(2000);
offALL();			
	
}




	
