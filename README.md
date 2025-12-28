# Game of Life (C++)

A modern C++ implementation of Conway’s Game of Life featuring configurable rules, interactive controls, and flexible command-line options.

This project simulates cellular automata evolution on a 2D grid and supports multiple variations of the classic Game of Life.

---

## Features

* Classic 2-state Conway’s Game of Life
* Optional 3-state mode with decaying cells
* Wrap-around (toroidal) grid support
* Interactive pause mode with live cell editing
* Customizable display characters
* Output redirection to file
* Command-line interface using `getopt`
* Built with modern C++ (C++20)

---

## Build Instructions

Make sure you have `g++` installed.

```bash
make
```

This produces the executable:

```bash
./game_of_life
```

To clean build artifacts:

```bash
make clean
```

---

## Usage

```bash
./game_of_life -f <input_file> [options]
```

### Command-line Options

| Flag        | Description                         |
| ----------- | ----------------------------------- |
| `-f <file>` | Input file (required)               |
| `-g <n>`    | Number of generations (default: 10) |
| `-p <n>`    | Print interval (default: 1)         |
| `-s`        | Enable 3-state mode                 |
| `-w`        | Enable wrap-around grid             |
| `-x <n>`    | Pause interval                      |
| `-a <char>` | Alive cell character                |
| `-d <char>` | Dead cell character                 |
| `-e <char>` | Decay cell character                |
| `-o <file>` | Output results to file              |

> Note: `-s` and `-w` are mutually exclusive.

---

## Input File Format

```
<height> <width>
X O X X X
X X O X X
O O O X X
X X X X X
X X X X X
```

* `O` = alive cell
* `X` = dead cell

---

## Example

```bash
./game_of_life -f examples/glider -g 20 -p 4 -w
```

---

## Why This Project?

This project demonstrates:

* Object-oriented design in C++
* Command-line application development
* File parsing and validation
* Simulation and state-transition logic
* Interactive terminal programs
* Makefile-based builds

