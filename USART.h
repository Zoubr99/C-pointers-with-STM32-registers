#ifndef _USART_H_
#define _USART_H_
#include <stm32f4xx.h>
#include <stdio.h>
#define USART_MODULE USART3
#define USART_PORT GPIOD
#define USART_TX_pin 8
#define USART_RX_pin 9
#define BAUDRATE 9600

void init_USART(void);
void send_usart(unsigned char d);
int fputc(int ch, FILE *f);
char RXNE (void);
int USART_GetData(void);
//char morse;
#endif
