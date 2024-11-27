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

/* HSE State */
typedef struct
{
	uint32_t CSS_STATE;
	HSE_StateTypeDef HSE_STATE;
}HSE_ConfigTypeDef;

/* HSI State */
typedef struct
{
	uint32_t HSI_CAL;
	HSI_StateTypeDef HSI_STATE;
}HSI_ConfigTypeDef;

/* Oscillator Config structure */
typedef struct
{
	uint32_t OSC_TYPE;
	PLL_ConfigTypeDef PLL_SET;
	HSE_ConfigTypeDef HSE_SET;
	HSI_ConfigTypeDef HSI_SET;
}OSC_ConfigSetTypeDef;


/* Clock Config structure */
typedef struct
{
	uint32_t CLOCK_TYPE;
	uint32_t SYSCLK_SOURCE;
	uint32_t AHBCLK_DIV;
	uint32_t APB1CLK_DIV;
	uint32_t APB2CLK_DIV;
	uint32_t FLatency;
}Clock_ConfigTypeDef;


#define OSC_TYPE_HSE						   ((uint32_t)0x01)
#define OSC_TYPE_HSI						   ((uint32_t)0x02)

#define HSE_TIMEOUT_VALUE					   ((uint32_t)100U)
#define HSI_TIMEOUT_VALUE					   ((uint32_t)2U)
#define CLK_SW_TIMEOUT_VALUE				   ((uint32_t)5000)

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

#define HSI_ENABLE() 						   SET_BIT(RCC->CR, RCC_CR_HSION)
#define HSI_DISEBLE()						   CLEAR_BIT(RCC->CR, RCC_CR_HSION)

#define RCC_HSI_CALIBRATION_ADJUST(__HSICALIBRATIONVALUE__) \
	(MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, (uint32_t)(__HSICALIBRATIONVALUE__) << RCC_CR_HSITRIM_Pos))


#define RCC_CLK_TYPE_SYSCLK					   ((uint32_t)0x01U)
#define RCC_CLK_TYPE_HCLK					   ((uint32_t)0x02U)
#define RCC_CLK_TYPE_PCLK1					   ((uint32_t)0x04U)
#define RCC_CLK_TYPE_PCLK2					   ((uint32_t)0x08U)

#define RCC_SYSCLKSOURCE_HSI            	   RCC_CFGR_SW_HSI
#define RCC_SYSCLKSOURCE_HSE            	   RCC_CFGR_SW_HSE
#define RCC_SYSCLKSOURCE_PLLCLK        		   RCC_CFGR_SW_PLL

#define RCC_SYSCLKSOURCE_STATUS_HSI     	   RCC_CFGR_SWS_HSI   /*!< HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE    		   RCC_CFGR_SWS_HSE   /*!< HSE used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK  	   RCC_CFGR_SWS_PLL   /*!< PLL used as system clock */

#define RCC_SYSCLK_DIV1               		   RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_DIV2               		   RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_DIV4               		   RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_DIV8               		   RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_DIV16             		   RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_DIV64             		   RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_DIV128            		   RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_DIV256            		   RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_DIV512            		   RCC_CFGR_HPRE_DIV512

#define RCC_HCLK_DIV1                		   RCC_CFGR_PPRE1_DIV1
#define RCC_HCLK_DIV2                		   RCC_CFGR_PPRE1_DIV2
#define RCC_HCLK_DIV4                		   RCC_CFGR_PPRE1_DIV4
#define RCC_HCLK_DIV8                		   RCC_CFGR_PPRE1_DIV8
#define RCC_HCLK_DIV16               		   RCC_CFGR_PPRE1_DIV16


#define FLASH_GET_LATENCY()						READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY)
#define FLASH_SET_LATENCY(__LATENCY__)			MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, __LATENCY__)


#define RCC_GPIOCLK_ENABLE(__RCC_GPIO_PORT__)	SET_BIT(RCC->AHB1ENR, __RCC_GPIO_PORT__)


Error_HandleTypeDef Clock_Setup_OSC(OSC_ConfigSetTypeDef *osc_config);
Error_HandleTypeDef Clock_Setup_Clock(Clock_ConfigTypeDef *clock_config);
uint32_t Get_SysClock_Freq(void);

#endif /* SYSTEM_DRIVER_CLOCK_CONFIG_H_ */
