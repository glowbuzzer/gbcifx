cmake_minimum_required(VERSION 3.5)

project(gbcifx_config C)

file(GLOB SOURCES "src/*.c")

add_library(gbcifx_config INTERFACE)
target_include_directories(gbcifx_config INTERFACE inc ${gbcifx_config_BINARY_DIR})