#ifndef __HR_TIMER_H__
#define __HR_TIMER_H__

#include "types.h"

/************************* data structures ******************/

struct heart_rate
{
	UINT16 pulse;
	UINT16 timer_new_val;
	UINT16 timer_old_val;
}; 
struct heart_rate hr_data;

/************************************************************/

void tc0_init (void);
void start_hr_timer (void);
UINT16 stop_hr_timer (void);
void hr_pin_config (void);


#endif /* __HR_TIMER_H__ */