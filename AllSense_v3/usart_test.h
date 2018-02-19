/*
 * usart_test.h
 *
 * Created: 2/19/2018 3:06:38 PM
 *  Author: Teodor
 */ 


#ifndef USART_TEST_H_
#define USART_TEST_H_

// USARTE0 receive function
char getchar_usarte0(void);
// USARTE0 transmit function
void putchar_usarte0(char c);
// USARTE0 initialization
void usarte0_init(void);

#endif /* USART_TEST_H_ */