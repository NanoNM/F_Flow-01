################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/VL53L1X/platform/vl53l1_platform.c 

C_DEPS += \
./Core/Inc/VL53L1X/platform/vl53l1_platform.d 

OBJS += \
./Core/Inc/VL53L1X/platform/vl53l1_platform.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/VL53L1X/platform/%.o Core/Inc/VL53L1X/platform/%.su Core/Inc/VL53L1X/platform/%.cyclo: ../Core/Inc/VL53L1X/platform/%.c Core/Inc/VL53L1X/platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-VL53L1X-2f-platform

clean-Core-2f-Inc-2f-VL53L1X-2f-platform:
	-$(RM) ./Core/Inc/VL53L1X/platform/vl53l1_platform.cyclo ./Core/Inc/VL53L1X/platform/vl53l1_platform.d ./Core/Inc/VL53L1X/platform/vl53l1_platform.o ./Core/Inc/VL53L1X/platform/vl53l1_platform.su

.PHONY: clean-Core-2f-Inc-2f-VL53L1X-2f-platform

