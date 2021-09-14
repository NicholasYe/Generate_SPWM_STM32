/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//一周期内分多少段
#define SPWM_N 840

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//序列计数
static int spwmCnt = 0;
//SPWM计数
static int spwmData[SPWM_N] = {
	4012,4038,4063,4088,4114,4139,4165,4190,4215,4241,4266,4292,4317,4342,4367,4393,
	4418,4443,4468,4494,4519,4544,4569,4594,4619,4644,4669,4694,4719,4744,4768,4793,
	4818,4842,4867,4892,4916,4941,4965,4989,5014,5038,5062,5086,5110,5134,5158,5182,
	5206,5230,5253,5277,5300,5324,5347,5371,5394,5417,5440,5463,5486,5509,5532,5554,
	5577,5599,5622,5644,5666,5688,5710,5732,5754,5776,5797,5819,5840,5862,5883,5904,
	5925,5946,5967,5987,6008,6028,6049,6069,6089,6109,6129,6149,6168,6188,6207,6227,
	6246,6265,6284,6302,6321,6340,6358,6376,6394,6412,6430,6448,6465,6483,6500,6517,
	6534,6551,6568,6585,6601,6617,6633,6649,6665,6681,6697,6712,6727,6742,6757,6772,
	6787,6801,6815,6830,6844,6858,6871,6885,6898,6911,6924,6937,6950,6962,6975,6987,
	6999,7011,7023,7034,7046,7057,7068,7079,7089,7100,7110,7120,7130,7140,7150,7159,
	7169,7178,7187,7195,7204,7212,7221,7229,7237,7244,7252,7259,7266,7273,7280,7286,
	7293,7299,7305,7311,7317,7322,7327,7332,7337,7342,7347,7351,7355,7359,7363,7367,
	7370,7373,7376,7379,7382,7384,7386,7389,7390,7392,7394,7395,7396,7397,7398,7398,
	7399,7399,7399,7399,7398,7398,7397,7396,7395,7394,7392,7390,7389,7386,7384,7382,
	7379,7376,7373,7370,7367,7363,7359,7355,7351,7347,7342,7337,7332,7327,7322,7317,
	7311,7305,7299,7293,7286,7280,7273,7266,7259,7252,7244,7237,7229,7221,7212,7204,
	7195,7187,7178,7169,7159,7150,7140,7130,7120,7110,7100,7089,7079,7068,7057,7046,
	7034,7023,7011,6999,6987,6975,6962,6950,6937,6924,6911,6898,6885,6871,6858,6844,
	6830,6815,6801,6787,6772,6757,6742,6727,6712,6697,6681,6665,6649,6633,6617,6601,
	6585,6568,6551,6534,6517,6500,6483,6465,6448,6430,6412,6394,6376,6358,6340,6321,
	6302,6284,6265,6246,6227,6207,6188,6168,6149,6129,6109,6089,6069,6049,6028,6008,
	5987,5967,5946,5925,5904,5883,5862,5840,5819,5797,5776,5754,5732,5710,5688,5666,
	5644,5622,5599,5577,5554,5532,5509,5486,5463,5440,5417,5394,5371,5347,5324,5300,
	5277,5253,5230,5206,5182,5158,5134,5110,5086,5062,5038,5014,4989,4965,4941,4916,
	4892,4867,4842,4818,4793,4768,4744,4719,4694,4669,4644,4619,4594,4569,4544,4519,
	4494,4468,4443,4418,4393,4367,4342,4317,4292,4266,4241,4215,4190,4165,4139,4114,
	4088,4063,4038,4012,3987,3961,3936,3911,3885,3860,3834,3809,3784,3758,3733,3707,
	3682,3657,3632,3606,3581,3556,3531,3505,3480,3455,3430,3405,3380,3355,3330,3305,
	3280,3255,3231,3206,3181,3157,3132,3107,3083,3058,3034,3010,2985,2961,2937,2913,
	2889,2865,2841,2817,2793,2769,2746,2722,2699,2675,2652,2628,2605,2582,2559,2536,
	2513,2490,2467,2445,2422,2400,2377,2355,2333,2311,2289,2267,2245,2223,2202,2180,
	2159,2137,2116,2095,2074,2053,2032,2012,1991,1971,1950,1930,1910,1890,1870,1850,
	1831,1811,1792,1772,1753,1734,1715,1697,1678,1659,1641,1623,1605,1587,1569,1551,
	1534,1516,1499,1482,1465,1448,1431,1414,1398,1382,1366,1350,1334,1318,1302,1287,
	1272,1257,1242,1227,1212,1198,1184,1169,1155,1141,1128,1114,1101,1088,1075,1062,
	1049,1037,1024,1012,1000,988,976,965,953,942,931,920,910,899,889,879,869,859,849,
	840,830,821,812,804,795,787,778,770,762,755,747,740,733,726,719,713,706,700,694,
	688,682,677,672,667,662,657,652,648,644,640,636,632,629,626,623,620,617,615,613,
	610,609,607,605,604,603,602,601,601,600,600,600,600,601,601,602,603,604,605,607,
	609,610,613,615,617,620,623,626,629,632,636,640,644,648,652,657,662,667,672,677,
	682,688,694,700,706,713,719,726,733,740,747,755,762,770,778,787,795,804,812,821,
	830,840,849,859,869,879,889,899,910,920,931,942,953,965,976,988,1000,1012,1024,
	1037,1049,1062,1075,1088,1101,1114,1128,1141,1155,1169,1184,1198,1212,1227,1242,
	1257,1272,1287,1302,1318,1334,1350,1366,1382,1398,1414,1431,1448,1465,1482,1499,
	1516,1534,1551,1569,1587,1605,1623,1641,1659,1678,1697,1715,1734,1753,1772,1792,
	1811,1831,1850,1870,1890,1910,1930,1950,1971,1991,2012,2032,2053,2074,2095,2116,
	2137,2159,2180,2202,2223,2245,2267,2289,2311,2333,2355,2377,2400,2422,2445,2467,
	2490,2513,2536,2559,2582,2605,2628,2652,2675,2699,2722,2746,2769,2793,2817,2841,
	2865,2889,2913,2937,2961,2985,3010,3034,3058,3083,3107,3132,3157,3181,3206,3231,
	3255,3280,3305,3330,3355,3380,3405,3430,3455,3480,3505,3531,3556,3581,3606,3632,
	3657,3682,3707,3733,3758,3784,3809,3834,3860,3885,3911,3936,3961,3987
};


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(2000);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_Delay(2000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
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
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

//比较中断服务函数
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim1)
  {
    TIM1->CCR1 = spwmData[spwmCnt++];
    if(spwmCnt >= SPWM_N)
    {
      spwmCnt = 0;
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
  while (1)
  {
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
