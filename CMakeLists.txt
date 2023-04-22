cmake_minimum_required(VERSION 3.13)

    # initialize the SDK based on PICO_SDK_PATH
    # note: this must happen before project()
    include(pico_sdk_import.cmake)
    project(my_pio_project)
    pico_sdk_init()

    add_compile_options(
        -Wall
        -Wno-format
        -Wno-unused-function
        -Wno-maybe-uninitialized
        -Wextra
        )

    add_executable(my_pio_project)

    # >>> CHANGE THIS LINE to reference your .PIO file >>>
    # ----------------------------------------------------
    pico_generate_pio_header(my_pio_project ${CMAKE_CURRENT_LIST_DIR}/ledcontrol.pio)

    # >>> CHANGE THIS LINE to reference your .C file(s) >>>
    # -----------------------------------------------------
    target_sources(my_pio_project PRIVATE main.c)

    # change these lines to decide where printf() output is sent to
    pico_enable_stdio_usb(my_pio_project 0)
    pico_enable_stdio_uart(my_pio_project 1)

    target_link_libraries(my_pio_project PRIVATE pico_stdlib hardware_pio)

    pico_add_extra_outputs(my_pio_project)
