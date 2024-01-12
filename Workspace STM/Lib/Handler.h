#include "stm32f1xx_hal.h"

void switchState(void);
void distanceMeasure(uint8_t state);
void cycleBegin(void);
void cycleEnd(void);
int readDistance();
void Display(uint8_t distance);
void saveToMem(uint8_t distance);
