################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/System/Driver/clock.c \
../Src/System/Driver/gpio.c \
../Src/System/Driver/interrupt.c \
../Src/System/Driver/system_config.c \
../Src/System/Driver/uart.c 

OBJS += \
./Src/System/Driver/clock.o \
./Src/System/Driver/gpio.o \
./Src/System/Driver/interrupt.o \
./Src/System/Driver/system_config.o \
./Src/System/Driver/uart.o 

C_DEPS += \
./Src/System/Driver/clock.d \
./Src/System/Driver/gpio.d \
./Src/System/Driver/interrupt.d \
./Src/System/Driver/system_config.d \
./Src/System/Driver/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/System/Driver/%.o Src/System/Driver/%.su Src/System/Driver/%.cyclo: ../Src/System/Driver/%.c Src/System/Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -g3 -DDEBUG -DSTM32F723xx -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/User" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-System-2f-Driver

clean-Src-2f-System-2f-Driver:
	-$(RM) ./Src/System/Driver/clock.cyclo ./Src/System/Driver/clock.d ./Src/System/Driver/clock.o ./Src/System/Driver/clock.su ./Src/System/Driver/gpio.cyclo ./Src/System/Driver/gpio.d ./Src/System/Driver/gpio.o ./Src/System/Driver/gpio.su ./Src/System/Driver/interrupt.cyclo ./Src/System/Driver/interrupt.d ./Src/System/Driver/interrupt.o ./Src/System/Driver/interrupt.su ./Src/System/Driver/system_config.cyclo ./Src/System/Driver/system_config.d ./Src/System/Driver/system_config.o ./Src/System/Driver/system_config.su ./Src/System/Driver/uart.cyclo ./Src/System/Driver/uart.d ./Src/System/Driver/uart.o ./Src/System/Driver/uart.su

.PHONY: clean-Src-2f-System-2f-Driver

