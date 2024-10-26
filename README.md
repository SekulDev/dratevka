# Dratewka the Shoemaker - Console Game

## About

This project is a console-based remake of the classic Atari game "Dratewka the Shoemaker". It was developed as a side
project to explore new programming territories and challenge myself with low-level programming concepts.

[Preview of original version on Atari](https://youtu.be/Pu7lSEa_0B8?si=BPe_A8AEJa0B0bHr&t=60)

## Technology

The game is written in C and uses CMake for build management.

### Why C?

Coming from a background in high-level programming languages, I wanted to challenge myself by learning and understanding
a low-level language. This project served as an excellent opportunity to explore memory management, pointers, and
system-level programming concepts.

## Building and Running

### Prerequisites

- C compiler (GCC or MSVC)
- CMake (version 3.28 or higher)

### Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Platform Support

⚠️ Note: The game was primarily developed and tested on Windows. While it should theoretically work on Unix-based
systems, this hasn't been extensively tested. The codebase includes basic platform-specific handling, but there might be
compatibility issues.

## Development Notes

### Project Management

As the only one developer, I opted to commit directly to main, as implementing a more complex branching strategy
wouldn't provide significant benefits for a project of this size.

### Learning Experience

Despite initial challenges with pointer manipulation and memory management, the development process was enjoyable and
educational.
The project provided valuable insights into low-level programming concepts.

### Current Limitations

- No unit tests were implemented due to the project's small scope.
- The code might benefit from refactoring and improvements, as this was my first experience with C.
- Platform compatibility might need enhancement for better Unix support.

### Future Improvements

Feel free to suggest and improve through GitHub Issues.
As this was my first C project, I'm particularly interested in feedback regarding best practices and potential optimizations.
Potential areas for enhancement include:

- Cross-platform compatibility
- Unit testing implementation
- Code organization and structure
- Memory management optimization
