/*
 * system_config.c
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#include "system_config.h"

void System_Config(void)
{
	uint32_t priority_group = 0x00;
	NVIC_SetPriorityGrouping((uint32_t)0x05);

	priority_group = NVIC_GetPriorityGrouping();
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(priority_group, 3, 0));
}
