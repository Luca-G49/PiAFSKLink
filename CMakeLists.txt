# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(PiAFSKLink LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory for header files
include_directories(include)

# Add all source files
set(SOURCE_FILES
    src/main.cpp
    src/transmitter.cpp
    src/receiver.cpp
    src/audio_utils.cpp
)

# Add the executable
add_executable(PiAFSKLink ${SOURCE_FILES})

# Link the ALSA library
target_link_libraries(PiAFSKLink asound)
