/*
 * AllSense_v3.cpp
 *
 * Created: 2/19/2018 1:07:10 PM
 * Author : Teodor
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "main.h"
#include "event_system_init.h"
#include "clock_init.h"
#include "ports_init.h"
#include "serial.h"

Serial debug(&USARTE0, F_BAUD, F_CPU);
Serial gsm(&USARTC0, F_BAUD, F_CPU);

int main(void)
{
	// Interrupt system initialization
	// Make sure the interrupts are disabled
	cli();
	// Low level interrupt: On
	// The interrupt vectors will be placed at the start of the Application FLASH section
	PMIC.CTRL = (PMIC.CTRL & (~(PMIC_RREN_bm | PMIC_IVSEL_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm))) | PMIC_LOLVLEN_bm;

	// System clocks initialization
	system_clocks_init();

	// Event system initialization
	event_system_init();

	// Ports initialization
	ports_init();

	// Virtual Ports initialization
	vports_init();
	
	// Enable interrupts
	sei();
	
    /* Replace with your application code */
    while (1) 
    {	
		loop();
    }
}

void loop() {
	debug.write('I');
	debug.write('n');
	debug.write('i');
	debug.write('t');
	debug.write('\r');
	debug.write('\n');
	
	gsm.write('A');
	gsm.write('T');
	gsm.write('\r');
	
	while (gsm.available()) {
		debug.write(gsm.read());
	}
}

ISR(USARTE0_RXC_vect)
{
	debug.recv();
}

ISR(USARTE0_TXC_vect) {
	debug.send();
}
