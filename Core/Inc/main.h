/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g0xx_hal.h"

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
#define BTN_UP_Pin GPIO_PIN_13
#define BTN_UP_GPIO_Port GPIOC
#define BTN_DOWN_Pin GPIO_PIN_0
#define BTN_DOWN_GPIO_Port GPIOA
#define LS_Y2_Pin GPIO_PIN_6
#define LS_Y2_GPIO_Port GPIOA
#define LS_Y1_Pin GPIO_PIN_7
#define LS_Y1_GPIO_Port GPIOA
#define DIR_Y_Pin GPIO_PIN_0
#define DIR_Y_GPIO_Port GPIOB
#define STEP_Y_Pin GPIO_PIN_1
#define STEP_Y_GPIO_Port GPIOB
#define SLEEP_Y_Pin GPIO_PIN_2
#define SLEEP_Y_GPIO_Port GPIOB
#define LS_X1_Pin GPIO_PIN_13
#define LS_X1_GPIO_Port GPIOB
#define LS_X2_Pin GPIO_PIN_14
#define LS_X2_GPIO_Port GPIOB
#define RESET_Y_Pin GPIO_PIN_7
#define RESET_Y_GPIO_Port GPIOC
#define MS3_Y_Pin GPIO_PIN_10
#define MS3_Y_GPIO_Port GPIOA
#define MS2_Y_Pin GPIO_PIN_11
#define MS2_Y_GPIO_Port GPIOA
#define MS1_Y_Pin GPIO_PIN_12
#define MS1_Y_GPIO_Port GPIOA
#define ENABLE_Y_Pin GPIO_PIN_15
#define ENABLE_Y_GPIO_Port GPIOA
#define DIR_X_Pin GPIO_PIN_0
#define DIR_X_GPIO_Port GPIOD
#define STEP_X_Pin GPIO_PIN_1
#define STEP_X_GPIO_Port GPIOD
#define SLEEP_X_Pin GPIO_PIN_2
#define SLEEP_X_GPIO_Port GPIOD
#define RESET_X_Pin GPIO_PIN_3
#define RESET_X_GPIO_Port GPIOD
#define MS3_X_Pin GPIO_PIN_3
#define MS3_X_GPIO_Port GPIOB
#define MS2_X_Pin GPIO_PIN_4
#define MS2_X_GPIO_Port GPIOB
#define MS1_X_Pin GPIO_PIN_5
#define MS1_X_GPIO_Port GPIOB
#define ENABLE_X_Pin GPIO_PIN_6
#define ENABLE_X_GPIO_Port GPIOB
#define BTN_LEFT_Pin GPIO_PIN_8
#define BTN_LEFT_GPIO_Port GPIOB
#define BTN_RIGHT_Pin GPIO_PIN_9
#define BTN_RIGHT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
uint8_t opposite(uint8_t a);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
