# [GJK Algorithm](/FunProjects/GJKAlgorithm.cpp)

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
   
