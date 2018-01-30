#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"
#include "pca9532.h"

#include "LPC17xx.h"
#include "lpc_types.h"

#include "../scheduler/ttc_scheduler_o.h"
#include "../tasks/light.h"
#include "../tasks/joy_input.h"
#include "../tasks/rotary_input.h"



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
	pca9532_setBlink0Leds(0xAA00);
	// Set timer 0 to have a very high frequency (151, or 0x97, is 1 Hz)
	// See pca9532.c in Lib_EaBaseBoard for full details.
	pca9532_setBlink0Period(0x01);
	// Set four LEDs to be controlled by timer 1:
	//   0x5500 = 0101010100000000
	pca9532_setBlink1Leds(0x5500);
	pca9532_setBlink1Period(0x01);
	// The other eight bits will be turned on and off by the timer ISR.
	// The timer ISR will also adjust the duty cycle for the two timers
	// which makes the LEDs they control fade up and down.

	SCH_Init();

    SCH_Add_Task(other_light, 0, 10); //100
    SCH_Add_Task(pwm_light, 5, 10);    //10
    SCH_Add_Task(joy_input,3,100);
    SCH_Add_Task(rotary_input,2,50);

    SCH_Start();


    while(1)
    {
    	SCH_Dispatch_Tasks();
    }

}

void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
