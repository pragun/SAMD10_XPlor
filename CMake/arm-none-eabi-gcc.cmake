#
# Without that flag CMake is not able to pass test compilation check
#

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/utils.cmake)


find_toolchain_exe(CMAKE_AR arm-none-eabi-ar)
find_toolchain_exe(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
find_toolchain_exe(CMAKE_C_COMPILER arm-none-eabi-gcc)
find_toolchain_exe(CMAKE_CXX_COMPILER arm-none-eabi-g++)
find_toolchain_exe(CMAKE_CXX_LINK_EXECUTABLE arm-none-eabi-ld)
find_toolchain_exe(CMAKE_LINKER arm-none-eabi-ld)
find_toolchain_exe(CMAKE_OBJCOPY arm-none-eabi-objcopy)
find_toolchain_exe(CMAKE_RANLIB arm-none-eabi-ranlib)
find_toolchain_exe(CMAKE_SIZE arm-none-eabi-size)
find_toolchain_exe(CMAKE_STRIP arm-none-eabi-strip)
find_toolchain_exe(CMAKE_GCOV arm-none-eabi-gcov)
find_toolchain_exe(CMAKE_OBJDUMP arm-none-eabi-objdump)

set(c_flags -mthumb -Og -ffunction-sections -mlong-calls -g3 -Wall -Wextra -mcpu=cortex-m0plus -std=gnu99 -MD -MP -MF)
set(cxx_flags -fno-exceptions)

set(CMAKE_ASM_COMPILER ${CMAKE_ASM_COMPILER} CACHE FILEPATH "ASM compiler")
set(CMAKE_ASM_COMPILE_OBJECT "<CMAKE_ASM_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT>   -c <SOURCE>")
set(CMAKE_INCLUDE_FLAG_ASM "-I")
set(CMAKE_OBJCOPY ${CMAKE_OBJCOPY} CACHE FILEPATH "")
set(CMAKE_OBJDUMP ${CMAKE_OBJDUMP} CACHE FILEPATH "")

# Disable compiler checks.
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

add_compile_options(
  "$<$<COMPILE_LANGUAGE:C>:${c_flags}>"
  "$<$<COMPILE_LANGUAGE:CXX>:${cxx_flags}>"
)

add_link_options(-mthumb --specs=nosys.specs -Wl,-Map=output.map -Wl,--gc-sections -mcpu=cortex-m0plus)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(CMAKE_C_OUTPUT_EXTENSION .o)

#######
## The following is deprecated for now
##
#set(CMAKE_C_FLAGS                   "${APP_C_FLAGS} -x c -Og -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99 -MD -MP -MF" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS                 "${APP_CXX_FLAGS} ${CMAKE_C_FLAGS} -fno-exceptions" CACHE INTERNAL "")

#set(CMAKE_C_FLAGS_DEBUG             "-Og -g3 -DDEBUG" CACHE INTERNAL "")
#set(CMAKE_C_FLAGS_RELEASE           "-Os -DNDEBUG" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")
#set(CMAKE_EXE_LINKER_FLAGS           "--specs=nano.specs -Wl,--gc-sections" CACHE INTERNAL "")

#set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_COMPILER} <LINK_FLAGS> <OBJECTS> -o <TARGET>")
#set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_COMPILER} <LINK_FLAGS> <OBJECTS> -o <TARGET>")
#set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)
