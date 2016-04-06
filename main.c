#include "samd20.h"
#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "trp868_uart.h"
#include "hr_timer.h"

#include <stdio.h> 
#include <string.h>
#include <math.h>


volatile uint32_t msTicks;

/**************** data structures ************************/


/*********************************************************/

/**************** Delay function *************************/
void SysTick_Handler(void)
{
	msTicks++;
}

static void Delay (UINT32 dlyTicks)
{
	uint32_t curTicks;
	
	curTicks = msTicks;
	while ((msTicks - curTicks) < dlyTicks);
}

/*********************************************************/
/**************** IRQ_Handlers ***************************/

void EIC_Handler(void)
{
	NVIC_DisableIRQ(4);
	
	EIC->INTFLAG.reg = EIC_INTFLAG_EXTINT14;
	NVIC_EnableIRQ(4);
}
/*********************************************************/

/**************** private functions **********************/


/*********************************************************/


int main(void)
{
	SystemCoreClockUpdate();
	main_clock_init();
	SysTick_Config(SystemCoreClock/1000);
	
	PORT->Group[1].DIRSET.reg = PORT_PB00;
	
	while(1)
	{
		
		//Delay(1000);
		PORT->Group[1].OUTTGL.reg = PORT_PB00;
		//Delay(1000);
		


		/* user loop */
	}
	
}

