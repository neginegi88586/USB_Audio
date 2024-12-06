/*
 * clock_config.h
 *
 *  Created on: Nov 27, 2024
 *      Author: idune
 */

#ifndef SYSTEM_DRIVER_CLOCK_CONFIG_H_
#define SYSTEM_DRIVER_CLOCK_CONFIG_H_

#include "main.h"
#include "system_config.h"

typedef enum
{
	HSE_OFF = 0x00,
	HSE_ON = RCC_CR_HSEON,
	HSE_BYP = (RCC_CR_HSEBYP | RCC_CR_HSEON),
	HSE_Default = 0x00
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
	PLL_NONE = 0x00U,
	PLL_OFF = 0x01U,
	PLL_ON = 0x02U,
}PLL_StateTypeDef;

typedef enum
{
	PLLSRC_HSE = RCC_PLLCFGR_PLLSRC_HSE,
	PLLSRC_HSI = RCC_PLLCFGR_PLLSRC_HSI,
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


typedef struct
{
	  uint32_t PLLI2SN;    /*!< Specifies the multiplication factor for PLLI2S VCO output clock.
	                            This parameter must be a number between Min_Data = 50 and Max_Data = 432.
	                            This parameter will be used only when PLLI2S is selected as Clock Source I2S or SAI */

	  uint32_t PLLI2SR;    /*!< Specifies the division factor for I2S clock.
	                            This parameter must be a number between Min_Data = 2 and Max_Data = 7.
	                            This parameter will be used only when PLLI2S is selected as Clock Source I2S or SAI */

	  uint32_t PLLI2SQ;    /*!< Specifies the division factor for SAI1 clock.
	                            This parameter must be a number between Min_Data = 2 and Max_Data = 15.
	                            This parameter will be used only when PLLI2S is selected as Clock Source SAI */

	#if defined (STM32F745xx) || defined (STM32F746xx) || defined (STM32F756xx) || defined (STM32F765xx) || defined (STM32F767xx) || \
	    defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx) || defined (STM32F750xx)
	  uint32_t PLLI2SP;    /*!< Specifies the division factor for SPDIF-RX clock.
	                            This parameter must be a value of @ref RCCEx_PLLI2SP_Clock_Divider.
	                            This parameter will be used only when PLLI2S is selected as Clock Source SPDIF-RX */
	#endif /* STM32F745xx || STM32F746xx || STM32F756xx || STM32F765xx || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx || STM32F750xx */
}RCC_PLLI2S_ConfigTypeDef;

typedef struct
{
	  uint32_t PLLSAIN;    /*!< Specifies the multiplication factor for PLLI2S VCO output clock.
	                            This parameter must be a number between Min_Data = 50 and Max_Data = 432.
	                            This parameter will be used only when PLLSAI is selected as Clock Source SAI or LTDC */

	  uint32_t PLLSAIQ;    /*!< Specifies the division factor for SAI1 clock.
	                            This parameter must be a number between Min_Data = 2 and Max_Data = 15.
	                            This parameter will be used only when PLLSAI is selected as Clock Source SAI or LTDC */

	#if defined (STM32F745xx) || defined (STM32F746xx) || defined (STM32F756xx) || defined (STM32F765xx) || defined (STM32F767xx) || \
	    defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx) || defined (STM32F750xx)
	  uint32_t PLLSAIR;    /*!< specifies the division factor for LTDC clock
	                            This parameter must be a number between Min_Data = 2 and Max_Data = 7.
	                            This parameter will be used only when PLLSAI is selected as Clock Source LTDC */
	#endif /* STM32F745xx || STM32F746xx || STM32F756xx || STM32F765xx || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx || STM32F750xx */

	  uint32_t PLLSAIP;    /*!< Specifies the division factor for 48MHz clock.
	                            This parameter must be a value of @ref RCCEx_PLLSAIP_Clock_Divider
	                            This parameter will be used only when PLLSAI is disabled */
}RCC_PLLSAI_ConfigTypeDef;

typedef struct
{
	  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
	                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

	  RCC_PLLI2S_ConfigTypeDef PLLI2S;  /*!< PLL I2S structure parameters.
	                                      This parameter will be used only when PLLI2S is selected as Clock Source I2S or SAI */

	  RCC_PLLSAI_ConfigTypeDef PLLSAI;  /*!< PLL SAI structure parameters.
	                                      This parameter will be used only when PLLI2S is selected as Clock Source SAI or LTDC */

	  uint32_t PLLI2SDivQ;           /*!< Specifies the PLLI2S division factor for SAI1 clock.
	                                      This parameter must be a number between Min_Data = 1 and Max_Data = 32
	                                      This parameter will be used only when PLLI2S is selected as Clock Source SAI */

	  uint32_t PLLSAIDivQ;           /*!< Specifies the PLLI2S division factor for SAI1 clock.
	                                      This parameter must be a number between Min_Data = 1 and Max_Data = 32
	                                      This parameter will be used only when PLLSAI is selected as Clock Source SAI */

	  uint32_t PLLSAIDivR;           /*!< Specifies the PLLSAI division factor for LTDC clock.
	                                      This parameter must be one value of @ref RCCEx_PLLSAI_DIVR */

	  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock source Selection.
	                                        This parameter can be a value of @ref RCC_RTC_Clock_Source */

	  uint32_t I2sClockSelection;      /*!< Specifies I2S Clock source Selection.
	                                        This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

	  uint32_t TIMPresSelection;      /*!< Specifies TIM Clock Prescalers Selection.
	                                       This parameter can be a value of @ref RCCEx_TIM_Prescaler_Selection */

	  uint32_t Sai1ClockSelection;     /*!< Specifies SAI1 Clock Prescalers Selection
	                                        This parameter can be a value of @ref RCCEx_SAI1_Clock_Source */

	  uint32_t Sai2ClockSelection;     /*!< Specifies SAI2 Clock Prescalers Selection
	                                        This parameter can be a value of @ref RCCEx_SAI2_Clock_Source */

	  uint32_t Usart1ClockSelection; /*!< USART1 clock source
	                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

	  uint32_t Usart2ClockSelection; /*!< USART2 clock source
	                                      This parameter can be a value of @ref RCCEx_USART2_Clock_Source */

	  uint32_t Usart3ClockSelection; /*!< USART3 clock source
	                                      This parameter can be a value of @ref RCCEx_USART3_Clock_Source */

	  uint32_t Uart4ClockSelection;  /*!< UART4 clock source
	                                      This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

	  uint32_t Uart5ClockSelection;  /*!< UART5 clock source
	                                      This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

	  uint32_t Usart6ClockSelection;  /*!< USART6 clock source
	                                      This parameter can be a value of @ref RCCEx_USART6_Clock_Source */

	  uint32_t Uart7ClockSelection;  /*!< UART7 clock source
	                                      This parameter can be a value of @ref RCCEx_UART7_Clock_Source */

	  uint32_t Uart8ClockSelection;  /*!< UART8 clock source
	                                      This parameter can be a value of @ref RCCEx_UART8_Clock_Source */

	  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
	                                      This parameter can be a value of @ref RCCEx_I2C1_Clock_Source */

	  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source
	                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

	  uint32_t I2c3ClockSelection;   /*!< I2C3 clock source
	                                      This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

	  uint32_t I2c4ClockSelection;   /*!< I2C4 clock source
	                                      This parameter can be a value of @ref RCCEx_I2C4_Clock_Source */

	  uint32_t Lptim1ClockSelection;   /*!< Specifies LPTIM1 clock source
	                                        This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source */

	  uint32_t CecClockSelection;      /*!< CEC clock source
	                                        This parameter can be a value of @ref RCCEx_CEC_Clock_Source */

	  uint32_t Clk48ClockSelection;    /*!< Specifies 48Mhz clock source used by USB OTG FS, RNG and SDMMC
	                                        This parameter can be a value of @ref RCCEx_CLK48_Clock_Source */

	  uint32_t Sdmmc1ClockSelection;     /*!< SDMMC1 clock source
	                                        This parameter can be a value of @ref RCCEx_SDMMC1_Clock_Source */

	#if defined (STM32F722xx) || defined (STM32F723xx) || defined (STM32F732xx) || defined (STM32F733xx) || defined (STM32F765xx) ||\
	    defined (STM32F767xx) || defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx) || defined (STM32F730xx)
	  uint32_t Sdmmc2ClockSelection;     /*!< SDMMC2 clock source
	                                        This parameter can be a value of @ref RCCEx_SDMMC2_Clock_Source */
	#endif /* STM32F722xx || STM32F723xx || STM32F732xx || STM32F733xx || STM32F765xx || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx || STM32F730xx */
}RCC_Periph_CLK_ConfigTypedef;


#define RCC_MCO1                        	   ((uint32_t)0x00000000U)
#define RCC_MCO2                        	   ((uint32_t)0x00000001U)


#define OSC_TYPE_HSE						   ((uint32_t)0x01)
#define OSC_TYPE_HSI						   ((uint32_t)0x02)

#define HSE_TIMEOUT_VALUE					   ((uint32_t)100U)
#define HSI_TIMEOUT_VALUE					   ((uint32_t)2U)
#define LSI_TIMEOUT_VALUE          			   ((uint32_t)2)
#define PLL_TIMEOUT_VALUE            		   ((uint32_t)2)
#define CLK_SW_TIMEOUT_VALUE				   ((uint32_t)5000)
#define PLLI2S_TIMEOUT_VALUE       			   100U
#define PLLSAI_TIMEOUT_VALUE       			   100U


#define UART_TIMEOUT_VALUE					   0x1FFFFFFU

#define MS_MAX_DELAY						   0xffffffffU


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

#define PLL_ENABLE()						   SET_BIT(RCC->CR, RCC_CR_PLLON)
#define PLL_DISEBLE()						   CLEAR_BIT(RCC->CR, RCC_CR_PLLON)

#define PLL_CONFIG(__PLL_SOURCE__, __PLLM__, __PLLN__, __PLLP__, __PLLQ__) \
        (RCC->PLLCFGR = (0x20000000 | (__PLL_SOURCE__) | (__PLLM__)| \
        ((__PLLN__) << RCC_PLLCFGR_PLLN_Pos)                          | \
        ((((__PLLP__) >> 1) -1) << RCC_PLLCFGR_PLLP_Pos)              | \
        ((__PLLQ__) << RCC_PLLCFGR_PLLQ_Pos)))


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


#define FLASH_GET_LATENCY()					   READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY)
#define FLASH_SET_LATENCY(__LATENCY__)		   \
											   CLEAR_BIT(FLASH->ACR, FLASH_ACR_LATENCY);   \
											   SET_BIT(FLASH->ACR, __LATENCY__);


#define RCC_GPIOCLK_ENABLE(__RCC_GPIO_PORT__)  SET_BIT(RCC->AHB1ENR, (uint32_t)__RCC_GPIO_PORT__)


#define RCC_GET_USART1_SOURCE() 		 	   ((uint32_t)(READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_USART1SEL)))
#define RCC_GET_USART2_SOURCE() 			   ((uint32_t)(READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_USART2SEL)))
#define RCC_GET_USART3_SOURCE() 			   ((uint32_t)(READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_USART3SEL)))
#define RCC_GET_UART4_SOURCE() 				   ((uint32_t)(READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_UART4SEL)))
#define RCC_GET_UART5_SOURCE() 				   ((uint32_t)(READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_UART5SEL)))
#define RCC_GET_USART6_SOURCE() 			   ((uint32_t)(READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_USART6SEL)))
#define RCC_GET_UART7_SOURCE() 				   ((uint32_t)(READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_UART7SEL)))
#define RCC_GET_UART8_SOURCE() 				   ((uint32_t)(READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_UART8SEL)))


#define RCC_USART1CLKSOURCE_PCLK2      		   ((uint32_t)0x00000000U)
#define RCC_USART1CLKSOURCE_SYSCLK     		   RCC_DCKCFGR2_USART1SEL_0
#define RCC_USART1CLKSOURCE_HSI        		   RCC_DCKCFGR2_USART1SEL_1
#define RCC_USART1CLKSOURCE_LSE        		   RCC_DCKCFGR2_USART1SEL


#define RCC_USART2CLKSOURCE_PCLK1       	   ((uint32_t)0x00000000U)
#define RCC_USART2CLKSOURCE_SYSCLK     	       RCC_DCKCFGR2_USART2SEL_0
#define RCC_USART2CLKSOURCE_HSI        		   RCC_DCKCFGR2_USART2SEL_1
#define RCC_USART2CLKSOURCE_LSE        		   RCC_DCKCFGR2_USART2SEL


#define RCC_USART3CLKSOURCE_PCLK1       	   ((uint32_t)0x00000000U)
#define RCC_USART3CLKSOURCE_SYSCLK     		   RCC_DCKCFGR2_USART3SEL_0
#define RCC_USART3CLKSOURCE_HSI        		   RCC_DCKCFGR2_USART3SEL_1
#define RCC_USART3CLKSOURCE_LSE        		   RCC_DCKCFGR2_USART3SEL


#define RCC_UART4CLKSOURCE_PCLK1        	   ((uint32_t)0x00000000U)
#define RCC_UART4CLKSOURCE_SYSCLK       	   RCC_DCKCFGR2_UART4SEL_0
#define RCC_UART4CLKSOURCE_HSI          	   RCC_DCKCFGR2_UART4SEL_1
#define RCC_UART4CLKSOURCE_LSE          	   RCC_DCKCFGR2_UART4SEL


#define RCC_UART5CLKSOURCE_PCLK1       		   ((uint32_t)0x00000000U)
#define RCC_UART5CLKSOURCE_SYSCLK       	   RCC_DCKCFGR2_UART5SEL_0
#define RCC_UART5CLKSOURCE_HSI          	   RCC_DCKCFGR2_UART5SEL_1
#define RCC_UART5CLKSOURCE_LSE          	   RCC_DCKCFGR2_UART5SEL


#define RCC_USART6CLKSOURCE_PCLK2      		   ((uint32_t)0x00000000U)
#define RCC_USART6CLKSOURCE_SYSCLK      	   RCC_DCKCFGR2_USART6SEL_0
#define RCC_USART6CLKSOURCE_HSI         	   RCC_DCKCFGR2_USART6SEL_1
#define RCC_USART6CLKSOURCE_LSE         	   RCC_DCKCFGR2_USART6SEL


#define RCC_UART7CLKSOURCE_PCLK1       		   ((uint32_t)0x00000000U)
#define RCC_UART7CLKSOURCE_SYSCLK      		   RCC_DCKCFGR2_UART7SEL_0
#define RCC_UART7CLKSOURCE_HSI         		   RCC_DCKCFGR2_UART7SEL_1
#define RCC_UART7CLKSOURCE_LSE         		   RCC_DCKCFGR2_UART7SEL


#define RCC_UART8CLKSOURCE_PCLK1       		   ((uint32_t)0x00000000U)
#define RCC_UART8CLKSOURCE_SYSCLK      		   RCC_DCKCFGR2_UART8SEL_0
#define RCC_UART8CLKSOURCE_HSI         		   RCC_DCKCFGR2_UART8SEL_1
#define RCC_UART8CLKSOURCE_LSE         		   RCC_DCKCFGR2_UART8SEL


Error_HandleTypeDef Clock_Setup_OSC(OSC_ConfigSetTypeDef *osc_config);
Error_HandleTypeDef Clock_Setup_Clock(Clock_ConfigTypeDef *clock_config);
void MCO_Config(uint32_t MCOx, uint32_t MCO_SRC, uint32_t MCO_DIV);
uint32_t Get_SysClock_Freq(void);
uint32_t RCC_GetPCLK_Freq(uint32_t cfgr_ppre, uint32_t cfgr_pos);
void Delay_Ms(uint32_t delay_time);

Error_HandleTypeDef PeriphCLKConfig(RCC_Periph_CLK_ConfigTypedef *periph_clk_config);

#endif /* SYSTEM_DRIVER_CLOCK_CONFIG_H_ */
