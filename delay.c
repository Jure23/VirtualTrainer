#include "samd20.h"
#include "delay.h"
#include "types.h"

volatile uint32_t msTicks;


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

