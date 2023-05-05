# Visualgo_CS162

This program will visualize some basic data structures, including animations (similar to Visualgo.net). The data structures are:
- Linked List
  - Singly Linked List
  - Doubly Linked List
  - Circular Linked List
- Stack
- Queue
- Array
  - Static Array
  - Dynamic Array

The program is written in C++ and uses SFML library for graphics. 
The features of this project are followed from [this requirements](./docs/CS162-CSC10002-Solo%20Project.pdf).

## How to run

### Pre-requisites

- C++ 17 – GNU GCC 7.3.0+
  - For Windows users, please follow [this instructions](https://www.msys2.org/#installation) to install.
  - For Debian users, run the following command:
    - `sudo apt-get update && sudo apt-get install build-essential`
  - For Mac users, run the following command:
    - `xcode-select --install`
- [CMake 3.26+](https://cmake.org/download/)
- Makefile
  - For Windows users, open the `MSYS2 MinGW 64-bit` terminal and run the following command:
    - `pacman -S make`
  - For Debian users, run the following command:
    - `sudo apt-get install make`
  - For Mac users, `make` is already installed when you run the above command.
- SFML 2.5+
  - For Windows users, please download [this version](https://www.sfml-dev.org/download/sfml/2.5.1/#:~:text=GCC%207.3.0%20MinGW%20(SEH)%20%2D%2064%2Dbit).
  - For Debian users, run the following command:
    - `sudo apt-get install libsfml-dev`
  - For Mac users, please follow [this instructions](https://www.sfml-dev.org/tutorials/2.5/start-osx.php#installing-sfml) to install.
- [Doxygen](https://www.doxygen.nl/download.html) (optional) – for generating documentation

### Build

- Clone this repository
- Run the following commands:
  - `cd Visualgo_CS162`
  - Build the project:
    - for Windows users:
      - `cmake -DSFML_DIR:PATH=<path_to_SFML>/lib/cmake/SFML -G"MinGW Makefiles" -S . -B build`
    - for Debian and Mac users:
      - `cmake -S . -B build`
  - `make -C build`
- The executable file will be in the `build` folder

### Run

- Click on the executable file in the folder `build` to run the program.
- If you want to run the program in the terminal, run the following command:
  - `cd build && ./Visualgo_CS162`

## How to use

\the user manual that will be written later\

## Documentation

You can find the documentation [here](https://diriimq.github.io/Visualgo_CS162/html/) and watch the demo [here](https://youtu.be/).

## License

This project is licensed under the `GPL-3.0 License` - see the [LICENSE](./LICENSE) file for details.