################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/USB_Device/usb_core.c \
../Src/USB_Device/usb_desc.c 

OBJS += \
./Src/USB_Device/usb_core.o \
./Src/USB_Device/usb_desc.o 

C_DEPS += \
./Src/USB_Device/usb_core.d \
./Src/USB_Device/usb_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/USB_Device/%.o Src/USB_Device/%.su Src/USB_Device/%.cyclo: ../Src/USB_Device/%.c Src/USB_Device/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -g3 -DDEBUG -DSTM32F723xx -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Inc/User" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/CMSIS" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/System/Driver" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/USB_Device" -I"C:/Users/idune/STM32CubeIDE/workspace_1.16.1/USB_Audio/Src/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-USB_Device

clean-Src-2f-USB_Device:
	-$(RM) ./Src/USB_Device/usb_core.cyclo ./Src/USB_Device/usb_core.d ./Src/USB_Device/usb_core.o ./Src/USB_Device/usb_core.su ./Src/USB_Device/usb_desc.cyclo ./Src/USB_Device/usb_desc.d ./Src/USB_Device/usb_desc.o ./Src/USB_Device/usb_desc.su

.PHONY: clean-Src-2f-USB_Device

