/*******************************************************
© Copyright 2018 Teodor Garzdin

Project : AllSense v3
*******************************************************/

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <avr/io.h>

#include "buffer.h"

#define F_CPU 7378200UL
#define F_BAUD 115200UL

#define _BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,bscale) (                \
((bscale) < 0) ?                                                      \
(int)((((float)(f_cpu)/(16*(float)(baud)))-1)*(1/1<<-(bscale)))        \
: (int)((float)(f_cpu)/((1<<(bscale))*16*(float)(baud)))-1 )

#define _BSCALE(f_cpu,baud) (                                         \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,-7) < 4096) ? -7 :              \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,-6) < 4096) ? -6 :              \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,-5) < 4096) ? -5 :              \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,-4) < 4096) ? -4 :              \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,-3) < 4096) ? -3 :              \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,-2) < 4096) ? -2 :              \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,-1) < 4096) ? -1 :              \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,0) < 4096) ? 0 :                \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,1) < 4096) ? 1 :                \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,2) < 4096) ? 2 :                \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,3) < 4096) ? 3 :                \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,4) < 4096) ? 4 :                \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,5) < 4096) ? 5 :                \
(_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,6) < 4096) ? 6 :                \
7 )

#define BSEL(f_cpu,baud)                                              \
_BAUD_BSEL_FROM_BAUDSCALE(f_cpu,baud,_BSCALE(f_cpu,baud))

#define BSCALE(f_cpu,baud) ((_BSCALE(f_cpu,baud)<0) ? (16+_BSCALE(f_cpu,baud)) : _BSCALE(f_cpu,baud))

#ifndef _MAX_RX_BUFF_SIZE
#define _MAX_RX_BUFF_SIZE 256 // RX buffer size
#endif

#define _NUMBER_OF_SERIALS 5

struct usart_to_port_s {
	USART_t * usart;
	PORT_t * port;
};

typedef struct usart_to_port_s usart_to_port_t;

extern usart_to_port_t usart_to_port[];

class Serial
{	
	public:
		Serial(USART_t * usart, uint32_t baud, uint32_t f_cpu);
		~Serial();

		// Interrupt handler
		void recv();
		void send();
		
		void write(uint8_t byte);
		uint8_t read();
		bool available();
	
	private:
		USART_t * _usart;
		PORT_t * _port;
		uint32_t _baud;
		Buffer * _rx_buffer;
		Buffer * _tx_buffer;
};

#endif
