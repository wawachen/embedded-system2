#include "lpc17xx_timer.h"
#include "../adc/adc.h"
#include "rgb.h"

void timer0_init(void)
{
	// See p63-64 of the LPC1769 manual for a description
	// of the PCONP register.
	LPC_SC->PCONP |= 1 << 1;

	// p502-3 for the TCR (timer control register).
	// Why is it being set to 2 here?
	LPC_TIM0->TCR = 2;

	// These lines control the timer.
	// PR is the "prescale register" - the timer counter register increments
	// every time the timer reaches this value.
	LPC_TIM0->PR  = 250 - 1;
	// MR0 is one of the four "match registers" - when the timer counter
	// reaches this value, something happens (what that something is, is
	// defined by the "match control register").
	LPC_TIM0->MR0 = 5 - 1;
	// The "match control register" is on p505 of the manual.
	// Setting bit 0 means the interrupt service routine TIMER0_IRQHandler
	// is called when MR0 and TC (the timer counter) have the same value,
	// setting bit 1 means the timer counter is reset to zero.
	LPC_TIM0->MCR |= (1<<0 | 1<<1);

	// A note on timing: the processor operates at 100 MHz, and the timer
	// updates every four processor cycles, i.e. at 25 MHz.  The frequency
	// of the interrupt is therefore 25e6 / PR * MR0, or 1 Hz.  If you run this
	// code unaltered, the RGB LED will update every second, precisely.

	// Enable interrupts.
	NVIC_EnableIRQ(TIMER0_IRQn);

	// Why is the TCR being set to 1 here?
	LPC_TIM0->TCR = 1;
}


void TIMER0_IRQHandler(void)
{
	// static variables maintain their value between function calls
	static uint8_t colour = RGB_GREEN;
	uint32_t reading = 0;
	// Store the current state of the timer interrupt register
	uint8_t ir = LPC_TIM0->IR;

	if (ir & (1<<0))  // Interrupt generated from MR0 (bit 0 set)
	{
		LPC_TIM0->IR |= (1<<0); // Clear the interrupt register (write 1 to bit 0)

		reading = adc_read();
		printf("the adc value is %d \n", reading);
		if (reading > 2000)
		{
		colour = RGB_RED;
					}
		else
		{
		colour = RGB_BLUE;
					}

		rgb_setLeds(colour);

		static uint16_t on;
		on = reading;
		uint16_t   off = ~on;
	    pca9532_setLeds(on, off);




	 }
}
