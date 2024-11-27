/*
 * clock_config.h
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#ifndef SYSTEM_DRIVER_CLOCK_CONFIG_H_
#define SYSTEM_DRIVER_CLOCK_CONFIG_H_

#include "main.h"

typedef enum
{
	HSE_OFF = 0,
	HSE_ON,
	HSE_BYP,
	HSE_Default
}HSE_StateTypeDef;

typedef enum
{
	HSI_OFF = 0,
	HSI_ON,
	HSI_BYP,
	HSI_Default
}HSI_StateTypeDef;

typedef enum
{
	PLL_OFF = 0,
	PLL_ON,
}PLL_StateTypeDef;

typedef enum
{
	PLLSRC_HSI = 0,
	PLLSRC_HSE,
}PLL_SourceTypeDef;

typedef struct
{
	/* PLL State */
	PLL_StateTypeDef PLL_STATE;
	PLL_StateTypeDef PLLSAI_STATE;
	PLL_StateTypeDef PLLI2S_STATE;

	/* PLL Setup */
	PLL_SourceTypeDef PLLSRC;
	uint32_t PLLM;
	uint32_t PLLN;
	uint32_t PLLP;
	uint32_t PLLQ;
}PLL_ConfigTypeDef;

typedef struct
{
	/* HSE State */
	uint32_t CSS_STATE;
	HSE_StateTypeDef HSE_STATE;
}HSE_ConfigTypeDef;

typedef struct
{
	/* HSI State */
	uint32_t HSI_CAL;
	uint32_t HSI_TRIM;
	HSI_StateTypeDef HSI_STATE;
}HSI_ConfigTypeDef;

typedef struct
{
	/* Clock Config structure */
	PLL_ConfigTypeDef PLL_SET;
	HSE_ConfigTypeDef HSE_SET;
	HSI_ConfigTypeDef HSI_SET;
}Clock_ConfigSetTypeDef;


#define HSE_CONFIG(__STATE__) \
	do\
	{\
		if((__STATE__) == HSE_OFF)\
		{\
			CLEAR_BIT(RCC->CR, RCC_CR_HSEON);\
			CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);\
		}\
		else if((__STATE__) == HSE_ON)\
		{\
			SET_BIT(RCC->CR, RCC_CR_HSEON);\
		}\
		else if((__STATE__) == HSE_BYP)\
		{\
			SET_BIT(RCC->CR, RCC_CR_HSEBYP);\
			SET_BIT(RCC->CR, RCC_CR_HSEON);\
		}\
		else\
		{\
			CLEAR_BIT(RCC->CR, RCC_CR_HSEON);\
			CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);\
		}\
	}while(0)


Error_HandleTypeDef Clock_Setup(Clock_ConfigSetTypeDef *clock_config);

#endif /* SYSTEM_DRIVER_CLOCK_CONFIG_H_ */
