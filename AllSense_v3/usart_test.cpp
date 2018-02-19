/*
 * usart_test.cpp
 *
 * Created: 2/19/2018 3:03:32 PM
 *  Author: Teodor
 */ 

/*******************************************************
USARTs initialization created by the
CodeWizardAVR V3.32 Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : AllSense v2
*******************************************************/

// I/O Registers definitions
#include <avr/io.h>

// USARTs initialization functions
#include "usart_test.h"

// USARTE0 initialization
void usarte0_init(void)
{
	// Note: The correct PORTE direction for the RxD, TxD and XCK signals
	// is configured in the ports_init function.

	// Transmitter is enabled
	// Set TxD=1
	PORTE.OUTSET = 0x08;

	// Communication mode: Asynchronous USART
	// Data bits: 8
	// Stop bits: 1
	// Parity: Disabled
	USARTE0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;

	// Receive complete interrupt: Disabled
	// Transmit complete interrupt: Disabled
	// Data register empty interrupt: Disabled
	USARTE0.CTRLA = (USARTE0.CTRLA & (~(USART_RXCINTLVL_gm | USART_TXCINTLVL_gm | USART_DREINTLVL_gm))) |
	USART_RXCINTLVL_OFF_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;

	// Required Baud rate: 600
	// Real Baud Rate: 600.0 (x1 Mode), Error: 0.0 %
	USARTE0.BAUDCTRLA = 0x17;
	USARTE0.BAUDCTRLB = ((0x01 << USART_BSCALE_gp) & USART_BSCALE_gm) | 0x00;

	// Receiver: On
	// Transmitter: On
	// Double transmission speed mode: Off
	// Multi-processor communication mode: Off
	USARTE0.CTRLB = (USARTE0.CTRLB & (~(USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm | USART_MPCM_bm | USART_TXB8_bm))) |
	USART_RXEN_bm | USART_TXEN_bm;
}

// Receive a character from USARTE0
char getchar_usarte0(void)
{
	char data;
	unsigned char status;

	while (1)
	{
		while (((status = USARTE0.STATUS) & USART_RXCIF_bm) == 0);
		data = USARTE0.DATA;
		if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) == 0) return data;
	}
}

// Write a character to the USARTE0 Transmitter
void putchar_usarte0(char c)
{
	while ((USARTE0.STATUS & USART_DREIF_bm) == 0);
	USARTE0.DATA = c;
}

