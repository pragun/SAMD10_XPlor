cmake_minimum_required(VERSION 3.6)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SYSTEM_NAME            Generic)
set(CMAKE_SYSTEM_PROCESSOR          ARM)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/CMake/arm-none-eabi-gcc.cmake)

project(samd10_xplor LANGUAGES ASM C CXX)

add_subdirectory(asf)

set(SEGGER_PATH "${CMAKE_SOURCE_DIR}/Segger_RTT")
set(SEGGER_SRCS RTT/SEGGER_RTT.c RTT/SEGGER_RTT_printf.c Syscalls/SEGGER_RTT_Syscalls_GCC.c)
list(TRANSFORM SEGGER_SRCS PREPEND "${SEGGER_PATH}/")

set(EXAMPLES ${CMAKE_SOURCE_DIR}/examples)

set(TARGET_NAME samd10_xplor)
set(SAMD10_EXE ${TARGET_NAME}.elf)

add_executable(${SAMD10_EXE} main.c  ${SEGGER_SRCS}) #${EXAMPLES}/driver_examples.c ${EXAMPLES}/touch_example.c)
target_link_libraries(${SAMD10_EXE} PRIVATE samd10_asf)
target_include_directories(${SAMD10_EXE} PRIVATE ${CMAKE_SOURCE_DIR} ${SEGGER_PATH}/RTT ${SEGGER_PATH}/CONFIG)

target_link_options(${SAMD10_EXE} PRIVATE "-T${ASF_LINKER_SCRIPT}")

add_custom_target("Binary_file" ALL DEPENDS ${SAMD10_EXE} COMMAND ${CMAKE_OBJCOPY} -Obinary ${SAMD10_EXE} ${TARGET_NAME}.bin)
add_custom_target("Size_calculation" ALL DEPENDS ${SAMD10_EXE} COMMAND ${CMAKE_SIZE} --format=berkeley ${SAMD10_EXE})
