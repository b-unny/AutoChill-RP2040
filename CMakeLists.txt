cmake_minimum_required(VERSION 3.13)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(FinalProject C CXX ASM)

pico_sdk_init()

add_executable(FinalProject main.c lib.c)

pico_generate_pio_header(FinalProject ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

target_link_libraries(FinalProject 
	pico_stdlib 
	hardware_adc
	hardware_pwm
	hardware_pio
	hardware_timer
)

# Habilitar saída USB (opcional)
pico_enable_stdio_usb(FinalProject 1)
pico_enable_stdio_uart(FinalProject 0)

pico_add_extra_outputs(FinalProject)

# Add executable. Default name is the project name, version 0.1
pico_set_program_name(FinalProject "FinalProject")
pico_set_program_version(FinalProject "0.1")

# Add the standard include files to the build
target_include_directories(FinalProject PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add any user requested libraries
target_link_libraries(FinalProject)
