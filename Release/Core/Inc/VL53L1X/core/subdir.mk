################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/VL53L1X/core/VL53L1X_api.c \
../Core/Inc/VL53L1X/core/VL53L1X_calibration.c 

C_DEPS += \
./Core/Inc/VL53L1X/core/VL53L1X_api.d \
./Core/Inc/VL53L1X/core/VL53L1X_calibration.d 

OBJS += \
./Core/Inc/VL53L1X/core/VL53L1X_api.o \
./Core/Inc/VL53L1X/core/VL53L1X_calibration.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/VL53L1X/core/%.o Core/Inc/VL53L1X/core/%.su Core/Inc/VL53L1X/core/%.cyclo: ../Core/Inc/VL53L1X/core/%.c Core/Inc/VL53L1X/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-VL53L1X-2f-core

clean-Core-2f-Inc-2f-VL53L1X-2f-core:
	-$(RM) ./Core/Inc/VL53L1X/core/VL53L1X_api.cyclo ./Core/Inc/VL53L1X/core/VL53L1X_api.d ./Core/Inc/VL53L1X/core/VL53L1X_api.o ./Core/Inc/VL53L1X/core/VL53L1X_api.su ./Core/Inc/VL53L1X/core/VL53L1X_calibration.cyclo ./Core/Inc/VL53L1X/core/VL53L1X_calibration.d ./Core/Inc/VL53L1X/core/VL53L1X_calibration.o ./Core/Inc/VL53L1X/core/VL53L1X_calibration.su

.PHONY: clean-Core-2f-Inc-2f-VL53L1X-2f-core

