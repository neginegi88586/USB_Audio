/*
 * uart.c
 *
 *  Created on: Nov 28, 2024
 *      Author: idune
 */

#include "uart.h"
#include "gpio.h"
#include "clock.h"

static void UART_EndRxTransfer(UART_HandleTypeDef *huart);


Error_HandleTypeDef UART_Config(UART_HandleTypeDef *huart)
{
	if(huart == NULL)
	{
		return STATE_ERROR;
	}

	if(huart->gSTATE == UART_STATE_RST)
	{
		huart->LOCK = UNLOCKED;

		UART_Pin_Config(huart);
	}
	huart->gSTATE = UART_STATE_BUSY;

	huart->INSTANCE->CR1 &= ~(USART_CR1_UE);
	if(huart->ADV_INIT.ADV_FEAT_INIT != 0x00U)
	{

	}

	if(UART_SetConfig(huart) == STATE_ERROR)
	{
		return STATE_ERROR;
	}

	CLEAR_BIT(huart->INSTANCE->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
	CLEAR_BIT(huart->INSTANCE->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));

	huart->INSTANCE->CR1 |= USART_CR1_UE;

	return (UART_CheckIdleState(huart));
}

Error_HandleTypeDef UART_SetConfig(UART_HandleTypeDef *huart)
{
	uint32_t tmpreg;
	uint16_t brrtemp;
	UART_ClockSourceTypeDef clocksource;
	uint32_t usartdiv;
	Error_HandleTypeDef ret = STATE_OK;
	uint32_t pclk;

	tmpreg = (uint32_t)huart->INIT.WORD_LEN | huart->INIT.PARITY | huart->INIT.MODE | huart->INIT.OVER_SAMPLE ;
	MODIFY_REG((huart->INSTANCE->CR1), USART_CR1_FIELDS, tmpreg);

	MODIFY_REG(huart->INSTANCE->CR2, USART_CR2_STOP, huart->INIT.STOP_BIT);

	tmpreg = (uint32_t)huart->INIT.FLOW_CTRL;

	tmpreg |= huart->INIT.ONEB_SAMPLE;
	MODIFY_REG(huart->INSTANCE->CR3, USART_CR3_FIELDS, tmpreg);
	UART_GETCLOCKSOURCE(huart, clocksource);

	if (huart->INIT.OVER_SAMPLE == USART_CR1_OVER8)
	{
		switch (clocksource)
		{
		case UART_CLOCKSOURCE_PCLK1:
			pclk = RCC_GetPCLK_Freq((RCC->CFGR & RCC_CFGR_PPRE1), RCC_CFGR_PPRE1_Pos);
			break;
		case UART_CLOCKSOURCE_PCLK2:
			pclk = RCC_GetPCLK_Freq((RCC->CFGR & RCC_CFGR_PPRE2), RCC_CFGR_PPRE2_Pos);
	        break;
		case UART_CLOCKSOURCE_HSI:
			pclk = (uint32_t) HSI_VALUE;
	        break;
		case UART_CLOCKSOURCE_SYSCLK:
	        pclk = Get_SysClock_Freq();
	        break;
		case UART_CLOCKSOURCE_LSE:
	        pclk = (uint32_t) LSE_VALUE;
	        break;
		default:
	        pclk = 0U;
	        ret = STATE_ERROR;
	        break;
		}
		if (pclk != 0U)
		{
			usartdiv = (uint32_t)(UART_DIV_SAMPLING8(pclk, huart->INIT.BAUD));
			if ((usartdiv >= UART_BRR_MIN) && (usartdiv <= UART_BRR_MAX))
			{
				brrtemp = (uint16_t)(usartdiv & 0xFFF0U);
				brrtemp |= (uint16_t)((usartdiv & (uint16_t)0x000FU) >> 1U);
				huart->INSTANCE->BRR = brrtemp;
			}
			else
			{
				ret = STATE_ERROR;
			}
		}
	}
	else
	{
	    switch (clocksource)
	    {
	    case UART_CLOCKSOURCE_PCLK1:
	        pclk = RCC_GetPCLK_Freq((RCC->CFGR & RCC_CFGR_PPRE1), RCC_CFGR_PPRE1_Pos);
	        break;
	    case UART_CLOCKSOURCE_PCLK2:
	        pclk = RCC_GetPCLK_Freq((RCC->CFGR & RCC_CFGR_PPRE2), RCC_CFGR_PPRE2_Pos);
	        break;
	    case UART_CLOCKSOURCE_HSI:
	        pclk = (uint32_t) HSI_VALUE;
	        break;
	    case UART_CLOCKSOURCE_SYSCLK:
	        pclk = Get_SysClock_Freq();
	        break;
	    case UART_CLOCKSOURCE_LSE:
	        pclk = (uint32_t) LSE_VALUE;
	        break;
	    default:
	        pclk = 0U;
	        ret = STATE_ERROR;
	        break;
	    }

	    if (pclk != 0U)
	    {
	      /* USARTDIV must be greater than or equal to 0d16 */
	    	usartdiv = (uint32_t)(UART_DIV_SAMPLING16(pclk, huart->INIT.BAUD));
	    	if ((usartdiv >= UART_BRR_MIN) && (usartdiv <= UART_BRR_MAX))
	    	{
	    		huart->INSTANCE->BRR = (uint16_t)usartdiv;
	    	}
	    	else
	    	{
	    		ret = STATE_ERROR;
	    	}
	    }
	}

	huart->TX_ISR = NULL;
	huart->RX_ISR = NULL;

	return ret;
}

Error_HandleTypeDef UART_CheckIdleState(UART_HandleTypeDef *huart)
{
	uint32_t TickStart;

	huart->ERR_CODE = 0x00U;
	TickStart = uwTick;

	if ((huart->INSTANCE->CR1 & USART_CR1_TE) == USART_CR1_TE)
	{
		if (UART_WaitOnFlagUntilTimeout(huart, USART_ISR_TEACK, RESET, TickStart, UART_TIMEOUT_VALUE) != STATE_OK)
		{
			ATOMIC_CLEAR_BIT(huart->INSTANCE->CR1, USART_CR1_TXEIE);

			huart->gSTATE = 0x20U;

			do
			{
				huart->LOCK = UNLOCKED;
			}
			while(0);

			return STATE_TIMEOUT;
		}
	}

	huart->gSTATE = 0x20U;
	huart->RX_STATE = 0x20;
	huart->RECEPT_TYP = 0x00U;
	huart->RX_EVT_TYP = 0x00U;

	do
	{
		huart->LOCK = UNLOCKED;
	}
	while(0);

	return STATE_OK;
}

void UART_Pin_Config(UART_HandleTypeDef *huart)
{
	GPIO_ConfigTypeDef gpio_config = {0};
	RCC_Periph_CLK_ConfigTypedef periph_clk_config = {0};

	if(huart->INSTANCE == USART1)
	{
		periph_clk_config.PeriphClockSelection = (uint32_t)0x40U;
		periph_clk_config.Usart1ClockSelection = (uint32_t)0x00U;

		if(PeriphCLKConfig(&periph_clk_config) != STATE_OK)
		{
			Error_Handler();
		}

		do
		{
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
		}
		while(0);

		RCC_GPIOCLK_ENABLE(RCC_AHB1ENR_GPIOAEN);

		gpio_config.PIN = ((1 << 9) | (1 << 10));
		gpio_config.MODE = GPIO_MODE_AF_PP;
		gpio_config.PULL = GPIO_NOPULL;
		gpio_config.SPEED = GPIO_SPEED_FREQ_VERY_HIGH;
		gpio_config.ALT = (uint8_t)0x07U;

		GPIO_Config(GPIOA, &gpio_config);
	}
}

Error_HandleTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status,
                                              uint32_t Tickstart, uint32_t Timeout)
{
	while(((huart->INSTANCE->ISR & Flag) == Flag) == RESET)
	{
		if(Timeout != MS_MAX_DELAY)
		{
			if((uwTick - Tickstart) > Timeout || Timeout == 0U)
			{
				return STATE_TIMEOUT;
			}
			if((READ_BIT(huart->INSTANCE->CR1, USART_CR1_RE) != 0U) && (Flag != USART_ISR_TXE) && (Flag != USART_ISR_TC))
			{
				if(((huart->INSTANCE->ISR & USART_ISR_ORE) == USART_ISR_ORE) == SET)
				{
					(huart->INSTANCE->ICR) = USART_ICR_ORECF;

					UART_EndRxTransfer(huart);

					huart->ERR_CODE = 0x08U;

					do
					{
						huart->LOCK = UNLOCKED;
					}
					while(0);

					return STATE_ERROR;
				}
				if(((huart->INSTANCE->ISR & USART_ISR_RTOF) == USART_ISR_RTOF) == SET)
				{
					(huart->INSTANCE->ICR) = USART_ICR_RTOCF;

					UART_EndRxTransfer(huart);

					huart->ERR_CODE = 0x20U;

					do
					{
						huart->LOCK = UNLOCKED;
					}
					while(0);

					return STATE_TIMEOUT;
				}
			}
		}
	}
	return STATE_OK;
}

static void UART_EndRxTransfer(UART_HandleTypeDef *huart)
{
	ATOMIC_CLEAR_BIT(huart->INSTANCE->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));
	ATOMIC_CLEAR_BIT(huart->INSTANCE->CR3, USART_CR3_EIE);

	if(huart->RECEPT_TYP == 0x01U)
	{
		ATOMIC_CLEAR_BIT(huart->INSTANCE->CR1, USART_CR1_IDLEIE);
	}

	huart->RX_STATE = 0x20U;
	huart->RECEPT_TYP = 0x00U;

	huart->RX_ISR = NULL;
}

Error_HandleTypeDef UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	const uint8_t  *pdata8bits;
	const uint16_t *pdata16bits;
	uint32_t TickStart;

	if (huart->gSTATE == 0x20U)
	{
		if(pData == NULL || Size == 0U)
		{
			return STATE_ERROR;
		}

		huart->ERR_CODE = 0x00U;
		huart->gSTATE = 0x21U;

		TickStart = uwTick;

	    huart->TX_XFER_SIZE  = Size;
	    huart->TX_XFER_COUNT = Size;

	    if((huart->INIT.WORD_LEN == USART_CR1_M0) && (huart->INIT.PARITY == 0x00))
	    {
	        pdata8bits = NULL;
	        pdata16bits = (const uint16_t *) pData;
	    }
	    else
	    {
	    	pdata8bits = (const uint8_t *) pData;
	    	pdata16bits = NULL;
	    }

	    while(huart->TX_XFER_COUNT > 0U)
	    {
	    	if(UART_WaitOnFlagUntilTimeout(huart, USART_ISR_TXE, RESET, TickStart, Timeout) != STATE_OK)
	    	{
	    		huart->gSTATE = 0x20U;

	    		return STATE_TIMEOUT;
	    	}

	        if (pdata8bits == NULL)
	        {
	        	huart->INSTANCE->TDR = (uint16_t)(*pdata16bits & 0x01FFU);
	        	pdata16bits++;
	        }
	        else
	        {
	        	huart->INSTANCE->TDR = (uint8_t)(*pdata8bits & 0xFFU);
	        	pdata8bits++;
	        }
	        if (UART_WaitOnFlagUntilTimeout(huart, USART_ISR_TC, RESET, TickStart, Timeout) != STATE_OK)
	        {
	        	huart->gSTATE = 0x20U;

	        	return STATE_TIMEOUT;
	        }
	    }

	    huart->gSTATE = 0x20U;

	    return STATE_OK;
	}
	else
	{
		return STATE_BUSY;
	}
}
