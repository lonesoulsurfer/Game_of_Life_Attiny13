# Game of Life on an ATtiny13

This is Conway's Game of Life on a 16 × 16 LED display. It uses an ATtiny13 microcontroller. A diffuser in front of the LEDs makes the cells look more alive.

![Game of Life ATtiny13](https://github.com/user-attachments/assets/ab6fc993-5127-49f7-96ff-d019d419f60b)

## Build guide and video

- Step-by-step build guide on Instructables: [Conway's Game of Life Running on an ATtiny13](https://www.instructables.com/Conways-Game-of-Life-Running-on-an-ATtiny13/)
- Video on YouTube: [Game of Life ATtiny13](https://youtu.be/9KQFAfuK4dU)

## What is the Game of Life?

The Game of Life is a cellular automaton by the mathematician John Conway. It is a "zero-player game": you set the start pattern, and then the cells live, die or multiply by simple rules. The patterns can look alive.

## What you need

### Hardware

- All parts are in the [parts list](Parts%20List.pdf).
- The schematic is [Schematic.png](Schematic.png).
- The Gerber files for the PCB and the front panel are in [Gerber Files](Gerber%20Files/). You can send them to a PCB maker.

### Software

- Arduino IDE, with the [MicroCore](https://github.com/MCUdude/MicroCore) board package for the ATtiny13
- A programmer for the ATtiny13, for example my [ATtiny85 programmer](https://github.com/lonesoulsurfer/ATtiny_85_Programmer)

## Program the ATtiny13

The Instructables guide shows each step. In short:

1. Install the MicroCore board package in the Arduino IDE.
2. Open `Game_of_Life Arduino_Sketch/Game_of_life/Game_of_life.ino`.
3. Put the ATtiny13 in your programmer.
4. Set the board and programmer settings that the guide tells you.
5. Click **Sketch → Upload Using Programmer**.

The sketch folder also has a ready `.hex` file.

## Changes from the original project

- I designed a PCB and a front panel.
- I changed some values in the sketch, so that the game runs faster and longer.
- I added a diffuser in front of the LEDs.

## Files in this repository

| Folder or file | Contents |
|----------------|----------|
| `Game_of_Life Arduino_Sketch/Game_of_life/` | Firmware and a ready `.hex` file |
| `Eagle Files/` | Eagle files for the PCB |
| `Front Panel Design/` | KiCad, SVG and DXF files for the front panel |
| `Gerber Files/` | Gerber files for the PCB and the front panel, ready to order |
| `Parts List.pdf` | Parts list |
| `Schematic.png`, `PCB - Image.png` | Schematic and PCB image |

## More information

- [Original project on Instructables](https://www.instructables.com/Conways-Life-of-Life-of-1616-Cells-Made-With-ATtin/) by Sanuki Udon
- [Conway's Game of Life on Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
- [Play the Game of Life online](https://playgameoflife.com/)
- [A computer built in the Game of Life](https://www.nicolasloizeau.com/gol-computer)

## Credits

- Original project and code: Kei Takagi (Sanuki Udon), 2017.
- PCB, front panel and changes: Marcus ([lonesoulsurfer](https://github.com/lonesoulsurfer)).

## Support

Do you like this project? You can support my work on [GitHub Sponsors](https://github.com/sponsors/lonesoulsurfer).

## Licence

- **Code:** [MIT License](LICENSE). The original code by Kei Takagi uses the MIT License. Copyright (c) 2017 Kei Takagi and 2025 Marcus (lonesoulsurfer).
- **Hardware** (PCB, front panel and Gerber files): [CERN Open Hardware Licence v2, Strongly Reciprocal](LICENSE-HARDWARE). You can make, change and sell boards. If you share or sell a changed design, you must also share the changed design files under the same licence.
