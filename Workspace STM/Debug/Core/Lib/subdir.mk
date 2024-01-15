################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/EEPROM.c \
../Core/Lib/Handler.c \
../Core/Lib/TM1637.c \
../Core/Lib/VL53_API_Interface.c 

OBJS += \
./Core/Lib/EEPROM.o \
./Core/Lib/Handler.o \
./Core/Lib/TM1637.o \
./Core/Lib/VL53_API_Interface.o 

C_DEPS += \
./Core/Lib/EEPROM.d \
./Core/Lib/Handler.d \
./Core/Lib/TM1637.d \
./Core/Lib/VL53_API_Interface.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/%.o Core/Lib/%.su Core/Lib/%.cyclo: ../Core/Lib/%.c Core/Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/VL53L0X/platform/inc -I../Drivers/VL53L0X/core/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Lib

clean-Core-2f-Lib:
	-$(RM) ./Core/Lib/EEPROM.cyclo ./Core/Lib/EEPROM.d ./Core/Lib/EEPROM.o ./Core/Lib/EEPROM.su ./Core/Lib/Handler.cyclo ./Core/Lib/Handler.d ./Core/Lib/Handler.o ./Core/Lib/Handler.su ./Core/Lib/TM1637.cyclo ./Core/Lib/TM1637.d ./Core/Lib/TM1637.o ./Core/Lib/TM1637.su ./Core/Lib/VL53_API_Interface.cyclo ./Core/Lib/VL53_API_Interface.d ./Core/Lib/VL53_API_Interface.o ./Core/Lib/VL53_API_Interface.su

.PHONY: clean-Core-2f-Lib

