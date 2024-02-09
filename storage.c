#include "storage.h"
#include <string.h>
#include "LCD.h"
#include "USART.h"
#include "LEDs.h"
extern int result;
extern char morseinput[5];
extern char morseinput1[5];





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
	
	


void LDRmorse (void){
	
																result = strcmp(morseinput, morsecode_1); 
															if (result == 0) {
																printf("1");
																LCDprint4BIT('1');
																TL1();
															}
															result = strcmp(morseinput, morsecode_2); 
															if (result == 0) {
																printf("2");
																LCDprint4BIT('2');
																TL1();
															}
															result = strcmp(morseinput, morsecode_3); 
															if (result == 0) {
																printf("3");
																LCDprint4BIT('3');
																TL1();
															}
															result = strcmp(morseinput, morsecode_4); 
															if (result == 0) {
																printf("4");
																LCDprint4BIT('4');
																TL1();
															}
															result = strcmp(morseinput, morsecode_5); 
															if (result == 0) {
																printf("5");
																LCDprint4BIT('5');
																TL1();
															}
															result = strcmp(morseinput, morsecode_6); 
															if (result == 0) {
																printf("6");
																LCDprint4BIT('6');
																TL1();
															}
															result = strcmp(morseinput, morsecode_7); 
															if (result == 0) {
																printf("7");
																LCDprint4BIT('7');
																TL1();
															}
															result = strcmp(morseinput, morsecode_8); 
															if (result == 0) {
																printf("8");
																LCDprint4BIT('8');
																TL1();
															}
															result = strcmp(morseinput, morsecode_9); 
															if (result == 0) {
																printf("9");
																LCDprint4BIT('9');
																TL1();
															}
															result = strcmp(morseinput, morsecode_0); 
															if (result == 0) {
																printf("0");
																LCDprint4BIT('0');
																TL1();
															}
															result = strcmp(morseinput, morscode_space_words); 
															if (result == 0) {
																printf(" ");
																LCDprint4BIT(' ');
																TL1();
															}
		
		
		
		
		
		/**********************************************************************Now the letters ********************************************************************************/
		
		
		
		
		
															result = strcmp(morseinput, morsecode_A); 
															if (result == 0) {
																printf("A");
																LCDprint4BIT('A');
																TL1();
															}
															
																			result = strcmp(morseinput, morsecode_B); 
																			if (result == 0) {
																				printf("B");
																				LCDprint4BIT('B');
																				TL1();
																			}
														
																						result = strcmp(morseinput, morsecode_C); 
																						if (result == 0) {
																							printf("C");
																							TL1();
																						}
																
																									result = strcmp(morseinput, morsecode_D); 
																									if (result == 0) {
																										printf("D");
																										LCDprint4BIT('C');
																										TL1();
																									}
																
																											result = strcmp(morseinput, morsecode_E); 
																											if (result == 0) {
																												printf("E");
																												LCDprint4BIT('E');
																												TL1();
																											}
																								
																													result = strcmp(morseinput, morsecode_F); 
																													if (result == 0) {
																														printf("F");
																														LCDprint4BIT('F');
																														TL1();
																													}
																
																															result = strcmp(morseinput, morsecode_G); 
																															if (result == 0) {
																																printf("G");
																																LCDprint4BIT('G');
																																TL1();
																															}
															
																																	result = strcmp(morseinput, morsecode_H); 
																																	if (result == 0) {
																																		printf("H");
																																		LCDprint4BIT('H');
																																		TL1();
																																	}
															
																																			result = strcmp(morseinput, morsecode_I); 
																																			if (result == 0) {
																																				printf("I");
																																				LCDprint4BIT('I');
																																				TL1();
																																			}
															
																																					result = strcmp(morseinput, morsecode_J); 
																																					if (result == 0) {
																																						printf("J");
																																						LCDprint4BIT('J');
																																						TL1();
																																					}
																										
																																							result = strcmp(morseinput, morsecode_K); 
																																							if (result == 0) {
																																								printf("K");
																																								LCDprint4BIT('K');
																																								TL1();
																																							}
																																				
																																					result = strcmp(morseinput, morsecode_L); 
																																					if (result == 0) {
																																						printf("L");
																																						LCDprint4BIT('L');
																																						TL1();
																																					}
															
																																	result = strcmp(morseinput, morsecode_M); 
																																	if (result == 0) {
																																		printf("M");
																																		LCDprint4BIT('M');
																																		TL1();
																																	}
															
																														result = strcmp(morseinput, morsecode_N); 
																														if (result == 0) {
																															printf("N");
																															LCDprint4BIT('N');
																															TL1();
																														}
																										
																											result = strcmp(morseinput, morsecode_O); 
																											if (result == 0) {
																												printf("O");
																												LCDprint4BIT('O');
																												TL1();
																											}
																											
																								result = strcmp(morseinput, morsecode_P); 
																								if (result == 0) {
																									printf("P");
																									LCDprint4BIT('P');
																									TL1();
																								}
															
																					result = strcmp(morseinput, morsecode_Q); 
																					if (result == 0) {
																						printf("Q");
																						LCDprint4BIT('Q');
																						TL1();
																					}
															
																		result = strcmp(morseinput, morsecode_R); 
																		if (result == 0) {
																			printf("R");
																			LCDprint4BIT('R');
																			TL1();
																		}
									
															result = strcmp(morseinput, morsecode_S); 
															if (result == 0) {
																printf("S");
																LCDprint4BIT('S');
																TL1();
															}
													
													result = strcmp(morseinput, morsecode_T); 
													if (result == 0) {
														printf("T");
														LCDprint4BIT('T');
														TL1();
													}
										
											result = strcmp(morseinput, morsecode_U); 
											if (result == 0) {
												printf("U");
												LCDprint4BIT('U');
												TL1();
											}
									
									result = strcmp(morseinput, morsecode_V); 
									if (result == 0) {
										printf("V");
										LCDprint4BIT('V');
										TL1();
									}
					
							result = strcmp(morseinput, morsecode_W); 
							if (result == 0) {
								printf("W");
								LCDprint4BIT('W');
								TL1();
							}
						
				result = strcmp(morseinput, morsecode_Y); 
				if (result == 0) {
					printf("Y");
					LCDprint4BIT('Y');
					TL1();
				}
		
	result = strcmp(morseinput, morsecode_Z); 
	if (result == 0) {
		printf("Z");
		LCDprint4BIT('Z');
		TL1();
	}

																//************************ end of comparing elemnts, and printiong onto the terminal ************************// 
	
	
	
	
	
}
