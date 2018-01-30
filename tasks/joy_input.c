#include "joy_input.h"
#include "lpc_types.h"
#include "rgb.h"
#include "light.h"
#include "joystick.h"

void joy_input(void)
{
	uint8_t joy = joystick_read(); //read data from joystick



	if (joy & JOYSTICK_DOWN)
	{

		if(r_counter>0x01)
		{
		 r_counter--;
		}

	}


	if (joy & JOYSTICK_UP)
	{
		if(r_counter<0x0F)
		{   //g_counter <= 0x0A
		 r_counter++;
		}
	}


}





