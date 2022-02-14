cmake_minimum_required(VERSION 3.6)

# Define application name and settings.

#set(CMAKE_TOOLCHAIN_FILE arm3.cmake)
#set(CMAKE_TOOLCHAIN_FILE arm2.cmake)

set(CMAKE_TOOLCHAIN_FILE arm-none-eabi-gcc.cmake)

project(samd10_xplor VERSION 1.1.2 LANGUAGES ASM C CXX)

#target_link_options(samd10_xplor PUBLIC "--specs=nosys.specs")

add_executable(samd10_xplor main.c driver_init.c atmel_start.c)


