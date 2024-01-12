
#define EEPROM_PAGE 1
#define EEPROM_OFFSET 1

#include "Handler.h"
#include "TM1637.h"
#include "EEPROM.h"
#include "VL53_API_Interface.h"

uint8_t status = 0;
uint8_t mode = 0;
uint8_t TofDataRead = 0;

uint8_t state = 0;
uint8_t state_flag[3] = {0, 0, 0}; // variable that tells if the full cycle of measurement was finnished
//full cycle is considered as finnished when state_flag = {1, 1, 1} after cycle they will be reseted to 0
// {0,0,0} <==> {measurement, write to EEPROM, display}

void switchState()
{
	/* Function that switches mode from 0 = single to 1 = cont*/
	state = !state;
}

void distanceMeasure(uint8_t state)
{
	for(int i = 0;i<3;i++)
	  	if (state_flag[i] == 0)
	  	{
	  		cycleBegin();
	  	}
	  	else if (state_flag[i] == 1)
	  	{
	  		cycleEnd();
	  	}
}


void cycleBegin()
{
	/*Function that starts the measurement cycle*/
	uint8_t distance = readDistance();
	saveToMem(distance);
	Display(distance);
}

void cycleEnd()
{
	/*Function that resets progress flags. It is called after end of sequence:
	 * 1. readDistance
	 * 2. saveToMem
	 * 3. Display
	 */
	for(int i = 0;i<3;i++)
	{
		state_flag[i] = 0;
	}
}

int readDistance()
{
	/*Function that reads distance from VL530L0X and returns as uint8_t */

	//readfunction
	uint8_t distance = 0; // do wyrzucenia
	state_flag[0] = 1; //Change temporary progress flag to 1 (1 = task done)
	return distance;
}

void Display(uint8_t distance)
{
	TM1637_DisplayDecimal(distance, 0);
	state_flag[2] = 1; //Change temporary progress flag to 1 (1 = task done)
}

void saveToMem(uint8_t distance)
{
	EEPROM_Write_NUM(EEPROM_PAGE, EEPROM_OFFSET, distance);
	state_flag[1] = 1; //Change temporary progress flag to 1 (1 = task done)
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//save button
	if (GPIO_Pin == B2_Pin)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		status = 3;
	}
	//change state button
	if (GPIO_Pin == B1_Pin)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		if(mode == 0)
		{
			mode = 1;
		}
		else
		{
			mode = 0;
		}

	}
	if(GPIO_Pin == TOF_INT_Pin)
	{
		VL53_CLEAR_INTERRUPT_DATA();
		TofDataRead = 1;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
	{
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		status = 4;
	}
}
