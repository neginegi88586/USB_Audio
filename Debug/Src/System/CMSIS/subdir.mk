################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/System/CMSIS/syscalls.c \
../Src/System/CMSIS/sysmem.c \
../Src/System/CMSIS/system_stm32f7xx.c 

OBJS += \
./Src/System/CMSIS/syscalls.o \
./Src/System/CMSIS/sysmem.o \
./Src/System/CMSIS/system_stm32f7xx.o 

C_DEPS += \
./Src/System/CMSIS/syscalls.d \
./Src/System/CMSIS/sysmem.d \
./Src/System/CMSIS/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/System/CMSIS/%.o Src/System/CMSIS/%.su Src/System/CMSIS/%.cyclo: ../Src/System/CMSIS/%.c Src/System/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -g3 -DDEBUG -DSTM32F723xx -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/User" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-System-2f-CMSIS

clean-Src-2f-System-2f-CMSIS:
	-$(RM) ./Src/System/CMSIS/syscalls.cyclo ./Src/System/CMSIS/syscalls.d ./Src/System/CMSIS/syscalls.o ./Src/System/CMSIS/syscalls.su ./Src/System/CMSIS/sysmem.cyclo ./Src/System/CMSIS/sysmem.d ./Src/System/CMSIS/sysmem.o ./Src/System/CMSIS/sysmem.su ./Src/System/CMSIS/system_stm32f7xx.cyclo ./Src/System/CMSIS/system_stm32f7xx.d ./Src/System/CMSIS/system_stm32f7xx.o ./Src/System/CMSIS/system_stm32f7xx.su

.PHONY: clean-Src-2f-System-2f-CMSIS

