/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "gpio.h"
#include "tim.h"
#include "display.h"
#include <string.h>

void SystemClock_Config(void);

extern uint64_t disp_time;

uint64_t saved_time;
double num_to_display = 10;

char retazec[] = "Marian\0";
//char retazec[] = "Marian_Tvarozek_98374_Peter_Skunda_98371";

extern char pole[4];
int start = 0;

int main(void)
{

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  SystemClock_Config();

  MX_GPIO_Init();

  setSegments();
  setDigits();

  LL_mDelay(2000);

  resetDigits();
  resetSegments();

  MX_TIM2_Init();

  int dlzka = strlen(retazec);
  while (1)
  {

	  for (int i = 0; i < dlzka; i++){
		  while(disp_time <= (saved_time + 100)){
			  ;
		  }
		  saved_time = disp_time;
		  pole[0] = retazec[i];
		  pole[1] = retazec[i+1];
		  pole[2] = retazec[i+2];
		  pole[3] = retazec[i+3];
		  pole[4] = '\0';

		  //start = 0;

		  //LL_mDelay(500);
		  //updateDisplay(pole);

	  }
	  for (int j = dlzka; j > 0; j--){
		  while(disp_time <= (saved_time + 100)){
			  ;
		  }
		  saved_time = disp_time;
		  pole[0] = retazec[j-4];
		  pole[1] = retazec[j-3];
		  pole[2] = retazec[j-2];
		  pole[3] = retazec[j-1];
		  pole[4] = '\0';
		  /*
		  while(start != 1){
			  ;
		  }
		  start = 0;
		  */
		  //LL_mDelay(500);
		  //updateDisplay(pole);
	  }
	  /*
	  if(disp_time > (saved_time + 100))
	  {
		  displayNumber(num_to_display);
	  	  num_to_display -= 0.10;
	  	  saved_time = disp_time;

	  	  if(num_to_display <= 0)
	  	  {
	  		  num_to_display = 100;
	  	  }
	  }
	  */
  }


}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SYSTICK_EnableIT();
  LL_SetSystemCoreClock(8000000);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
