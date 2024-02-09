#include <stm32f4xx.h>
#include <stm32f429xx.h>
#include "ADC.h"
#include "DAC.h"
#include "USART.h"
#include "LEDs.h"
#include "Timers_nINTs.h"
#include "PLL_Config.h"
#include "EXTI.h"
#include "Buzzer.h"
#include <string.h>
#include "LCD.h"



int main (void){

	
//***********these are the arrays which the input morse sequence to be compared with.************//
																			char morsecode_A[] = ".-";
																			char morsecode_B[] = "-...";
																			char morsecode_C[] = "-.-.";
																			char morsecode_D[] = "-..";
																			char morsecode_E[] = ".";
																			char morsecode_F[] = "..-.";
																			char morsecode_G[] = "--.";
																			char morsecode_H[] = "....";
																			char morsecode_I[] = "..";
																			char morsecode_J[] = ".---";
																			char morsecode_K[] = "-.-";
																			char morsecode_L[] = ".-..";
																			char morsecode_M[] = "--";
																			char morsecode_N[] = "-.";
																			char morsecode_O[] = "---";
																			char morsecode_P[] = ".--.";
																			char morsecode_Q[] = "--.-";
																			char morsecode_R[] = ".-.";
																			char morsecode_S[] = "...";
																			char morsecode_T[] = "-";
																			char morsecode_U[] = "..-";
																			char morsecode_V[] = "...-";
																			char morsecode_W[] = ".--";
																			char morsecode_Y[] = "-.--";
																			char morsecode_Z[] = "--..";
																			char morsecode_1[] = ".----";
																			char morsecode_2[] = "..---";
																			char morsecode_3[] = "...--";
																			char morsecode_4[] = "....-";
																			char morsecode_5[] = ".....";
																			char morsecode_6[] = "-....";
																			char morsecode_7[] = "--...";
																			char morsecode_8[] = "---..";
																			char morsecode_9[] = "----.";
																			char morsecode_0[] = "-----";
																			char morscode_space_words[] = "......";
	
//********************************************************************************************************//	
		//this approach compares 2 arrays the input and the one stored in memmory
		// this comparison is stored in a variable called "result"
		// if both arrays are equal, the result = 0
		// if result was 0 = true a letter was found then enter the below loop 
	int result; // the variable where the result of the comparison to be stored
	
	

	PLL_Config();
	SystemCoreClockUpdate();
	extern int PWM[2];
	extern uint16_t samples[3]; // array which has the ADC inputs ie (POT, MIC , LDR)
						// these lines are just to call the initilizations//

										//init_ext();
										init_timer5(); // timer for button periods
										init_timer2(); // timer for delay
										init_timer3(); // timer for adc 
										init_timer4(); // timer for dac1 
										init_timer7(); /// timer for dac2
										init_timer8();
									//init_LCD();
                    init_LCD4BIT();
										ADCone();
										init_DAC1();
										init_USART();
										init_led1();
										init_led2();
										init_led3();
										//init_extC();
										Buzzer_init();
										inputUser();
										inputpinA();
										inputpinB();
										inputpinC();
										inputpinD();
										RGB_init();
										seg_init();
											/*calling traffic lights functions*/
										pin2_int();
										pin3_int();
										pin6_int();
										pin7_int();
										pin8_int();
										pin9_int();
										pin10_int();
										offp7led();
										offp8led();
										offp9led();
										pin10_int();
										offGREEN();
										offRED();
										offYELLOW();
										RED();
										p7led();
//										init_DAC2();
										DAC->CR &= ~(DAC_CR_EN1);
//										DAC->CR &= ~(DAC_CR_EN2);
//										DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
										
								/***************************************/
								
	TIM5->CNT = 0; // counnter for TIM 5 to be set on zero at the beggeining 
	int breakcheck = 0; // break check set to 0 // this will be needed to break out of the loop as soon the intended sequence is entered and break button is pressed {A}
  int breaking1 =0;
	int breaking2 = 0;
	int breaking3 = 0;
	offALL();
	int LDRwhilebreak =0;
	uint16_t MIC[128];
	uint16_t POT[128];
	
	
	
	while(1)
	{	


						L_segment_display(three());
				R_segment_display(six());
		
				
					char manual_mode;
			char automatic_mode;
			char analogue_test;
		commands4BIT(0x80);
		write("Analogue: Blu B");
		commands4BIT(0xc0);
		write("auto: B man: C");
				while(1)
				{
					if (GPIOC->IDR & 1<<13){
					delay_mS(1000); // 100 mS debounce 
					goto analogue_test; // THIS TAKES THE USER TO THE ANALOGUE TEST MODE
					}
					
					if(GPIOG->IDR & 1<<2){
					delay_mS(1000);	// 100 mS debounce 
					goto manual_mode; // THIS TAKES THE USERT TO THE MANUAL MORSE CODE MODE
					}

					if(GPIOG->IDR & 1<<1){
					delay_mS(1000);	// 100 mS debounce 
					goto automatic_mode; // THIS TAKES THE USERT TO THE AUTO MORSE CODE MODE
					}	
						
				}
				
				
				

	automatic_mode:
		while(1){		
			
			
			
			
			
			
		delay_mS(1000); // 100 mS debounce
		TL3(); delay_mS(1000); TL3();
		commands4BIT(0x80);
			write("Blu B: transmit");
		commands4BIT(0xc0);
			write("C:MIC R D:LDR R");
		
				while(1)
				{
					if (GPIOC->IDR & 1<<13){
					delay_mS(1000); // 100 mS debounce 
					goto transmit; // THIS TAKES THE USER TO THE ANALOGUE TEST MODE
					}
					
					if(GPIOG->IDR & 1<<3){
					delay_mS(1000);	// 100 mS debounce 
					goto LDR_Recieve; // THIS TAKES THE USERT TO THE LDR Rec mode
					}

					if(GPIOG->IDR & 1<<2){
					delay_mS(1000);	// 100 mS debounce 
					goto MIC_Recieve; // THIS TAKES THE USERT TO THE MIC as Rec MODE
					}	
						
				}
				
				
				
				// TRANSMIT THROUGH PUTTY
			transmit:		while(1){
			delay_mS(1000); // 100 mS debounce
			TL3(); delay_mS(1000); TL3();
			commands4BIT(0x01);
			write("    Transmit");
				transmission_start();
			while(1){
			if (GPIOC->IDR & 1<<13) goto manual_mode;
			delay_mS(1000); // 100 mS debounce
			extern char morse;
			switch (morse){
				case 'A': dot(); dash(); morse=0; break;
				case 'B': dash(); dot(); dot(); dot(); morse=0; break;
				case 'C': dash(); dot(); dash(); dot(); morse=0; break;
				case 'D': dash(); dot(); dot(); morse=0; break;
				case 'E': dot(); morse=0; break;
				case 'F': dot(); dot(); dash(); dot(); morse=0; break;
				case 'G': dash(); dash(); dot(); morse=0; break;
				case 'H': dot(); dot(); dot(); dot(); morse=0; break;
				case 'I': dot(); dot(); morse=0; break;
				case 'J': dot(); dash(); dash(); dash(); morse=0; break;
				case 'K': dash(); dot(); dash(); morse=0; break;
				case 'L': dot(); dash(); dot(); dot(); morse=0; break;
				case 'M': dash(); dash(); morse=0; break;
				case 'N': dash(); dot(); morse=0; break;
				case 'O': dash(); dash(); dash(); morse=0; break;
				case 'P': dot(); dash(); dash(); dot(); morse=0; break;
				case 'Q': dash(); dash(); dot(); dash(); morse=0; break;
				case 'R': dot(); dash(); dot(); morse=0; break;
				case 'S': dot(); dot(); dot(); morse=0; break;
				case 'T': dash(); morse=0; break;
				case 'U': dot(); dot(); dash(); morse=0; break;
				case 'V': dot(); dot(); dot(); dash(); morse=0; break;
				case 'W': dot(); dash(); dash(); morse=0; break;
				case 'X': dash(); dot(); dot(); dash(); morse=0; break;
				case 'Y': dash(); dot(); dash(); dash(); morse=0; break;
				case 'Z': dash(); dash(); dot(); dot(); morse=0; break;
				case '1': dot(); dash(); dash(); dash(); dash(); morse=0; break;
				case '2': dot(); dot(); dash(); dash(); dash(); morse=0; break;
				case '3': dot(); dot(); dot(); dash(); dash(); morse=0; break;
				case '4': dot(); dot(); dot(); dot(); dash(); morse=0; break;
				case '5': dot(); dot(); dot(); dot(); dot(); morse=0; break;
				case '6': dash(); dot(); dot(); dot(); dot(); morse=0; break;
				case '7': dash(); dash(); dot(); dot(); dot(); morse=0; break;
				case '8': dash(); dash(); dash(); dot(); dot(); morse=0; break;
				case '9': dash(); dash(); dash(); dash(); dot(); morse=0; break;
				case '0': dash(); dash(); dash(); dash(); dash(); morse=0; break;
				case ' ': dot(); dot(); dot(); dot(); dot(); morse=0; break;
				//and so on.......
				transmission_end();
			}
			
		}	
		}// TRANSMIT THROUGH PUTTY out
			//START OF MIC AS RECIEVER
// for good results just blow on MIC
	MIC_Recieve:
		delay_mS(1000); // 100 mS debounce
		TL3(); delay_mS(1000); TL3();
		write("  MIC Recieve");	
			delay_mS(10000);
				commands4BIT(0x01);
					commands4BIT(0x80);
						write("Hold Blu Button");
							commands4BIT(0xc0);
								write(" To Clr Display");	
									transmission_start();
										commands4BIT(0x01);
			while(1)
							{
									commands4BIT(0x01);
							while(!(GPIOC->IDR & 1<<13)){
											char morseinput2[5] = {0,0,0,0,0};
												for(int x =0; x<5; ++x){
								TIM5->CNT=0 ;
									TIM5->CR1 |= (TIM_CR1_CEN);
							while(!(samples[1] >2080 && samples[1] < 2000)){										
													if(TIM5->CNT > 180000000){
														
														TIM5->CR1 &= ~(TIM_CR1_CEN);
//														++LDRwhilebreak;
														TIM5->CNT=0;
//														break;
														transmission_end();
														goto comparison2;
													}
												}
//						if(LDRwhilebreak == 1){ break;}
						TIM5->CR1 &= ~(TIM_CR1_CEN);
								TIM5->CNT=0 ;
									TIM5->CR1 |= (TIM_CR1_CEN);
											while((((samples[1]+samples[1]+samples[1]+samples[1]+samples[1])/5) > 2060)
														|| (((samples[1]+samples[1]+samples[1]+samples[1]+samples[1])/5) < 2010)){printf("[%d]", samples[1]);} // while there is still light it will keep in loop and increase timer count
												TIM5->CR1 &= ~(TIM_CR1_CEN);
													long long time5_auto = TIM5->CNT ;
														if(time5_auto < 45000000){
				
															dot();
															morseinput2[x]='.';
															TIM5->CNT =0;
															//time5_auto=0;
	
															}
														
															if(time5_auto>45000000 ){
																dash();
																morseinput2[x]='-';
																TIM5->CNT =0;
																//time5_auto=0;
												
															}
															
//															if(time5_auto>300000000){
//																TIM5->CNT =0;
//																transmission_end();
//																commands4BIT(0x01);
//																goto comparison2;
//																			
//															}
																									
				
														} // end of MIC as RECIEVER
						
									comparison2:
															result = strcmp(morseinput2, morsecode_1); 
															if (result == 0) {
																printf("1");
																LCDprint4BIT('1');
															
															}
															result = strcmp(morseinput2, morsecode_2); 
															if (result == 0) {
																printf("2");
																LCDprint4BIT('2');
																
															}
															result = strcmp(morseinput2, morsecode_3); 
															if (result == 0) {
																printf("3");
																LCDprint4BIT('3');
															
															}
															result = strcmp(morseinput2, morsecode_4); 
															if (result == 0) {
																printf("4");
																LCDprint4BIT('4');
															
															}
															result = strcmp(morseinput2, morsecode_5); 
															if (result == 0) {
																printf("5");
																LCDprint4BIT('5');
															
															}
															result = strcmp(morseinput2, morsecode_6); 
															if (result == 0) {
																printf("6");
																LCDprint4BIT('6');
															
															}
															result = strcmp(morseinput2, morsecode_7); 
															if (result == 0) {
																printf("7");
																LCDprint4BIT('7');
															
															}
															result = strcmp(morseinput2, morsecode_8); 
															if (result == 0) {
																printf("8");
																LCDprint4BIT('8');
															
															}
															result = strcmp(morseinput2, morsecode_9); 
															if (result == 0) {
																printf("9");
																LCDprint4BIT('9');
															
															}
															result = strcmp(morseinput2, morsecode_0); 
															if (result == 0) {
																printf("0");
																LCDprint4BIT('0');
																
															}
															result = strcmp(morseinput2, morscode_space_words); 
															if (result == 0) {
																printf(" ");
																LCDprint4BIT(' ');
																
															}
		
		
		
		
		
		/**********************************************************************Now the letters ********************************************************************************/
		
		
		
		
		
															result = strcmp(morseinput2, morsecode_A); 
															if (result == 0) {
																printf("A");
																LCDprint4BIT('A');
															
															}
															
																			result = strcmp(morseinput2, morsecode_B); 
																			if (result == 0) {
																				printf("B");
																				LCDprint4BIT('B');
																				
																			}
														
																						result = strcmp(morseinput2, morsecode_C); 
																						if (result == 0) {
																							printf("C");
																							LCDprint4BIT('C');
																							
																						}
																
																									result = strcmp(morseinput2, morsecode_D); 
																									if (result == 0) {
																										printf("D");
																										LCDprint4BIT('D');
																									
																									}
																
																											result = strcmp(morseinput2, morsecode_E); 
																											if (result == 0) {
																												printf("E");
																												LCDprint4BIT('E');
																									
																											}
																								
																													result = strcmp(morseinput2, morsecode_F); 
																													if (result == 0) {
																														printf("F");
																														LCDprint4BIT('F');
																												
																													}
																
																															result = strcmp(morseinput2, morsecode_G); 
																															if (result == 0) {
																																printf("G");
																																LCDprint4BIT('G');
																														
																															}
															
																																	result = strcmp(morseinput2, morsecode_H); 
																																	if (result == 0) {
																																		printf("H");
																																		LCDprint4BIT('H');
																															
																																	}
															
																																			result = strcmp(morseinput2, morsecode_I); 
																																			if (result == 0) {
																																				printf("I");
																																				LCDprint4BIT('I');
																															
																																			}
															
																																					result = strcmp(morseinput2, morsecode_J); 
																																					if (result == 0) {
																																						printf("J");
																																						LCDprint4BIT('J');
																															
																																					}
																										
																																							result = strcmp(morseinput2, morsecode_K); 
																																							if (result == 0) {
																																								printf("K");
																																								LCDprint4BIT('K');
																																						
																																							}
																																				
																																					result = strcmp(morseinput2, morsecode_L); 
																																					if (result == 0) {
																																						printf("L");
																																						LCDprint4BIT('L');
																																				
																																					}
															
																																	result = strcmp(morseinput2, morsecode_M); 
																																	if (result == 0) {
																																		printf("M");
																																		LCDprint4BIT('M');
																																
																																	}
															
																														result = strcmp(morseinput2, morsecode_N); 
																														if (result == 0) {
																															printf("N");
																															LCDprint4BIT('N');
																														
																														}
																										
																											result = strcmp(morseinput2, morsecode_O); 
																											if (result == 0) {
																												printf("O");
																												LCDprint4BIT('O');
																										
																											}
																											
																								result = strcmp(morseinput2, morsecode_P); 
																								if (result == 0) {
																									printf("P");
																									LCDprint4BIT('P');
																									
																								}
															
																					result = strcmp(morseinput2, morsecode_Q); 
																					if (result == 0) {
																						printf("Q");
																						LCDprint4BIT('Q');
																				
																					}
															
																		result = strcmp(morseinput2, morsecode_R); 
																		if (result == 0) {
																			printf("R");
																			LCDprint4BIT('R');
																		
																		}
									
															result = strcmp(morseinput2, morsecode_S); 
															if (result == 0) {
																printf("S");
																LCDprint4BIT('S');
															
															}
													
													result = strcmp(morseinput2, morsecode_T); 
													if (result == 0) {
														printf("T");
														LCDprint4BIT('T');
												
													}
										
											result = strcmp(morseinput2, morsecode_U); 
											if (result == 0) {
												printf("U");
												LCDprint4BIT('U');
								
											}
									
									result = strcmp(morseinput2, morsecode_V); 
									if (result == 0) {
										printf("V");
										LCDprint4BIT('V');
							
									}
					
							result = strcmp(morseinput2, morsecode_W); 
							if (result == 0) {
								printf("W");
								LCDprint4BIT('W');
						
							}
						
				result = strcmp(morseinput2, morsecode_Y); 
				if (result == 0) {
					printf("Y");
					LCDprint4BIT('Y');
			
				}
		
	result = strcmp(morseinput2, morsecode_Z); 
	if (result == 0) {
		printf("Z");
		LCDprint4BIT('Z');

	}
}
					}	 // END OF  MIC AS  RECIEVER
		
		// for good results use in dark
// LDR AS A RECIEVER		
LDR_Recieve:
					
					while(1)
						{
delay_mS(1000); // 100 mS debounce
	TL3(); delay_mS(1000); TL3();							
		commands4BIT(0x01);
			write("  LDR Recieve");	
				delay_mS(20000);
					commands4BIT(0x01);				
						write("Hold Blu Button");
							commands4BIT(0xc0);
								write(" To Clr Display");	
									transmission_start();
										commands4BIT(0x01);				
				while(1){
					commands4BIT(0x01);
							while(!(GPIOC->IDR & 1<<13)){
						

					char morseinput1[5] = {0,0,0,0,0};
							for(int x =0; x<5; ++x){
								TIM5->CNT=0 ;
									TIM5->CR1 |= (TIM_CR1_CEN);
						while(samples[2]>1000){										
													if(TIM5->CNT > 300000000){
														
														TIM5->CR1 &= ~(TIM_CR1_CEN);
//														++LDRwhilebreak;
														TIM5->CNT=0;
//														break;
														transmission_end();
														goto comparison1;
													}
												}
//						if(LDRwhilebreak == 1){ break;}
						TIM5->CR1 &= ~(TIM_CR1_CEN);
								TIM5->CNT=0 ;
									TIM5->CR1 |= (TIM_CR1_CEN);
											while(samples[2]<1500){} // while there is still light it will keep in loop and increase timer count
												TIM5->CR1 &= ~(TIM_CR1_CEN);
													long long time5_auto = TIM5->CNT ;
														if(time5_auto < 45000000){
				
															dot();
															morseinput1[x]='.';
															TIM5->CNT =0;
															time5_auto=0;
	
															}
														
															if(time5_auto>45000000 && time5_auto<90000000){
																dash();
																morseinput1[x]='-';
																TIM5->CNT =0;
												
															}
															
															
															if(time5_auto>300000000){
																TIM5->CNT =0;
																transmission_end();
																goto comparison1;
																			
															}
																									
				
						}
					
//			if(LDRwhilebreak == 1){LDRwhilebreak =0; break;}			
						
						comparison1:
															result = strcmp(morseinput1, morsecode_1); 
															if (result == 0) {
																printf("1");
																LCDprint4BIT('1');
																
															}
															result = strcmp(morseinput1, morsecode_2); 
															if (result == 0) {
																printf("2");
																LCDprint4BIT('2');
																
															}
															result = strcmp(morseinput1, morsecode_3); 
															if (result == 0) {
																printf("3");
																LCDprint4BIT('3');
																
															}
															result = strcmp(morseinput1, morsecode_4); 
															if (result == 0) {
																printf("4");
																LCDprint4BIT('4');
																
															}
															result = strcmp(morseinput1, morsecode_5); 
															if (result == 0) {
																printf("5");
																LCDprint4BIT('5');

															}
															result = strcmp(morseinput1, morsecode_6); 
															if (result == 0) {
																printf("6");
																LCDprint4BIT('6');
															
															}
															result = strcmp(morseinput1, morsecode_7); 
															if (result == 0) {
																printf("7");
																LCDprint4BIT('7');
															
															}
															result = strcmp(morseinput1, morsecode_8); 
															if (result == 0) {
																printf("8");
																LCDprint4BIT('8');
																
															}
															result = strcmp(morseinput1, morsecode_9); 
															if (result == 0) {
																printf("9");
																LCDprint4BIT('9');
															
															}
															result = strcmp(morseinput1, morsecode_0); 
															if (result == 0) {
																printf("0");
																LCDprint4BIT('0');
																
															}
															result = strcmp(morseinput1, morscode_space_words); 
															if (result == 0) {
																printf(" ");
																LCDprint4BIT(' ');
																
															}
		
		
		
		
		
		/**********************************************************************Now the letters ********************************************************************************/
		
		
		
		
		
															result = strcmp(morseinput1, morsecode_A); 
															if (result == 0) {
																printf("A");
																LCDprint4BIT('A');
																
															}
															
																			result = strcmp(morseinput1, morsecode_B); 
																			if (result == 0) {
																				printf("B");
																				LCDprint4BIT('B');
																				
																			}
														
																						result = strcmp(morseinput1, morsecode_C); 
																						if (result == 0) {
																							printf("C");
																							
																						}
																
																									result = strcmp(morseinput1, morsecode_D); 
																									if (result == 0) {
																										printf("D");
																										LCDprint4BIT('C');
																									
																									}
																
																											result = strcmp(morseinput1, morsecode_E); 
																											if (result == 0) {
																												printf("E");
																												LCDprint4BIT('E');
																											
																											}
																								
																													result = strcmp(morseinput1, morsecode_F); 
																													if (result == 0) {
																														printf("F");
																														LCDprint4BIT('F');
																													
																													}
																
																															result = strcmp(morseinput1, morsecode_G); 
																															if (result == 0) {
																																printf("G");
																																LCDprint4BIT('G');
																															
																															}
															
																																	result = strcmp(morseinput1, morsecode_H); 
																																	if (result == 0) {
																																		printf("H");
																																		LCDprint4BIT('H');
																																	
																																	}
															
																																			result = strcmp(morseinput1, morsecode_I); 
																																			if (result == 0) {
																																				printf("I");
																																				LCDprint4BIT('I');
																																			
																																			}
															
																																					result = strcmp(morseinput1, morsecode_J); 
																																					if (result == 0) {
																																						printf("J");
																																						LCDprint4BIT('J');
																																					
																																					}
																										
																																							result = strcmp(morseinput1, morsecode_K); 
																																							if (result == 0) {
																																								printf("K");
																																								LCDprint4BIT('K');
																																						
																																							}
																																				
																																					result = strcmp(morseinput1, morsecode_L); 
																																					if (result == 0) {
																																						printf("L");
																																						LCDprint4BIT('L');
																																						
																																					}
															
																																	result = strcmp(morseinput1, morsecode_M); 
																																	if (result == 0) {
																																		printf("M");
																																		LCDprint4BIT('M');
																																		
																																	}
															
																														result = strcmp(morseinput1, morsecode_N); 
																														if (result == 0) {
																															printf("N");
																															LCDprint4BIT('N');
																															
																														}
																										
																											result = strcmp(morseinput1, morsecode_O); 
																											if (result == 0) {
																												printf("O");
																												LCDprint4BIT('O');
																												
																											}
																											
																								result = strcmp(morseinput1, morsecode_P); 
																								if (result == 0) {
																									printf("P");
																									LCDprint4BIT('P');
																								
																								}
															
																					result = strcmp(morseinput1, morsecode_Q); 
																					if (result == 0) {
																						printf("Q");
																						LCDprint4BIT('Q');
																					
																					}
															
																		result = strcmp(morseinput1, morsecode_R); 
																		if (result == 0) {
																			printf("R");
																			LCDprint4BIT('R');
																			
																		}
									
															result = strcmp(morseinput1, morsecode_S); 
															if (result == 0) {
																printf("S");
																LCDprint4BIT('S');
																
															}
													
													result = strcmp(morseinput1, morsecode_T); 
													if (result == 0) {
														printf("T");
														LCDprint4BIT('T');
														
													}
										
											result = strcmp(morseinput1, morsecode_U); 
											if (result == 0) {
												printf("U");
												LCDprint4BIT('U');
												
											}
									
									result = strcmp(morseinput1, morsecode_V); 
									if (result == 0) {
										printf("V");
										LCDprint4BIT('V');
										
									}
					
							result = strcmp(morseinput1, morsecode_W); 
							if (result == 0) {
								printf("W");
								LCDprint4BIT('W');
								
							}
						
				result = strcmp(morseinput1, morsecode_Y); 
				if (result == 0) {
					printf("Y");
					LCDprint4BIT('Y');
					
				}
		
	result = strcmp(morseinput1, morsecode_Z); 
	if (result == 0) {
		printf("Z");
		LCDprint4BIT('Z');

	}


}						
}
}
}		
		
		

	
				


		// manual mode start
manual_mode:while(1){
	delay_mS(1000); // 100 mS debounce
		TL3(); delay_mS(1000); TL3();
				commands4BIT(0x01);
					write("  Manual Mode");
						delay_mS(10000);
						commands4BIT(0x01);
						commands4BIT(0x80);
						write("C:Seq B:clr Dsply");
								commands4BIT(0xc0);
									write("A:cnfrm BLu:Mode");
																	transmission_start();
																commands4BIT(0x01);									
			while(1){
				white();

		char morseinput[5] = {0,0,0,0,0}; // morse code input array
		
		for (int i = 0; i < 5; ++i) { // for loop will be repeated 5 times if no break occured
			
				while (!(GPIOG->IDR & (1<<2))) { // wait for button {C} press
					
													if(GPIOC->IDR & 1<<13){offALL(); commands4BIT(1); goto automatic_mode;}
															if(GPIOG->IDR & 2){ // BUTTON B TO CLEAR
																	commands4BIT(1);
																	printf("\r\n");
																	break;
															}
													//***************Breaks*******************//
														if (GPIOG->IDR & 1) { // button {A} used to break 			
															transmission_end();
															breakcheck = 1;
															break; // this breaks out of this while loop only	
														}
				}
														
														if (breakcheck == 1) {
															breakcheck = 0; // sets the break check 0 so the process can be repeated again
															//clear uart and lcd
															break; // this breaks out of the for loop!!!
														}
														//******************end of break code****************//
										
										
											//***************The code below checks the duration of the button press *******************//
										//if the press duration < 90M counts ie 1Sec return {. : dot} if the duration was > 90M return {-:dash}  //
																																
																if (GPIOG->IDR & (1<<2)){
																delay_mS(100);
																TIM5->CR1 |= TIM_CR1_CEN;

																		while (GPIOG->IDR & (1<<2)) {} // wait for button a to be released
																		TIM5->CR1 &= ~(TIM_CR1_CEN);
																		long long time5_count = TIM5->CNT ;
																		
															
																			
																										if(time5_count < 45000000) // if tim5 count < 90 millions send . to morse code input array
																										{
																										
																										dot();
																										morseinput[i] = '.';
																										TIM5->CNT = 0;
																										}
																										
																										
																										if(time5_count > 45000000)	// if tim5 count > 90 millions send - to morse code input array
																										{
																										dash();
																										morseinput[i] = '-';
																										TIM5->CNT = 0;
																										}
																																					
																														}
																//***************end of checking and calculating *******************//
								
		}
//************************ Here {{strcmp}} compares elements of two arrays if the elemnts match rsults is true (0) (here 0 is true), therefore print the letter and so on ************************// 
		
															result = strcmp(morseinput, morsecode_1); 
															if (result == 0) {
																printf("1");
																LCDprint4BIT('1');
																
															}
															result = strcmp(morseinput, morsecode_2); 
															if (result == 0) {
																printf("2");
																LCDprint4BIT('2');
																
															}
															result = strcmp(morseinput, morsecode_3); 
															if (result == 0) {
																printf("3");
																LCDprint4BIT('3');
																
															}
															result = strcmp(morseinput, morsecode_4); 
															if (result == 0) {
																printf("4");
																LCDprint4BIT('4');
																
															}
															result = strcmp(morseinput, morsecode_5); 
															if (result == 0) {
																printf("5");
																LCDprint4BIT('5');
																
															}
															result = strcmp(morseinput, morsecode_6); 
															if (result == 0) {
																printf("6");
																LCDprint4BIT('6');
																
															}
															result = strcmp(morseinput, morsecode_7); 
															if (result == 0) {
																printf("7");
																LCDprint4BIT('7');
															
															}
															result = strcmp(morseinput, morsecode_8); 
															if (result == 0) {
																printf("8");
																LCDprint4BIT('8');
															
															}
															result = strcmp(morseinput, morsecode_9); 
															if (result == 0) {
																printf("9");
																LCDprint4BIT('9');
															
															}
															result = strcmp(morseinput, morsecode_0); 
															if (result == 0) {
																printf("0");
																LCDprint4BIT('0');
															
															}
															result = strcmp(morseinput, morscode_space_words); 
															if (result == 0) {
																printf(" ");
																LCDprint4BIT(' ');
															
															}
		
		
		
		
		
		/**********************************************************************Now the letters ********************************************************************************/
		
		
		
		
		
															result = strcmp(morseinput, morsecode_A); 
															if (result == 0) {
																printf("A");
																LCDprint4BIT('A');
																
															}
															
																			result = strcmp(morseinput, morsecode_B); 
																			if (result == 0) {
																				printf("B");
																				LCDprint4BIT('B');
																			
																			}
														
																						result = strcmp(morseinput, morsecode_C); 
																						if (result == 0) {
																							printf("C");
																						
																						}
																
																									result = strcmp(morseinput, morsecode_D); 
																									if (result == 0) {
																										printf("D");
																										LCDprint4BIT('C');
																									
																									}
																
																											result = strcmp(morseinput, morsecode_E); 
																											if (result == 0) {
																												printf("E");
																												LCDprint4BIT('E');
																												
																											}
																								
																													result = strcmp(morseinput, morsecode_F); 
																													if (result == 0) {
																														printf("F");
																														LCDprint4BIT('F');
																												
																													}
																
																															result = strcmp(morseinput, morsecode_G); 
																															if (result == 0) {
																																printf("G");
																																LCDprint4BIT('G');
																														
																															}
															
																																	result = strcmp(morseinput, morsecode_H); 
																																	if (result == 0) {
																																		printf("H");
																																		LCDprint4BIT('H');
																																	
																																	}
															
																																			result = strcmp(morseinput, morsecode_I); 
																																			if (result == 0) {
																																				printf("I");
																																				LCDprint4BIT('I');
																																				
																																			}
															
																																					result = strcmp(morseinput, morsecode_J); 
																																					if (result == 0) {
																																						printf("J");
																																						LCDprint4BIT('J');
																																						
																																					}
																										
																																							result = strcmp(morseinput, morsecode_K); 
																																							if (result == 0) {
																																								printf("K");
																																								LCDprint4BIT('K');
																																							
																																							}
																																				
																																					result = strcmp(morseinput, morsecode_L); 
																																					if (result == 0) {
																																						printf("L");
																																						LCDprint4BIT('L');
																																					
																																					}
															
																																	result = strcmp(morseinput, morsecode_M); 
																																	if (result == 0) {
																																		printf("M");
																																		LCDprint4BIT('M');
																																		
																																	}
															
																														result = strcmp(morseinput, morsecode_N); 
																														if (result == 0) {
																															printf("N");
																															LCDprint4BIT('N');
																													
																														}
																										
																											result = strcmp(morseinput, morsecode_O); 
																											if (result == 0) {
																												printf("O");
																												LCDprint4BIT('O');
																										
																											}
																											
																								result = strcmp(morseinput, morsecode_P); 
																								if (result == 0) {
																									printf("P");
																									LCDprint4BIT('P');
																								
																								}
															
																					result = strcmp(morseinput, morsecode_Q); 
																					if (result == 0) {
																						printf("Q");
																						LCDprint4BIT('Q');
																						
																					}
															
																		result = strcmp(morseinput, morsecode_R); 
																		if (result == 0) {
																			printf("R");
																			LCDprint4BIT('R');
																			
																		}
									
															result = strcmp(morseinput, morsecode_S); 
															if (result == 0) {
																printf("S");
																LCDprint4BIT('S');
															
															}
													
													result = strcmp(morseinput, morsecode_T); 
													if (result == 0) {
														printf("T");
														LCDprint4BIT('T');
													
													}
										
											result = strcmp(morseinput, morsecode_U); 
											if (result == 0) {
												printf("U");
												LCDprint4BIT('U');
											
											}
									
									result = strcmp(morseinput, morsecode_V); 
									if (result == 0) {
										printf("V");
										LCDprint4BIT('V');
									
									}
					
							result = strcmp(morseinput, morsecode_W); 
							if (result == 0) {
								printf("W");
								LCDprint4BIT('W');
								
							}
						
				result = strcmp(morseinput, morsecode_Y); 
				if (result == 0) {
					printf("Y");
					LCDprint4BIT('Y');
			
				}
		
	result = strcmp(morseinput, morsecode_Z); 
	if (result == 0) {
		printf("Z");
		LCDprint4BIT('Z');
	
	}
//man mode out
																//************************ end of comparing elemnts, and printiong onto the terminal ************************// 

}

	
	
  }//auto mode out
			
	analogue_test:{
		while(1){
		delay_mS(1000); // 100 mS debounce
		TL3(); delay_mS(1000); TL3();
			TIM8->CNT = 0;
			TIM8->CR1 |= TIM_CR1_CEN;
			
			while(GPIOC->IDR & 1<<13){}
				TIM8->CR1 &= ~(TIM_CR1_CEN);
				long long presscount =TIM8->CNT;
				if(presscount < 1373){ goto mode_selection;}
					if(presscount > 1373){goto HOLD;}
					mode_selection:
					{
								while(1)
								{
							commands4BIT(0x01);
								commands4BIT(0x80);
									write("    Press A");
										commands4BIT(0xc0);
									write("    for MENU");
												while(!(GPIOG->IDR & 1)){}
													delay_mS(1000); // debounce
															while(1){
																commands4BIT(0x01);
																commands4BIT(0x80);
																write("Blu B:PuTy->DAC1");
																		commands4BIT(0xc0);
																write("   A : Scroll");
																	while(!(GPIOG->IDR & 1))
																		{																	
																		if(GPIOC->IDR & 1<<13)
																			{
																				commands4BIT(0x01);
																					commands4BIT(0x80);
																							write("PuTTy->DAC1 ON");
																								commands4BIT(0xc0);
																									write("Blu Btn:Go Back");
																							DAC->CR |= DAC_CR_EN1;
																							while(1){
																								delay_mS(1000); // 100mS debounce

																										extern float a;
																											usartV(a);
																											if(GPIOC->IDR & 1<<13)
																											{
																													delay_mS(1000); // 100mS debounce
																													//++breaking1; 
																												break;
																											}	
																										}break;
																							DAC->CR &= ~(DAC_CR_EN1);
																						
																						}															
																					}
														delay_mS(2000); // 50mS debounce
							commands4BIT(0x01);
								commands4BIT(0x80);
									write("Blu B:LDR->DAC1");
										commands4BIT(0xc0);
												write("   A : Scroll");										
													while(!(GPIOG->IDR & 1))
														{
															if(GPIOC->IDR & 1<<13){
																delay_mS(1000); // 100mS debounce
																	commands4BIT(0x01);
																		commands4BIT(0x80);
																			write("LDR->DAC1 ON");
																				commands4BIT(0xc0);
																				write("Blu Btn:Go Back");
																				DAC->CR |= DAC_CR_EN1;
																					while(1)
																					{																		
																							output_dac1(samples[2]);
																								if(GPIOC->IDR & 1<<13)
																									{
																										delay_mS(1000); // 100mS debounce
																										//++breaking2; 
																										break;
																									}
																																								
																						}
																					DAC->CR &= ~(DAC_CR_EN1);
																					break;
																					}
																			}
																		delay_mS(2000); // 200mS debounce
							commands4BIT(0x01);
								commands4BIT(0x80);
									write("Blu B:ADC->PuTTy");
										commands4BIT(0xc0);
											write("   A : Scroll");										
													while(!(GPIOG->IDR & 1))
														{
															if(GPIOC->IDR & 1<<13){
																delay_mS(1000); // 100mS debounce
																	commands4BIT(0x01);
																		commands4BIT(0x80);
																			write("ADC to PuTTY ON");
																				commands4BIT(0xc0);
																write("Blu Btn:Go Back");
														
																					while(1)
																					{																		
																							printf("POT[%d] MIC[%d] LDR[%d]\r\n", samples[0], samples[1], samples[2]);
																								if(GPIOC->IDR & 1<<13)
																									{
																										delay_mS(1000); // 100mS debounce
																										//++breaking2; 
																										break;
																									}
																																							
																						}
																					  
																						break;
																					}	
																			}
																		delay_mS(2000); // 100mS debounce	
							commands4BIT(0x01);
								commands4BIT(0x80);
									write("Blu B:DAC1Sqr wv");
										commands4BIT(0xc0);
											write("   A : Scroll");										
													while(!(GPIOG->IDR & 1))
														{
															if(GPIOC->IDR & 1<<13){
																delay_mS(1000); // 100mS debounce
																	commands4BIT(0x01);
																		commands4BIT(0x80);
																			write("DAC1 Sqr wav ON");  // due the interrupts working in background there will be a bit of jittering
																				commands4BIT(0xc0);
																write("Blu Btn:Go Back");
																DAC->CR |= DAC_CR_EN1;
																					while(1)
																					{					
																						//pwm1();
																					DAC->DHR12R1=4000;
																						delay_mS(1);
																						DAC->DHR12R1= 0;
																						delay_mS(1);
																							
																								if(GPIOC->IDR & 1<<13)
																									{
																										delay_mS(1000); // 100mS debounce
																										//++breaking2; 
																										
																										break;
																									}
																																							
																						}
																					 DAC->CR &= ~(DAC_CR_EN1);																			
																						break;
																					}		
																				}	
							commands4BIT(0x01);
								commands4BIT(0x80);
									write("Blu B:DAC2 POT");  // due the interrupts working in background there will be a bit of jittering
										commands4BIT(0xc0);
											write("   A : Scroll");										
													while(!(GPIOG->IDR & 1))
														{
															if(GPIOC->IDR & 1<<13){
																delay_mS(1000); // 100mS debounce
																	commands4BIT(0x01);
																		commands4BIT(0x80);
																			write("DAC2 POT ON");
																				commands4BIT(0xc0);
																write("Blu Btn:Go Back");
																															DAC->CR &= ~(DAC_CR_EN2);
																	DMA1_Stream6->CR &= ~(DMA_SxCR_EN);												
																		init_DAC2(POT);	
																			DAC->CR |= DAC_CR_EN2;
																				DMA1_Stream6->CR |= DMA_SxCR_EN;	
																					while(1)
																					{	
																						for(int i =0; i<128; ++i){																
																						extern const uint16_t function[128];
//																						MIC[i]= ((function[i]) * (samples[0]/2000));
																							POT[i]= samples[0];
																						}
																							DAC->DHR12R2=POT;

																								if(GPIOC->IDR & 1<<13)
																									{
																										delay_mS(1000); // 100mS debounce

																										
																										break;
																									}
																				
																					}		DAC->CR &= ~(DAC_CR_EN2);
																									DMA1_Stream6->CR &= ~(DMA_SxCR_EN);	
																						break;	
																				}																					
																				}	
							commands4BIT(0x01);
								commands4BIT(0x80);
									write("Blu B:DAC2 MIC");
										commands4BIT(0xc0);
											write("   A : Scroll");										
													while(!(GPIOG->IDR & 1))
														{
															if(GPIOC->IDR & 1<<13){
																delay_mS(1000); // 100mS debounce
																	commands4BIT(0x01);
																		commands4BIT(0x80);
																			write("DAC2 MIC");  // due the interrupts working in background there will be a bit of jittering
																				commands4BIT(0xc0);
																write("Blu Btn:Go Back");
																DAC->CR &= ~(DAC_CR_EN2);
																	DMA1_Stream6->CR &= ~(DMA_SxCR_EN);												
																		init_DAC2(MIC);	
																			DAC->CR |= DAC_CR_EN2;
																				DMA1_Stream6->CR |= DMA_SxCR_EN;	
																					while(1)
																					{	
																						for(int i =0; i<128; ++i){																
																						extern const uint16_t function[128];
//																						MIC[i]= ((function[i]) * (samples[0]/2000));
																							MIC[i]= samples[1];
																						}
																							DAC->DHR12R2=MIC;

																								if(GPIOC->IDR & 1<<13)
																									{
																										delay_mS(1000); // 100mS debounce
																										//++breaking2; 
																										
																										break;
																									}
																																							
																						}
																						DAC->CR &= ~(DAC_CR_EN2);
																						DMA1_Stream6->CR &= ~(DMA_SxCR_EN);	
																						break;
																					}		
																				}
						commands4BIT(0x01);
							commands4BIT(0x80);
									write("Blu B:DAC2 SineW");
										commands4BIT(0xc0);
											write("   A : Scroll");										
													while(!(GPIOG->IDR & 1))
														{
															if(GPIOC->IDR & 1<<13){
																delay_mS(1000); // 100mS debounce
																	commands4BIT(0x01);
																		commands4BIT(0x80);
																			write("DAC2 SineW ON");
																				commands4BIT(0xc0);
																write("Blu Btn:Go Back");
																DAC->CR &= ~(DAC_CR_EN2);
																DMA1_Stream6->CR &=~(DMA_SxCR_EN);
																extern const uint16_t function[128]; 
																init_DAC2(function);
																DAC->CR |= DAC_CR_EN2;
																DMA1_Stream6->CR |= DMA_SxCR_EN;
																//DAC->DHR12R2=function;
																					while(1)
																					{																		
																								if(GPIOC->IDR & 1<<13)
																									{
																										delay_mS(1000); // 100mS debounce
																										//++breaking2; 
																										
																										break;
																									}
																																							
																						}
																	DAC->CR &= ~(DAC_CR_EN2);
																		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
																						break;
																					}		
																				}														
															}		
											}

									}	
					}
					/**********************************************/
					HOLD:
					{
							delay_mS(1000); // 100 mS debounce
							TL3(); delay_mS(1000); TL3();
						commands4BIT(0x01);
																		commands4BIT(0xc0);
																			write("      HOLD");
								while(1)
								{
									
									
										
									
									
									
								}
							}
				
				 
			}//end of analogue test
		}// end of head while
} // end of main




//void EXTI15_10_IRQHandler (void){
//	if(EXTI->PR & (1<<13)) {
//	while(1){
//		extern char manual_mode;
//		while(!(GPIOC->IDR & 13)){LCDprint('c');}
//			while(!(GPIOC->IDR & 13))
//				{LCDprint('m');
//					if(GPIOG->IDR & 3)
//						{goto manual_mode;}
//	}
//		EXTI->PR |= (1<<13);
//}
//	}


/*
volatile int Press;
char morseinput [5];
void EXTI2_IRQHandler (void){
		if (EXTI->PR & EXTI_PR_PR2)
			delay_mS(100);
			TL2();
			Sbuzzer();
			{ // Need to clear interrupt first otherwise it will occur twice.
			//EXTI->PR |= EXTI_PR_PR2;
			Press++; // Increment Press counter
			delay_mS(100);
				input();
		EXTI->PR |= EXTI_PR_PR2;
			}
}
*/

void TIM3_IRQHandler (void){
	
	extern uint16_t samples[3];			
	TIM3->SR&=~TIM_SR_UIF;
}


void TIM7_IRQHandler(void){

	TIM7->SR&=~TIM_SR_UIF;

	
}

void TIM4_IRQHandler(void){
	LDR_RGB();
				MIC_RGB();
					POT_RGB();

	TIM4->SR&=~TIM_SR_UIF;


}

void TIM1_UP_TIM10_IRQHandler (void){
	TL2();
	TIM10->SR&=~TIM_SR_UIF;

}


