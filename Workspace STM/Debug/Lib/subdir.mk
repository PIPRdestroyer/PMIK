################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/EEPROM.c \
../Lib/Handler.c \
../Lib/TM1637.c \
../Lib/VL53_API_Interface.c 

OBJS += \
./Lib/EEPROM.o \
./Lib/Handler.o \
./Lib/TM1637.o \
./Lib/VL53_API_Interface.o 

C_DEPS += \
./Lib/EEPROM.d \
./Lib/Handler.d \
./Lib/TM1637.d \
./Lib/VL53_API_Interface.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o Lib/%.su Lib/%.cyclo: ../Lib/%.c Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/VL53L0X/platform/inc -I../Drivers/VL53L0X/core/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Lib

clean-Lib:
	-$(RM) ./Lib/EEPROM.cyclo ./Lib/EEPROM.d ./Lib/EEPROM.o ./Lib/EEPROM.su ./Lib/Handler.cyclo ./Lib/Handler.d ./Lib/Handler.o ./Lib/Handler.su ./Lib/TM1637.cyclo ./Lib/TM1637.d ./Lib/TM1637.o ./Lib/TM1637.su ./Lib/VL53_API_Interface.cyclo ./Lib/VL53_API_Interface.d ./Lib/VL53_API_Interface.o ./Lib/VL53_API_Interface.su

.PHONY: clean-Lib

