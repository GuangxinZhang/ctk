################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/config.c \
../src/ctail.c \
../src/ctk.c \
../src/ini.c \
../src/kafka_manage.c 

OBJS += \
./src/config.o \
./src/ctail.o \
./src/ctk.o \
./src/ini.o \
./src/kafka_manage.o 

C_DEPS += \
./src/config.d \
./src/ctail.d \
./src/ctk.d \
./src/ini.d \
./src/kafka_manage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/local/lib -I/usr/local/lib/log4c/include -I/usr/local/lib/log4c/lib -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


