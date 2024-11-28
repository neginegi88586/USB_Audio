################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/User/main.c 

OBJS += \
./Src/User/main.o 

C_DEPS += \
./Src/User/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/User/%.o Src/User/%.su Src/User/%.cyclo: ../Src/User/%.c Src/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F723xx -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/User" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-User

clean-Src-2f-User:
	-$(RM) ./Src/User/main.cyclo ./Src/User/main.d ./Src/User/main.o ./Src/User/main.su

.PHONY: clean-Src-2f-User

