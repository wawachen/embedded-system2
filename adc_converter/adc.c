#include "adc.h"

void adc_init (void)
{
	PINSEL_CFG_Type PinCfg;

	// Configure pin 23 on port 0 - the trimming pot is connected to this.
	// Take a look at page 7 of the schematic (which shows that the trimming
	// pot, labelled "Analog Input" is connected to GPIO_11, and then on
	// page 2 you can see that GPIO_11 (middle column) is P0.23 and also AD0.0
	// (Channel 0 of the ADC).
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 23;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);

	// To go to where a function is declared, select the name of the function,
	// right-click and select "Open Declaration" (or press F3).  These ADC functions
	// are in Lib_MCU/src/lpc17xx_adc.c

	// Configure ADC: 0.2 MHz
	ADC_Init(LPC_ADC, 200000);
	// Disable interrupt
	ADC_IntConfig(LPC_ADC,ADC_CHANNEL_0,DISABLE);
	// Enable ADC
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_0,ENABLE);
}

uint32_t adc_read(void)
{
	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	// The line below sits in an infinite while loop until data collection
	// is complete.  There is a fairly obvious risk here!
	while (!(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_0,ADC_DATA_DONE)));
	return ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
}
