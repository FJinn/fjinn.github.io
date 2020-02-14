# [Path Finding](/Experiences/Assignments/AIProgramming/GameOfLifeAndPathFinding/PathFindingAlgorithm.h)

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Experiences/Assignments/AIProgramming/Images/PathFinding.gif?raw=true" width="800" height="450" />

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

**Note: in this simulation, I didn't consider Euclidean distance, underestimated Heuristic, overestimated Heuristic, or cluster Heuristic, just a simple distance calculation based on difference in cells' row and column. Mostly because I hadn't learn about them when I was implementing this pathfinding simulation.**

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
 
