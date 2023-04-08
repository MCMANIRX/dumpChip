cmake_minimum_required(VERSION 3.12)

#build fcns
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
#include($ENV{PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)
#include(pico_extras_import.cmake)




project(dump C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)



pico_sdk_init()



#添加编译子目录




#添加头文件目录





add_executable(${PROJECT_NAME}
   # raw.c
   # frame_test.c
   # frame_test.h
   # waveshare_frame.c
   # barometer.c
   # run_motors.c
  #temp.c

    #vga_out.c
    # ./lib/GUI/GUI_Paint.c
    

    #ErinLED.c
    #runMotors.c

    dump.c
    
    )




# make uf2
pico_add_extra_outputs(${PROJECT_NAME})

#link to pico stdlib


target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_spi

    
    
    
)


pico_enable_stdio_usb(dump 1)
pico_enable_stdio_uart(dump 0)