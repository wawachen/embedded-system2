#ifndef ADC_HEADER
#define ADC_HEADER

#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include <LPC17xx.h>

void adc_init(void);
uint32_t adc_read(void);

#endif
