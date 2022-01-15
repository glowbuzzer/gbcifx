cmake_minimum_required(VERSION 3.5)

project(gbcifx C)

set(SOURCE_FILES Source/cifXEndianess.c Source/cifXFunctions.c Source/cifXHWFunctions.c Source/cifXInit.c SerialDPM/SerialDPMInterface.c OSAbstraction/OS_SPICustom.c)
add_executable(gbcfix ${SOURCE_FILES})

target_include_directories(gbcfix PUBLIC Source SerialDPM OSAbstraction Common/cifXAPI Common/HilscherDefinitions)

