/*
 * main.h
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f7xx.h"

typedef enum
{
	STATE_OK = 0U,
	STATE_ERROR,
	STATE_BUSY,
	STATE_TIMEOUT,
}Error_HandleTypeDef;

void Error_Handler(void);

#endif /* MAIN_H_ */
