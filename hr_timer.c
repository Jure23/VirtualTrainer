#include "hr_timer.h"
#include "samd20.h"
#include "types.h"
#include <math.h>



void tc0_init (void)
{
	/* GCLK1 - 1MHz / 100 = 10kHz, increase counter with prescaler clck 10kHz / 256 = 39Hz */
	GCLK->GENDIV.reg = GCLK_GENDIV_ID_GCLK1 | GCLK_GENDIV_DIV(100);
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK1 | GCLK_GENCTRL_SRC_OSC8M |  GCLK_GENCTRL_GENEN;
	GCLK->CLKCTRL.reg |= GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_TC0_TC1 | GCLK_CLKCTRL_GEN_GCLK1;
	/* enable clock power to PM module */
	PM->APBCMASK.reg = PM_APBCMASK_TC0;
	/* pure tc0 init */
	//TC0->COUNT16.CC[0].reg = 0XFFFF;
	//TC0->COUNT16.CTRLA.reg = TC_CTRLA_ENABLE | TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV256 | TC_CTRLA_PRESCSYNC_PRESC;
}

void start_hr_timer (void)
{
	TC0->COUNT16.COUNT.reg = 0;
	TC0->COUNT16.CTRLA.reg = TC_CTRLA_ENABLE;
}

UINT16 stop_hr_timer (void)
{
	UINT16 stop_cnt_val;
	
	TC0->COUNT16.CTRLA.reg ^= TC_CTRLA_ENABLE;
	stop_cnt_val = TC0->COUNT16.COUNT.reg;
	
	return stop_cnt_val;
}

void hr_pin_config (void)
{
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_EIC;
	PORT->Group[1].PINCFG[14].reg |= 0x01;
	
	EIC->CTRL.reg |= 0x02; //poglej ae kaj moraa zapisati za lepai enable
	EIC->INTENSET.reg = EIC_INTENSET_EXTINT14;
	EIC->CONFIG[1].reg = EIC_CONFIG_SENSE6_RISE;
	/* enable 32kHz clock on module */
	SYSCTRL->XOSC32K.reg = SYSCTRL_XOSC32K_ENABLE | SYSCTRL_XOSC32K_XTALEN | SYSCTRL_XOSC32K_EN32K; 
}




