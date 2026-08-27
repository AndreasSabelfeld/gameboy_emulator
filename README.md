# Game Boy Emulator

A custom, fully functional original Nintendo Game Boy (DMG) emulator written from scratch in modern C++.

This project was built to understand the intricacies of low-level hardware emulation, cycle-accurate timing, and system architecture. It successfully boots the original Game Boy Boot ROM, passes major hardware test ROMs (like Blargg's CPU tests), and plays classic games like *Tetris*.

![Game Boy Emulator Screenshot](docs/screenshot.png)

## Features
* **Custom CPU Core:** Fully implemented LR35902 instruction set with cycle-accurate NOP NOP interrupt dispatching.
* **Pixel Processing Unit (PPU):** Supports background rendering, the window overlay, 8x8/8x16 sprites, X/Y flipping, and accurate palette translation.
* **Memory Management Unit (MMU):** Handles internal routing for VRAM, WRAM, HRAM, Echo RAM, and restricted memory-mapped I/O zones.
* **Hardware Interrupts:** Fully functioning `IME`, `IE`, and `IF` registers supporting VBlank, LCD STAT, and Joypad interrupts.
* **Direct Memory Access (DMA):** Safe, hardware-accurate DMA OAM transfers for sprite rendering.
* **Boot ROM Support:** Watch the iconic Nintendo logo drop.
* **SDL2 Frontend:** Hardware-accelerated rendering and mapped keyboard inputs.

## Controls
The keyboard is currently mapped to the Game Boy Joypad as follows:

| Game Boy | Keyboard |
| :--- |:---------|
| **D-Pad** | WASD     |
| **A** | `P`      |
| **B** | `O`      |
| **Start** | `.`      |
| **Select** | `,`      |

## Building from Source

### Prerequisites
* A C++17 (or newer) compatible compiler (GCC, Clang, or MSVC)
* [CMake](https://cmake.org/) (3.10 or higher)
* [SDL2](https://www.libsdl.org/) development libraries

### macOS (using Homebrew)
```bash
brew install cmake sdl2