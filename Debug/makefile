################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/User/subdir.mk
-include Src/USB_Device/subdir.mk
-include Src/System/Driver/subdir.mk
-include Src/System/CMSIS/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := USB_Audio
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
USB_Audio.elf \

MAP_FILES += \
USB_Audio.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
USB_Audio.list \


# All Target
all: main-build

# Main-build Target
main-build: USB_Audio.elf secondary-outputs

# Tool invocations
USB_Audio.elf USB_Audio.map: $(OBJS) $(USER_OBJS) C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\STM32F723VETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "USB_Audio.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\STM32F723VETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="USB_Audio.map" -Wl,--gc-sections -static -L"C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\Inc\System\CMSIS" -L"C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\Inc\System\Driver" -L"C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\Inc\USB_Device" -L"C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\Inc\User" -L"C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\Src\System" -L"C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\Src\USB_Device" -L"C:\Users\idune\STM32CubeIDE\workspace_1.16.1\USB_Audio\Src\User" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

USB_Audio.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "USB_Audio.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) USB_Audio.elf USB_Audio.list USB_Audio.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
