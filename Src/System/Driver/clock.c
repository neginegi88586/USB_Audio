/*
 * osc_config.c
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#include "clock.h"
#include "gpio.h"


#define MCO1_CLK_ENABLE()	  	RCC_GPIOCLK_ENABLE(RCC_AHB1ENR_GPIOAEN)
#define MCO1_GPIO_PORT        	GPIOA
#define MCO1_PIN              	(1 << 8)

#define MCO2_CLK_ENABLE()		RCC_GPIOCLK_ENABLE(RCC_AHB1ENR_GPIOCEN)
#define MCO2_GPIO_PORT			GPIOC
#define MCO2_PIN           	    (1 << 9)


Error_HandleTypeDef Clock_Setup_OSC(OSC_ConfigSetTypeDef *osc_config)
{
	uint32_t pll_config;
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
	if((osc_config->OSC_TYPE & OSC_TYPE_HSI) == OSC_TYPE_HSI)
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

	if(osc_config->PLL_SET.PLL_STATE != PLL_NONE)
	{
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL)
		{
			if(osc_config->PLL_SET.PLL_STATE == PLL_ON)
			{
				PLL_DISEBLE();

				TickStart = uwTick;

				while((RCC->CR & RCC_CR_PLLON) != RESET)
				{
					if((uwTick - TickStart) > PLL_TIMEOUT_VALUE)
					{
						return STATE_TIMEOUT;
					}
				}

				RCC_PLL_CONFIG(osc_config->PLL_SET.PLLSRC, osc_config->PLL_SET.PLLM, osc_config->PLL_SET.PLLN, osc_config->PLL_SET.PLLP, osc_config->PLL_SET.PLLQ);

				PLL_ENABLE();

				TickStart = uwTick;

				while((RCC->CR & RCC_CR_PLLON) == RESET)
				{
					if((uwTick - TickStart) > PLL_TIMEOUT_VALUE)
					{
						return STATE_TIMEOUT;
					}
				}
			}
			else
			{
				PLL_DISEBLE();

				TickStart = uwTick;

				while((RCC->CR & RCC_CR_PLLON) != RESET)
				{
					if((uwTick - TickStart) > PLL_TIMEOUT_VALUE)
					{
						return STATE_TIMEOUT;
					}
				}
			}
		}
		else
		{
			pll_config = RCC->PLLCFGR;
			if(osc_config->PLL_SET.PLL_STATE == PLL_OFF ||
					READ_BIT(pll_config, RCC_PLLCFGR_PLLSRC) != osc_config->PLL_SET.PLLSRC ||
					READ_BIT(pll_config, RCC_PLLCFGR_PLLM) != osc_config->PLL_SET.PLLM ||
					READ_BIT(pll_config, RCC_PLLCFGR_PLLN) != osc_config->PLL_SET.PLLN << RCC_PLLCFGR_PLLN_Pos ||
					READ_BIT(pll_config, RCC_PLLCFGR_PLLP) != (((osc_config->PLL_SET.PLLP) >> 1U) - 1U) << RCC_PLLCFGR_PLLP_Pos ||
					READ_BIT(pll_config, RCC_PLLCFGR_PLLQ) != osc_config->PLL_SET.PLLQ << RCC_PLLCFGR_PLLQ_Pos)
			{
				return STATE_ERROR;
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

		TickStart = uwTick;
		while((FLASH->ACR & FLASH_ACR_LATENCY) != clock_config->FLatency)
		{
			if((uwTick - TickStart) > 1000)
			{
				return STATE_TIMEOUT;
			}
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
			if((RCC->CR & RCC_CR_HSERDY) != RESET)
			{
				return STATE_ERROR;
			}
		}
		else if((clock_config->SYSCLK_SOURCE) == RCC_SYSCLKSOURCE_PLLCLK)
		{
			if((RCC->CR & RCC_CR_PLLRDY) != RESET)
			{
				return STATE_ERROR;
			}
		}
		else
		{
			if((RCC->CR & RCC_CR_HSIRDY) != RESET)
			{
				return STATE_ERROR;
			}
		}

		MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (clock_config->SYSCLK_SOURCE));

		TickStart = uwTick;

		while((RCC->CFGR & RCC_CFGR_SWS) != (clock_config->SYSCLK_SOURCE) << RCC_CFGR_SWS_Pos)
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

	Tick_Init(uwTickPrio);

	return STATE_OK;
}

void MCO_Config(uint32_t MCOx, uint32_t MCO_SRC, uint32_t MCO_DIV)
{
	GPIO_ConfigTypeDef config;

	if(MCOx == RCC_MCO1)
	{
		MCO1_CLK_ENABLE();

		config.PIN = MCO1_PIN;
		config.MODE = GPIO_MODE_AF_PP;
		config.SPEED = GPIO_SPEED_FREQ_HIGH;
		config.PULL = GPIO_NOPULL;
		config.ALT = (uint8_t)0x00;
		GPIO_Config(MCO1_GPIO_PORT, &config);

		MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO1 | RCC_CFGR_MCO1PRE), (MCO_SRC | MCO_DIV));
	}
	else
	{
		MCO2_CLK_ENABLE();

		config.PIN = MCO2_PIN;
		config.MODE = GPIO_MODE_AF_PP;
		config.SPEED = GPIO_SPEED_FREQ_HIGH;
		config.PULL = GPIO_NOPULL;
		config.ALT = (uint8_t)0x00;
		GPIO_Config(MCO2_GPIO_PORT, &config);

		MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO2 | RCC_CFGR_MCO2PRE), (MCO_SRC | (MCO_DIV << 3)));
	}
}

uint32_t Get_SysClock_Freq(void)
{
	uint32_t pllm = 0, pllvco = 0, pllp = 0;
	uint32_t sysclock_freq = 0;
	switch (RCC->CFGR & RCC_CFGR_SWS)
	{
	case RCC_SYSCLKSOURCE_STATUS_HSI:
	{
		sysclock_freq = HSI_VALUE;
		break;
	}
	case RCC_SYSCLKSOURCE_STATUS_HSE:
	{
		sysclock_freq = HSE_VALUE;
		break;
	}
	case RCC_SYSCLKSOURCE_STATUS_PLLCLK:
	{
		pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
		if((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) != RCC_PLLCFGR_PLLSRC_HSI)
		{
	        pllvco = (uint32_t)((((uint64_t) HSE_VALUE * ((uint64_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
		}
		else
		{
	        pllvco = (uint32_t)((((uint64_t) HSI_VALUE * ((uint64_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
		}
	    pllp = ((((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos) + 1) * 2);

	    sysclock_freq = pllvco / pllp;
		break;
	}
	default:
	{
		sysclock_freq = HSI_VALUE;
		break;
	}
	}

	Tick_Init(uwTickPrio);

	return sysclock_freq;
}

void Delay_Ms(uint32_t delay_time)
{
	uint32_t TickStart = uwTick;
	uint32_t wait = delay_time;

	if(wait < MS_MAX_DELAY)
	{
		wait += (uint32_t)1;
	}

	while((uwTick - TickStart) < wait);
}

uint32_t RCC_GetPCLK_Freq(uint32_t cfgr_ppre, uint32_t cfgr_pos)
{
	return (SystemCoreClock >> APBPrescTable[cfgr_ppre >> cfgr_pos]);
}

Error_HandleTypeDef PeriphCLKConfig(RCC_Periph_CLK_ConfigTypedef *periph_clk_config)
{
	uint32_t TickStart = 0;
	uint32_t tmpreg0 = 0;
	uint32_t plli2s_used = 0;
	uint32_t pllsai_used = 0;

	if(((periph_clk_config->PeriphClockSelection) & (uint32_t)0x80000) == (uint32_t)0x80000U)
	{
		MODIFY_REG(RCC->DCKCFGR1, RCC_DCKCFGR1_SAI1SEL, (uint32_t)(periph_clk_config->Sai1ClockSelection));
		if((periph_clk_config->Sai1ClockSelection) == (uint32_t)0x00U)
		{
			pllsai_used = 1;
		}
	}

	if(((periph_clk_config->PeriphClockSelection) & 0x40U) == 0x40U)
	{
		MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_USART1SEL, (uint32_t)(periph_clk_config->Usart1ClockSelection));
	}

	if(pllsai_used == 1)
	{
		RCC->CR &= ~(RCC_CR_PLLSAION);

		TickStart = uwTick;
		while(((RCC->CR & RCC_CR_PLLSAIRDY) == RCC_CR_PLLSAIRDY) == RESET)
		{
			if((uwTick - TickStart) > PLLSAI_TIMEOUT_VALUE)
			{
				return STATE_ERROR;
			}
		}

	    if(((((periph_clk_config->PeriphClockSelection) & (uint32_t)0x80000U) == (uint32_t)0x80000U) && (periph_clk_config->Sai1ClockSelection == (uint32_t)0x00U)) ||\
	       ((((periph_clk_config->PeriphClockSelection) & (uint32_t)0x100000U) == (uint32_t)0x100000) && (periph_clk_config->Sai2ClockSelection == (uint32_t)0x00U)))
	    {
	    	tmpreg0 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIP) >> RCC_PLLSAICFGR_PLLSAIP_Pos);

	    	RCC->PLLSAICFGR = ((periph_clk_config->PLLSAI.PLLSAIN) << RCC_PLLSAICFGR_PLLSAIN_Pos) |
	    			tmpreg0 |
					((periph_clk_config->PLLSAI.PLLSAIQ) << RCC_PLLSAICFGR_PLLSAIQ_Pos);

	    	MODIFY_REG(RCC->DCKCFGR1, RCC_DCKCFGR1_PLLSAIDIVQ, (periph_clk_config->PLLSAIDivQ - 1) << 8);
	    }

	    if((((periph_clk_config->PeriphClockSelection) & (uint32_t)0x200000U) == (uint32_t)0x200000U) && (periph_clk_config->Clk48ClockSelection == RCC_DCKCFGR2_CK48MSEL))
		{

	    	tmpreg0 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> RCC_PLLSAICFGR_PLLSAIQ_Pos);

	    	RCC->PLLSAICFGR = ((periph_clk_config->PLLSAI.PLLSAIN) << RCC_PLLSAICFGR_PLLSAIN_Pos) |
					((periph_clk_config->PLLSAI.PLLSAIP) << RCC_PLLSAICFGR_PLLSAIP_Pos) |
					tmpreg0;
		}

	    (RCC->CR |= (RCC_CR_PLLSAION));

	    TickStart = uwTick;

	    while(((RCC->CR & RCC_CR_PLLSAIRDY) == RCC_CR_PLLSAIRDY) == RESET)
	    {
			if((uwTick - TickStart) > PLLSAI_TIMEOUT_VALUE)
			{
				return STATE_ERROR;
			}
	    }
	}
	return STATE_OK;
}
