# -> [Spatial Partition](/Experiences/Programming/Math/SpatialPartition.cpp) <-

[Game Programming Pattern - by Robert Nystrom](https://gameprogrammingpatterns.com/spatial-partition.html) 

After reading the Spatial Partition Chapter, thought it would be fun to implement in my Top-down Multiplayer Shooter (assignment) using OpenGL. This is a simple spatial partition method, like a base or fundamental knowledge to QuadTree, Binary Space Partition, Octree, etc. which may or may not be in this folder in the future.

**Note: In my Top-down 2-Players Shooter game, it is kinda unnecessary (drag down the performance/efficiency) as there aren't much objects in the game. So the trade-off isn't worth it in my game. Ultimately, it is just a platform for me to learn more about spatial partition**

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Math/Image/SpatialPartition.jpg?raw=true" />

The idea is simple. It segments the game world/space into 10 x 10 cells and add/put/move objects from/to one another. 

Every cell has one pointer that points to the latest object it contains and the latest object will point to the previous object if there is one. If there isn't one, the object will become the head.

For example, as in the image above, let's say cell A contains 4 objects, cell B has 1 object, and cell C has nothing. 

In my implementation, if a cell has nothing like C, its pointer points to NULL.

For cell B, it points to an object and the object points to NULL.

Whereas in cell A, cell A's pointer points to one object, and the object points to another while keeping a record of previous pointing object if there is one. This goes on until the last one in the 'list' points to NULL.

So when running the collision test, the machine does not need to run the test for one object against every single other objects in the game. Just those who are in the same cell or nearby cells. 

Objects in cell A will only be tested using GJK alorithm against every objects in cell A. So are other cells.

Empty cells like cell C will not run the test since there isn't any objects.

## Performance

Again, due to its nature, the performance time (loop) is still O(n^2). So if the nummber of game objects in the game is small, it may not be a good practice to implement spatial partition which takes extra processing power to move around game objects from one cell to another. 

Such as the example, running the algorithm for all 5 objects will not have any significant improvement against running the test for 4 objects. In anything, it makes it worst when the objects move to other cells because the objects and cells pointers need to be switched and moved around as well.

However, when the number of game objects is large enough, it does help improve the machine efficiency as one object does not need to run the collision test against every single objects but just those that are nearby.

## Constant Size

Compare to other spatial partition methods, such as Quadtree, which subdivide the spaces into 4 rectangles based on the object weight/number, the spatial partition I implement has a constant cell size. 

It saves the machine from running the subdivision code. Easier to implement and understand. 

To gain insight about its pros and cons against method with subdivision, please do refer to the Game Programming Pattern (reference link above).
