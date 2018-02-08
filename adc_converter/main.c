#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "timer.h"
#include "rgb.h"
#include "../adc/adc.h"


int main (void)
{
	PINSEL_CFG_Type PinCfg;

		/* Initialize I2C2 pin connect */
		PinCfg.Funcnum = 2;
		PinCfg.Pinnum = 10;
		PinCfg.Portnum = 0;
		PINSEL_ConfigPin(&PinCfg);
		PinCfg.Pinnum = 11;
		PINSEL_ConfigPin(&PinCfg);

		// Initialize I2C peripheral
		I2C_Init(LPC_I2C2, 100000);

		/* Enable I2C1 operation */
		I2C_Cmd(LPC_I2C2, ENABLE);

		pca9532_init();

		// The PCA9532 can control 16 LEDs and has two internal PWM timers
		// so some or all of them can be made to blink or fade.
		// Set four LEDs to be controlled by timer 0:
		//   0xAA00 = 1010101000000000

        rgb_init();
        adc_init();
        timer0_init();

        while(1)
        {
            }
}

void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
