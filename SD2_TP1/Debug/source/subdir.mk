################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MEF_CALLE_SECUNDARIA.c \
../source/MEF_MAIN.c \
../source/MEF_PEATON.c \
../source/SD2_board.c \
../source/key.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/MEF_CALLE_SECUNDARIA.d \
./source/MEF_MAIN.d \
./source/MEF_PEATON.d \
./source/SD2_board.d \
./source/key.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/MEF_CALLE_SECUNDARIA.o \
./source/MEF_MAIN.o \
./source/MEF_PEATON.o \
./source/SD2_board.o \
./source/key.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MKL46Z256VLH4_cm0plus -DCPU_MKL46Z256VLH4 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/MEF_CALLE_SECUNDARIA.d ./source/MEF_CALLE_SECUNDARIA.o ./source/MEF_MAIN.d ./source/MEF_MAIN.o ./source/MEF_PEATON.d ./source/MEF_PEATON.o ./source/SD2_board.d ./source/SD2_board.o ./source/key.d ./source/key.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

