# PiAFSKLink

![Version](https://img.shields.io/github/v/release/LUCA-G49/PiAFSKLink?include_prereleases) ![Milestone Progress](https://img.shields.io/github/milestones/progress-percent/LUCA-G49/PiAFSKLink/1) ![Open Issues](https://img.shields.io/github/issues/LUCA-G49/PiAFSKLink) ![License](https://img.shields.io/github/license/Luca-G49/PiAFSKLink?label=License)


PiAFSKLink is a project that uses a Raspberry Pi to transmit and receive AFSK (Audio Frequency Shift Keying) signals. The project is designed for digital radio communication, allowing users to send and receive data over radio frequencies using AFSK modulation.

## Features

- Use a Raspberry Pi to handle AFSK modulation and demodulation.

## How It Works

PiAFSKLink operates by modulating and demodulating data into audio signals using AFSK. The Raspberry Pi handles the entire process, allowing you to interface with any radio device capable of transmitting and receiving audio signals (such as a transceiver with audio input and output).

### 1. **Transmission (AFSK Modulation)**

- The software takes digital data (e.g., text or binary information) and converts it into AFSK-modulated audio signals.
- These audio signals are then transmitted via the audio output of the Raspberry Pi.
- The frequency shifts in the audio correspond to the different binary states of the transmitted data.

### 2. **Reception (AFSK Demodulation)**

- The Raspberry Pi uses its audio input to capture the incoming AFSK signals.
- The software then demodulates the audio signal back into digital data, extracting the transmitted information.
- This data can be displayed on the Raspberry Pi or sent to another system for further processing.

## Requirements

- **Raspberry Pi** (with Raspbian OS)
- **ALSA** (Advanced Linux Sound Architecture) library for audio playback and capture.
- **C++17 or later** for compiling the code.

### Software Dependencies

To install ALSA development libraries:

```bash
sudo apt-get update
sudo apt-get install libasound2-dev
```

## Build Instructions

This project uses **CMake** as the build system to manage and configure the build process.

If you don't have CMake installed on your Raspberry Pi, install it using the following command:

```bash
sudo apt-get install cmake
```
### Visual Studio Code Integration

For convenience, I've included two CMake tasks in the `tasks.json` file for Visual Studio Code:

1. **CMake Build**: This task configures and builds the project using CMake.
2. **Build Project**: This task runs the build process directly from Visual Studio Code.

To use these tasks, simply open the Command Palette in Visual Studio Code (Ctrl+Shift+P), search for **Tasks: Run Task**, and choose the desired task.

These tasks make it easier to build and manage the project directly from within Visual Studio Code.

## Project structure
```
PiAFSKLink/
├── build/                     # Build directory
├── include/                   # Project header files
│   ├── receiver.h             # Header for `receiver.cpp`
│   └── transmitter.h          # Header for `transmitter.cpp`
├── src/                       # Main source code
│   ├── audio/                 # Audio device-related modules
│   │   ├── audio_device.cpp   # Implementation of audio device handling
│   │   └── audio_device.h     # Header for `audio_device.cpp`
│   ├── config/                # Configuration-related modules
│   │   ├── app_config.cpp     # Implementation of application configuration
│   │   └── app_config.h       # Header for `app_config.cpp`
│   ├── gui/                   # User interface modules
│   │   ├── exit_menu.cpp      # Implementation of the exit menu
│   │   ├── exit_menu.h        # Header for `exit_menu.cpp`
│   │   ├── gui_utils.cpp      # Utility functions for GUI
│   │   ├── gui_utils.h        # Header for `gui_utils.cpp`
│   │   ├── main_menu.cpp      # Implementation of the main menu
│   │   ├── main_menu.h        # Header for `main_menu.cpp`
│   │   ├── receive_menu.cpp   # Implementation of the receive menu
│   │   ├── receive_menu.h     # Header for `receive_menu.cpp`
│   │   ├── setup_menu.cpp     # Implementation of the setup menu
│   │   ├── setup_menu.h       # Header for `setup_menu.cpp`
│   │   ├── transmit_menu.cpp  # Implementation of the transmit menu
│   │   └── transmit_menu.h    # Header for `transmit_menu.cpp`
│   ├── logic/                 # Application logic
│   │   ├── receiver.cpp       # Implementation of the receiver logic
│   │   └── transmitter.cpp    # Implementation of the transmitter logic
│   ├── utils/                 # General utility functions
│   │   ├── serialization.cpp  # Implementation of Serialization functions
│   │   └── serialization.h    # Header for `serialization.cpp`
│   └── main.cpp               # Program entry point
├── CMakeLists.txt         # CMake build configuration
├── LICENSE                # LICENSE file
└── README.md              # Project documentation
```