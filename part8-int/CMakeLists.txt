cmake_minimum_required( VERSION 3.0 )

# Mark the language as C so that CMake doesn't try to test the C++
# cross-compiler's ability to compile a simple program because that will fail
project( arm-os-learning C ASM )

# We had to adjust the CMAKE_C_FLAGS variable in the toolchain file to make sure
# the compiler would work with CMake's simple program compilation test. So unset
# it explicitly before re-setting it correctly for our system
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles -Wl,-T,rpi.x" )

add_executable( main.elf main.c gpio.c boot.S systimer.c rpi-aux.c util.c)

add_custom_command(
        TARGET main.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ./main.elf -O binary ./kernel.img
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Convert the ELF output file to a binary image" )
