/*
 * sys_tick_config.h
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#ifndef INC_SYSTEM_DRIVER_SYSTEM_CONFIG_H_
#define INC_SYSTEM_DRIVER_SYSTEM_CONFIG_H_

#include "main.h"


#define PRIORITY_GROUP			0x03U
#define TICK_INT_PRIORITY		0x15U


void System_Config(void);
void Tick_Init(uint32_t TickPriority);

#endif /* INC_SYSTEM_DRIVER_SYSTEM_CONFIG_H_ */
