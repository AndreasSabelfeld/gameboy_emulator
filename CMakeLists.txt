cmake_minimum_required(VERSION 3.20)
project(GameBoyEmulator VERSION 1.0 LANGUAGES CXX)

# Require C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set strict compiler warnings to catch bugs early
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()

# Add the subdirectories
add_subdirectory(core)
add_subdirectory(frontend)

# uncomment when you add tests
# target_compile_definitions(GameBoyEmulator PRIVATE EMULATOR_DEBUG)
# enable_testing()
# add_subdirectory(tests)