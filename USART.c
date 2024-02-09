#include "USART.h"
#include "DAC.h"
FILE __stdout; // used for output – printf()
FILE __stdin; // used for input – getchar()

char morse;
float a;


void init_USART(void)
{
	unsigned char i1,i2;
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;		//usart port clock enable
	
	USART_PORT->MODER&=~(										//clear pin function bits
		(3u<<(2*USART_TX_pin))
		|(3u<<(2*USART_RX_pin))
			);
	USART_PORT->MODER|=(										//reset pin function bits (alternate function)
		(2u<<(2*USART_TX_pin))
		|(2u<<(2*USART_RX_pin))
			);
	
	i1=USART_TX_pin/8;											// used to select AFR[reg] for TX_pin ... pins 0-7 AFR[0] pins 8-15 AFR[1]   / 8/8 = 1
	i2=USART_RX_pin>>3;											// same as above for RX_pin (uses shift to divide) / 9/3^2 = 1
	// ALTERNATE FUNCTION SELECT BITS
	USART_PORT->AFR[i1]&=~(0x0f<<(4*(USART_TX_pin-(i1*8))));    //clear pin function
	USART_PORT->AFR[i1]|=(0x07<<(4*(USART_TX_pin-(i1*8))));			// set usart as alternate function for TX_pin
	USART_PORT->AFR[i2]&=~(0x0f<<(4*(USART_RX_pin-(i2*8))));		// clear pin function
	USART_PORT->AFR[i2]|=(0x07<<(4*(USART_RX_pin-(i2*8))));			//set usart as alternate function for RX_pin
	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;			//usart clock enable
	USART_MODULE->CR1 &= ~(USART_CR1_M); // SETTING USART DATA AS 8 BITS
	USART_MODULE->CR2 &= ~(USART_CR2_STOP); // SETTING USART STOP BITS AS 1 STOP BITS
	
	USART_MODULE->CR1|=(										//USART CONFIG
			USART_CR1_TE												//transmit enable
			|USART_CR1_RE												//receive enable
			|USART_CR1_UE												//usart main enable bit
			|USART_CR1_RXNEIE										//RXNEIE READING DATA INTERRUPT ENABLE
			//|USART_CR1_TCIE transfer complete interrupt enable bit 
				);
				
				
				
				// these lines should set the parity for the uart however i couldnt manage to have them function on 8 bit data they only work on 9 bit 
				
//				USART_MODULE->CR1 |= USART_CR1_PCE;  // parity  control enable bit
//				USART_MODULE->CR1 &= ~(USART_CR1_PS); // parity selection
//				USART_MODULE->CR1 |= USART_CR1_PEIE;  // parity interrupt enable bit
			

//setting and calculating the baud rate and enabling the interrupt for the uart
			int temp = 0;
			temp = (((SystemCoreClock/4)<<5) / (16 * 230400)); //twice BRR needed for LSB accuracy 0.5%
			USART_MODULE->BRR = (temp>>1) + (temp&0x1);
			NVIC_EnableIRQ(USART3_IRQn);																						
}


// this function sends data to the uart
void send_usart(unsigned char d)
{
	while(!(USART_MODULE->SR & USART_SR_TC));
	USART_MODULE->DR=d;												//write byte to usart data register
}

// this function points to the printf() command to be used as a command to write on uart
int fputc(int ch, FILE *f){
send_usart ((uint8_t) ch);
return ch;
}


// this function reads data on the UART DATA REGISTER AFTER IT HAS BEEN SENT SUCCSESSFULLY
char RXNE (void){
while(!(USART_MODULE->SR & USART_SR_RXNE )){}

	return USART_MODULE->DR;
}


// this is the usart interrupt service routine it is entered whenever data transfer is complete // it also could  be used as an interrupt service routine for parity interrupts 
void USART3_IRQHandler (void){
	if (USART_MODULE->SR & USART_SR_RXNE)
		USART_MODULE->DR; // To clear the interrupt flag
	//if (USART_MODULE->SR & USART_SR_PE) // parity interrupt flag must come after the data send complection lines and
			//USART_MODULE->DR; // To clear the interrupt flag
	
	 morse = USART_MODULE->DR;
	//send_usart(USART_MODULE->DR);
	a = ((USART_MODULE->DR)-48); // this is to be used when adjusting voltage thorugh putty

	}
