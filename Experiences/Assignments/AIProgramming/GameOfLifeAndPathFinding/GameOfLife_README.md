# [Game Of Life](/Experiences/Assignments/AIProgramming/GameOfLifeAndPathFinding/GameOfLife.h)

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Assignments/AIProgramming/Images/GameOfLife.gif?raw=true" width="800" height="450" />

**Play/Pause** : Play or stop the simulation.

**Clear** : Reset map (set cells to live or die)

**Map Size** : Switch map size

**Simulation Time** : Switch simulation speed

-> [**Rules of Conway's Game of Life**](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) <-

Every cell interacts with its 8 neighbours (horizontal, vertical, and diagonal). At each step in time, the following transitions occur:

1. Any live cell with 1 or no live neighbours dies (loneliness).
2. Any live cell with 2 or 3 live neighbours survives to the next iteration (stasis).
3. Any live cell with 4 or more live neighbours dies (overcrowding).
4. Any dead cell with exactly three live neighbours becomes a live cell (reproduction).

## Implementation

To make these rules 'alive', I create a board with boolean that indicating if it is 'alive' or 'dead'.

The rest is pretty simple, in the loop, the cells will check their neighbours state, and then update their own state, with the Conway's Game of Life's rules as the indicator. 
