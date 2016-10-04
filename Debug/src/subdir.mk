################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/display.c \
../src/gpioPort0.c \
../src/irSensor.c \
../src/projectWekker.c \
../src/realTimeClock.c \
../src/speaker.c \
../src/timer.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/display.o \
./src/gpioPort0.o \
./src/irSensor.o \
./src/projectWekker.o \
./src/realTimeClock.o \
./src/speaker.o \
./src/timer.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/display.d \
./src/gpioPort0.d \
./src/irSensor.d \
./src/projectWekker.d \
./src/realTimeClock.d \
./src/speaker.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Mandrake\Documents\LPCXpresso_7.9.2_493\workspace\Project-wekker\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


