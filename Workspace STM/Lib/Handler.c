#define EEPROM_PAGE 3 // Starting page in EEPROM memory
#define EEPROM_OFFSET 1 //Starting byte in EEPROM memory

#include "Handler.h"
#include "TM1637.h"
#include "EEPROM.h"
#include "VL53_API_Interface.h"
#include "tim.h"
#include "usart.h"


uint8_t status = 0;
uint8_t mode = 0; // 0 single 1 cont
uint8_t TofDataRead = 0;
uint16_t Measure = 0;
uint8_t znak;
uint8_t komunikat[20];

uint8_t state_flag[3] = {0, 0, 0}; // variable that tells if the full cycle of measurement was finnished
//full cycle is considered as finnished when state_flag = {1, 1, 1} after cycle they will be reseted to 0
// {0,0,0} <==> {measurement, write to EEPROM, display}

void peripherialsInit()
{
  TM1637_SetBrightness(3);
  VL53_init();
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_UART_Receive_IT(&huart2, &znak, 1);
}

void switchMode()
{
	/* Function that switches mode from 0 = single to 1 = cont*/
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
//	for(int i = 0;i<3;i++)
//	  	if (state_flag[i] == 0)
//	  	{
//	  		cycleBegin(status);
//	  	}
//	  	else if (state_flag[i] == 1)
//	  	{
//	  		cycleEnd();
//	  	}
}

/*
 * status = 1 measure
 * status = 2 button save
 * status = 3 timer
 *
 *  */

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



//void cycleBegin()
//{
//	/*Function that starts the measurement cycle*/
//	uint16_t Measure = readMeasure();
//	saveToMem(Measure);
//	Display(Measure);
//}
//
//void cycleEnd()
//{
//	/*Function that resets progress flags. It is called after end of sequence:
//	 * 1. readMeasure
//	 * 2. saveToMem
//	 * 3. Display
//	 */
//	for(int i = 0;i<3;i++)
//	{
//		state_flag[i] = 0;
//	}
//}

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
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		uint16_t dl_kom;
		if(znak == 'e')
		{
			dl_kom = sprintf((char *)komunikat, "First data\n");
		}
		else if(znak == 'd')
		{
			dl_kom = sprintf((char *)komunikat, "Another data\n");
		}
		else
		{
			dl_kom = sprintf((char *)komunikat, "Wrong char\n");
		}
		HAL_UART_Transmit_IT(&huart2, komunikat, dl_kom);
		HAL_UART_Receive_IT(&huart2, &znak, 1);
	}
}

/*
 * status = 1 measure
 * status = 2 button save
 * status = 3 timer
 *
 *  */

