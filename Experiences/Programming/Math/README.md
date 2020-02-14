## [Bezier Curve](/Experiences/Programming/Math/BezierCurve.h)
Put it in a simple way, it is a (curve) line from Point A to Point B, in 0-1 time, with a control point.

A point's position in a Bezier Curve line is based on the position of a point in three lines at the time(t).

Three lines: Point A to Control Point (Line 1), Control Point to Point B (Line 2), Line 1 to Line 2 (Line 3) based on time(t) at Line 1 and Line 2.

Bezier Curve is formed based on the point at time(t) in Line 3. 

Example of how the curve is formed: 
1. When t = 0, Line 3 = Point A at Line 1 -> Control Point at Line 2, Bezier Curve point will be at the start of Line 3 (Point A) as well.
2. When t = 0.5, Line 3 = Line 1 middle point -> Line 2 middle point, Bezier Curve point will be at the middle of Line 3.
2. When t = 1, Line 3 = Control Point at Line 1 -> Point B at Line 2, Bezier Curve point will be at the end of Line 3 (Point B).

_


## [GJK Algorithm](/Experiences/Programming/Math/GJKAlgorithm.cpp)

[Casey Muratori's tutorial](https://youtu.be/Qupqu1xe7Io) and [Igor Kroitor's Github Page](https://github.com/kroitor/gjk.c) are **must-see-reference**.

GJK algorithm is an algorithm for collision detection for convex polygon.
Only 2D is implemented/tested/coded here.

The basic idea: 
1. Get Minkowski difference between two polygons.
2. If the result shape contains origin (0,0,0), there are intersection between the polyons. No intersection if origin is not within the result shape.

The 'detail' process (to know the **WHY and Real Details**, refer to the reference link above):
1. Support function
   1. Get the furthest point using Minkowski difference from two polygons with the direction vector provided and put it in a container (for simplexes).
2. Loop
   1. First, get another simplex point using Support function with opposite direction vector.   
  **Note: if the dot product of new point and the search direction vector is lesser than 0, means the new point does not pass through origin, so it is impossible for the result shape to contain origin. Thus, not collision.**
   2. Second, get third point using Support function with direction vector pointing toward origin from the line formed by the previous 2 points in simplex container. **3D will be a tetrahedron/3-simplex (0-simplex is a point, 1-simplex is a line, 2-simplex is a triangle etc.)**
   3. For 2D, if there are 3 points to form a triangle, check if the triangle contains origin.
   4. If origin is found, there is collision.
   5. If not, there isn't. Continue to Support function by providing a direction vector toward origin then Loop again.
   
## [Spatial Partition](/Experiences/Programming/Math/SpatialPartition.cpp)

[Game Programming Pattern - by Robert Nystrom](https://gameprogrammingpatterns.com/spatial-partition.html) 

After reading the Spatial Partition Chapter, thought it would be fun to implement in my Top-down Multiplayer Shooter (assignment) using OpenGL. This is a simple spatial partition method, like a base or fundamental knowledge to QuadTree, Binary Space Partition, Octree, etc. which may or may not be in this folder in the future.

**Note: In my Top-down 2-Players Shooter game, it is kinda unnecessary (drag down the performance/efficiency) as there aren't much objects in the game. So the trade-off isn't worth it in my game. Ultimately, it is just a platform for me to learn more about spatial partition**

The idea is simple. It segments the game world/space into 10 x 10 cells and add/put/move objects from/to one another. So when running the collision test, the machine does not need to run the test for one object against every single other objects in the game. Just those who are in the same cell or nearby cells. 

Again, due to its nature, the loop is still O(n^2). So if the nummber of game objects in the game is small, it may not be a good practice to implement spatial partition which takes extra processing power to move around game objects from one cell to another. However, when the number of game objects is large enough, it does help improve the machine efficiency as one object does not need to run the collision test against every single objects but just those that are nearby.

Compare to other spatial partition methods, such as Quadtree, which subdivide the spaces into 4 rectangles based on the object weight/number, the spatial partition I implement has a constant cell size. It saves the machine from running the subdivision code. Easier to implement and understand. To gain insight about its pros and cons against method with subdivision, please do refer to the Game Programming Pattern (reference link above).
