/**
  ******************************************************************************
  * @file    EEPROM.h
  * @brief   This file contains all the function prototypes for
  *          the EEPROM.c file
  * @note Memory contains 512 pages witch 64 bytes each.
  ******************************************************************************
  */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"

/**
 * @brief Writes data to EEPROM memory
 *
 * Function gets page, byte offset, data to save and it's size and writes that to memory
 *
 * @param page Page of EEPROM memory (0-512) pages
 * @param offset Byte number from which we start writing data (0-64) per page
 * @param *data Data to write
 * @param size Size of data to write
 *
 * <b>Example</b>
 * @code
 *	int main()
 *	{
 * 		uint8_t dataw1[] = "hello world from EEPROM"; //definition of data to write
 * 		uint8_t dataw2[] = "This is the second string from EEPROM";
 * 		EEPROM_Write(3, 0, dataw1, strlen((char *)dataw1)); //Writing data
 * 		EEPROM_Write(5, 20, dataw2, strlen((char *)dataw2));
 *     	return 0;
 * 	}
 * @endcode
 */
void EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);

/**
 * @brief Reads data from EEPROM memory
 *
 * Function gets page, byte offset, data to save and it's size and reads that from memory
 *
 * @param page Page of EEPROM memory (0-512) pages
 * @param offset Byte number from which we start reading data (0-64) bytes per page
 * @param *data Data variable to save data to. It needs to be defined before as array or single variable
 * @param size Size of data to read
 *
 *<b>Example</b>
 * @code
 *	int main()
 *	{
 * 		uint8_t datar1[100];
 * 		uint8_t datar2[100];
 * 		EEPROM_Read(3, 0, datar1, 50); //Reading data to datar1 array
 *		EEPROM_Read(5, 15, datar2, 50);
 *     	return 0;
 * 	}
 * @endcode
 */
void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);

/**
 * @brief Erase a page in the EEPROM Memory
 *
 * Function erases byte by byte whole page
 *
 * @param page Number of the page to erase
 * @note In order to erase multiple pages, function should be used in the for loop
 *
 *
 *<b>Example</b>
 * @code
 *	int main()
 *	{
 *		for (int i=0; i<512; i++)
 *		{
 *			EEPROM_PageErase(i);
 *		}
 *     	return 0;
 * 	}
 * @endcode
 */
void EEPROM_PageErase (uint16_t page);


/**
 * @brief Writes a single number to EEPROM memory
 *
 * Function gets page, byte offset and a number and writes it to memory
 *
 * @param page Page of EEPROM memory (0-512) pages
 * @param offset Byte number from which we start writing data (0-64) per page
 * @param fdata Data to write
 *
 *
 *<b>Example</b>
 * @code
 *	int main()
 *	{
 * 		float dataw3 = 1234.5678; //definition of a number to write
 * 		EEPROM_Write_NUM(6, 0, dataw3); //Writing a number to dataw3
 *     	return 0;
 * 	}
 * @endcode
 */
void EEPROM_Write_NUM (uint16_t page, uint16_t offset, float  fdata);

/**
 * @brief Reads a single number from EEPROM memory
 *
 * Function gets page, byte offset and a number and writes it to memory
 *
 * @param page Page of EEPROM memory (0-512) pages
 * @param offset Byte number from which we start writing data (0-64) per page
 * @return Returns float type number from EEPROM memory
 *
 *
 *<b>Example</b>
 * @code
 *	int main()
 *	{
 * 		float datar3;
 * 		datar3 = EEPROM_Read_NUM(6, 0); //Reading a number to datar3
 *     	return 0;
 * 	}
 * @endcode
 */
float EEPROM_Read_NUM (uint16_t page, uint16_t offset);

#endif /* INC_EEPROM_H_ */
