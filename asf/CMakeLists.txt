cmake_minimum_required(VERSION 3.6)

set(HAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/hal)
set(HAL_UTILS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/hal/utils)
set(HRI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/hri)
set(HPL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/hpl)
set(QTOUCH_PATH ${CMAKE_CURRENT_SOURCE_DIR}/qtouch)
set(CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Config)
set(DEVICE_STARTUP ${CMAKE_CURRENT_SOURCE_DIR}/Device_Startup)
set(EXAMPLES ${CMAKE_CURRENT_SOURCE_DIR}/examples)

set(DEVICE_STARTUP_CSRCS ${DEVICE_STARTUP}/startup_samd10.c ${DEVICE_STARTUP}/system_samd10.c)
set(ATMEL_START_CSRCS ${CMAKE_CURRENT_SOURCE_DIR}/driver_init.c ${CMAKE_CURRENT_SOURCE_DIR}/atmel_start.c)

## HPL Sources
set(HPL_ITEMS adc dac dmac eic evsys gclk pm rtc sercom sysctrl)
set(HPL_CSRCS )

foreach(X IN LISTS HPL_ITEMS)
list(APPEND HPL_CSRCS ${X}/hpl_${X}.c)
endforeach()
list(APPEND HPL_CSRCS core/hpl_init.c core/hpl_core_m0plus_base.c)
list(TRANSFORM HPL_CSRCS PREPEND "${HPL_PATH}/")

list(APPEND HPL_ITEMS core port )
list(TRANSFORM HPL_ITEMS PREPEND "${HPL_PATH}/")

## HAL Sources
set(HAL_CSRCS )
set(HAL_ITEMS adc_sync atomic dac_sync delay evsys ext_irq gpio i2c_s_async init io sleep timer usart_async)
foreach(X IN LISTS HAL_ITEMS)
list(APPEND HAL_CSRCS ${HAL_PATH}/src/hal_${X}.c)
endforeach()

## HAL Util Sources
set(HAL_UTILS_CSRCS )
set(HAL_UTILS_ITEMS assert event list ringbuffer syscalls)
foreach(X IN LISTS HAL_UTILS_ITEMS)
list(APPEND HAL_UTILS_CSRCS ${HAL_UTILS_PATH}/src/utils_${X}.c)
endforeach()

set(CMSIS_INCLUDE "F:\\samd10\\CMSIS\\5.4.0\\CMSIS\\Core\\Include")
set(SAMD10_INCLUDE "F:\\samd10\\SAMD10_DFP\\1.1.77\\include")

set(ASF_INCLUDES ${HAL_PATH}/include ${HAL_UTILS_PATH}/include ${SAMD10_INCLUDE} ${CMSIS_INCLUDE} ${HRI_PATH} ${HPL_ITEMS} ${QTOUCH_PATH})
set(QTOUCH_INCLUDES ${QTOUCH_PATH} ${QTOUCH_PATH}/include ${QTOUCH_PATH}/datastreamer)

add_library(samd10_asf)
target_sources(samd10_asf PRIVATE ${ATMEL_START_CSRCS})
target_sources(samd10_asf PRIVATE ${HAL_UTILS_CSRCS})
target_sources(samd10_asf PRIVATE ${DEVICE_STARTUP_CSRCS})
target_sources(samd10_asf PRIVATE ${HPL_CSRCS})
target_sources(samd10_asf PRIVATE ${HAL_CSRCS})
target_sources(samd10_asf PRIVATE ${QTOUCH_PATH}/touch.c ${QTOUCH_PATH}/datastreamer/datastreamer_UART_sam.c)

target_include_directories(samd10_asf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SEGGER_PATH}/RTT ${SEGGER_PATH}/CONFIG)
target_include_directories(samd10_asf PUBLIC ${ASF_INCLUDES})
target_include_directories(samd10_asf PUBLIC ${QTOUCH_INCLUDES})
target_include_directories(samd10_asf PUBLIC ${CONFIG_PATH})
target_compile_definitions(samd10_asf PUBLIC __SAMD10D14AM__=1)
target_link_directories(samd10_asf PUBLIC ${QTOUCH_PATH}/lib/gcc/)
target_link_libraries(samd10_asf PUBLIC qtm_touch_key_cm0p_0x0002 qtm_freq_hop_auto_cm0p_0x0004 qtm_acq_runtime_samd10_0x000a)

set(ASF_LINKER_SCRIPT ${DEVICE_STARTUP}/samd10d14am_flash.ld PARENT_SCOPE)
