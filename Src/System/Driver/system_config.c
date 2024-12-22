/*
 * system_config.c
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#include "system_config.h"


void System_Config(void)
{
	NVIC_SetPriorityGrouping((uint32_t)PRIORITY_GROUP);

	Tick_Init(TICK_INT_PRIORITY);

	do
	{
		__IO uint32_t tmpreg;
		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
		tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
		UNUSED(tmpreg);
	}
	while(0);

	do
	{
		__IO uint32_t tmpreg;
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
		tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
		UNUSED(tmpreg);
	}
	while(0);

	MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_CR1_VOS);
}

void Tick_Init(uint32_t TickPriority)
{
	uint32_t priority_group = 0x00;

	priority_group = NVIC_GetPriorityGrouping();
	SysTick_Config(SystemCoreClock / (1000U / 1U));

	if(TickPriority < (1U << __NVIC_PRIO_BITS))
	{
		NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(priority_group, TickPriority, 0));
		uwTickPrio = TickPriority;
	}
}
