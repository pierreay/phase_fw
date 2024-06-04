cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(aesonly-poc C CXX ASM)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(aesonly-poc
    main.c
    tinyaes/aes.c
)

pico_enable_stdio_usb(aesonly-poc 1)
pico_enable_stdio_uart(aesonly-poc 0)

pico_add_extra_outputs(aesonly-poc)

target_include_directories(aesonly-poc PRIVATE ${CMAKE_CURRENT_LIST_DIR} )

target_link_libraries(aesonly-poc
    pico_cyw43_arch_lwip_threadsafe_background
    pico_stdlib
    pico_btstack_ble
    pico_btstack_cyw43
    cyw43_driver
    pico_cyw43_arch_none
)
