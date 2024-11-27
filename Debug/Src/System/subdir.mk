################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/System/syscalls.c \
../Src/System/sysmem.c \
../Src/System/system_stm32f7xx.c 

OBJS += \
./Src/System/syscalls.o \
./Src/System/sysmem.o \
./Src/System/system_stm32f7xx.o 

C_DEPS += \
./Src/System/syscalls.d \
./Src/System/sysmem.d \
./Src/System/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/System/%.o Src/System/%.su Src/System/%.cyclo: ../Src/System/%.c Src/System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F723VETx -DSTM32 -DSTM32F7 -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/User" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-System

clean-Src-2f-System:
	-$(RM) ./Src/System/syscalls.cyclo ./Src/System/syscalls.d ./Src/System/syscalls.o ./Src/System/syscalls.su ./Src/System/sysmem.cyclo ./Src/System/sysmem.d ./Src/System/sysmem.o ./Src/System/sysmem.su ./Src/System/system_stm32f7xx.cyclo ./Src/System/system_stm32f7xx.d ./Src/System/system_stm32f7xx.o ./Src/System/system_stm32f7xx.su

.PHONY: clean-Src-2f-System

