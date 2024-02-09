#ifndef _LCD_H
#define _LCD_H





#define LCD_LINE1		0x80
#define LCD_LINE2		0xc0


#define LCD_CLR()		cmdLCD(0x01)

#define RS 11  // defining pin connected to RS
#define RW 12		// defining pin connected to RW
#define E 13		// defining pin connected to E

#define SRS()	GPIOD->BSRR=(1u<<(RS))  // // defining command setting RS
#define CRS()	GPIOD->BSRR=(1u<<((RS)+16))		// defining command clearing RS
#define SRW()	GPIOD->BSRR=(1u<<(RW))		// defining command setting RW
#define CRW()	GPIOD->BSRR=(1u<<((RW)+16))		// defining command clearing RS
#define SE()	GPIOD->BSRR=(1u<<(E))		// defining command setting E
#define CE()	GPIOD->BSRR=(1u<<((E)+16))		// defining command clearing E

#define GPIOD_IN()		GPIOD->MODER&=~(0xffff<<(2*0))
#define GPIOD_OUT()	GPIOD->MODER|=(0x5555<<(2*0))
#include   <stm32f4xx.h>

void init_port(void);
//4BIT
void init_LCD4BIT (void);
void commands4BIT (unsigned char cmd);
void set_data4BIT (char data, unsigned char control);
void LCDprint4BIT (char data);
// 8 BIT
void delay_mS1 (int n);
void init_LCD(void);
void bussy(void);
void commands (unsigned char cmd);
void commandsnopoll (unsigned char cmd);
void LCDprint(char data);
void write (char *str);
#endif
