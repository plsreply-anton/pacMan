# PacMan Game Project

Setting up a new git repo for personal project. Initilized in order to learn more about CMake and C++ pointers. Come a long way. Working on adding levels. Game engine and physics working well! Tested on Mac but should run smoothly on all UNIX-like computers. Windows can be a hazzzleeeeee :(

*Note: This project is using unreleased SFML 3.0 which is installed locally from source. The offical rep can be found *[here](https://github.com/SFML/SFML)*

![Alt](/util/sprites/menuImage.png)

## TODO
- Implement levels
- Implement more path searching algorithms with different heuristics
- Make window rezisable on desktop use (bottom part sometimes invisible)
- Perhaps use constexpr etc and update project to C++20/c++23
- Update SFML (Probably nothing new)
- Implement difference color themes
- Migrate to smart pointer(?)
- Fix the pause-functionality

## Compiling
*Make sure SFML 3.0 is installed locally from source. See their github and official website for instrutions. Probably require CMake which in turn require adding ENV-variable to run from terminal on Mac*

1. Clone the repo into desired directory
2. Navigate to the projects build folder and run `cmake -S .. -B . ` to generate a makefile
3. Run `make` inside the build folder to generate an executable
4. Execute the program by running `./pacMan`
