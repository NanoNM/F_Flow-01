################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/PMW3901MB/pmw_3901.c 

C_DEPS += \
./Core/Src/PMW3901MB/pmw_3901.d 

OBJS += \
./Core/Src/PMW3901MB/pmw_3901.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/PMW3901MB/%.o Core/Src/PMW3901MB/%.su Core/Src/PMW3901MB/%.cyclo: ../Core/Src/PMW3901MB/%.c Core/Src/PMW3901MB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-PMW3901MB

clean-Core-2f-Src-2f-PMW3901MB:
	-$(RM) ./Core/Src/PMW3901MB/pmw_3901.cyclo ./Core/Src/PMW3901MB/pmw_3901.d ./Core/Src/PMW3901MB/pmw_3901.o ./Core/Src/PMW3901MB/pmw_3901.su

.PHONY: clean-Core-2f-Src-2f-PMW3901MB

