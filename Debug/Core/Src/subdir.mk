################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/control.c \
../Core/Src/crc.c \
../Core/Src/ctiic.c \
../Core/Src/dma2d.c \
../Core/Src/fmc.c \
../Core/Src/freertos.c \
../Core/Src/ft5206.c \
../Core/Src/gpio.c \
../Core/Src/gt9147.c \
../Core/Src/ltdc.c \
../Core/Src/main.c \
../Core/Src/quadspi.c \
../Core/Src/sensors.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_hal_timebase_tim.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c \
../Core/Src/usart.c 

C_DEPS += \
./Core/Src/control.d \
./Core/Src/crc.d \
./Core/Src/ctiic.d \
./Core/Src/dma2d.d \
./Core/Src/fmc.d \
./Core/Src/freertos.d \
./Core/Src/ft5206.d \
./Core/Src/gpio.d \
./Core/Src/gt9147.d \
./Core/Src/ltdc.d \
./Core/Src/main.d \
./Core/Src/quadspi.d \
./Core/Src/sensors.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_hal_timebase_tim.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d \
./Core/Src/usart.d 

OBJS += \
./Core/Src/control.o \
./Core/Src/crc.o \
./Core/Src/ctiic.o \
./Core/Src/dma2d.o \
./Core/Src/fmc.o \
./Core/Src/freertos.o \
./Core/Src/ft5206.o \
./Core/Src/gpio.o \
./Core/Src/gt9147.o \
./Core/Src/ltdc.o \
./Core/Src/main.o \
./Core/Src/quadspi.o \
./Core/Src/sensors.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_hal_timebase_tim.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o \
./Core/Src/usart.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/control.d ./Core/Src/control.o ./Core/Src/control.su ./Core/Src/crc.d ./Core/Src/crc.o ./Core/Src/crc.su ./Core/Src/ctiic.d ./Core/Src/ctiic.o ./Core/Src/ctiic.su ./Core/Src/dma2d.d ./Core/Src/dma2d.o ./Core/Src/dma2d.su ./Core/Src/fmc.d ./Core/Src/fmc.o ./Core/Src/fmc.su ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/ft5206.d ./Core/Src/ft5206.o ./Core/Src/ft5206.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/gt9147.d ./Core/Src/gt9147.o ./Core/Src/gt9147.su ./Core/Src/ltdc.d ./Core/Src/ltdc.o ./Core/Src/ltdc.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/quadspi.d ./Core/Src/quadspi.o ./Core/Src/quadspi.su ./Core/Src/sensors.d ./Core/Src/sensors.o ./Core/Src/sensors.su ./Core/Src/stm32f7xx_hal_msp.d ./Core/Src/stm32f7xx_hal_msp.o ./Core/Src/stm32f7xx_hal_msp.su ./Core/Src/stm32f7xx_hal_timebase_tim.d ./Core/Src/stm32f7xx_hal_timebase_tim.o ./Core/Src/stm32f7xx_hal_timebase_tim.su ./Core/Src/stm32f7xx_it.d ./Core/Src/stm32f7xx_it.o ./Core/Src/stm32f7xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f7xx.d ./Core/Src/system_stm32f7xx.o ./Core/Src/system_stm32f7xx.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

