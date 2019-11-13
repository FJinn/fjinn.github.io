# -> [Spatial Partition](/FunProjects/SpatialPartition.cpp) <-

[Game Programming Pattern - by Robert Nystrom](https://gameprogrammingpatterns.com/spatial-partition.html) 

After reading the Spatial Partition Chapter, thought it would be fun to implement in my Top-down Multiplayer Shooter (assignment) using OpenGL. This is a simple spatial partition method, like a base or fundamental knowledge to QuadTree, Binary Space Partition, Octree, etc. which may or may not be in this folder in the future.

**Note: In my Top-down 2-Players Shooter game, it is kinda unnecessary (drag down the performance/efficiency) as there aren't much objects in the game. So the trade-off isn't worth it in my game. Ultimately, it is just a platform for me to learn more about spatial partition**

The idea is simple. It segments the game world/space into 10 x 10 cells and add/put/move objects from/to one another. So when running the collision test, the machine does not need to run the test for one object against every single other objects in the game. Just those who are in the same cell or nearby cells. 

Again, due to its nature, the loop is still O(n^2). So if the nummber of game objects in the game is small, it may not be a good practice to implement spatial partition which takes extra processing power to move around game objects from one cell to another. However, when the number of game objects is large enough, it does help improve the machine efficiency as one object does not need to run the collision test against every single objects but just those that are nearby.

Compare to other spatial partition methods, such as Quadtree, which subdivide the spaces into 4 rectangles based on the object weight/number, the spatial partition I implement has a constant cell size. It saves the machine from running the subdivision code. Easier to implement and understand. To gain insight about its pros and cons against method with subdivision, please do refer to the Game Programming Pattern (reference link above).
