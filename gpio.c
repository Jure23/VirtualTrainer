#include "samd20.h"
#include "gpio.h"
#include "types.h"

/*
PORT	0 = PA
			1 = PB
PIN		1...31
FUNC	0 = A
			1 = B
			2 = C...
*/
BOOL set_pin_mux (UINT8 port, UINT8 pin, UINT8 func)
{
	
	return TRUE;
}


/*
PORT	0 = PA
			1 = PB
PIN		0...31
*/

BOOL set_pin_out (UINT8 port, UINT8 pin)
{
	if (port == 0)
	{
		PORT->Group[0].DIRSET.reg |= (1 << pin);
	}
	else 
	{
		PORT->Group[1].DIRSET.reg |= (1 << pin);
	}
	
	return TRUE;
}


/*
PORT	0 = PA
			1 = PB
PIN		0...31
*/

BOOL set_pin_in (UINT8 port, UINT8 pin)
{
	if (port == 0)
	{
		PORT->Group[0].DIRCLR.reg |= (1 << pin);
	}
	else 
	{
		PORT->Group[1].DIRCLR.reg |= (1 << pin);
	}
	
	return TRUE;
}

/*
PORT	0 = PA
			1 = PB
PIN		0...31
*/

BOOL toggle_pin (UINT8 port, UINT8 pin)
{
	if (port == 0)
	{
		PORT->Group[0].DIRTGL.reg |= (1 << pin);
	}
	else 
	{
		PORT->Group[1].DIRTGL.reg |= (1 << pin);
	}
	
	return TRUE;
}

BOOL set_pin_state (UINT8 port, UINT8 pin, UINT8 state)
{
	switch (state)
	{
		case 0:
			
			if (port == 0)
			{
				PORT->Group[0].OUTCLR.reg |= (1 << pin);
			}
			else 
			{
				PORT->Group[1].OUTCLR.reg |= (1 << pin);
			}
			break;
			
		case 1:
			
			if (port == 0)
			{
				PORT->Group[0].OUTSET.reg |= (1 << pin);
			}
			else 
			{
				PORT->Group[1].OUTSET.reg |= (1 << pin);
			}
			break;
			
		default:
			
			return FALSE;
	}
	return TRUE;
}