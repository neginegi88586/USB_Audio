/*
 * gpio.c
 *
 *  Created on: Nov 28, 2024
 *      Author: idune
 */

#include "gpio.h"


#define GPIO_NUMBER           ((uint32_t)16U)


void GPIO_Config(GPIO_TypeDef *GPIOx, GPIO_ConfigTypeDef *GPIO_Conf)
{
	uint32_t position = 0;
	uint32_t ioposition = 0x00;
	uint32_t iocurrent = 0x00;
	uint32_t temp = 0x00;

	for(position = 0; position < GPIO_NUMBER; position++)
	{
		ioposition = ((uint32_t)0x01) << position;

		iocurrent = (uint32_t)(GPIO_Conf->PIN) & ioposition;

		if(iocurrent == ioposition)
		{
			if(((GPIO_Conf->MODE & GPIO_MODE) == MODE_OUTPUT) || ((GPIO_Conf->MODE & GPIO_MODE) == MODE_AF))
			{
				temp = GPIOx->OSPEEDR;
				temp &= ~(GPIO_OSPEEDR_OSPEEDR0 << (position * 2));
				temp |= (GPIO_Conf->SPEED << (position * 2));
				GPIOx->OSPEEDR = temp;

				temp = GPIOx->OTYPER;
				temp &= ~(GPIO_OTYPER_OT0 << position);
				temp |= ((GPIO_Conf->MODE & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos) << position;
				GPIOx->OTYPER = temp;
			}
		    if((GPIO_Conf->MODE & GPIO_MODE) != MODE_ANALOG)
		    {
		        temp = GPIOx->PUPDR;
		        temp &= ~(GPIO_PUPDR_PUPDR0 << (position * 2));
		        temp |= ((GPIO_Conf->PULL) << (position * 2));
		        GPIOx->PUPDR = temp;
		    }
		    if ((GPIO_Conf->MODE & GPIO_MODE) == MODE_AF)
		    {
		        temp = GPIOx->AFR[position >> 3];
		        temp &= ~((uint32_t)0xF << ((uint32_t)(position & (uint32_t)0x07) * 4)) ;
		        temp |= ((uint32_t)(GPIO_Conf->ALT) << (((uint32_t)position & (uint32_t)0x07) * 4));
		        GPIOx->AFR[position >> 3] = temp;
		    }
		    temp = GPIOx->MODER;
		    temp &= ~(GPIO_MODER_MODER0 << (position * 2));
		    temp |= ((GPIO_Conf->MODE & GPIO_MODE) << (position * 2));
		    GPIOx->MODER = temp;

		    if((GPIO_Conf->MODE & EXTI_MODE) != 0x00u)
		    {
		    	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

		    	temp = SYSCFG->EXTICR[position >> 2];
		    	temp &= ~(((uint32_t)0x0F) << (4 * (position & 0x03)));
		    	temp |= ((uint32_t)(GPIO_GET_INDEX(GPIOx)) << (4 * (position & 0x03)));
		    	SYSCFG->EXTICR[position >> 2] = temp;

		        temp = EXTI->RTSR;
		        temp &= ~((uint32_t)iocurrent);
		        if ((GPIO_Conf->MODE & TRIGGER_RISING) != 0x00u)
		        {
		        	temp |= iocurrent;
		        }
		        EXTI->RTSR = temp;

		        temp = EXTI->FTSR;
		        temp &= ~((uint32_t)iocurrent);
		        if ((GPIO_Conf->MODE & TRIGGER_FALLING) != 0x00u)
		        {
		        	temp |= iocurrent;
		        }
		        EXTI->FTSR = temp;

		        temp = EXTI->EMR;
		        temp &= ~((uint32_t)iocurrent);
		        if ((GPIO_Conf->MODE & EXTI_EVT) != 0x00u)
		        {
		        	temp |= iocurrent;
		        }
		        EXTI->EMR = temp;

		        temp = EXTI->IMR;
		        temp &= ~((uint32_t)iocurrent);
		        if ((GPIO_Conf->MODE & EXTI_IT) != 0x00u)
		        {
		        	temp |= iocurrent;
		        }
		        EXTI->IMR = temp;
		    }
		}
	}
}

void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t Pin, GPIO_State State)
{
	if(State != GPIO_RESET)
	{
		GPIOx->BSRR = Pin;
	}
	else
	{
		GPIOx->BSRR = (uint32_t)Pin << 16;
	}
}
