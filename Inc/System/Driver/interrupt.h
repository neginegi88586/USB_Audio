/*
 * interrupt.h
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#ifndef INC_SYSTEM_DRIVER_INTERRUPT_H_
#define INC_SYSTEM_DRIVER_INTERRUPT_H_

#include "main.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif /* INC_SYSTEM_DRIVER_INTERRUPT_H_ */
