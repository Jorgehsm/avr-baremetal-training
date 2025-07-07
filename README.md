# AVR Bare-Metal Training

This repository contains simple bare-metal programming examples for AVR microcontrollers (e.g., ATmega328P), without using the Arduino IDE or high-level libraries. The goal is to practice direct register-level control of peripherals.

## Included Examples

- **analogInput**: Reads an analog value from ADC0 and prints it to the Serial Monitor.
- **blink**: Toggles the state of pins PB5 and PD5 in a loop.
- **digitalInput**: Reads the digital state of pin PD7 and sets PB5 and PD5 accordingly.
- **pwmWrite**: Reads an analog value from ADC0 and adjusts the PWM duty cycle on PD5 (OC0B) proportionally.

## Requirements

- [PlatformIO](https://platformio.org/) (VSCode extension or CLI)
- AVR toolchain (managed automatically by PlatformIO)
- `atmelavr` platform
- atmega328p microcontroller

## How to Build

This project uses [PlatformIO](https://platformio.org/) to manage compilation and uploading.

To build and upload a specific example:

```bash
# Open the example folder
cd examples/pwmWrite  # for instance

# Compile the project
pio run

# Upload to the board (make sure the correct port is set)
pio run --target upload

# Open the serial monitor (optional)
pio device monitor
```
