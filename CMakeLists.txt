# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(PiAFSKLink LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory for header files
include_directories(include)

# Add subdirectory
#add_subdirectory(src)

# Add all source files
#set(SOURCE_FILES
#    src/main.cpp
#    src/transmitter.cpp
#    src/receiver.cpp
#    src/audio_utils.cpp
#)

# Percorso principale dei sorgenti
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Aggiungi tutti i file sorgenti
set(SOURCES
    ${SRC_DIR}/audio/audio_device.cpp
    ${SRC_DIR}/config/app_config.cpp
    ${SRC_DIR}/gui/gui_utils.cpp
    ${SRC_DIR}/gui/main_menu.cpp
    ${SRC_DIR}/gui/receive_menu.cpp
    ${SRC_DIR}/gui/transmit_menu.cpp
    ${SRC_DIR}/gui/setup_menu.cpp
    ${SRC_DIR}/gui/exit_menu.cpp
    ${SRC_DIR}/logic/receiver.cpp
    ${SRC_DIR}/logic/transmitter.cpp
    ${SRC_DIR}/utils/serialization.cpp
    ${SRC_DIR}/main.cpp
)

# Add the executable
add_executable(PiAFSKLink ${SOURCES})

# Link the ALSA library
target_link_libraries(PiAFSKLink asound)

# Includi le directory per gli header
target_include_directories(PiAFSKLink PUBLIC
    ${SRC_DIR}/audio
    ${SRC_DIR}/config
    ${SRC_DIR}/gui
    ${SRC_DIR}/logic
    ${SRC_DIR}/utils
)
