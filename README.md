# Terminal Treasure Hunter

<p align="center">
  <img src="demo.gif" alt="3D replay of a game: the player's path winding past red bombs to the gold treasure" width="600">
</p>

A 3D treasure hunt played in the terminal, written in C++17. Navigate a 3D grid using only a "hot/cold" thermometer, avoid hidden bombs, and find the treasure in as few moves as possible. When the game ends, a Python/matplotlib script replays your path as an animated 3D plot showing every bomb you avoided (or hit).

## Features

- **3D grid movement** across a 59×59×59 world (coordinates -29 to 29 on each axis)
- **Proximity thermometer:** 11 levels of feedback, from "absolutely freezing" to "SCORCHING", based on your straight-line distance to the treasure
- **Procedurally generated hazards:** 10–40 bombs per game, each with a 3×3×3 kill zone. Bombs are always placed away from the start and the treasure, so every game is winnable.
- **Efficiency score:** compares your move count to the shortest possible path
- **3D replay:** an animated matplotlib visualization of your path, the bombs, and the treasure

## Getting started

Requirements: a C++17 compiler (clang++ or g++), `make`, and Python 3.

```bash
git clone https://github.com/coopermay/px.git
cd px
pip3 install -r requirements.txt
make run
```

Run the game from the repository folder so it can find `visual.py` for the replay.

## Controls

| Key | Action |
| --- | --- |
| `W` / `S` | Move +x / -x |
| `D` / `A` | Move +z / -z |
| `-` / `C` | Move up (+y) / down (-y) |
| `X` | Quit |

Press Enter after each move, or type several moves at once (for example `wwwdd`) and press Enter to run them in order.

## How it works

- **Game (`px.cpp`):** The treasure is placed at random at least 10 moves from the start. Bombs are then placed so that none of them is within 3 cells of the start or the treasure. After each move, the game checks whether you're in any bomb's kill zone (Chebyshev distance ≤ 1) and reports your distance to the treasure as a thermometer reading. Efficiency is `shortest path / your moves`, where the shortest path is the Manhattan distance from the start to the treasure.
- **Replay (`visual.py`):** At the end of every game, the C++ program writes the bomb positions, the treasure position, and your full path to text files, then launches the Python script. The script animates your path in 3D, drawing the game's y axis vertically.

## Project structure

```
px.cpp            game logic, input handling, world generation
visual.py         3D replay of the last game (matplotlib)
Makefile          build and run targets
requirements.txt  Python dependencies
```
