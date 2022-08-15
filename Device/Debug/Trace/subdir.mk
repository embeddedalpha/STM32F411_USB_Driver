################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Trace/Trace.c 

OBJS += \
./Trace/Trace.o 

C_DEPS += \
./Trace/Trace.d 


# Each subdirectory must supply rules for building sources it contributes
Trace/%.o Trace/%.su: ../Trace/%.c Trace/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/Inc/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/Inc/CMSIS/Include" -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/USB_Driver" -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/GPIO" -I"C:/Users/Kunal/STM32CubeIDE/STM32F411_Workspace/STM32F411_USB_Driver/Trace" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Trace

clean-Trace:
	-$(RM) ./Trace/Trace.d ./Trace/Trace.o ./Trace/Trace.su

.PHONY: clean-Trace

