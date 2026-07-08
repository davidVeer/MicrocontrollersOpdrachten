# MicrocontrollersOpdrachten

<!-- Short one-line description, e.g.: -->
<!-- Coursework and final assignment for the Microcontrollers course, targeting the ATmega128 on a BigAVR6 (UNI-DS6) board. -->

## About this project

- **Target MCU:** ATmega128
- **Board:** BigAVR6 (UNI-DS6)
- **Toolchain:** [PlatformIO](https://platformio.org/) inside VS Code
- **Flashing tool:** AVRflash (`.hex` output)

<!-- TODO: Add a short paragraph about why PlatformIO is used here instead of Microchip Studio -->
<!-- e.g.: PlatformIO is used purely as a build system so VS Code can be used as the editor; -->
<!-- the compiler produces a .hex file which is then flashed onto the ATmega128 using AVRflash. -->

## Repository structure

```
.
├── platformio.ini      # PlatformIO project configuration (env, board, platform)
├── main.c               # Entry point / current assignment code
├── LCD.c / LCD.h         # LCD driver (4-bit mode)
├── ioisr.c               # <!-- TODO: describe purpose (interrupt/ISR related?) -->
└── ...
```

<!-- TODO: expand structure as more assignments / files are added -->
<!-- Consider organizing per-assignment in separate folders or branches, and note that here -->

## Prerequisites

- [VS Code](https://code.visualstudio.com/)
- [PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode)
- AVRflash (or your preferred AVR programmer software)
- <!-- TODO: hardware programmer used, e.g. USBasp / AVRISP mkII -->

## Getting started

1. Clone this repository:
   ```bash
   git clone https://github.com/davidVeer/MicrocontrollersOpdrachten.git
   cd MicrocontrollersOpdrachten
   git checkout EindOpdracht
   ```
2. Open the folder in VS Code with the PlatformIO extension installed.
3. Build the project:
   ```bash
   pio run
   ```
4. The compiled `.hex` file will be located in:
   ```
   .pio/build/uno/firmware.hex
   ```
   <!-- TODO: verify/update this path, since platformio.ini currently uses env:uno with board=atmega128 -->
5. Flash the `.hex` file to the ATmega128 using AVRflash.

## Configuration notes

<!-- TODO: explain platformio.ini choices, e.g.: -->
<!-- - Why env is named "uno" despite targeting atmega128 -->
<!-- - F_CPU / clock source used (see #define F_CPU in main.c) -->
<!-- - Any fuse settings required for the BigAVR6 board -->

## Assignments

<!-- TODO: list assignments and briefly what each demonstrates -->
- [ ] Assignment 1 — ...
- [ ] Assignment 2 — ...
- [ ] Eindopdracht (final assignment) — ...

## Hardware / wiring

<!-- TODO: document pin connections, e.g. LCD wiring to PORTA/PORTC as used in LCD.c -->

## Known issues / TODO

<!-- TODO: list any current limitations, bugs, or planned improvements -->

## License

<!-- TODO: add license if applicable -->
