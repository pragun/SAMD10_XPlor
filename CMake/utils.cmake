function(find_toolchain_exe compiler_path compiler_exe)
    # Search user provided path first.
    find_program(
            ${compiler_path} ${compiler_exe}
            PATHS ENV SAMD10_TOOLCHAIN_PATH
            PATH_SUFFIXES bin
            NO_DEFAULT_PATH
    )

    # If not then search system paths.
    if ("${${compiler_path}}" STREQUAL "${compiler_path}-NOTFOUND")
        if (DEFINED ENV{SAMD10_TOOLCHAIN_PATH})
            message(WARNING "SAMD10_TOOLCHAIN_PATH specified ($ENV{SAMD10_TOOLCHAIN_PATH}), but ${compiler_exe} not found there")
        endif()
        find_program(${compiler_path} ${compiler_exe})
    endif ()
    if ("${${compiler_path}}" STREQUAL "${compiler_path}-NOTFOUND")
        set(SAMD10_TOOLCHAIN_PATH "" CACHE PATH "Path to search for compiler.")
        message(FATAL_ERROR "Compiler '${compiler_exe}' not found, you can specify search path with\
            \"SAMD10_TOOLCHAIN_PATH\".")
    endif ()
endfunction()
