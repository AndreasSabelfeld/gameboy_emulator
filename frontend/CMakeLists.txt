# Create the actual runnable executable
add_executable(emulator
        src/Audio.cpp
        src/Input.cpp
        src/main.cpp
        src/Renderer.cpp
        src/Window.cpp
)

# Tell the frontend where its own header files are
target_include_directories(emulator PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Find SDL2 via vcpkg
find_package(SDL2 CONFIG REQUIRED)

# Link the core library and SDL2 to our "emulator" executable
target_link_libraries(emulator
        PRIVATE
        gbcore                                                           # 1. Your core Gameboy hardware logic
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>                          # 2. SDL2 main entry point wrapper
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>   # 3. The actual SDL2 library from vcpkg
)