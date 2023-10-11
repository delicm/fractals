cmake_minimum_required(VERSION 3.10)
project(Fractal-C)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# List the source files explicitly
set(SOURCES
    src/boilerplate.cpp
    src/functions.cpp
    src/fractal.cpp
    src/interactions.cpp
    src/main.cpp
)

# Add the source files to the project
add_executable(fractal_main ${SOURCES})

# Include the source directory
target_include_directories(fractal_main PRIVATE src)

# Specify the path to SFML
list(APPEND CMAKE_PREFIX_PATH "/home/mdelic/Software/C-Includes/SFML/SFML-2.6.0/lib/cmake/SFML")

# Find the SFML library
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Link the SFML library to your executable
target_link_libraries(fractal_main PRIVATE sfml-graphics)
