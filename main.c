#include "samd20.h"
#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "trp868_uart.h"
#include "hr_timer.h"
#include "Delay.h"

#include <stdio.h> 
#include <string.h>
#include <math.h>

/**************** private functions prototypes ***********/

void calc_pulse (void);
void EIC_Handler(void);
/*********************************************************/

/**************** data structures ************************/

struct heart_rate
{
	UINT16 pulse;
	UINT16 timer_new_val;
	UINT16 timer_old_val;
}; 
struct heart_rate hr_data;
/*********************************************************/

/**************** IRQ_Handlers ***************************/

void EIC_Handler(void)
{
	NVIC_DisableIRQ(4);
	hr_data.timer_new_val = TC0->COUNT16.COUNT.reg;
	TC0->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;

	TC0->COUNT16.CTRLA.reg = TC_CTRLA_ENABLE;
	
	//start_hr_timer();
	EIC->INTFLAG.reg = EIC_INTFLAG_EXTINT14;
	//TC0->COUNT16.COUNT.reg = 0;
	NVIC_EnableIRQ(4);
}
/*********************************************************/

/**************** private functions **********************/

void calc_pulse (void)
{
	UINT16 dif;
	double time;
	double pulse;
	dif = hr_data.timer_new_val - hr_data.timer_old_val;
	time = (dif / 39);
	pulse = (60 / time);
	hr_data.pulse = round(pulse);
	
	hr_data.timer_old_val = hr_data.timer_new_val;
}
/*********************************************************/


int main(void)
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	/* config RF module to send data */
	trp868_init();
	
	/* config HR module */
	hr_pin_config();
	tc0_init();
	//TC0->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE | TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV256 | TC_CTRLA_PRESCSYNC_PRESC;

	
	/* enable EIC interrupts */
	NVIC_EnableIRQ(4);

	while(1)
	{
		
		if (hr_data.timer_new_val != hr_data.timer_old_val)
		{
			//char out_buff[100];
			//UINT16 lenght;
			calc_pulse();
			//memset(out_buff, 0, 100);
			//snprintf(out_buff, 100, "%d BPM \n", hr_data.pulse);
			//trp868_write (out_buff,  strlen(out_buff) );
		}


		/* user loop */
	}
	
}

