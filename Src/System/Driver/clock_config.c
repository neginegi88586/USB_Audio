/*
 * osc_config.c
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#include "clock_config.h"

Error_HandleTypeDef Clock_Setup_OSC(OSC_ConfigSetTypeDef *osc_config)
{
	uint32_t TickStart;
	if(osc_config == NULL)
	{
		return STATE_ERROR;
	}

	/* ---------------------HSE Configuration--------------------- */
	if((osc_config->OSC_TYPE & OSC_TYPE_HSE) == OSC_TYPE_HSE)
	{
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_HSE || ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL && (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC_HSE) == RCC_PLLCFGR_PLLSRC_HSE))
		{
			if((RCC->CR & RCC_CR_HSERDY) != RESET && (osc_config->HSE_SET.HSE_STATE) == HSE_OFF)
			{
				return STATE_ERROR;
			}
		}
		else
		{
			HSE_CONFIG(osc_config->HSE_SET.HSE_STATE);
			if(osc_config->HSE_SET.HSE_STATE == HSE_ON)
			{
				TickStart = uwTick;

				while((RCC->CR & RCC_CR_HSERDY) == RESET)
				{
					if((uwTick - TickStart) > HSE_TIMEOUT_VALUE)
					{
						return STATE_TIMEOUT;
					}
				}
			}
			else
			{
				TickStart = uwTick;

				while((RCC->CR & RCC_CR_HSERDY) == RESET)
				{
					if((uwTick - TickStart) > HSE_TIMEOUT_VALUE)
					{
						return STATE_TIMEOUT;
					}
				}
			}
		}
	}

	/* ---------------------HSI Configuration--------------------- */
	if((osc_config->OSC_TYPE & OSC_TYPE_HSE) == OSC_TYPE_HSE)
	{
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_HSI || ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL && (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSI))
		{
			if((RCC->CR & RCC_CR_HSIRDY) != RESET && (osc_config->HSI_SET.HSI_STATE) == HSI_OFF)
			{
				return STATE_ERROR;
			}
			else
			{
				RCC_HSI_CALIBRATION_ADJUST(osc_config->HSI_SET.HSI_CAL);
			}
		}
		else
		{
			if(osc_config->HSI_SET.HSI_STATE == HSI_ON)
			{
				HSI_ENABLE();
				TickStart = uwTick;

				while((RCC->CR & RCC_CR_HSIRDY) == RESET)
				{
					if((uwTick - TickStart) > HSI_TIMEOUT_VALUE)
					{
						return STATE_TIMEOUT;
					}
				}
				RCC_HSI_CALIBRATION_ADJUST(osc_config->HSI_SET.HSI_CAL);
			}
			else
			{
				HSI_DISEBLE();
				TickStart = uwTick;
				while((RCC->CR & RCC_CR_HSIRDY) == RESET)
				{
					if((uwTick - TickStart) > HSI_TIMEOUT_VALUE)
					{
						return STATE_TIMEOUT;
					}
				}
			}
		}
	}
	return STATE_OK;
}

Error_HandleTypeDef Clock_Setup_Clock(Clock_ConfigTypeDef *clock_config)
{
	uint32_t TickStart;

	if(clock_config == NULL)
	{
		return STATE_ERROR;
	}

	if(clock_config->FLatency > FLASH_GET_LATENCY())
	{
		FLASH_SET_LATENCY(clock_config->FLatency);

		if(FLASH_GET_LATENCY() != clock_config->FLatency)
		{
			return STATE_ERROR;
		}
	}

	if((clock_config->CLOCK_TYPE & RCC_CLK_TYPE_HCLK) == RCC_CLK_TYPE_HCLK)
	{
		if((clock_config->CLOCK_TYPE & RCC_CLK_TYPE_PCLK1) == RCC_CLK_TYPE_PCLK1)
		{
			MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_HCLK_DIV16);
		}
		if((clock_config->CLOCK_TYPE & RCC_CLK_TYPE_PCLK2) == RCC_CLK_TYPE_PCLK2)
		{
			MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, (RCC_HCLK_DIV16 << 3));
		}

		MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, clock_config->AHBCLK_DIV);
	}

	if((clock_config->CLOCK_TYPE & RCC_CLK_TYPE_SYSCLK) == RCC_CLK_TYPE_SYSCLK)
	{
		if((clock_config->SYSCLK_SOURCE) == RCC_SYSCLKSOURCE_HSE)
		{
			if((RCC->CR & RCC_CR_HSERDY) == RESET)
			{
				return STATE_ERROR;
			}
		}
		else if((clock_config->SYSCLK_SOURCE) == RCC_SYSCLKSOURCE_PLLCLK)
		{
			if((RCC->CR & RCC_CR_PLLRDY) == RESET)
			{
				return STATE_ERROR;
			}
		}
		else
		{
			if((RCC->CR & RCC_CR_HSIRDY) == RESET)
			{
				return STATE_ERROR;
			}
		}

		MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (clock_config->SYSCLK_SOURCE));

		TickStart = uwTick;

		while((RCC->CFGR) & RCC_CFGR_SWS == (clock_config->SYSCLK_SOURCE) << RCC_CFGR_SWS_Pos)
		{
			if((uwTick - TickStart) > CLK_SW_TIMEOUT_VALUE)
			{
				return STATE_TIMEOUT;
			}
		}
	}

	if(clock_config->FLatency < FLASH_GET_LATENCY())
	{
		FLASH_SET_LATENCY(clock_config->FLatency);

		if(FLASH_GET_LATENCY() != clock_config->FLatency)
		{
			return STATE_ERROR;
		}
	}

	if((clock_config->CLOCK_TYPE & RCC_CLK_TYPE_PCLK1) == RCC_CLK_TYPE_PCLK1)
	{
	    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, clock_config->APB1CLK_DIV);
	}
	if((clock_config->CLOCK_TYPE & RCC_CLK_TYPE_PCLK2) == RCC_CLK_TYPE_PCLK2)
	{
	    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, clock_config->APB2CLK_DIV);
	}

	SystemCoreClock = Get_SysClock_Freq() >> AHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos];

	return STATE_OK;
}

uint32_t Get_SysClock_Freq(void)
{
	uint32_t pllm = 0, pllvco = 0, pllp = 0;
	uint32_t sysclock_freq = 0;
	switch (RCC->CFGR & RCC_CFGR_SWS)
	{
	case RCC_SYSCLKSOURCE_STATUS_HSI:
		sysclock_freq = HSI_VALUE;
		break;
	case RCC_SYSCLKSOURCE_STATUS_HSE:
		sysclock_freq = HSE_VALUE;
		break;
	case RCC_SYSCLKSOURCE_STATUS_PLLCLK:
		pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
		if((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) != RCC_PLLCFGR_PLLSRC_HSI)
		{
			pllvco = (uint32_t)((((uint64_t)HSE_VALUE * ((uint64_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
		}
		else
		{
			pllvco = (uint32_t)((((uint64_t)HSI_VALUE * ((uint64_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
		}
		pllp = ((((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos) + 1) * 2);

		sysclock_freq = pllvco / pllp;
		break;
	default:
		sysclock_freq = HSI_VALUE;
		break;
	}

	Tick_Init(uwTickPrio);

	return sysclock_freq;
}
