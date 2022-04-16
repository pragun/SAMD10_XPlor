cmake_minimum_required(VERSION 3.6)

file(GLOB_RECURSE ASF_SRC ${CMAKE_CURRENT_SOURCE_DIR} *.c)
#message(${ASF_SRC})

set(HAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/hal)
set(HAL_UTILS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/hal/utils)
set(HRI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/hri)
set(HPL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/hpl)
set(QTOUCH_PATH ${CMAKE_CURRENT_SOURCE_DIR}/qtouch)
set(CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Config)
set(DEVICE_STARTUP ${CMAKE_CURRENT_SOURCE_DIR}/Device_Startup)
set(EXAMPLES ${CMAKE_CURRENT_SOURCE_DIR}/examples)


## HPL Include paths
set(HPL_ITEMS adc dac dmac eic evsys gclk pm sercom sysctrl tc)
list(APPEND HPL_ITEMS core port )
list(TRANSFORM HPL_ITEMS PREPEND "${HPL_PATH}/")

set(CMSIS_INCLUDE "F:\\samd10\\CMSIS\\5.4.0\\CMSIS\\Core\\Include")
set(SAMD10_INCLUDE "F:\\samd10\\SAMD10_DFP\\1.1.77\\include")

set(ASF_INCLUDES ${HAL_PATH}/include ${HAL_UTILS_PATH}/include ${SAMD10_INCLUDE} ${CMSIS_INCLUDE} ${HRI_PATH} ${HPL_ITEMS} ${QTOUCH_PATH})
set(QTOUCH_INCLUDES ${QTOUCH_PATH} ${QTOUCH_PATH}/include)

add_library(samd10_asf OBJECT)
target_sources(samd10_asf PRIVATE ${ASF_SRC})

target_include_directories(samd10_asf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SEGGER_PATH}/RTT ${SEGGER_PATH}/CONFIG)
target_include_directories(samd10_asf PUBLIC ${ASF_INCLUDES})
target_include_directories(samd10_asf PUBLIC ${QTOUCH_INCLUDES})
target_include_directories(samd10_asf PUBLIC ${CONFIG_PATH})
target_compile_definitions(samd10_asf PUBLIC __SAMD10D14AM__=1)
target_link_directories(samd10_asf PUBLIC ${QTOUCH_PATH}/lib/gcc/)
target_link_libraries(samd10_asf PUBLIC qtm_touch_key_cm0p_0x0002 qtm_freq_hop_auto_cm0p_0x0004 qtm_acq_runtime_samd10_0x000a)

set(ASF_LINKER_SCRIPT ${DEVICE_STARTUP}/samd10d14am_flash.ld PARENT_SCOPE)
