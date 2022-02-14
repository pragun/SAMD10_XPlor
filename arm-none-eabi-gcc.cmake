#

# Without that flag CMake is not able to pass test compilation check
#

set(CMAKE_SYSTEM_NAME              Generic)
set(CMAKE_SYSTEM_PROCESSOR          ARM)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)

function(_find_compiler compiler_path compiler_exe)
    # Search user provided path first.
    find_program(
            ${compiler_path} ${compiler_exe}
            PATHS ENV PICO_TOOLCHAIN_PATH
            PATH_SUFFIXES bin
            NO_DEFAULT_PATH
    )

    # If not then search system paths.
    if ("${${compiler_path}}" STREQUAL "${compiler_path}-NOTFOUND")
        if (DEFINED ENV{PICO_TOOLCHAIN_PATH})
            message(WARNING "PICO_TOOLCHAIN_PATH specified ($ENV{PICO_TOOLCHAIN_PATH}), but ${compiler_exe} not found there")
        endif()
        find_program(${compiler_path} ${compiler_exe})
    endif ()
    if ("${${compiler_path}}" STREQUAL "${compiler_path}-NOTFOUND")
        set(PICO_TOOLCHAIN_PATH "" CACHE PATH "Path to search for compiler.")
        message(FATAL_ERROR "Compiler '${compiler_exe}' not found, you can specify search path with\
            \"PICO_TOOLCHAIN_PATH\".")
    endif ()
endfunction()

_find_compiler(CMAKE_AR arm-none-eabi-ar)
_find_compiler(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
_find_compiler(CMAKE_C_COMPILER arm-none-eabi-gcc)
_find_compiler(CMAKE_CXX_COMPILER arm-none-eabi-g++)
_find_compiler(CMAKE_LINKER arm-none-eabi-ld)
_find_compiler(CMAKE_OBJCOPY arm-none-eabi-objcopy)
_find_compiler(CMAKE_RANLIB arm-none-eabi-ranlib)
_find_compiler(CMAKE_SIZE arm-none-eabi-size)
_find_compiler(CMAKE_STRIP arm-none-eabi-strip)
_find_compiler(CMAKE_GCOV arm-none-eabi-gcov)

set(CMAKE_C_FLAGS                   "${APP_C_FLAGS} -Wno-psabi -fdata-sections -ffunction-sections -Wl,--gc-sections" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS                 "${APP_CXX_FLAGS} ${CMAKE_C_FLAGS} -fno-exceptions" CACHE INTERNAL "")

set(CMAKE_C_FLAGS_DEBUG             "-Os -g" CACHE INTERNAL "")
set(CMAKE_C_FLAGS_RELEASE           "-Os -DNDEBUG" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")
set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


