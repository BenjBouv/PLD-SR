################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EnOcean2.cpp \
../src/EnOceanAnalyser.cpp \
../src/EnOceanReceptor.cpp \
../src/PeriphTable.cpp \
../src/Receptor.cpp \
../src/Sensors.cpp 

OBJS += \
./src/EnOcean2.o \
./src/EnOceanAnalyser.o \
./src/EnOceanReceptor.o \
./src/PeriphTable.o \
./src/Receptor.o \
./src/Sensors.o 

CPP_DEPS += \
./src/EnOcean2.d \
./src/EnOceanAnalyser.d \
./src/EnOceanReceptor.d \
./src/PeriphTable.d \
./src/Receptor.d \
./src/Sensors.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


