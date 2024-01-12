#include "stm32f1xx_hal.h"
#include "main.h"

extern uint8_t status;
extern uint8_t mode;
extern uint8_t TofDataRead;
extern uint8_t znak;
extern uint8_t komunikat[20];

void peripherialsInit(void);
void switchMode(void);
void Compute(uint8_t mode, uint8_t status);
void singleMode(uint8_t status);
void continuousMode(uint8_t status);
//void cycleBegin(void);
//void cycleEnd(void);
void readMeasure();
void Display(uint16_t measure);
void saveToMem(uint16_t measure);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
