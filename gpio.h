#ifndef _GPIO_H_
#define _GPIO_H_

#include "types.h"

BOOL set_pin_out (UINT8 port, UINT8 pin);
BOOL set_pin_in (UINT8 port, UINT8 pin);
BOOL toggle_pin (UINT8 port, UINT8 pin);
BOOL set_pin_state (UINT8 port, UINT8 pin, UINT8 state);

#endif /*_GPIO_H_*/
