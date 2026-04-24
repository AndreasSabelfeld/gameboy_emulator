include(FetchContent)

# Automatically download Catch2 from GitHub
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(cpu_tests cpu_tests.cpp)
target_link_libraries(cpu_tests PRIVATE gbcore Catch2::Catch2WithMain)

# Create a test executable
add_executable(cpu_tests
        cpu_tests.cpp
)

# Link the core emulator library so we can test the CPU functions
target_link_libraries(cpu_tests PRIVATE gbcore)

# If you use Catch2 or GoogleTest, you would link them here.
# For example, with GoogleTest:
# find_package(GTest REQUIRED)
# target_link_libraries(cpu_tests PRIVATE GTest::gtest_main)

# Register the test so CLion's test runner can see it
add_test(NAME CPU_Instruction_Tests COMMAND cpu_tests)