#include "VL53_API_Interface.h"
#include "main.h"
#include "gpio.h"
#include "i2c.h"
#include "stm32f1xx_hal.h"
#include "vl53l0x_api.h"

VL53L0X_RangingMeasurementData_t RangingData;
VL53L0X_Dev_t  vl53l0x_c; // center module
VL53L0X_DEV    Dev = &vl53l0x_c;

void VL53_init()
{
	uint32_t refSpadCount;
	uint8_t isApertureSpads;
	uint8_t VhvSettings;
	uint8_t PhaseCal;

	Dev->I2cHandle = &hi2c2;
	Dev->I2cDevAddr = 0x52;

	HAL_GPIO_WritePin(TOF_XSHUT_GPIO_Port, TOF_XSHUT_Pin, GPIO_PIN_RESET); // Disable XSHUT
	HAL_Delay(20);
	HAL_GPIO_WritePin(TOF_XSHUT_GPIO_Port, TOF_XSHUT_Pin, GPIO_PIN_SET); // Enable XSHUT
	HAL_Delay(20);

	HAL_NVIC_DisableIRQ(EXTI1_IRQn);

	VL53L0X_WaitDeviceBooted( Dev );
	VL53L0X_DataInit( Dev );
	VL53L0X_StaticInit( Dev );
	VL53L0X_PerformRefCalibration(Dev, &VhvSettings, &PhaseCal);
	VL53L0X_PerformRefSpadManagement(Dev, &refSpadCount, &isApertureSpads);
	VL53L0X_SetDeviceMode(Dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
	VL53L0X_StartMeasurement(Dev);

	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

uint16_t VL53_MEASURE()
{	uint16_t Measure = RangingData.RangeMilliMeter;
	return Measure;
}

void VL53_CLEAR_INTERRUPT_DATA()
{
	VL53L0X_GetRangingMeasurementData(Dev, &RangingData);
	VL53L0X_ClearInterruptMask(Dev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
}
