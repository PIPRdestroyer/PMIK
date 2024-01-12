#include "stm32f1xx_hal.h"
#include "main.h"

extern uint8_t status;
extern uint8_t mode;
extern uint8_t TofDataRead;

void switchState(void);
void distanceMeasure(uint8_t state);
void cycleBegin(void);
void cycleEnd(void);
int readDistance();
void Display(uint8_t distance);
void saveToMem(uint8_t distance);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
