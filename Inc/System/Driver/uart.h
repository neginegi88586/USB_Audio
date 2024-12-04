/*
 * uart.h
 *
 *  Created on: Nov 28, 2024
 *      Author: idune
 */

#ifndef INC_SYSTEM_DRIVER_UART_H_
#define INC_SYSTEM_DRIVER_UART_H_

#include "main.h"

typedef struct
{
	uint32_t BAUD;
	uint32_t WORD_LEN;
	uint32_t STOP_BIT;
	uint32_t PARITY;
	uint32_t MODE;
	uint32_t FLOW_CTRL;
	uint32_t OVER_SAMPLE;
	uint32_t ONEB_SAMPLE;
}UART_ConfigType;

typedef struct
{
	uint32_t ADV_FEAT_INIT;
	uint32_t TXP_LEVEL_INV;
	uint32_t RXP_LEVEL_INV;
	uint32_t DATA_INV;
	uint32_t SWAP;
	uint32_t OVER_RUN_DIS;
	uint32_t DMA_DIS_ON_RX_ERR;
	uint32_t AUTO_BAUD_EN;
	uint32_t AUTO_BAUD_MODE;
	uint32_t MSB_FIRST;
}UART_AdvFeat_ConfigTypeDef;

typedef struct __UART_Handle
{
	USART_TypeDef *INSTANCE;
	UART_ConfigType INIT;
	UART_AdvFeat_ConfigTypeDef ADV_INIT;
	const uint8_t *TX_BUFF_PTR;
	uint16_t TX_XFER_SIZE;
	__IO uint16_t TX_XFER_COUNT;
	uint8_t *RX_BUFF_PTR;
	uint16_t RX_XFER_SIZE;
	__IO uint16_t RX_XFER_COUNT;
	uint16_t MSK;
	__IO uint32_t RECEPT_TYP;
	__IO uint32_t RX_EVT_TYP;
	void (*TX_ISR)(struct __UART_Handle *huart);
	void (*RX_ISR)(struct __UART_Handle *huart);


	LockTypeDef LOCK;
	__IO uint32_t gSTATE;
	__IO uint32_t RX_STATE;
	__IO uint32_t ERR_CODE;
}UART_HandleTypeDef;

typedef enum
{
  UART_CLOCKSOURCE_PCLK1      = 0x00U,    /*!< PCLK1 clock source  */
  UART_CLOCKSOURCE_PCLK2      = 0x01U,    /*!< PCLK2 clock source  */
  UART_CLOCKSOURCE_HSI        = 0x02U,    /*!< HSI clock source    */
  UART_CLOCKSOURCE_SYSCLK     = 0x04U,    /*!< SYSCLK clock source */
  UART_CLOCKSOURCE_LSE        = 0x08U,    /*!< LSE clock source       */
  UART_CLOCKSOURCE_UNDEFINED  = 0x10U     /*!< Undefined clock source */
} UART_ClockSourceTypeDef;


#define USART_CR1_FIELDS  ((uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | USART_CR1_TE | USART_CR1_RE | \
                                      USART_CR1_OVER8)) /*!< UART or USART CR1 fields of parameters set by UART_SetConfig API */

#define USART_CR3_FIELDS  ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE |\
                                      USART_CR3_ONEBIT)) /*!< UART or USART CR3 fields of parameters set by UART_SetConfig API */

#define UART_BRR_MIN    0x10U        /* UART BRR minimum authorized value */
#define UART_BRR_MAX    0x0000FFFFU  /* UART BRR maximum authorized value */


#define UART_STATE_RST				0x00U
#define UART_STATE_RDY				0x20U

#define UART_STATE_BUSY				0x24U
#define UART_STATE_BUSY_TX			0x21U
#define UART_STATE_BUSY_RX			0x22U
#define UART_STATE_BUSY_TX_RX		0x23U

#define UART_STATE_TIMEOUT			0xa0U
#define UART_STATE_ERROR			0xe0U


#define UART_DIV_SAMPLING8(__PCLK__, __BAUD__)   ((((__PCLK__)*2U) + ((__BAUD__)/2U)) / (__BAUD__))
#define UART_DIV_SAMPLING16(__PCLK__, __BAUD__)  (((__PCLK__) + ((__BAUD__)/2U)) / (__BAUD__))


#define UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__)       \
  do {                                                        \
    if((__HANDLE__)->INSTANCE == USART1)                      \
    {                                                         \
      switch(RCC_GET_USART1_SOURCE())                   	  \
      {                                                       \
        case RCC_USART1CLKSOURCE_PCLK2:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK2;         \
          break;                                              \
        case RCC_USART1CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART1CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART1CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
      }                                                       \
    }                                                         \
    else if((__HANDLE__)->INSTANCE == USART2)                 \
    {                                                         \
      switch(RCC_GET_USART2_SOURCE())                   	  \
      {                                                       \
        case RCC_USART2CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_USART2CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART2CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART2CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
      }                                                       \
    }                                                         \
    else if((__HANDLE__)->INSTANCE == USART3)                 \
    {                                                         \
      switch(RCC_GET_USART3_SOURCE())          		          \
      {                                                       \
        case RCC_USART3CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_USART3CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART3CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART3CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
      }                                                       \
    }                                                         \
    else if((__HANDLE__)->INSTANCE == UART4)                  \
    {                                                         \
      switch(RCC_GET_UART4_SOURCE())                    \
      {                                                       \
        case RCC_UART4CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_UART4CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_UART4CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_UART4CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
      }                                                       \
    }                                                         \
    else if ((__HANDLE__)->INSTANCE == UART5)                 \
    {                                                         \
      switch(RCC_GET_UART5_SOURCE())                    	  \
      {                                                       \
        case RCC_UART5CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_UART5CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_UART5CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_UART5CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
      }                                                       \
    }                                                         \
    else if((__HANDLE__)->INSTANCE == USART6)                 \
    {                                                         \
      switch(RCC_GET_USART6_SOURCE())                   	  \
      {                                                       \
        case RCC_USART6CLKSOURCE_PCLK2:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK2;         \
          break;                                              \
        case RCC_USART6CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART6CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART6CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
      }                                                       \
    }                                                         \
    else if ((__HANDLE__)->INSTANCE == UART7)                 \
    {                                                         \
      switch(RCC_GET_UART7_SOURCE())                    	  \
      {                                                       \
        case RCC_UART7CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_UART7CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_UART7CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_UART7CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
      }                                                       \
    }                                                         \
    else if ((__HANDLE__)->INSTANCE == UART8)                 \
    {                                                         \
      switch(RCC_GET_UART8_SOURCE())                    	  \
      {                                                       \
        case RCC_UART8CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_UART8CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_UART8CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_UART8CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
      }                                                       \
    }                                                         \
    else                                                      \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;         \
    }                                                         \
  } while(0U)


Error_HandleTypeDef UART_Config(UART_HandleTypeDef *huart);
Error_HandleTypeDef UART_SetConfig(UART_HandleTypeDef *huart);
void UART_Pin_Config(UART_HandleTypeDef *huart);
Error_HandleTypeDef UART_CheckIdleState(UART_HandleTypeDef *huart);
Error_HandleTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status,
                                              uint32_t Tickstart, uint32_t Timeout);
Error_HandleTypeDef UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);

#endif /* INC_SYSTEM_DRIVER_UART_H_ */
