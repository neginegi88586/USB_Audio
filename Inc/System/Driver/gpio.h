/*
 * gpio.h
 *
 *  Created on: Nov 28, 2024
 *      Author: idune
 */

#ifndef INC_SYSTEM_DRIVER_GPIO_H_
#define INC_SYSTEM_DRIVER_GPIO_H_

#include "main.h"

typedef enum
{
	GPIO_RESET = 0,
	GPIO_SET
}GPIO_State;

typedef struct
{
	uint32_t PIN;
	uint32_t MODE;
	uint32_t PULL;
	uint32_t SPEED;
	uint32_t ALT;
}GPIO_ConfigTypeDef;


#define  GPIO_SPEED_FREQ_LOW         ((uint32_t)0x00000000U)  /*!< Low speed     */
#define  GPIO_SPEED_FREQ_MEDIUM      ((uint32_t)0x00000001U)  /*!< Medium speed  */
#define  GPIO_SPEED_FREQ_HIGH        ((uint32_t)0x00000002U)  /*!< Fast speed    */
#define  GPIO_SPEED_FREQ_VERY_HIGH   ((uint32_t)0x00000003U)  /*!< High speed    */


#define  GPIO_NOPULL        					((uint32_t)0x00000000U)   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP        					((uint32_t)0x00000001U)   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN      					((uint32_t)0x00000002U)   /*!< Pull-down activation                */


#define GPIO_MODE_Pos                           0U
#define GPIO_MODE                               (0x3UL << GPIO_MODE_Pos)
#define MODE_INPUT                              (0x0UL << GPIO_MODE_Pos)
#define MODE_OUTPUT                             (0x1UL << GPIO_MODE_Pos)
#define MODE_AF                                 (0x2UL << GPIO_MODE_Pos)
#define MODE_ANALOG                             (0x3UL << GPIO_MODE_Pos)
#define OUTPUT_TYPE_Pos                         4U
#define OUTPUT_TYPE                             (0x1UL << OUTPUT_TYPE_Pos)
#define OUTPUT_PP                               (0x0UL << OUTPUT_TYPE_Pos)
#define OUTPUT_OD                               (0x1UL << OUTPUT_TYPE_Pos)
#define EXTI_MODE_Pos                           16U
#define EXTI_MODE                               (0x3UL << EXTI_MODE_Pos)
#define EXTI_IT                                 (0x1UL << EXTI_MODE_Pos)
#define EXTI_EVT                                (0x2UL << EXTI_MODE_Pos)
#define TRIGGER_MODE_Pos                         20U
#define TRIGGER_MODE                            (0x7UL << TRIGGER_MODE_Pos)
#define TRIGGER_RISING                          (0x1UL << TRIGGER_MODE_Pos)
#define TRIGGER_FALLING                         (0x2UL << TRIGGER_MODE_Pos)


#define  GPIO_MODE_INPUT                        MODE_INPUT                                                  /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT_PP                    (MODE_OUTPUT | OUTPUT_PP)                                   /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_OUTPUT_OD                    (MODE_OUTPUT | OUTPUT_OD)                                   /*!< Output Open Drain Mode                */
#define  GPIO_MODE_AF_PP                        (MODE_AF | OUTPUT_PP)                                       /*!< Alternate Function Push Pull Mode     */
#define  GPIO_MODE_AF_OD                        (MODE_AF | OUTPUT_OD)                                       /*!< Alternate Function Open Drain Mode    */

#define  GPIO_MODE_ANALOG                       MODE_ANALOG                                                 /*!< Analog Mode  */

#define  GPIO_MODE_IT_RISING                    (MODE_INPUT | EXTI_IT | TRIGGER_RISING)                     /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_FALLING                   (MODE_INPUT | EXTI_IT | TRIGGER_FALLING)                    /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RISING_FALLING            (MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

#define  GPIO_MODE_EVT_RISING                   (MODE_INPUT | EXTI_EVT | TRIGGER_RISING)                     /*!< External Event Mode with Rising edge trigger detection             */
#define  GPIO_MODE_EVT_FALLING                  (MODE_INPUT | EXTI_EVT | TRIGGER_FALLING)                    /*!< External Event Mode with Falling edge trigger detection            */
#define  GPIO_MODE_EVT_RISING_FALLING           (MODE_INPUT | EXTI_EVT | TRIGGER_RISING | TRIGGER_FALLING)   /*!< External Event Mode with Rising/Falling edge trigger detection     */


#if defined (STM32F722xx) || defined (STM32F723xx) || defined (STM32F732xx) || defined (STM32F733xx) || defined (STM32F730xx)
#define GPIO_GET_INDEX(__GPIOx__)   (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                              ((__GPIOx__) == (GPIOB))? 1U :\
                                              ((__GPIOx__) == (GPIOC))? 2U :\
                                              ((__GPIOx__) == (GPIOD))? 3U :\
                                              ((__GPIOx__) == (GPIOE))? 4U :\
                                              ((__GPIOx__) == (GPIOF))? 5U :\
                                              ((__GPIOx__) == (GPIOG))? 6U :\
                                              ((__GPIOx__) == (GPIOH))? 7U : 8U)
#endif /* STM32F722xx || STM32F723xx || STM32F732xx || STM32F733xx || STM32F730xx */


void GPIO_Config(GPIO_TypeDef *GPIOx, GPIO_ConfigTypeDef *GPIO_Conf);
void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t Pin, GPIO_State State);

#endif /* INC_SYSTEM_DRIVER_GPIO_H_ */
