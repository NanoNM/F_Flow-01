################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Adapter/massage_adapter.c 

C_DEPS += \
./Core/Src/Adapter/massage_adapter.d 

OBJS += \
./Core/Src/Adapter/massage_adapter.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Adapter/%.o Core/Src/Adapter/%.su Core/Src/Adapter/%.cyclo: ../Core/Src/Adapter/%.c Core/Src/Adapter/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Adapter

clean-Core-2f-Src-2f-Adapter:
	-$(RM) ./Core/Src/Adapter/massage_adapter.cyclo ./Core/Src/Adapter/massage_adapter.d ./Core/Src/Adapter/massage_adapter.o ./Core/Src/Adapter/massage_adapter.su

.PHONY: clean-Core-2f-Src-2f-Adapter

