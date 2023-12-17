/**
  ******************************************************************************

  EEPROM.h Using the HAL I2C Functions
  Author:   ControllersTech
  Updated:  Feb 16, 2021

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/

/*
 * #define DEV_ADDR 0xa0 //EEProm addres definition
 * EXAMPLE
 * Variables to write:
 * uint8_t dataw1[] = "hello world from EEPROM";
 * uint8_t dataw2[] = "This is the second string from EEPROM";
 * float dataw3 = 1234.5678;
 * uint8_t datar1[100];
 * uint8_t datar2[100];
 * float datar3;
 *
  for (int i=0; i<512; i++)
    {
  	  EEPROM_PageErase(i);
    }


    EEPROM_Write(3, 0, dataw1, strlen((char *)dataw1));

    EEPROM_Write(5, 20, dataw2, strlen((char *)dataw2));

    EEPROM_Write_NUM (6, 0, dataw3);


    EEPROM_Read(3, 0, datar1, 50);

    EEPROM_Read(5, 15, datar2, 50);

    datar3 = EEPROM_Read_NUM (6, 0);
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"


void EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_PageErase (uint16_t page);

void EEPROM_Write_NUM (uint16_t page, uint16_t offset, float  fdata);
float EEPROM_Read_NUM (uint16_t page, uint16_t offset);

#endif /* INC_EEPROM_H_ */
