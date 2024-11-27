################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c 

OBJS += \
./Src/main.o 

C_DEPS += \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F723VETx -DSTM32 -DSTM32F7 -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su

.PHONY: clean-Src

