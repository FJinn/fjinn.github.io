# AI Programming

Game of Life, A* and Dijkstra algorithm for path-finding, and boids simulation.

Since the assignments were given out in a progressive order, the project file was reused. So some repetitive files are removed and some might might be overlooked and stay in the folder.

## [Game Of Life](Assignments/AIProgramming/GameOfLifeAndPathFinding/GameOfLife.h)

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Assignments/AIProgramming/Images/GameOfLife.gif" width="800" height="450" />

**Play/Pause** : Play or stop the simulation.
**Clear** : Reset map (set cells to live or die)
**Map Size** : Switch map size
**Simulation Time** : Switch simulation speed

-> **Rules of Conway's Game of Life** <-
Every cell interacts with its 8 neighbours (horizontal, vertical, and diagonal). At each step in time, the following transitions occur:

1. Any live cell with 1 or no live neighbours dies (loneliness).
2. Any live cell with 2 or 3 live neighbours survives to the next iteration (stasis).
3. Any live cell with 4 or more live neighbours dies (overcrowding).
4. Any dead cell with exactly three live neighbours becomes a live cell (reproduction).


_

## [Path Finding](Assignments/AIProgramming/GameOfLifeAndPathFinding/PathFindingAlgorithm.h)

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Assignments/AIProgramming/Images/PathFinding.gif" width="800" height="450" />

**Dijkstra's Algorithm (1 list)**

1. Prepare 1 empty Lists: Open List.
2. Each node's distance value (shortest distance from the source node) is set to infinity, with state setting to unsettled.
3. Add source node to open list with its distance set to 0.
4. Select the node from open list with lowest distance value, set it as current node and set the node state to settled, remove the node from open list.
5. Evaluate all the accessible neighbours (nodes that are settled are not accessible) of current node, if new distance is smaller, update its distance value and parent node, if the neighbours are not in open list, add the neighbours to open list.
6. Stop if destination node is set to settled state or open list is empty.
7. Go back to step 4.
8. Path: Working backwards from the target node, go from each node to its parent node until you reach the starting node.

**A-star Algorithm**

Cost: F = G + (W) * H

G: The movement cost to move from the starting point A to a given node on the grid, following the path generated to get there.
H: The estimated movement cost to move from that given node on the grid to the final destination, point B. This if often referred to as the heuristic, the reason why it is called that is because it is a guess.
W: Heuristic cost multiplier to adjust quality and performance of the path. If W is 0, you will get Dijkstra path finding.

1. Prepare 1 empty list : open list.
2. Initialize each node with state of unsettled.
3. Add the source node to the open list. (You can initialize its F cost with any value)
4. Select the node that with the lowest F cost from the open list, set it as current node and set the node state to settled, remove the node from open list.
5. For each of the neighbours to this current node:
   1. If it is not walkable or if it is settled, ignore it. Otherwise, do the following.
   2. If it isn't in the open list, add it to the open list. Make the current node the parent of this node. Calculate the F, G, and H costs of the node.
   3. If it is in the open list already, check to see if this path to that node is better, using G cost as the measure. A lower G cost means that it is a better path. If so, change the parent of the node to current node, and update the G and F scores of the node.
6. Stop when you add the target node to be settled state (path has been found) or the open list is empty. (there is no path)  
7. Go back and repeat Step 3.
8. Path: Working backwards from the target node, go from each node to its parent node until you reach the starting node.
 

_

## [Boid Simulation](Assignments/AIProgramming/Boids/Boids.h)

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Assignments/AIProgramming/Images/BoidSimulation.gif" width="800" height="450" />

**Greed Triangle** = Attractor
**Pink Circle** = Obstacle avoidance
**Orance Circle** = Repeller
**Boids (Blue Triangle) Behaviours** = Separation, Alignment, and Coherence.
