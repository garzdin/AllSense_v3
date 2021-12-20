/*******************************************************
© Copyright 2018 Teodor Garzdin

Project : AllSense v3
*******************************************************/

// I/O Registers definitions
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// USARTs initialization functions
#include "serial.h"

usart_to_port_t usart_to_port[_NUMBER_OF_SERIALS] = {
	{
		.usart = &USARTC0,
		.port = &PORTC,
	},
	{
		.usart = &USARTC1,
		.port = &PORTC,
	},
	{
		.usart = &USARTE0,
		.port = &PORTE,
	},
	{
		.usart = &USARTD0,
		.port = &PORTD,
	},
	{
		.usart = &USARTD1,
		.port = &PORTD,
	}
};

//
Serial::Serial(USART_t * usart, uint32_t baud, uint32_t f_cpu) {
	_usart = usart;
	
	for (uint8_t i = 0; i < _NUMBER_OF_SERIALS; i++) {
		if (usart_to_port[i].usart == usart) _port = usart_to_port[i].port;
	}
	
	if (!baud) _baud = F_BAUD;
	
	cli();
	
	// Note: The correct PORTE direction for the RxD, TxD and XCK signals
	// is configured in the ports_init function.

	// Transmitter is enabled
	// Set TxD=1
	_port->OUTSET = USART_TXEN_bm;

	// Communication mode: Asynchronous USART
	// Data bits: 8
	// Stop bits: 1
	// Parity: Disabled
	_usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;

	// Receive complete interrupt: Enabled
	// Transmit complete interrupt: Enabled
	// Data register empty interrupt: Disabled
	_usart->CTRLA = (_usart->CTRLA & (~(USART_RXCINTLVL_gm | USART_TXCINTLVL_gm | USART_DREINTLVL_gm))) |
		USART_RXCINTLVL_LO_gc | USART_TXCINTLVL_LO_gc | USART_DREINTLVL_OFF_gc;

	// Required Baud rate: 115200
	// Real Baud Rate: 115200.0 (x1 Mode), Error: 0.0 %
	_usart->BAUDCTRLA = (BSEL(f_cpu, baud) & 0xff);
	_usart->BAUDCTRLB = (((BSCALE(f_cpu, baud) << USART_BSCALE_gp) & USART_BSCALE_gm) | (BSEL(f_cpu, baud) >> 8));

	// Receiver: On
	// Transmitter: On
	// Double transmission speed mode: Off
	// Multi-processor communication mode: Off
	_usart->CTRLB = (_usart->CTRLB & (~(USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm | USART_MPCM_bm | USART_TXB8_bm))) |
		USART_RXEN_bm | USART_TXEN_bm;
	
	sei();
	
	_rx_buffer = new Buffer(256);
	_tx_buffer = new Buffer(256);
}

//
Serial::~Serial() {
	free(_usart);
	free(_port);
	free(_rx_buffer);
	free(_tx_buffer);
}

void Serial::recv() {
	uint8_t status = _usart->STATUS;
	if ((status & USART_RXCIF_bm) == 0) return;
	if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) == 0) {
		uint8_t c = _usart->DATA;
		_rx_buffer->put(c);
	}
}

void Serial::send() {
	uint8_t status = _usart->STATUS;
	if ((status & USART_TXCIF_bm) == 0) return;
	if (!_tx_buffer->empty()) {
		uint8_t c = _tx_buffer->get();
		_usart->DATA = c;
	}
}

void Serial::write(uint8_t byte) {
	if ((_usart->STATUS & USART_DREIF_bm) == 0) {
		_tx_buffer->put(byte);
	} else {
		_usart->DATA = byte;
	}
}

uint8_t Serial::read() {	
	return _rx_buffer->get();
}

bool Serial::available()
{
	return !_rx_buffer->empty();
}
