/*******************************************************
System clock initialization created by the
CodeWizardAVR V3.32 Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : AllSense v2
*******************************************************/

// I/O Registers definitions
#include <avr/interrupt.h>
#include <avr/io.h>

// System Clocks initialization
void system_clocks_init(void)
{
	unsigned char n, s;

	// Save interrupts enabled/disabled state
	s = SREG;
	// Disable interrupts

	// External 7372.800 kHz oscillator initialization
	// Crystal oscillator increased drive current: Off
	// External Clock Source - Startup Time: 0.4-16 MHz Quartz Crystal - 16k CLK
	OSC.XOSCCTRL = OSC_FRQRANGE_2TO9_gc | OSC_XOSCSEL_XTAL_16KCLK_gc;
	// Enable the external oscillator/clock source
	OSC.CTRL |= OSC_XOSCEN_bm;
	// Wait for the external oscillator to stabilize
	while ((OSC.STATUS & OSC_XOSCRDY_bm) == 0);

	// System Clock prescaler A division factor: 1
	// System Clock prescalers B & C division factors: B:1, C:1
	// ClkPer4: 7372.800 kHz
	// ClkPer2: 7372.800 kHz
	// ClkPer:  7372.800 kHz
	// ClkCPU:  7372.800 kHz
	n = (CLK.PSCTRL & (~(CLK_PSADIV_gm | CLK_PSBCDIV1_bm | CLK_PSBCDIV0_bm))) |
		CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc;
	CCP = CCP_IOREG_gc;
	CLK.PSCTRL = n;

	// Select the system clock source: External Oscillator or Clock
	n = (CLK.CTRL & (~CLK_SCLKSEL_gm)) | CLK_SCLKSEL_XOSC_gc;
	CCP = CCP_IOREG_gc;
	CLK.CTRL = n;

	// Disable the unused oscillators: 32 kHz, 2 MHz, 32 MHz, PLL
	OSC.CTRL &= ~(OSC_RC32KEN_bm | OSC_RC2MEN_bm | OSC_RC32MEN_bm | OSC_PLLEN_bm);

	// ClkPer output disabled
	PORTCFG.CLKEVOUT &= ~(PORTCFG_CLKOUTSEL_gm | PORTCFG_CLKOUT_gm);
	// PLL fault detection: Off
	// External clock source failure detection: On
	n = (OSC.XOSCFAIL & (~(OSC_PLLFDEN_bm | OSC_XOSCFDEN_bm))) | OSC_XOSCFDEN_bm;
	CCP = CCP_IOREG_gc;
	OSC.XOSCFAIL = n;

	// Restore interrupts enabled/disabled state
	SREG = s;
}

// Oscillator failure non-maskable interrupt
ISR(OSC_OSCF_vect)
{
	if (OSC.XOSCFAIL & OSC_XOSCFDIF_bm)
		{
		// External clock source failure detected
		// Clear the failure detection interrupt flag
		OSC.XOSCFAIL |= OSC_XOSCFDIF_bm;
		// Write your code here

		}
}

