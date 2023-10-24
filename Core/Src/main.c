/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dm_motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
struct DM_Motor m4310_01;
struct DM_Motor m4310_02;
struct DM_Motor m4310_03;
struct DM_Motor m4310_04;
struct DM_Motor m4310_05;
struct DM_Motor m4310_06;
struct DM_Motor m4310_07;
struct DM_Motor m4310_08;
struct DM_Motor m4310_09;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void main_handle(void);//没有任何意义，只因while里回车有6个空格不习惯
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_TIM8_Init();
  MX_CAN2_Init();
  /* USER CODE BEGIN 2 */
    DM_Motor_Init(&m4310_01, 0x01, MIT, -12.5, 12.5, -30, 30, -20, 20); /*1*/
    DM_Motor_Init(&m4310_02, 0x02, MIT, -12.5, 12.5, -30, 30, -20, 20); /*2*/
    DM_Motor_Init(&m4310_03, 0x03, MIT, -12.5, 12.5, -30, 30, -20, 20); /*3*/
    DM_Motor_Init(&m4310_04, 0x04, MIT, -12.5, 12.5, -30, 30, -20, 20); /*2*/
    DM_Motor_Init(&m4310_05, 0x05, MIT, -12.5, 12.5, -30, 30, -20, 20); /*1*/
    DM_Motor_Init(&m4310_06, 0x06, MIT, -12.5, 12.5, -30, 30, -20, 20); /*3*/
    DM_Motor_Init(&m4310_07, 0x07, MIT, -12.5, 12.5, -30, 30, -20, 20);
    DM_Motor_Init(&m4310_08, 0x08, MIT, -12.5, 12.5, -30, 30, -20, 20);
    DM_Motor_Init(&m4310_09, 0x09, MIT, -12.5, 12.5, -30, 30, -20, 20);




    HAL_Delay(3000);
//    DM_Motor_SaveZore(&m4310_02);
//    HAL_Delay(100);
    DM_Motor_Enable(&m4310_01);
    HAL_Delay(1);
    DM_Motor_Enable(&m4310_02);
    HAL_Delay(1);
    DM_Motor_Enable(&m4310_03);
    HAL_Delay(1);
    DM_Motor_Enable(&m4310_04);
    HAL_Delay(1);
    DM_Motor_Enable(&m4310_05);
    HAL_Delay(1);
    DM_Motor_Enable(&m4310_06);
    HAL_Delay(1);
    DM_Motor_Enable(&m4310_07);
    HAL_Delay(1);
    DM_Motor_Enable(&m4310_08);
    HAL_Delay(1);
    DM_Motor_Enable(&m4310_09);
    HAL_Delay(1);



//    HAL_TIM_Base_Start_IT(&htim8);
//    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
//    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);/*初始化通道1*/
//    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
//    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
//        main_handle();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /*天线往上运动*/
        DM_Motor_MitCtrl(&m4310_01, 0, 4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_02, 0, 8, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_03, 0, 4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_04, 0, 12, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_05, 0, 4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_06, 0, 12, 0, 0, 1);

        HAL_Delay(5000);

        /*到达位置停止移动*/
        DM_Motor_MitCtrl(&m4310_01, 0, 0, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_02, 0, 0, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_03, 0, 0, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_04, 0, 0, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_05, 0, 0, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_06, 0, 0, 0, 0, 1);

        /*待测物前移*/
        DM_Motor_MitCtrl(&m4310_07, 0, 4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_08, 0, 4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_09, 0, 4, 0, 0, 1);
        HAL_Delay(5000);

        /*待测物后移*/
        DM_Motor_MitCtrl(&m4310_07, 0, 4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_08, 0, 4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_09, 0, 4, 0, 0, 1);
        HAL_Delay(5000);

        /*待测物停止*/
        DM_Motor_MitCtrl(&m4310_07, 0, 0, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_08, 0, 0, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_09, 0, 0, 0, 0, 1);
        HAL_Delay(100);

        /*天线往下运动*/
        DM_Motor_MitCtrl(&m4310_01, 0, -4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_02, 0, -8, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_03, 0, -12, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_04, 0, -8, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_05, 0, -4, 0, 0, 1);
        HAL_Delay(1);
        DM_Motor_MitCtrl(&m4310_06, 0, -12, 0, 0, 1);
        HAL_Delay(6000);

//        DM_Motor_Disable(&m4310_01);
//        HAL_Delay(1);
//        DM_Motor_Disable(&m4310_02);
//        HAL_Delay(1);
//        DM_Motor_Disable(&m4310_03);
//        HAL_Delay(1);
//        DM_Motor_Disable(&m4310_04);
//        HAL_Delay(1);
//        DM_Motor_Disable(&m4310_05);
//        HAL_Delay(1);
//        DM_Motor_Disable(&m4310_06);
//        HAL_Delay(1);




//        int dt1 = 1000;/* dt1=1000ms */
//
//                __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, 500);/* 0 */
//        HAL_Delay(dt1);
//                __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, 2500);/* 180 */
//        HAL_Delay(dt1);

//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
//        HAL_Delay(500);
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
//        HAL_Delay(500);
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
//        HAL_Delay(200);
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
//        HAL_Delay(200);
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
//        HAL_Delay(300);
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
//        HAL_Delay(300);
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
float dePos = 0;
float deVel = 0;

//uint16_t cnt = 0;
void main_handle(void) {
//    DM_Motor_MitCtrl(&testMotor, dePos, 0, 0, 30, 1);
//    DM_Motor_MitCtrl(&m4310_01, 0, deVel, 0, 0, 2);
//    DM_Motor_MitCtrl(&testMotor, 0, 0, 0.5, 0, 0);
//    DM_Motor_PosVelCtrl(&m4310_01, dePos, deVel);
//    DM_Motor_VelCtrl(&m4310_01, deVel);
//    DM_Motor_MitCtrl(&m4310_02, dePos, 0, 0, 30, 1);

//    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//    cnt++;
//    if (cnt == 20)
//    {
//        DM_Motor_Disable(&m4310_01);
//    }
    HAL_Delay(500);
}

/* 用户重定义can发送接口 */
void DM_Motor_CanSend(uint16_t can_id, uint8_t *data, uint8_t size) {
    CAN_TxHeaderTypeDef txHeader;
    uint32_t mailBox;
    txHeader.StdId = can_id;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = size;

    HAL_CAN_AddTxMessage(&hcan2, &txHeader, data, &mailBox);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (hcan == &hcan2) {
        CAN_RxHeaderTypeDef rxHeader;
        uint8_t rxData[8];
        HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &rxHeader, rxData);
        if (rxHeader.StdId == 0) {
            /* 用户调用 */
            DM_Motor_RecieveHandle(rxData);
        }
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
