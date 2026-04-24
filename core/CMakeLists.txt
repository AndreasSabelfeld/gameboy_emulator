# Define the core emulator as a static library
add_library(gbcore STATIC
        src/APU.cpp
        src/Cartridge.cpp
        src/CPU.cpp
        src/Joypad.cpp
        src/MMU.cpp
        src/PPU.cpp
        src/Timer.cpp

        src/MBC/MBC1.cpp
        src/MBC/MBC2.cpp
        src/MBC/MBC3.cpp
        src/MBC/MBC30.cpp
        src/MBC/MBC5.cpp
        src/MBC/MBC6.cpp
        src/MBC/MBC7.cpp

        include/CPU.h
        include/APU.h
        include/Cartridge.h
        include/Joypad.h
        include/MMU.h
        include/PPU.h
        include/Timer.h
)

# Tell the compiler where to find the header files for the core
target_include_directories(gbcore PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(gbcore PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)