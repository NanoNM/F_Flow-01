################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/VL53L1X/vl53l1x.c 

C_DEPS += \
./Core/Inc/VL53L1X/vl53l1x.d 

OBJS += \
./Core/Inc/VL53L1X/vl53l1x.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/VL53L1X/%.o Core/Inc/VL53L1X/%.su Core/Inc/VL53L1X/%.cyclo: ../Core/Inc/VL53L1X/%.c Core/Inc/VL53L1X/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-VL53L1X

clean-Core-2f-Inc-2f-VL53L1X:
	-$(RM) ./Core/Inc/VL53L1X/vl53l1x.cyclo ./Core/Inc/VL53L1X/vl53l1x.d ./Core/Inc/VL53L1X/vl53l1x.o ./Core/Inc/VL53L1X/vl53l1x.su

.PHONY: clean-Core-2f-Inc-2f-VL53L1X

