################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../common.c \
../linkedList.c \
../queue.c \
../taskQueue.c 

OBJS += \
./common.o \
./linkedList.o \
./queue.o \
./taskQueue.o 

C_DEPS += \
./common.d \
./linkedList.d \
./queue.d \
./taskQueue.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


