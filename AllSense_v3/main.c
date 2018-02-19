/*******************************************************
This program was created by the CodeWizardAVR V3.32
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : AllSense v2
Version : 0.1
Date    : 2/17/2018
Author  : Teodor Garzdin
Company :
Comments:


Chip type               : ATxmega32A4U
Program type            : Application
AVR Core Clock frequency: 7.372800 MHz
Memory model            : Small
Data Stack size         : 1024
*******************************************************/

// I/O Registers definitions
#include <xmega32a4u.h>

// Standard Input/Output functions
#include <stdio.h>

// Clock System initialization function
#include "clock_init.h"

// Event System initialization function
#include "event_system_init.h"

// I/O Ports initialization function
#include "ports_init.h"

// USARTs initialization functions
#include "usarts_init.h"

// Declare your global variables here

void main(void)
{
	// Declare your local variables here
	unsigned char n;

	// Check the reset source
	n = RST.STATUS;
	if (n & RST_PORF_bm)
		{
		// Power on reset

		}
	else if (n & RST_EXTRF_bm)
		{
		// External reset

		}
	else if (n & RST_BORF_bm)
		{
		// Brown out reset

		}
	else if (n & RST_WDRF_bm)
		{
		// Watchdog reset

		}
	else if (n & RST_PDIRF_bm)
		{
		// Program and debug interface reset

		}
	else if (n & RST_SRF_bm)
		{
		// Software reset

		}
	// Clear the reset flag
	RST.STATUS = n;

	// Interrupt system initialization
	// Optimize for speed
#pragma optsize-
	// Make sure the interrupts are disabled
#asm("cli")
	// Low level interrupt: On
	// Round-robin scheduling for low level interrupt: On
	// Medium level interrupt: On
	// High level interrupt: On
	// The interrupt vectors will be placed at the start of the Application FLASH section
	n = (PMIC.CTRL & (~(PMIC_RREN_bm | PMIC_IVSEL_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm))) |
		PMIC_LOLVLEN_bm | PMIC_RREN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	CCP = CCP_IOREG_gc;
	PMIC.CTRL = n;
	// Set the default priority for round-robin scheduling
	PMIC.INTPRI = 0x00;
	// Restore optimization for size if needed
#pragma optsize_default

	// System clocks initialization
	system_clocks_init();

	// Event system initialization
	event_system_init();

	// Ports initialization
	ports_init();

	// Virtual Ports initialization
	vports_init();

	// USARTE0 initialization
	usarte0_init();

	// Globally enable interrupts
#asm("sei")

	while (1)
		{
			// Place your code here
			//putchar_usarte0('W');
			//putchar_usarte0('a');
			//putchar_usarte0('i');
			//putchar_usarte0('t');
			//putchar_usarte0('i');
			//putchar_usarte0('n');
			//putchar_usarte0('g');
			//putchar_usarte0('.');
			//putchar_usarte0('.');
			//putchar_usarte0('.');
			//putchar_usarte0('\r');
			//putchar_usarte0('\n');
			//char c = getchar_usarte0();
			//switch(c) {
				//case 'H':
					//putchar_usarte0('H');
					//putchar_usarte0('e');
					//putchar_usarte0('l');
					//putchar_usarte0('l');
					//putchar_usarte0('o');
					//putchar_usarte0('\r');
					//putchar_usarte0('\n');
				//break;
				//default:
					//putchar_usarte0('W');
					//putchar_usarte0('i');
					//putchar_usarte0('t');
					//putchar_usarte0('i');
					//putchar_usarte0('n');
					//putchar_usarte0('g');
					//putchar_usarte0('.');
					//putchar_usarte0('.');
					//putchar_usarte0('.');
					//putchar_usarte0('\r');
					//putchar_usarte0('\n');
				//break;
			//}
		}
}
