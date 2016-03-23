#include "trp868_uart.h"
#include "samd20.h"
#include "types.h"

void trp868_init (void)
{
	/* mux enable on PB08 and PB09 */
	PORT->Group[1].PINCFG[8].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[1].PINCFG[9].reg = PORT_PINCFG_PMUXEN;
	/* select peripheral function D for PB08 and PB09 */
	PORT->Group[1].PMUX[4].reg = PORT_PMUX_PMUXE_D | PORT_PMUX_PMUXO_D;
	/* enable power clocl for sercom4 */
	PM->APBCMASK.reg = PM_APBCMASK_SERCOM4;
	/* enable generic clock for sercom */
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM4_CORE;
	/*  sercom init */
	SERCOM4->USART.CTRLB.reg = SERCOM_USART_CTRLB_TXEN;
	/* current BAUDRATE 1200 */
	SERCOM4->USART.BAUD.reg =  0xFB15;
	SERCOM4->USART.CTRLA.reg = SERCOM_USART_CTRLA_MODE_USART_INT_CLK | SERCOM_USART_CTRLA_ENABLE | SERCOM_USART_CTRLA_DORD;
}

BOOL trp868_write (char * buff,  UINT16 lenght )
{
	int pos = 0;
	
	while (lenght)
	{
		SERCOM4->USART.DATA.reg = buff[pos];
		while (!(SERCOM4->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_TXC)) 
		{
			/* Wait until data is sent */
		}
		pos++;
	}
	return TRUE;
}

