#include "samd20.h"
#include "clock.h"

/* enable CLKGEN0 output on PB14 */
#define OUTEN_GEN0	1

#define OUTEN_GEN1	0
#define OUTEN_GEN2	0
#define OUTEN_GEN3	0
#define OUTEN_GEN4	0

/***************************************************************
Init and enable clock to all peripherals.
****************************************************************/

void main_clock_init (void)
{
	/* enable the xosc32k and set the start up time */
	SYSCTRL->XOSC32K.reg = SYSCTRL_XOSC32K_STARTUP(6) | SYSCTRL_XOSC32K_EN32K |
												 SYSCTRL_XOSC32K_XTALEN | SYSCTRL_XOSC32K_ENABLE;
	
	while (!SYSCTRL->PCLKSR.bit.XOSC32KRDY){}
	
	/* enable the generic clock GEN1 and configure the XOSC32K as clock source for it */
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK1 | GCLK_GENCTRL_SRC_XOSC32K | 
											GCLK_GENCTRL_GENEN | GCLK_GENCTRL_IDC;
	
	while (GCLK->STATUS.bit.SYNCBUSY){}
	
	/* Enable the DFLL and set the operation mode as closed loop */
  SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_ENABLE | SYSCTRL_DFLLCTRL_MODE;
  
  while(!SYSCTRL->PCLKSR.bit.DFLLRDY){}
		
  /* Load the Multiply factor, Coarse Step and fine Step for DFLL */
  SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_CSTEP(0x1F/4) | SYSCTRL_DFLLMUL_FSTEP(0xFF/4) |  
												 SYSCTRL_DFLLMUL_MUL(1465);
		
  /* Enable the Generic Clock GEN 1 as DFLL48 as Reference */ 
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK1 | GCLK_CLKCTRL_ID(0);
  /* wait for fine lock */
  while(!SYSCTRL->PCLKSR.bit.DFLLLCKF){}
		
  /* Set the NVM Read Wait States to 1, Since the operating frequency 48 MHz */
  NVMCTRL->CTRLB.bit.RWS = 1;
		
  /*  Enable the Generic Clock 0 and Configure the DFLL as Clock Source for it*/
  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK0 | GCLK_GENCTRL_SRC_DFLL48M |  GCLK_GENCTRL_GENEN | 
											GCLK_GENCTRL_IDC;
  
  while(GCLK->STATUS.bit.SYNCBUSY){}		
}

void port_clock_init (void)
{

}

void tc_clock_init (void)
{

}

void uart_clock_init (void)
{

}
