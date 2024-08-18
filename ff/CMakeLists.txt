cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProject)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Source files for the main executable
set(MAIN_SOURCES
    DynamicPool.c
    ErrorHandler.c
    DynamicContainer.c
)

# Header files
set(HEADERS
    DynamicPool.h
    ErrorHandler.h
    DynamicContainer.h
)

# Create the main executable
add_executable(MyExecutable ${MAIN_SOURCES} ${HEADERS})

# Link pthread library to the main executable
target_link_libraries(MyExecutable pthread)

# Define the output directory for executables
set_target_properties(MyExecutable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Create a separate executable for the test file
add_executable(TestExecutable Test.c ${MAIN_SOURCES}  ${HEADERS})

# Link pthread library to the test executable
target_link_libraries(TestExecutable pthread)

# Add custom command to run the main executable after building
add_custom_command(TARGET MyExecutable
    POST_BUILD
    COMMAND ${CMAKE_BINARY_DIR}/bin/MyExecutable
    COMMENT "Running MyExecutable after build"
)

# Define the output directory for the test executable
set_target_properties(TestExecutable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add custom command to run the test executable after building it
add_custom_command(TARGET TestExecutable
    POST_BUILD
    COMMAND valgrind ${CMAKE_BINARY_DIR}/bin/TestExecutable
    COMMENT "Running TestExecutable after build"
)
