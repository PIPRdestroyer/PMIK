/**
  ******************************************************************************
  * @file    Handler.h
  * @brief   This file contains all the function prototypes for
  *          the Handler.c file
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"
#include "main.h"



extern uint8_t status;
extern uint8_t mode;
extern uint8_t TofDataRead;
extern uint8_t znak;
extern uint8_t komunikat[20];

/**
 * @brief Function initializes all components (range finder, display, timers and uart)
 */
void peripherialsInit(void);

/**
 * @brief Function that switches global variable "mode" between 0 and 1.
 *
 * @note 0 = single mode, 1 = continuous mode
 */
void switchMode(void);

/**
 * @brief Main function that reads meausurement from range finder, displays it on the display and writes to EEPROM depending on operational mode choosen
 * @details Takes two parameters and based on them tells what interrupt is being used and what mode is on.
 *
 * @param mode Variable that defines range finder operational mode
 * @param status Defines which interrupt is now being used (Uart, Buttons, rangefinder or timer)
 */
void Compute(uint8_t mode, uint8_t status);

/**
 * @brief Function handles single mode operation
 *
 * @param status Defines which interrupt is now being used (Uart, Buttons, rangefinder or timer)
 */
void singleMode(uint8_t status);

/**
 * @brief Function handles continuous mode operation
 *
 * @param status Defines which interrupt is now being used (Uart, Buttons, rangefinder or timer)
 */
void continuousMode(uint8_t status);
//void cycleBegin(void);
//void cycleEnd(void);

/**
 * @brief Function that saves measured distance to global variable "Measure" after recieving a signal from interrupt
 */
void readMeasure();

/**
 * @brief Function displays a uint16_t type number on the 7 segment display
 *
 * @param measure Distance returned from range finder
 */
void Display(uint16_t measure);

/**
 * @brief Function that saves measurement to EEPROM memory
 *
 * @param measure Distance returned from range finder
 */
void saveToMem(uint16_t measure);


//     																							#############################opisac
/**
 * @brief Function displays a uint16_t type number on the 7 segment display.
 *
 * @param measure Distance returned from range finder
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

/**
 * @brief Function displays a uint16_t type number on the 7 segment display.
 *
 * @param measure Distance returned from range finder
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

/**
 * @brief Function displays a uint16_t type number on the 7 segment display.
 *
 * @param measure Distance returned from range finder
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
