# Simple Snake Game Clone 144p

A classic Snake game implementation in C++ for Unix/Linux terminal environments.

## Description

This is a terminal-based Snake game where players control a snake to collect apples and grow longer. The game features smooth keyboard input handling, collision detection, and progressive difficulty as the snake grows.

## Features

- Terminal-based ASCII graphics
- Real-time keyboard input (WASD controls)
- Dynamic snake growth upon eating apples
- Collision detection (walls and self-collision)
- Score tracking
- Adjustable game speed

## Requirements

- Unix/Linux operating system (macOS, Linux distributions)
- C++ compiler with C++11 support (g++, clang++)
- POSIX-compliant terminal

## Compilation

```bash
g++ -o snake simple-snake-game-144p.cpp
```

Or with C++11 standard:

```bash
g++ -std=c++11 -o snake simple-snake-game-144p.cpp
```

## How to Run

```bash
./snake
```

## Controls

| Key | Action |
|-----|--------|
| `w` | Move Up |
| `a` | Move Left |
| `s` | Move Down |
| `d` | Move Right |
| `q` | Quit Game |

## Gameplay

- Control the snake (`O`) to eat apples (`*`)
- Each apple increases your score by 1 and grows the snake's tail
- Avoid hitting the walls (`#`) or the snake's own body (`o`)
- The game ends when a collision occurs

## Game Speed

The default speed is set to 120ms per game tick. To adjust the speed, modify the `usleep()` value in the main loop:

```cpp
usleep(120000); // Decrease for faster, increase for slower
```

Recommended range: 60000-200000 microseconds (60-200ms)

## Technical Details

- Board dimensions: 25×20 characters
- Maximum tail length: 100 segments
- Non-blocking keyboard input using termios
- Screen refresh using ANSI clear command

## Known Limitations

- Requires POSIX-compliant terminal (not compatible with Windows without WSL)
- Uses `system("clear")` which may cause screen flicker on some terminals

## License

This project is open source and available for educational purposes.

## Author

Created as a learning project for terminal-based game development in C++.
