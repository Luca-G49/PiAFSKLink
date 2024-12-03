# PiAFSKLink

![Version](https://img.shields.io/github/v/release/LUCA-G49/PiAFSKLink?include_prereleases) ![Milestone Progress](https://img.shields.io/github/milestones/progress-percent/LUCA-G49/PiAFSKLink/1) ![Open Issues](https://img.shields.io/github/issues/LUCA-G49/PiAFSKLink) ![License](https://img.shields.io/github/license/Luca-G49/PiAFSKLink?label=License)


**PiAFSKLink** is designed to transmitting and receiving AFSK (Audio Frequency Shift Keying) signals. It enables digital communication by modulating and demodulating audio signals.

The project has been developed and tested on a Raspberry Pi 4 with Raspbian OS but is designed to work on any Linux system that supports the required libraries. 

## How It Works

PiAFSKLink works by encoding and decoding digital data as AFSK audio signals, enabling communication via radio frequencies. It provides two primary functionalities:

### 1. **Transmission (AFSK Modulation)**

- Converts digital data (e.g., text or binary information) into AFSK-modulated audio signals.
- Transmits signals through the audio output of the system.

### 2. **Reception (AFSK Demodulation)**

- Captures incoming AFSK-modulated audio signals via the system’s audio input.
- Decodes the audio signals into digital data.

## Cryptography Support for Messages

PiAFSKLink includes optional message encryption to enhance the security of transmitted data. When encryption is enabled, messages are secured using the **AES-256-CBC** algorithm.

### Encryption Process:

1. **Encryption during Transmission**:
   - The message is encrypted with a 256-bit key using the AES-256-CBC algorithm.
   - A randomly generated Initialization Vector (IV) is prepended to the encrypted message for secure decryption.

2. **Decryption during Reception**:
   - The receiver extracts the IV from the incoming message.
   - The message is decrypted using the provided 256-bit key and the extracted IV.

## Requirements

### Hardware

- A Linux-based system (e.g., Raspberry Pi 4) with:
    - Audio input (e.g., microphone or line-in).
    - Audio output (e.g., headphones or speaker out).
- A radio device capable of transmitting/receiving audio signals (e.g., transceiver).

### Software

- **C++17 or later** for compiling the code.
- **ALSA** (Advanced Linux Sound Architecture) library for audio playback and capture.
- **FFTW** (Fast Fourier Transform) library.
- **spdlog** for logging.
- **OpenSSL** for cryptography.

### Software Dependencies

To install ALSA development libraries:

```bash
sudo apt-get update
sudo apt-get install libasound2-dev
```

To install FFTW development libraries:

```bash
sudo apt-get update
sudo apt-get install libfftw3-dev
```

To install spdlog:

```bash
sudo apt-get update
sudo apt-get install libspdlog-dev
```

To install OpenSSL:

```bash
sudo apt-get update
sudo apt-get install libssl-dev
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
│   ├── audio/                 # Audio device-related modules
│   │   └── audio_device.h     # Header for `audio_device.cpp`
│   ├── config/                # Configuration-related modules
│   │   └── app_config.h       # Header for `audio_device.cpp`
│   ├── gui/                   # User interface modules
│   │   ├── exit_menu.h        # Header for `exit_menu.cpp`
│   │   ├── gui_utils.h        # Header for `gui_utils.cpp`
│   │   ├── main_menu.h        # Header for `main_menu.cpp`
│   │   ├── receive_menu.h     # Header for `receive_menu.cpp`
│   │   ├── setup_menu.h       # Header for `setup_menu.cpp`
│   │   └── transmit_menu.h    # Header for `transmit_menu.cpp`
│   ├── logic/                 # Application logic
│   │   ├── receiver.h         # Header for `receiver.cpp`
│   │   └── transmitter.h      # Header for `transmitter.cpp`
│   └── utils/                 # General utility functions
│       ├── encryption.h        # Header for `encryption.cpp`
│       ├── fft.h              # Header for `fft.cpp`
│       ├── get_time.g         # Header for `get_time.cpp`
│       ├── logger.h           # Header for `logger.cpp`
│       └── serialization.h    # Header for `serialization.cpp`
├── src/                       # Main source code
│   ├── audio/                 # Audio device-related modules
│   │   └── audio_device.cpp   # Implementation of audio device handling
│   ├── config/                # Configuration-related modules
│   │   └── app_config.cpp     # Implementation of application configuration
│   ├── gui/                   # User interface modules
│   │   ├── exit_menu.cpp      # Implementation of the exit menu
│   │   ├── gui_utils.cpp      # Utility functions for GUI
│   │   ├── main_menu.cpp      # Implementation of the main menu
│   │   ├── receive_menu.cpp   # Implementation of the receive menu
│   │   ├── setup_menu.cpp     # Implementation of the setup menu
│   │   └── transmit_menu.cpp  # Implementation of the transmit menu
│   ├── logic/                 # Application logic
│   │   ├── receiver.cpp       # Implementation of the receiver logic
│   │   └── transmitter.cpp    # Implementation of the transmitter logic
│   ├── utils/                 # General utility functions
│   │   ├── encryption.cpp     # Implementation of encryption fuctions
│   │   ├── fft.cpp            # Implementation of FFT fuctions
│   │   ├── get_time.cpp       # Implementation of get time functions
│   │   ├── logger.cpp         # Implementation of logger fuctions
│   │   └── serialization.cpp  # Implementation of Serialization functions
│   └── main.cpp               # Program entry point
├── CMakeLists.txt             # CMake build configuration
├── LICENSE                    # LICENSE file
└── README.md                  # Project documentation
```

## Feedback and Suggestions

Feedbacks and suggestions are welcome! Feel free to share here in the [Discussions area](https://github.com/LUCA-G49/PiAFSKLink/discussions).

## License

This project is licensed under the MIT License. See the [License](LICENSE) file for details.