#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
#include "led7seg.h"
#include "rotary.h"
#include <stdint.h>
#include "light.h"

void rotary_input (void) {

          uint8_t state  = 0;
          state = rotary_read();

        if (state != ROTARY_WAIT)
        {

            if (state == ROTARY_RIGHT)
            {
            	if(duty_MAX<100){
            	duty_MAX+=10;
            	}
            }
            else
            {
            	  if (duty_MAX>10)
            	  {
            		 duty_MAX-=10;
            	   }
            }

        }

}

