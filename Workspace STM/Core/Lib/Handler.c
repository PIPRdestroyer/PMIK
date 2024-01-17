#define EEPROM_PAGE 3 // Starting page in EEPROM memory
#define EEPROM_OFFSET 1 //Starting byte in EEPROM memory
#define RxBuf_SIZE 	 10 //Uart buffer size

#include "Handler.h"
#include "TM1637.h"
#include "EEPROM.h"
#include "VL53_API_Interface.h"
#include "stdio.h"
#include "tim.h"
#include "usart.h"
#include <string.h>


uint8_t status = 0; //Variable that tells what interrupt is done at this moment
/*
 * status = 1 measure
 * status = 2 button save
 * status = 3 timer
 *
 *  */
uint8_t RxBuf[RxBuf_SIZE];
uint8_t mode = 0; // 0 = single 1 = continuous
uint8_t TofDataRead = 0;
uint16_t Measure = 0;
uint8_t announcement[20];

uint8_t state_flag[3] = {0, 0, 0}; // variable that tells if the full cycle of measurement was finnished
//full cycle is considered as finnished when state_flag = {1, 1, 1} after cycle they will be reseted to 0
// {0,0,0} <==> {measurement, write to EEPROM, display}

void hardwareInit()
{
  huart2.Init.BaudRate = 115200;
  htim1.Init.Prescaler = 6399;
  htim1.Init.Period = 9999;
  htim2.Init.Prescaler = 63999;
  htim2.Init.Period = 9999;
}

void peripherialsInit()
{
  TM1637_SetBrightness(3);
  VL53_init();
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_UARTEx_ReceiveToIdle_IT(&huart2, RxBuf, RxBuf_SIZE);
}

void switchMode()
{
	/* Function that switches mode from 0 = single to 1 = continuous*/
	if(mode == 0)
	{
		mode = 1;
	}
	else if (mode == 1)
	{
		mode = 0;
	}
}

void Compute(uint8_t mode, uint8_t status)
{
	if (mode == 0)
	{
		singleMode(status);
	}
	else if (mode == 1)
	{
		continuousMode(status);
	}
}

void singleMode(uint8_t status)
{
	if (status == 2)
	{
		readMeasure();
		Display(Measure);
		saveToMem(Measure);
	}
}
void continuousMode(uint8_t status)
{
	if (status == 1)
	{
		readMeasure();
	}
	else if (status == 2)
	{
		saveToMem(Measure);
	}
	else if (status == 3)
	{
		Display(Measure);
	}
}

void readMeasure()
{
	/*Function that reads distance from VL530L0X and returns as uint8_t */
	//measure if data is ready
	if(TofDataRead == 1)
		{
			Measure = VL53_MEASURE();
			TofDataRead = 0;
		}
		//data limit
	if (Measure > 1250)
		{
			Measure = 1250;
		}
	state_flag[0] = 1; //Change temporary progress flag to 1 (1 = task done)
}

void Display(uint16_t measure)
{
	TM1637_DisplayDecimal(measure, 0);
	state_flag[2] = 1; //Change temporary progress flag to 1 (1 = task done)
}

void saveToMem(uint16_t measure)
{
	EEPROM_Write_NUM(EEPROM_PAGE, EEPROM_OFFSET, measure);
	state_flag[1] = 1; //Change temporary progress flag to 1 (1 = task done)
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//save button
	if (GPIO_Pin == B2_Pin)
	{
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		status = 2;
	}
	//change state button
	if (GPIO_Pin == B1_Pin)
	{
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		switchMode();
	}
	if(GPIO_Pin == TOF_INT_Pin)
	{
		VL53_CLEAR_INTERRUPT_DATA();
		TofDataRead = 1;
		status = 1;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
		{
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			status = 3;
		}
	if(htim->Instance == TIM2)
	{
		char sendData[6];
		sprintf((char*)sendData, "%u\n", Measure);
		HAL_UART_Transmit_IT(&huart2, (uint8_t*)&sendData, strlen(sendData));
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART2)
		{
			if (strcmp((char*)RxBuf, "info") == 0)
			{
				sprintf((char *)announcement, "Device ID:3421\n");
			}
			else if (strcmp((char*)RxBuf, "measure") == 0)
			{
				sprintf((char *)announcement, "Measure: %u\n", Measure);
			}
			else
			{
				sprintf((char *)announcement, "Wrong command\n");
			}
			HAL_UARTEx_ReceiveToIdle_IT(&huart2, RxBuf, RxBuf_SIZE);
			HAL_UART_Transmit_IT(&huart2, announcement, strlen(announcement));
			memset(RxBuf, 0, RxBuf_SIZE);
		}
}

/*
 * status = 1 measure
 * status = 2 button save
 * status = 3 timer
 *
 *  */

