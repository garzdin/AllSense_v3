/*******************************************************
Event System initialization created by the
CodeWizardAVR V3.32 Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : AllSense v2
*******************************************************/

// I/O Registers definitions
#include <avr/io.h>

// Event System initialization
void event_system_init(void)
{
	// Event System Channel 0 source: None
	EVSYS.CH0MUX = EVSYS_CHMUX_OFF_gc;
	// Event System Channel 1 source: None
	EVSYS.CH1MUX = EVSYS_CHMUX_OFF_gc;
	// Event System Channel 2 source: None
	EVSYS.CH2MUX = EVSYS_CHMUX_OFF_gc;
	// Event System Channel 3 source: None
	EVSYS.CH3MUX = EVSYS_CHMUX_OFF_gc;
	// Event System Channel 4 source: None
	EVSYS.CH4MUX = EVSYS_CHMUX_OFF_gc;
	// Event System Channel 5 source: None
	EVSYS.CH5MUX = EVSYS_CHMUX_OFF_gc;
	// Event System Channel 6 source: None
	EVSYS.CH6MUX = EVSYS_CHMUX_OFF_gc;
	// Event System Channel 7 source: None
	EVSYS.CH7MUX = EVSYS_CHMUX_OFF_gc;

	// Event System Channel 0 Digital Filter Coefficient: 1 Sample
	// Quadrature Decoder: Off
	EVSYS.CH0CTRL = (EVSYS.CH0CTRL & (~(EVSYS_QDIRM_gm | EVSYS_QDIEN_bm | EVSYS_QDEN_bm | EVSYS_DIGFILT_gm))) |
					EVSYS_DIGFILT_1SAMPLE_gc;
	// Event System Channel 1 Digital Filter Coefficient: 1 Sample
	EVSYS.CH1CTRL = EVSYS_DIGFILT_1SAMPLE_gc;
	// Event System Channel 2 Digital Filter Coefficient: 1 Sample
	// Quadrature Decoder: Off
	EVSYS.CH2CTRL = (EVSYS.CH2CTRL & (~(EVSYS_QDIRM_gm | EVSYS_QDIEN_bm | EVSYS_QDEN_bm | EVSYS_DIGFILT_gm))) |
					EVSYS_DIGFILT_1SAMPLE_gc;
	// Event System Channel 3 Digital Filter Coefficient: 1 Sample
	EVSYS.CH3CTRL = EVSYS_DIGFILT_1SAMPLE_gc;
	// Event System Channel 4 Digital Filter Coefficient: 1 Sample
	// Quadrature Decoder: Off
	EVSYS.CH4CTRL = (EVSYS.CH4CTRL & (~(EVSYS_QDIRM_gm | EVSYS_QDIEN_bm | EVSYS_QDEN_bm | EVSYS_DIGFILT_gm))) |
					EVSYS_DIGFILT_1SAMPLE_gc;
	// Event System Channel 5 Digital Filter Coefficient: 1 Sample
	EVSYS.CH5CTRL = EVSYS_DIGFILT_1SAMPLE_gc;
	// Event System Channel 6 Digital Filter Coefficient: 1 Sample
	EVSYS.CH6CTRL = EVSYS_DIGFILT_1SAMPLE_gc;
	// Event System Channel 7 Digital Filter Coefficient: 1 Sample
	EVSYS.CH7CTRL = EVSYS_DIGFILT_1SAMPLE_gc;

	// Event System Channel output: Disabled
	PORTCFG.CLKEVOUT &= ~PORTCFG_EVOUT_gm;
	PORTCFG.EVOUTSEL &= ~PORTCFG_EVOUTSEL_gm;
}

