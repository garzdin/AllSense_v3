/*******************************************************
© Copyright 2018 Teodor Garzdin

Project : AllSense v3
*******************************************************/

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <avr/io.h>

#ifndef _MAX_RX_BUFF_SIZE
#define _MAX_RX_BUFF_SIZE 256 // RX buffer size
#endif

class Serial
{	
	public:
		Serial(USART_t * usart, PORT_t * port);
		~Serial();

		// Interrupt handler
		void recv();
		
		void write(uint8_t byte);
		uint8_t read();
		bool available();
	
	private:
		USART_t * _usart;
		PORT_t * _port;
		uint8_t _rx_buffer[_MAX_RX_BUFF_SIZE];
		volatile uint8_t _rx_buffer_tail;
		volatile uint8_t _rx_buffer_head;
};

#endif
