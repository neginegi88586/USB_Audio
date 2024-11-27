/*
 * clock_config.c
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#include "clock_config.h"

Error_HandleTypeDef Clock_Setup(Clock_ConfigSetTypeDef *clock_config)
{
	if(clock_config == NULL)
	{
		return STATE_ERROR;
	}

	if((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_HSE || ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL && (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC_HSE) == RCC_PLLCFGR_PLLSRC_HSE))
	{
		if(RCC->CR != RESET)
		{
			return STATE_ERROR;
		}
	}
	else
	{
		HSE_CONFIG(clock_config->HSE_SET.HSE_STATE);
		if(clock_config->HSE_SET.HSE_STATE != HSE_OFF)
		{
			while((RCC->CR & RCC_CR_HSERDY) == RESET);
		}
	}
	return STATE_OK;
}
