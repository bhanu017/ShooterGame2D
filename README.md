# Mini Mayhem - 2D Multiplayer Shooter Game

A 2D multiplayer shooter game built with SFML (Simple and Fast Multimedia Library). This game features multiplayer functionality, weapon systems, and dynamic maps.

## Project Structure

```
mini-mayhem/
├── src/
|   ├── core/
│   ├── entities/
│   ├── server/
│   └── physics/
├── assets/
│   ├── textures/
│   ├── fonts/
│   └── maps/
├── .gitignore
├── packages.config
├── CMakeLists.txt
└── README.md
```

## Features

- Multiplayer support (Client-Server architecture)
- Multiple weapons and weapon switching
- Dynamic map system
- Collision detection
- Player movement and shooting mechanics

## Requirements

### System Requirements
- Linux/Windows OS
- C++ compiler (GCC 9.0 or higher)
- CMake 3.10 or higher

### Dependencies
- SFML 2.6.1 or higher
- OpenGL
- X11 (for Linux)

## Installation

### Prerequisites

1. Ensure you have the required build tools:
   ```bash
   # Ubuntu/Debian
   sudo apt update
   sudo apt install -y build-essential cmake git

   # Fedora
   sudo dnf install gcc-c++ cmake git
   ```

2. Install SFML development libraries:
   ```bash
   # Ubuntu/Debian
   sudo apt install -y \
       libsfml-dev \
       libsfml-system2.6 \
       libsfml-window2.6 \
       libsfml-graphics2.6 \
       libsfml-audio2.6 \
       libsfml-network2.6

   # Fedora
   sudo dnf install SFML SFML-devel
   ```

### Building the Project

1. Clone the repository:
   ```bash
   git clone [repository-url] mini-mayhem
   cd mini-mayhem
   ```

2. Create a build directory and navigate to it:
   ```bash
   mkdir build && cd build
   ```

3. Configure and build the project:
   ```bash
   cmake -DCMAKE_BUILD_TYPE=Release ..
   cmake --build . --parallel
   ```

   For debug builds, use:
   ```bash
   cmake -DCMAKE_BUILD_TYPE=Debug ..
   cmake --build . --parallel
   ```

## Running the Game

1. Start the server:
```bash
./MiniMayhem 1
```

2. Start the client(s):
```bash
./MiniMayhem 0
```

Alternatively,
Run in test mode:
```bash
./MiniMayhem 2
```

## Controls

- Arrow Keys: Move player
- Left Mouse Button: Shoot
- L Alt: Switch weapon
- L: Release weapon
- G: Acquire weapon

## Contributing

Feel free to submit issues and enhancement requests!

## License

[Add your license information here]
