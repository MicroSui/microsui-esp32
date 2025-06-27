# ESP32 MicroSui Hardware Implementation

## Introduction

This is the code for the hardware implementation of the _ESP32 microcontroller_. Specifically, in this software, we are using version C3 of the ESP32 microcontroller (**_ESP32-C3_**), however, this code is compatible with all versions of ESP32.

For this hardware implementation, **_PlatformIO_** was chosen as the development environment and firmware builder.

## Getting Started

### 1. Install PlatformIO

**_PlatformIO_** is a _VSCode_ extension. Install _VSCode_ if you don't already have it.

### 2. Clone the Repository

```
git clone https://github.com/MicroSui/microsui-esp32.git
```

### 3. Open the Project in PlatformIO

Open the PlatformIO extension, click on `Open` in Quick Access, and select the project folder where you cloned it.

### 4. Check the Available Examples

Start your project from scratch, or begin with a reliable starting point by browsing the available examples.

### 5. Compile and Upload Firmware

Once you finish your project, compile and upload the firmware to the ESP32 by clicking `Upload and Monitor` in PlatformIO’s Project Tasks.

## Available Examples

These are the available examples in this Hardware Implementation:

- `signOfflineFromHexaPk` – Generate an offline Sui signature from a fixed message using a hexadecimal private key.
- `signOfflineFromBech32Pk` – Generate an offline Sui signature from a fixed message using a Sui Bech32 private key.

## Notes:

- If you want to use another version of ESP32 you simply need to change it to the version you want by modifying `board = xxxxxxx` (`board = esp32-c3-devkitm-1` by default) in the `/platformio.ini` file in the root of the project.
