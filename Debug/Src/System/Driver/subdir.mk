################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/System/Driver/clock_config.c \
../Src/System/Driver/system_config.c 

OBJS += \
./Src/System/Driver/clock_config.o \
./Src/System/Driver/system_config.o 

C_DEPS += \
./Src/System/Driver/clock_config.d \
./Src/System/Driver/system_config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/System/Driver/%.o Src/System/Driver/%.su Src/System/Driver/%.cyclo: ../Src/System/Driver/%.c Src/System/Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F723VETx -DSTM32 -DSTM32F7 -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/User" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-System-2f-Driver

clean-Src-2f-System-2f-Driver:
	-$(RM) ./Src/System/Driver/clock_config.cyclo ./Src/System/Driver/clock_config.d ./Src/System/Driver/clock_config.o ./Src/System/Driver/clock_config.su ./Src/System/Driver/system_config.cyclo ./Src/System/Driver/system_config.d ./Src/System/Driver/system_config.o ./Src/System/Driver/system_config.su

.PHONY: clean-Src-2f-System-2f-Driver

