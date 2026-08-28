# Create the actual runnable executable
add_executable(GameBoyFrontEnd
        src/main.cpp
        include/Renderer.h
        src/Renderer.cpp
        src/Input.cpp
        include/Audio.h
        src/Audio.cpp
)

# Tell the frontend where its own header files are
target_include_directories(GameBoyFrontEnd PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/core/include
)

# Find SDL2 via vcpkg
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(GameBoyFrontEnd PRIVATE
        gbcore
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)