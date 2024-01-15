/**
  ******************************************************************************
  * @file    TM1637.h
  * @brief   This file contains all the function prototypes for
  *          the TM1637.c file
  ******************************************************************************
  */
#include "stm32f1xx_hal.h"

#ifndef TM1637_H_
#define TM1637_H_


/**
 * @brief Function that simply counts numbers till uint32_t max and displays each iteration
 */
void TM1637_Demo(void);

/**
 * @brief Function that displays number.
 *
 * @param num Number that will be displayed
 * @param displaySeparator if 1 then the LED double dot in the display will be on
 */
void TM1637_DisplayDecimal(int num, int displaySeparator);
/**
 * @brief Function that changes the brightness of the display
 *
 * @param brightness Value that defines how bright the display is.
 * @details Options:
 * @details Valid brightness values: 0 - 8
 * @details 0 = display off
 */
void TM1637_SetBrightness(char brightness);

/**
 * @brief Function that starts the sequence of sending data to display
 */
void TM1637_Start(void);

/**
 * @brief Function that stops the sequence of sending data to display
 */
void TM1637_Stop(void);

/**
 * @brief Function that starts the sequence of sending data to display
 */
void TM1637_ReadResult(void);

/**
 * @brief Function writes byte to display register
 *
 * @param b Byte to write
 */
void TM1637_WriteByte(unsigned char b);

/**
 * @brief Function that waits defined time.
 *
 * @param i Time to wait
 */
void TM1637_DelayUsec(unsigned int i);

/**
 * @brief Function that changes CLK line state to high
 */
void TM1637_ClkHigh(void);

/**
 * @brief Function that changes CLK line state to low
 */
void TM1637_ClkLow(void);

/**
 * @brief Function that changes DATA line state to high
 */
void TM1637_DataHigh(void);

/**
 * @brief Function that changes DATA line state to low
 */
void TM1637_DATALow(void);
#endif /* TM1637_H_ */
