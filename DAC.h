#ifndef _DAC_H
#define _DAC_H
#include <stm32f4xx.h>
#define DAC_port	GPIOA
#define DAC_pin		5
void init_DAC2(uint16_t s[]);
char output_dac1(unsigned short d);
void usartV (unsigned short u);
void pwm1 (void);
int output_dac2(unsigned short l);
void init_DAC1(void);
void init_DAC22(void);

#endif