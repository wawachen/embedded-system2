#include "pca9532.h"
#include <stdint.h>

uint8_t  duty_MAX = 1;
uint16_t r_counter=0x0A;


void other_light(void)
{
    static uint16_t counter = 0x00;
    static uint16_t on = 0x0001;
    uint16_t   off = ~on & 0x00FF;

    if(counter == r_counter)
    {

	pca9532_setLeds(on, off);
	on <<= 1;
	if (on == 0x0100) on = 0x0001;
	counter=0;
    }

    else {counter++;}

}


void pwm_light(void)
{
	static int8_t   increment = 1;
	static uint16_t duty = 0;
	pca9532_setBlink0Duty(duty);
	pca9532_setBlink1Duty(100-duty);

	duty += increment;
	if ((duty == duty_MAX) || (duty == 0)) increment *= -1;


}


