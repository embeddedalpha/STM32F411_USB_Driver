################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_Driver/USB_Device_Driver.c \
../USB_Driver/USB_Device_Framework.c 

OBJS += \
./USB_Driver/USB_Device_Driver.o \
./USB_Driver/USB_Device_Framework.o 

C_DEPS += \
./USB_Driver/USB_Device_Driver.d \
./USB_Driver/USB_Device_Framework.d 


# Each subdirectory must supply rules for building sources it contributes
USB_Driver/%.o USB_Driver/%.su: ../USB_Driver/%.c USB_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/Inc/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/Inc/CMSIS/Include" -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/USB_Driver" -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/GPIO" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB_Driver

clean-USB_Driver:
	-$(RM) ./USB_Driver/USB_Device_Driver.d ./USB_Driver/USB_Device_Driver.o ./USB_Driver/USB_Device_Driver.su ./USB_Driver/USB_Device_Framework.d ./USB_Driver/USB_Device_Framework.o ./USB_Driver/USB_Device_Framework.su

.PHONY: clean-USB_Driver

