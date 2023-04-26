add_executable(${NAME}
        main.cpp
        Agent.cpp
        Screen.cpp
        ScreenWriter.cpp
        )

# include(common/pimoroni_i2c)
# include(common/pimoroni_bus)
# include(libraries/bitmap_fonts/bitmap_fonts)
# include(libraries/hershey_fonts/hershey_fonts)
# include(libraries/pico_explorer/pico_explorer)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
	 pico_stdlib
     FreeRTOS-Kernel-Heap4
     hardware_spi
     hardware_pwm
     hardware_dma
     rgbled
     button
     uc8151
     pico_graphics
	)


target_include_directories(${NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../lib/FreeRTOS-Kernel/include
     )
     
target_compile_definitions(${NAME} PRIVATE
    FREE_RTOS_KERNEL_SMP=1
    portSUPPORT_SMP=1
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)