################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../appli/SolTrack.c \
../appli/main.c \
../appli/secretary.c \
../appli/sun_tracker.c 

OBJS += \
./appli/SolTrack.o \
./appli/main.o \
./appli/secretary.o \
./appli/sun_tracker.o 

C_DEPS += \
./appli/SolTrack.d \
./appli/main.d \
./appli/secretary.d \
./appli/sun_tracker.d 


# Each subdirectory must supply rules for building sources it contributes
appli/%.o: ../appli/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/simon/OneDrive/Documents/ESEO/I1/SYSTEMES_EMBARQUES/PSE2_SUNTRACKER/sun-tracker/lib/bsp" -I"C:/Users/simon/OneDrive/Documents/ESEO/I1/SYSTEMES_EMBARQUES/PSE2_SUNTRACKER/sun-tracker/lib/bsp/MPU6050" -I../lib/bsp/iks01a1 -I../lib/bsp/iks01a1/Common -I../lib/bsp/iks01a1/hts221 -I../lib/bsp/iks01a1/lis3mdl -I../lib/bsp/iks01a1/lps22hb -I../lib/bsp/iks01a1/lps25hb -I../lib/bsp/iks01a1/lsm6ds0 -I../lib/bsp/iks01a1/lsm6ds3 -I../lib/bsp/tft_ili9341 -I../lib/bsp/tft_pcd8544 -I../lib/bsp/MCP23S17 -I"C:/Users/simon/OneDrive/Documents/ESEO/I1/SYSTEMES_EMBARQUES/PSE2_SUNTRACKER/sun-tracker/lib/hal/inc" -I../lib/bsp/Common -I../lib/bsp/lcd2x16 -I../lib/bsp/MLX90614 -I../lib/bsp/MatrixKeyboard -I../lib/bsp/MatrixLed -I"C:/Users/simon/OneDrive/Documents/ESEO/I1/SYSTEMES_EMBARQUES/PSE2_SUNTRACKER/sun-tracker/lib/CMSIS/core" -I"C:/Users/simon/OneDrive/Documents/ESEO/I1/SYSTEMES_EMBARQUES/PSE2_SUNTRACKER/sun-tracker/lib/CMSIS/device" -I../lib/middleware/FatFs -I../lib/middleware/FatFs/src -I../lib/middleware/FatFs/src/drivers -I"C:/Users/simon/OneDrive/Documents/ESEO/I1/SYSTEMES_EMBARQUES/PSE2_SUNTRACKER/sun-tracker/appli"  -Og -g3 -Wall -Wextra -Wconversion -fmessage-length=0 -ffunction-sections -fdata-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


