/**
  ******************************************************************************
  * @file    VL53_API_Interface.h
  * @brief   This file contains all the function prototypes for
  *          the VL53_API_Interface.c file
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"


/**
 * @brief Function that initializes range sensor
 */
void VL53_init(void);

/**
 * @brief Function that saves the measure to variable
 *
 * @return Returns uint16_t type distance
 */
uint16_t VL53_MEASURE();

/**
 * @brief Function that clears data in interrupt
 */
void VL53_CLEAR_INTERRUPT_DATA();
