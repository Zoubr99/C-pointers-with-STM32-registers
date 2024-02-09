#include "LCD.h"
#include "Timers_nINTs.h"

void init_port(void){
 //SystemCoreClockUpdate();
 RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // enabling clock for port D
	// now modifieng pins connected to the LCD
	// first set them 
	GPIOD->MODER &= ~((3u<<(2*RS))|(3u<<(2*RW))|(3u<<(2*E)) | (0xffff<<(2*0)));
	// now modify the pins each for its purpose
	// 1- RS as output  / 2- RW as output / 3- E as output / pins 0-7 as output
	GPIOD->MODER |= ((1u<<(2*RS))|(1u<<(2*RW))|(1u<<(2*E)) | (0x5555<<(2*0)));
}


//*************************************************** THE CODE BELOW IS TO HAVE THE LCD WORKING ON 4 BIT**********************************//


void init_LCD4BIT (void){
	// this must be done by sending commands to the LCD chip hence a command sending function needed first 
	// command function initilized under this function
	init_port();
	//CRS(); CRW(); CE();
	// now send initiliazation commands to set the lcd
	commands4BIT(0x28);
	commands4BIT(0x06);
	commands4BIT(0x01);
	commands4BIT(0x0c);
}

void bussy(void)		//blocking delay for LCD, argument is approximate number of micro-seconds to delay
{		//CRS = 0 : send commands 	//SRS = 1 : send data	//SR/W = 1 : when reading 	//CR/W = 0 : when writing 	//When data is supplied	//SE = 1 	//Wait 	//CE = 0 
	int status = 1;
	int dummy;
	GPIOD_IN(); // PORT D AS INPUT TO READ FROM PINS
	SRW(); // R/W IS SET 
	CRS(); // CLEAR RS 
	
		while(status )
		{
		SE(); // set enable bit
		delay_mS(10); // delay 
		status = (GPIOD->IDR & 1<<7); // read pin 7
		CE(); // clear enable bit 
		delay_mS(10); // delay
			
		SE(); // set enable bit again 
		delay_mS(10); // delay
		dummy = (GPIOD->IDR); // read the pin again 
		CE(); // clear enable bit
		delay_mS(10); // delay
			
			
		}
	CRW(); // clear read and write bits 
	GPIOD_OUT(); // set the port as output
	
}


// this function writes strings on lcd
void write (char *str){ // enter the string intended
	while(*str >0){ // keep writting chars of the string untill the whole string has  been written
		
		
		LCDprint4BIT(*str++); // sends the chars of the string to be displayed on the LCD
	}
	
}

// function to be used to print on lcd  using the 4 bits twice by shifting by 4
void LCDprint4BIT (char data){
	bussy();
	set_data4BIT(data,RS);
	set_data4BIT(data<<4,RS);
	//delay_mS(100);

}

// function to be used to send commands to the  lcd on 4 BIT mode using the 4 bits twice by shifting by 4
void commands4BIT (unsigned char cmd){
	bussy();
	//delay_mS(200);
	set_data4BIT(cmd, 0);
	set_data4BIT(cmd<<4,0);
	
}


void set_data4BIT (char data, unsigned char control){
	
	GPIOD->BSRR = (0xff<<(0+16));
	GPIOD->BSRR = (data<<(0)); // might need to be shifted 4 bits
	
	if (control & RS)
	{SRS();}
	else
	{CRS();}
	
		SE();
		delay_mS(0);
		CE();
	
}


//*************************************************** THE CODE BELOW IS TO HAVE THE LCD WORKING ON 8 BIT only WITH BUSSY FLAG **********************************//

//void init_LCD (void){
//	// this must be done by sending commands to the LCD chip hence a command sending function needed first 
//	// command function initilized under this function
//	init_port();

//	
//	CRS(); CRW(); CE();
//	// now send commands to set the lcd
//	commands(0x38);
//	commands(0x06);
//	commands(0x01);
//	commands(0x0F);
//}

//void bussy(void)		//blocking delay for LCD, argument is approximate number of micro-seconds to delay
//{		//CRS = 0 : send commands 	//SRS = 1 : send data	//SR/W = 1 : when reading 	//CR/W = 0 : when writing 	//When data is supplied	//SE = 1 	//Wait 	//CE = 0 
//	int status = 1;
//	GPIOD_IN(); // PORT D AS INPUT TO READ FROM PINS
//	SRW(); // R/W IS SET 
//	CRS(); // CLEAR RS 
//	
//		while(status )
//		{
//		SE();
//		delay_mS1(0);
//		status = (GPIOD->IDR & 1<<7);
//		CE();
//		delay_mS1(0);
//		}
//	CRW();
//	GPIOD_OUT();
//	
//}





//// sending commands to LCD func.
//void commands (unsigned char cmd){
////When sending commands
////RS = 0	//R/W = 0	//E = 1	//Wait 	//E = 0 
//	bussy();
//	CRS(); CRW(); 
//	
//	GPIOD->BSRR = (0xff<<(0+16));
//	GPIOD->BSRR = (cmd<<(0));
//	
//	SE(); delay_mS1(0); CE();

//}


//void commandsnopoll (unsigned char cmd){
////When sending commands
////RS = 0	//R/W = 0	//E = 1	//Wait 	//E = 0 
//	
//	CRS(); CRW(); 
//	
//	GPIOD->BSRR = (0xff<<(0+16));
//	GPIOD->BSRR = (cmd<<(0));
//	SE(); delay_mS1(0); CE();
//	
//	if (cmd <4){delay_mS(2);}
//	else{delay_mS1(1);}

//}


//// printing to LCD func.
//void LCDprint (char data){
//	//CRS = 0 : send commands 	//SRS = 1 : send data	//SR/W = 1 : when reading 	//CR/W = 0 : when writing 	//When data is supplied	//SE = 1 	//Wait 	//CE = 0 
//	//therfore
//	bussy();
//	SRS(); CRW();
//	
//	GPIOD->BSRR = (0xff<<(0+16));
//	GPIOD->BSRR = (data<<(0));
//	
//	SE(); delay_mS1(0); CE();
//}



//void delay_mS1 (int n){
//	int i;
//	for (; n>0; n--)
//				for(i =0; i<3195; i++);
//}