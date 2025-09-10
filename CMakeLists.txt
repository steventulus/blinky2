cmake_minimum_required(VERSION 3.13)
project(firmware C)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -g -O0 -Wall")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/link.ld)
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKER_SCRIPT} -nostdlib")

set(SOURCES
    main.c
    startup.c
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMENT "Generating binary file"
)

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -f ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin *.o
)
