/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_D2_Pin GPIO_PIN_2
#define LCD_D2_GPIO_Port GPIOE
#define LCD_D3_Pin GPIO_PIN_3
#define LCD_D3_GPIO_Port GPIOE
#define LCD_D4_Pin GPIO_PIN_4
#define LCD_D4_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_5
#define LCD_D5_GPIO_Port GPIOE
#define LCD_D6_Pin GPIO_PIN_6
#define LCD_D6_GPIO_Port GPIOE
#define LCD_CS_Pin GPIO_PIN_2
#define LCD_CS_GPIO_Port GPIOC
#define LCD_RST_Pin GPIO_PIN_3
#define LCD_RST_GPIO_Port GPIOC
#define ADC_CLK_Pin GPIO_PIN_5
#define ADC_CLK_GPIO_Port GPIOA
#define ADC_DOUT_Pin GPIO_PIN_6
#define ADC_DOUT_GPIO_Port GPIOA
#define ADC_DIN_Pin GPIO_PIN_7
#define ADC_DIN_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_4
#define LCD_RS_GPIO_Port GPIOC
#define LCD_WR_Pin GPIO_PIN_5
#define LCD_WR_GPIO_Port GPIOC
#define LCD_D7_Pin GPIO_PIN_7
#define LCD_D7_GPIO_Port GPIOE
#define LCD_D8_Pin GPIO_PIN_8
#define LCD_D8_GPIO_Port GPIOE
#define LCD_D9_Pin GPIO_PIN_9
#define LCD_D9_GPIO_Port GPIOE
#define LCD_D10_Pin GPIO_PIN_10
#define LCD_D10_GPIO_Port GPIOE
#define LCD_D11_Pin GPIO_PIN_11
#define LCD_D11_GPIO_Port GPIOE
#define LCD_D12_Pin GPIO_PIN_12
#define LCD_D12_GPIO_Port GPIOE
#define LCD_D13_Pin GPIO_PIN_13
#define LCD_D13_GPIO_Port GPIOE
#define LCD_D14_Pin GPIO_PIN_14
#define LCD_D14_GPIO_Port GPIOE
#define LCD_D15_Pin GPIO_PIN_15
#define LCD_D15_GPIO_Port GPIOE
#define B1_Pin GPIO_PIN_10
#define B1_GPIO_Port GPIOB
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define B2_Pin GPIO_PIN_11
#define B2_GPIO_Port GPIOB
#define B2_EXTI_IRQn EXTI15_10_IRQn
#define B3_Pin GPIO_PIN_12
#define B3_GPIO_Port GPIOB
#define B3_EXTI_IRQn EXTI15_10_IRQn
#define B4_Pin GPIO_PIN_13
#define B4_GPIO_Port GPIOB
#define B4_EXTI_IRQn EXTI15_10_IRQn
#define B5_Pin GPIO_PIN_14
#define B5_GPIO_Port GPIOB
#define B5_EXTI_IRQn EXTI15_10_IRQn
#define B5B15_Pin GPIO_PIN_15
#define B5B15_GPIO_Port GPIOB
#define B5B15_EXTI_IRQn EXTI15_10_IRQn
#define ADC_BUSY_Pin GPIO_PIN_6
#define ADC_BUSY_GPIO_Port GPIOB
#define ADC_CS_Pin GPIO_PIN_8
#define ADC_CS_GPIO_Port GPIOB
#define LCD_D0_Pin GPIO_PIN_0
#define LCD_D0_GPIO_Port GPIOE
#define LCD_D1_Pin GPIO_PIN_1
#define LCD_D1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
