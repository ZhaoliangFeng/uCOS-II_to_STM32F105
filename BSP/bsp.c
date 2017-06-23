/*****************************************************
* @Author  :  Fengzhaoliang
* @File    :  bsp.c
* @Date    :  2017-04-29
* @Function:  UCOSII transplant template
******************************************************/
#include "bsp.h"

int RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;
	RCC_ClocksTypeDef RCC_ClockFreq;

	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus != ERROR)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/****************************************************************/
		/* HSE= up to 25MHz (on EVB1000 is 12MHz),
		 * HCLK=72MHz, PCLK2=72MHz, PCLK1=36MHz 						*/
		/****************************************************************/
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1);
		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);
		/*  ADCCLK = PCLK2/4 */
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);

		/* Configure PLLs *********************************************************/
		/* PLL2 configuration: PLL2CLK = (HSE / 4) * 8 = 24 MHz */
		RCC_PREDIV2Config(RCC_PREDIV2_Div4);
		RCC_PLL2Config(RCC_PLL2Mul_8);

		/* Enable PLL2 */
		RCC_PLL2Cmd(ENABLE);

		/* Wait till PLL2 is ready */
		while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET){}

		/* PLL1 configuration: PLLCLK = (PLL2 / 3) * 9 = 72 MHz */
		RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div3);
		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);

		/* Enable PLL */
		RCC_PLLCmd(ENABLE);

		/* Wait till PLL is ready */
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source */
		while (RCC_GetSYSCLKSource() != 0x08){}
	}

	RCC_GetClocksFreq(&RCC_ClockFreq);

	/* Enable SPI1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	/* Enable SPI2 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	/* Enable GPIOs clocks */
	RCC_APB2PeriphClockCmd(
						RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
						RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
						RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,
						ENABLE);

	return 0;
}

void SysTick_init(void)
{
    SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);
}

void Bsp_Init(void)
{
    RCC_Configuration();
    SysTick_init();
    Bsp_Led_Init();
}



