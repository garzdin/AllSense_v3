/*******************************************************
© Copyright 2018 Teodor Garzdin

Project : AllSense v3
*******************************************************/

// I/O Registers definitions
#include <avr/io.h>
#include <avr/interrupt.h>

// USARTs initialization functions
#include "serial.h"

//
Serial::Serial(USART_t * usart, PORT_t * port) {
	cli();
	
	_usart = usart;
	_port = port;
	
	// Note: The correct PORTE direction for the RxD, TxD and XCK signals
	// is configured in the ports_init function.

	// Transmitter is enabled
	// Set TxD=1
	_port->OUTSET = 0x08;

	// Communication mode: Asynchronous USART
	// Data bits: 8
	// Stop bits: 1
	// Parity: Disabled
	_usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;

	// Receive complete interrupt: Disabled
	// Transmit complete interrupt: Disabled
	// Data register empty interrupt: Disabled
	_usart->CTRLA = (_usart->CTRLA & (~(USART_RXCINTLVL_gm | USART_TXCINTLVL_gm | USART_DREINTLVL_gm))) |
		USART_RXCINTLVL_LO_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;

	// Required Baud rate: 9600
	// Real Baud Rate: 9600.0 (x1 Mode), Error: 0.0 %
	_usart->BAUDCTRLA = 0x17;
	_usart->BAUDCTRLB = ((0x01 << USART_BSCALE_gp) & USART_BSCALE_gm) | 0x00;

	// Receiver: On
	// Transmitter: On
	// Double transmission speed mode: Off
	// Multi-processor communication mode: Off
	_usart->CTRLB = (_usart->CTRLB & (~(USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm | USART_MPCM_bm | USART_TXB8_bm))) |
		USART_RXEN_bm | USART_TXEN_bm;
	
	_rx_buffer_head = _rx_buffer_tail = 0;
	
	sei();
}

//
Serial::~Serial() {
	free(_usart);
	free(_port);
	free(_rx_buffer);
}

void Serial::recv() {
	uint8_t status = _usart->STATUS;
	if ((status & USART_RXCIF_bm) == 0) return;
	if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) == 0) {
		uint8_t c = _usart->DATA;
		uint8_t next = (_rx_buffer_tail + 1) % _MAX_RX_BUFF_SIZE;
		if (next != _rx_buffer_head) {
			_rx_buffer[_rx_buffer_tail] = c;
			_rx_buffer_tail = next;
		}
	}
}

void Serial::write(uint8_t byte) {
	if ((_usart->STATUS & USART_DREIF_bm) == 0) return;
	_usart->DATA = byte;
}

uint8_t Serial::read() {	
	if (_rx_buffer_head == _rx_buffer_tail) return -1;
	
	cli();
	
	uint8_t c = _rx_buffer[_rx_buffer_head];
	_rx_buffer_head = (_rx_buffer_head + 1) % _MAX_RX_BUFF_SIZE;
	
	sei();
	
	return c;
}

bool Serial::available()
{
	cli();
	
	uint8_t is_available = (_rx_buffer_tail + _MAX_RX_BUFF_SIZE - _rx_buffer_head) % _MAX_RX_BUFF_SIZE;
	
	sei();
	
	return is_available;
}
