# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(PiAFSKLink LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the source and include directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Automatically collect all source files
file(GLOB SOURCES
    ${SRC_DIR}/audio/*.cpp
    ${SRC_DIR}/config/*.cpp
    ${SRC_DIR}/gui/*.cpp
    ${SRC_DIR}/logic/*.cpp
    ${SRC_DIR}/utils/*.cpp
    ${SRC_DIR}/main.cpp
)

# Create the executable
add_executable(PiAFSKLink ${SOURCES})

# Include directories for headers
target_include_directories(PiAFSKLink PUBLIC
    ${INCLUDE_DIR}/audio
    ${INCLUDE_DIR}/config
    ${INCLUDE_DIR}/gui
    ${INCLUDE_DIR}/logic
    ${INCLUDE_DIR}/utils
)

# Link spdlog library
find_package(spdlog REQUIRED)

# Link OpenSSL library
find_package(OpenSSL REQUIRED)

# Link necessary libraries: spdlog, ALSA, and FFTW3
target_link_libraries(PiAFSKLink PRIVATE
    spdlog::spdlog
    asound
    fftw3
    OpenSSL::Crypto
    OpenSSL::SSL
)

# Set additional compile options (optional but recommended)
target_compile_options(PiAFSKLink PRIVATE -Wall -Wextra -pedantic)

# Optional: Set CMake to use C++20 standard if not already specified globally
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
