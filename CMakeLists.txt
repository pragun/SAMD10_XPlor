cmake_minimum_required(VERSION 3.6)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SYSTEM_NAME            Generic)
set(CMAKE_SYSTEM_PROCESSOR          ARM)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/CMake/arm-none-eabi-gcc.cmake)

project(samd10_xplor LANGUAGES ASM C CXX)

add_subdirectory(asf)

set(SEGGER_PATH ${CMAKE_SOURCE_DIR}/Segger_RTT)
set(EXAMPLES ${CMAKE_SOURCE_DIR}/examples)


add_executable(samd10_xplor main.c) #${EXAMPLES}/driver_examples.c ${EXAMPLES}/touch_example.c)
target_link_libraries(samd10_xplor PRIVATE samd10_asf)
target_include_directories(samd10_xplor PRIVATE ${CMAKE_SOURCE_DIR} ${SEGGER_PATH}/RTT ${SEGGER_PATH}/CONFIG)
target_link_options(samd10_xplor PRIVATE "-T${ASF_LINKER_SCRIPT}")

